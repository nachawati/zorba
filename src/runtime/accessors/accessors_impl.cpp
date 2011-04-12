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
 
#include "zorbaerrors/error_manager.h"
#include "zorbaerrors/assert.h"

#include "system/globalenv.h"

#include "context/namespace_context.h"
#include "context/static_context.h"

#include "runtime/accessors/accessors.h"

#include "runtime/visitors/planiter_visitor.h"

#include "store/api/item.h"
#include "store/api/iterator.h"
#include "store/api/item_factory.h"

namespace zorba {

/*******************************************************************************
  2.1 fn:node-name
********************************************************************************/
bool NodeNameIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t inNode;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(inNode, theChildren[0].getp(), planState))
  {
    if( inNode->getNodeKind() == store::StoreConsts::elementNode ||
        inNode->getNodeKind() == store::StoreConsts::attributeNode)
    {
      result = inNode->getNodeName();
      STACK_PUSH(true, state);
    }
    else if(inNode->getNodeKind() == store::StoreConsts::piNode)
    {
      GENV_ITEMFACTORY->createQName(result, zstring(), zstring(), inNode->getTarget());
      STACK_PUSH(true, state);
    }
  }
  STACK_END (state);
}


/*******************************************************************************
  2.2 fn:nilled
********************************************************************************/
bool NilledIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t inNode;

  PlanIteratorState *state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(inNode, theChildren[0].getp(), planState))
  {
    if (inNode->isNode()) {
      result = inNode->getNilled();
      STACK_PUSH(result != NULL, state);
    } else
      ZORBA_ERROR_LOC_DESC(XPTY0004, loc,
                            "The argument of the fn:nilled function is not a node");
  }

  STACK_END (state);
}

/*******************************************************************************
  2.3 fn:string
********************************************************************************/
bool FnStringIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t inVal;
  zstring strval;

  FnStringIteratorState* state;
  DEFAULT_STACK_INIT(FnStringIteratorState, state, planState);

  while(consumeNext(inVal, theChildren[0], planState))
  {
    if (inVal->isFunction()) 
    {
			throw XQUERY_EXCEPTION( FOTY0014, ERROR_LOC( loc ) );
    }
    state->hasOutput = true;
    inVal->getStringValue2(strval);
    GENV_ITEMFACTORY->createString(result, strval);
    STACK_PUSH(true, state);
  }

  if (!state->hasOutput && theEmptyStringOnNULL)
  {
    state->hasOutput = true;
    GENV_ITEMFACTORY->createString(result, strval);
    STACK_PUSH(true, state);
  }

  STACK_END (state);
}

/*******************************************************************************
  2.3 fn:data
********************************************************************************/
bool FnDataIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  PlanIter_t iter;
  store::Item_t itemNode;

  FnDataIteratorState* state;
  DEFAULT_STACK_INIT(FnDataIteratorState, state, planState);
  
  while (true) 
  {
    if (!consumeNext(result, theChildren[0], planState))
      break;

    if (result->isFunction())
    {
			throw XQUERY_EXCEPTION( FOTY0013, ERROR_LOC( loc ) );
    }
    if (result->isAtomic())
    {
      STACK_PUSH(true, state);
    }
    else
    {
      assert(result->isNode());

      itemNode.transfer(result);
      try {
        itemNode->getTypedValue(result, state->theTypedValueIter);
      } catch (XQueryException& e) {
				set_source( e, loc );
				throw;
      }

      if (state->theTypedValueIter == NULL)
      {
        if (result == NULL)
          continue;

        STACK_PUSH(true, state );
      }
      else
      {
        state->theTypedValueIter->open();
      
        while (true) 
        {
          if (!state->theTypedValueIter->next(result))
            break;

          assert(!result->isNode());
          STACK_PUSH(true, state );
        }
      }
    }
  }

  state->theTypedValueIter = 0; // TODO remove???
  STACK_END (state);
}

/*******************************************************************************
2.5 fn:base-uri
********************************************************************************/
bool BaseUriIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t inNode;
  zstring baseuri;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(inNode, theChildren[0].getp(), planState))
  {
    inNode->getBaseURI(baseuri);
    if (!baseuri.empty()) 
    {
      GENV_ITEMFACTORY->createAnyURI(result, baseuri);
      STACK_PUSH(true, state);
    }
  }

  STACK_END (state);
}


/*******************************************************************************
  2.6 fn:document-uri
********************************************************************************/
bool DocumentUriIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  zstring docuri;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (consumeNext(result, theChildren[0].getp(), planState))
  {
    result->getDocumentURI(docuri);
    if (!docuri.empty())
    {
      STACK_PUSH(GENV_ITEMFACTORY->createAnyURI(result, docuri), state);
    }
  }

  STACK_END (state);
}


/*******************************************************************************
  14.9 fn:root
********************************************************************************/
bool RootIterator::nextImpl(store::Item_t& result, PlanState& planState) const
{
  store::Item_t contextNode;
  store::Item_t parentNode;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, planState);

  if (!consumeNext(result, theChildren[0].getp(), planState))
    return false;

  parentNode = result->getParent();

  while (parentNode != NULL)
  {
    result = parentNode;
    parentNode = parentNode->getParent();
  }

  STACK_PUSH(true, state);
  STACK_END (state);
}


} // namespace zorba
/* vim:set ts=2 sw=2: */
