#include <iostream>
#include "errors/error_factory.h"
#include "runtime/debug/debug_iterators.h"
#include "store/api/item.h"

using namespace std;

namespace xqp {

void 
FnTraceIteratorState::init(PlanState& planState)
{
  PlanIteratorState::init(planState);
  theTagItem = NULL;
}

void 
FnTraceIteratorState::reset(PlanState& planState)
{
  PlanIteratorState::reset(planState);
  theTagItem = NULL;
}

Item_t 
FnTraceIterator::nextImpl(PlanState& planState)
{
  Item_t lSequenceItem;

  FnTraceIteratorState *state;
  DEFAULT_STACK_INIT(FnTraceIteratorState, state, planState);

  if ( (state->theTagItem = consumeNext(theChildren[1], planState)) == NULL ) {
    ZORBA_ERROR_ALERT(ZorbaError::FORG0006, &loc, DONT_CONTINUE_EXECUTION,
        "An empty sequence is not allowed as as second argument to fn:trace");
  }

  while ((lSequenceItem = consumeNext(theChildren[0], planState)) != NULL) {
    // FIXME: check the standard how to return this
    cerr << state->theTagItem->getStringValue() << lSequenceItem->getStringValue() << endl;
    STACK_PUSH(lSequenceItem, state);
  }

  STACK_END();
}

} /* namespace xqp */

/* vim:set ts=2 sw=2: */
