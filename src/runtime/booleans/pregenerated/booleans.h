/*
 * Copyright 2006-2012 2006-2016 zorba.io.
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
 
// ******************************************
// *                                        *
// * THIS IS A GENERATED FILE. DO NOT EDIT! *
// * SEE .xml FILE WITH SAME NAME           *
// *                                        *
// ******************************************

#ifndef ZORBA_RUNTIME_BOOLEANS_BOOLEANS_H
#define ZORBA_RUNTIME_BOOLEANS_BOOLEANS_H


#include "common/shared_types.h"



#include "runtime/base/narybase.h"


namespace zorba {

/**
 * op:is-same-node
 * Author: Zorba Team
 */
class IsSameNodeIterator : public NaryBaseIterator<IsSameNodeIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(IsSameNodeIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(IsSameNodeIterator,
    NaryBaseIterator<IsSameNodeIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  IsSameNodeIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<IsSameNodeIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~IsSameNodeIterator();

  zstring getNameAsString() const;

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};


/**
 * op:node-before
 * Author: Zorba Team
 */
class NodeBeforeIterator : public NaryBaseIterator<NodeBeforeIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(NodeBeforeIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(NodeBeforeIterator,
    NaryBaseIterator<NodeBeforeIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  NodeBeforeIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<NodeBeforeIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~NodeBeforeIterator();

  zstring getNameAsString() const;

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};


/**
 * op:node-after
 * Author: Zorba Team
 */
class NodeAfterIterator : public NaryBaseIterator<NodeAfterIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(NodeAfterIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(NodeAfterIterator,
    NaryBaseIterator<NodeAfterIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  NodeAfterIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<NodeAfterIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~NodeAfterIterator();

  zstring getNameAsString() const;

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};


}
#endif
/*
 * Local variables:
 * mode: c++
 * End:
 */ 
