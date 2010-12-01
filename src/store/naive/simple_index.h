/*
 * Copyright 2006-2008 The FLWOR Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef ZORBA_SIMPLE_STORE_INDEX
#define ZORBA_SIMPLE_STORE_INDEX

#include "store/api/shared_types.h"
#include "store/api/index.h"
#include "store/api/iterator.h"

#include "zorbautils/hashmap.h"

namespace zorba 
{ 

namespace simplestore 
{

class IndexPointConditionImpl;
class IndexBoxConditionImpl;


/******************************************************************************

********************************************************************************/
class IndexCompareFunction
{
  friend class HashIndex;
  friend class STLMapIndex;

private:
  ulong                              theNumColumns;
  long                               theTimezone;
  const std::vector<XQPCollator*>&   theCollators;

public:
  IndexCompareFunction(
       ulong numCols,
       long timezone,
       const std::vector<XQPCollator*>& collators)
    :
    theNumColumns(numCols),
    theTimezone(timezone),
    theCollators(collators)
  {
  }

  uint32_t hash(const store::IndexKey* key) const;

  bool equal(const store::IndexKey* key1, const store::IndexKey* key2) const;

  long compare(const store::IndexKey* key1, const store::IndexKey* key2) const;

  bool operator()(const store::IndexKey* key1, const store::IndexKey* key2) const
  {
    return compare(key1, key2) < 0;
  }
};


/******************************************************************************

********************************************************************************/
class IndexImpl : public store::Index
{
protected:  
  store::Item_t                   theQname;
  store::IndexSpecification       theSpec;
  std::vector<XQPCollator*>       theCollators;

  std::vector<store::Item_t>      theSources;

public:
  IndexImpl(const store::Item_t& qname, const store::IndexSpecification& spec);

  IndexImpl();

public:
  virtual ~IndexImpl();

  store::Item* getName() const { return theQname.getp(); }

  const store::IndexSpecification& getSpecification() const { return theSpec; }

  ulong getNumColumns() const { return theSpec.getNumColumns(); }

  long getTimezone() const { return theSpec.theTimezone; }

  const std::vector<XQPCollator*>& getCollators() const { return theCollators; }

  const XQPCollator* getCollator(ulong i) const { return theCollators[i]; }
 
  bool isUnique() const { return theSpec.theIsUnique; }

  bool isSorted() const { return theSpec.theIsSorted; }

  bool isTemporary() const { return theSpec.theIsTemp; }

  bool isThreadSafe() const { return theSpec.theIsThreadSafe; }

  bool isGeneral() const { return theSpec.theIsGeneral; }

  store::IndexCondition_t createCondition(store::IndexCondition::Kind k);

  virtual bool insert(
        store::IndexKey*& key,
        store::Item_t& item,
        bool multikey = false) = 0;

  virtual bool remove(
        const store::IndexKey* key,
        store::Item_t& item) = 0;
};


/*******************************************************************************

********************************************************************************/
class IndexPointCondition : public store::IndexCondition
{
  friend class ProbeTreeValueIndexIterator;
  friend class ProbeHashValueIndexIterator;
  friend class ProbeHashGeneralIndexIterator;

protected:
  rchandle<IndexImpl>   theIndex;
  store::IndexKey       theKey;
  ulong                 theNumColumns;

public:
  IndexPointCondition(IndexImpl* idx) 
    :
    theIndex(idx),
    theNumColumns(idx->getNumColumns())
  {
  }

  const store::IndexKey&  getKey() const { return theKey; }

  void clear();

  void pushItem(store::Item_t& item);

  void pushRange(
        store::Item_t& lower,
        store::Item_t& upper,
        bool haveLower,
        bool haveUpper,
        bool lowerIncl,
        bool upperIncl);

  bool test(const store::IndexKey& key) const;

  std::string toString() const;
};


std::ostream& operator<<(std::ostream& os, const IndexPointCondition& cond);


/*******************************************************************************

********************************************************************************/
class IndexPointValueCondition : public IndexPointCondition
{
  friend class ProbeTreeValueIndexIterator;
  friend class ProbeHashValueIndexIterator;
  friend class ProbeHashGeneralIndexIterator;

public:
  IndexPointValueCondition(IndexImpl* idx) : IndexPointCondition(idx) { }

  store::IndexCondition::Kind getKind() const { return POINT_VALUE; }

  std::string getKindString() const { return "POINT_VALUE"; }
};


/*******************************************************************************

********************************************************************************/
class IndexPointGeneralCondition : public IndexPointCondition
{
  friend class ProbeTreeValueIndexIterator;
  friend class ProbeHashValueIndexIterator;
  friend class ProbeHashGeneralIndexIterator;

public:
  IndexPointGeneralCondition(IndexImpl* idx) : IndexPointCondition(idx) { }

  store::IndexCondition::Kind getKind() const { return POINT_GENERAL; }

  std::string getKindString() const { return "POINT_GENERAL"; }
};


/*******************************************************************************

********************************************************************************/
class IndexBoxCondition : public store::IndexCondition
{
  friend class STLMapIndex;
  friend class ProbeTreeValueIndexIterator;

  friend std::ostream& operator<<(std::ostream& os, const IndexBoxCondition& cond);

public:
  static store::Item_t  theNegInf;
  static store::Item_t  thePosInf;

protected:
  struct RangeFlags
  {
    bool  theHaveLowerBound;
    bool  theHaveUpperBound;
    bool  theLowerBoundIncl;
    bool  theUpperBoundIncl;
  };

  rchandle<IndexImpl>      theIndex;
  store::IndexKey          theLowerBounds;
  store::IndexKey          theUpperBounds;
  std::vector<RangeFlags>  theRangeFlags;

public:
  IndexBoxCondition(IndexImpl* idx) : theIndex(idx) { }

  void clear();

  ulong numRanges() const { return theLowerBounds.size(); }

  bool test(const store::IndexKey& key) const;

  void pushItem(store::Item_t& item);

  void pushRange(
        store::Item_t& lower,
        store::Item_t& upper,
        bool haveLower,
        bool haveUpper,
        bool lowerIncl,
        bool upperIncl);

  std::string toString() const;
};


std::ostream& operator<<(std::ostream& os, const IndexBoxCondition& cond);


/*******************************************************************************

********************************************************************************/
class IndexBoxValueCondition : public IndexBoxCondition
{
  friend class STLMapIndex;
  friend class ProbeTreeValueIndexIterator;

public:
  IndexBoxValueCondition(IndexImpl* idx) : IndexBoxCondition(idx) { }

  store::IndexCondition::Kind getKind() const { return BOX_VALUE; }

  std::string getKindString() const { return "BOX_VALUE"; }
};
 



}
}

#endif

/*
 * Local variables:
 * mode: c++
 * End:
 */
