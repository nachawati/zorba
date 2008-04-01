/**
 * Copyright 2007 FLWOR Foundation
 *
 * Author: David Graf (david.graf@28msec.com)
 */

#ifndef ZORBA_NOARYBASE_H
#define ZORBA_NOARYBASE_H

#include "common/shared_types.h"
#include "runtime/base/plan_iterator.h"

namespace zorba
{
/**
 * Superclass for all iterators which have no child iterators
 * and no additional state variables.
 */
template <class IterType, class StateType>
class NoaryBaseIterator : public Batcher<IterType>
{
public:
  NoaryBaseIterator ( const QueryLoc& loc );

  virtual ~NoaryBaseIterator();

  void openImpl (PlanState&, uint32_t& offset);
  void resetImpl ( PlanState& planState ) const;
  void closeImpl ( PlanState& planState );

  virtual uint32_t getStateSize() const { return StateTraitsImpl<StateType>::getStateSize(); }
  virtual uint32_t getStateSizeOfSubtree() const { return getStateSize(); }
};


template <class IterType, class StateType>
NoaryBaseIterator<IterType, StateType>::NoaryBaseIterator ( const QueryLoc& loc )
  :
  Batcher<IterType> ( loc )
{
}


template <class IterType, class StateType>
NoaryBaseIterator<IterType, StateType>::~NoaryBaseIterator()
{
}


template <class IterType, class StateType>
void
NoaryBaseIterator<IterType, StateType>::openImpl ( PlanState& planState, uint32_t& offset )
{
  StateTraitsImpl<StateType>::createState(planState, this->stateOffset, offset);
  StateTraitsImpl<StateType>::initState(planState, this->stateOffset);
}


template <class IterType, class StateType>
void
NoaryBaseIterator<IterType, StateType>::resetImpl ( PlanState& planState ) const
{
  StateTraitsImpl<StateType>::reset(planState, this->stateOffset);
}


template <class IterType, class StateType>
void
NoaryBaseIterator<IterType, StateType>::closeImpl(PlanState& planState)
{
  StateTraitsImpl<StateType>::destroyState(planState, this->stateOffset);
}



}; /* namespace zorba*/

#endif /* ZORBA_NOARYBASE_H */

