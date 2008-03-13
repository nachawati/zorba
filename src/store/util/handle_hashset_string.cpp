
#include "util/Assert.h"
#include "store/util/handle_hashset_string.h"

namespace zorba { namespace store {

const ulong StringPool::DEFAULT_POOL_SIZE = 1024;
const float StringPool::DEFAULT_LOAD_FACTOR = 0.6f;


/*******************************************************************************

********************************************************************************/
StringPool::~StringPool() 
{
	ulong count = 0;
  ulong n = theHashTab.size();
  for (ulong i = 0; i < n; i++)
  {
    if (theHashTab[i].theItem != NULL &&
        theHashTab[i].theItem->getRefCount() != 1)
    {
      std::cout << "i = " << i << " String " << theHashTab[i].theItem->c_str()
                << " is still in the pool" << std::endl;
      //delete theHashTab[i].theString.getp();
      count++;
    }
  }

  if (count > 0)
    assert(0);
}


/*******************************************************************************
  Check if the given string is already in the pool and if not, make a copy of it
  and place the copy in the pool. Return true if the string was already in the
  pool, and false otherwise. Also return an rchandle to the string copy.
********************************************************************************/
bool StringPool::insertc(const char* str, xqpStringStore_t& outStr)
{
  bool found = false;

  ulong len = strlen(str);
  ulong hval = xqpStringStore::hash(str) % theHashTabSize;

  {
    SYNC_CODE(AutoMutex lock(theMutex);)

    HashEntry* entry = &theHashTab[hval];

    if (entry->theItem != NULL)
    {
      while (entry != NULL)
      {
        if (entry->theItem->byteEqual(str, len))
        {
          found = true;
          break;
        }
        entry = entry->theNext;
      }
    }

    if (found)
    {
      outStr = entry->theItem;
      return false;
    }
  }

  std::auto_ptr<xqpStringStore>tmp(new xqpStringStore(str));
  insert(tmp.get(), outStr);
  tmp.release();
  return true;
}


/*******************************************************************************
  Look for strings that are not used by anybody outside the pool. Delete each
  such string and place its entry in the free list.
********************************************************************************/
void StringPool::garbageCollect()
{
  HashEntry* entry;

  HashEntry* freeList = NULL;

  ulong size = theHashTabSize;

  for (ulong i = 0; i < size; i++)
  {
    entry = &theHashTab[i];

    // If the current hash bucket is empty, move to the next one
    if (entry->theItem == NULL)
    {
      ZORBA_ASSERT(entry->theNext == NULL);
      continue;
    }

    // Handle the 1st hash entry of the current hash bucket
    while(entry->theItem->getRefCount() == 1)
    {
      if (entry->theNext == NULL)
      {
        entry->theItem = NULL;
        theNumEntries--;
        break;
      }
      else
      {
        HashEntry* nextEntry = entry->theNext;
        *entry = *nextEntry;
        nextEntry->theItem = NULL;
        nextEntry->theNext = freeList;
        freeList = nextEntry;
        theNumEntries--;
      }
    }

    // Handle the overflow entries of the current hash bucket.
    HashEntry* prevEntry = entry;
    entry = entry->theNext;

    while (entry != NULL)
    {
      if (entry->theItem->getRefCount() == 1)
      {
        prevEntry->theNext = entry->theNext;
        entry->theItem = NULL;
        entry->theNext = freeList;
        freeList = entry;
        theNumEntries--;
      }

      prevEntry = entry;
      entry = entry->theNext;
    }
  }

  if (freeList != NULL)
  {
    entry = freeList;
    while (entry->theNext != NULL)
      entry = entry->theNext;

    entry->theNext = theHashTab[theHashTabSize].theNext;
    theHashTab[theHashTabSize].theNext = freeList;
  }
}

} // namespace store
} // namespace zorba
