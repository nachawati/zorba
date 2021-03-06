/*
 * Copyright 2006-2016 zorba.io
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


#include "stdafx.h"
#include "zorbatypes/rchandle.h"
#include "zorbatypes/zstring.h"
#include "runtime/visitors/planiter_visitor.h"
#include "runtime/sctx/sctx.h"
#include "system/globalenv.h"


#include "store/api/iterator.h"

namespace zorba {

// <SctxBaseUriIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxBaseUriIterator)

void SctxBaseUriIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxBaseUriIterator, PlanIteratorState>*)this);
}


void SctxBaseUriIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxBaseUriIterator::~SctxBaseUriIterator() {}


zstring SctxBaseUriIterator::getNameAsString() const {
  return "fn-zorba-sctx:base-uri";
}
// </SctxBaseUriIterator>


// <SctxBoundarySpacePolicyIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxBoundarySpacePolicyIterator)

void SctxBoundarySpacePolicyIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxBoundarySpacePolicyIterator, PlanIteratorState>*)this);
}


void SctxBoundarySpacePolicyIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxBoundarySpacePolicyIterator::~SctxBoundarySpacePolicyIterator() {}


zstring SctxBoundarySpacePolicyIterator::getNameAsString() const {
  return "fn-zorba-sctx:boundary-space-policy";
}
// </SctxBoundarySpacePolicyIterator>


// <SctxConstructionModeIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxConstructionModeIterator)

void SctxConstructionModeIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxConstructionModeIterator, PlanIteratorState>*)this);
}


void SctxConstructionModeIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxConstructionModeIterator::~SctxConstructionModeIterator() {}


zstring SctxConstructionModeIterator::getNameAsString() const {
  return "fn-zorba-sctx:construction-mode";
}
// </SctxConstructionModeIterator>


// <SctxCopyNamespacesModeIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxCopyNamespacesModeIterator)

void SctxCopyNamespacesModeIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxCopyNamespacesModeIterator, PlanIteratorState>*)this);
}


void SctxCopyNamespacesModeIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxCopyNamespacesModeIterator::~SctxCopyNamespacesModeIterator() {}


zstring SctxCopyNamespacesModeIterator::getNameAsString() const {
  return "fn-zorba-sctx:copy-namespaces-mode";
}
// </SctxCopyNamespacesModeIterator>


// <SctxDefaultCollationIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxDefaultCollationIterator)

void SctxDefaultCollationIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxDefaultCollationIterator, PlanIteratorState>*)this);
}


void SctxDefaultCollationIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxDefaultCollationIterator::~SctxDefaultCollationIterator() {}


zstring SctxDefaultCollationIterator::getNameAsString() const {
  return "fn-zorba-sctx:default-collation";
}
// </SctxDefaultCollationIterator>


// <SctxDefaultCollectionTypeIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxDefaultCollectionTypeIterator)

void SctxDefaultCollectionTypeIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxDefaultCollectionTypeIterator, PlanIteratorState>*)this);
}


void SctxDefaultCollectionTypeIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxDefaultCollectionTypeIterator::~SctxDefaultCollectionTypeIterator() {}


zstring SctxDefaultCollectionTypeIterator::getNameAsString() const {
  return "fn-zorba-sctx:default-collection-type";
}
// </SctxDefaultCollectionTypeIterator>


// <SctxDefaultFunctionNamespaceIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxDefaultFunctionNamespaceIterator)

void SctxDefaultFunctionNamespaceIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxDefaultFunctionNamespaceIterator, PlanIteratorState>*)this);
}


void SctxDefaultFunctionNamespaceIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxDefaultFunctionNamespaceIterator::~SctxDefaultFunctionNamespaceIterator() {}


zstring SctxDefaultFunctionNamespaceIterator::getNameAsString() const {
  return "fn-zorba-sctx:default-function-namespace";
}
// </SctxDefaultFunctionNamespaceIterator>


// <SctxDefaultOrderIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxDefaultOrderIterator)

void SctxDefaultOrderIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxDefaultOrderIterator, PlanIteratorState>*)this);
}


void SctxDefaultOrderIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxDefaultOrderIterator::~SctxDefaultOrderIterator() {}


zstring SctxDefaultOrderIterator::getNameAsString() const {
  return "fn-zorba-sctx:default-order";
}
// </SctxDefaultOrderIterator>


// <SctxFunctionAnnotationsIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxFunctionAnnotationsIterator)

void SctxFunctionAnnotationsIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxFunctionAnnotationsIterator, SctxFunctionAnnotationsIteratorState>*)this);
}


void SctxFunctionAnnotationsIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxFunctionAnnotationsIterator::~SctxFunctionAnnotationsIterator() {}

SctxFunctionAnnotationsIteratorState::SctxFunctionAnnotationsIteratorState() {}

SctxFunctionAnnotationsIteratorState::~SctxFunctionAnnotationsIteratorState() {}


void SctxFunctionAnnotationsIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxFunctionAnnotationsIterator::getNameAsString() const {
  return "fn-zorba-sctx:function-annotations";
}
// </SctxFunctionAnnotationsIterator>


// <SctxFunctionArgumentsCountIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxFunctionArgumentsCountIterator)

void SctxFunctionArgumentsCountIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxFunctionArgumentsCountIterator, SctxFunctionArgumentsCountIteratorState>*)this);
}


void SctxFunctionArgumentsCountIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxFunctionArgumentsCountIterator::~SctxFunctionArgumentsCountIterator() {}

SctxFunctionArgumentsCountIteratorState::SctxFunctionArgumentsCountIteratorState() {}

SctxFunctionArgumentsCountIteratorState::~SctxFunctionArgumentsCountIteratorState() {}


void SctxFunctionArgumentsCountIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxFunctionArgumentsCountIterator::getNameAsString() const {
  return "fn-zorba-sctx:function-arguments-count";
}
// </SctxFunctionArgumentsCountIterator>


// <SctxFunctionNamesIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxFunctionNamesIterator)

void SctxFunctionNamesIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxFunctionNamesIterator, SctxFunctionNamesIteratorState>*)this);
}


void SctxFunctionNamesIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxFunctionNamesIterator::~SctxFunctionNamesIterator() {}

SctxFunctionNamesIteratorState::SctxFunctionNamesIteratorState() {}

SctxFunctionNamesIteratorState::~SctxFunctionNamesIteratorState() {}


void SctxFunctionNamesIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxFunctionNamesIterator::getNameAsString() const {
  return "fn-zorba-sctx:function-names";
}
// </SctxFunctionNamesIterator>


// <SctxFunctionsIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxFunctionsIterator)

void SctxFunctionsIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxFunctionsIterator, SctxFunctionsIteratorState>*)this);
}


void SctxFunctionsIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxFunctionsIterator::~SctxFunctionsIterator() {}

SctxFunctionsIteratorState::SctxFunctionsIteratorState() {}

SctxFunctionsIteratorState::~SctxFunctionsIteratorState() {}


void SctxFunctionsIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxFunctionsIterator::getNameAsString() const {
  return "fn-zorba-sctx:functions";
}
// </SctxFunctionsIterator>


// <SctxInScopeAttributeDeclarationsIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxInScopeAttributeDeclarationsIterator)

void SctxInScopeAttributeDeclarationsIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxInScopeAttributeDeclarationsIterator, SctxInScopeAttributeDeclarationsIteratorState>*)this);
}


void SctxInScopeAttributeDeclarationsIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxInScopeAttributeDeclarationsIterator::~SctxInScopeAttributeDeclarationsIterator() {}

SctxInScopeAttributeDeclarationsIteratorState::SctxInScopeAttributeDeclarationsIteratorState() {}

SctxInScopeAttributeDeclarationsIteratorState::~SctxInScopeAttributeDeclarationsIteratorState() {}


void SctxInScopeAttributeDeclarationsIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxInScopeAttributeDeclarationsIterator::getNameAsString() const {
  return "fn-zorba-sctx:in-scope-attribute-declarations";
}
// </SctxInScopeAttributeDeclarationsIterator>


// <SctxInScopeAttributeGroupsIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxInScopeAttributeGroupsIterator)

void SctxInScopeAttributeGroupsIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxInScopeAttributeGroupsIterator, SctxInScopeAttributeGroupsIteratorState>*)this);
}


void SctxInScopeAttributeGroupsIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxInScopeAttributeGroupsIterator::~SctxInScopeAttributeGroupsIterator() {}

SctxInScopeAttributeGroupsIteratorState::SctxInScopeAttributeGroupsIteratorState() {}

SctxInScopeAttributeGroupsIteratorState::~SctxInScopeAttributeGroupsIteratorState() {}


void SctxInScopeAttributeGroupsIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxInScopeAttributeGroupsIterator::getNameAsString() const {
  return "fn-zorba-sctx:in-scope-attribute-groups";
}
// </SctxInScopeAttributeGroupsIterator>


// <SctxInScopeElementDeclarationsIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxInScopeElementDeclarationsIterator)

void SctxInScopeElementDeclarationsIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxInScopeElementDeclarationsIterator, SctxInScopeElementDeclarationsIteratorState>*)this);
}


void SctxInScopeElementDeclarationsIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxInScopeElementDeclarationsIterator::~SctxInScopeElementDeclarationsIterator() {}

SctxInScopeElementDeclarationsIteratorState::SctxInScopeElementDeclarationsIteratorState() {}

SctxInScopeElementDeclarationsIteratorState::~SctxInScopeElementDeclarationsIteratorState() {}


void SctxInScopeElementDeclarationsIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxInScopeElementDeclarationsIterator::getNameAsString() const {
  return "fn-zorba-sctx:in-scope-element-declarations";
}
// </SctxInScopeElementDeclarationsIterator>


// <SctxInScopeElementGroupsIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxInScopeElementGroupsIterator)

void SctxInScopeElementGroupsIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxInScopeElementGroupsIterator, SctxInScopeElementGroupsIteratorState>*)this);
}


void SctxInScopeElementGroupsIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxInScopeElementGroupsIterator::~SctxInScopeElementGroupsIterator() {}

SctxInScopeElementGroupsIteratorState::SctxInScopeElementGroupsIteratorState() {}

SctxInScopeElementGroupsIteratorState::~SctxInScopeElementGroupsIteratorState() {}


void SctxInScopeElementGroupsIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxInScopeElementGroupsIterator::getNameAsString() const {
  return "fn-zorba-sctx:in-scope-element-groups";
}
// </SctxInScopeElementGroupsIterator>


// <SctxInScopeSchemaTypesIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxInScopeSchemaTypesIterator)

void SctxInScopeSchemaTypesIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxInScopeSchemaTypesIterator, SctxInScopeSchemaTypesIteratorState>*)this);
}


void SctxInScopeSchemaTypesIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxInScopeSchemaTypesIterator::~SctxInScopeSchemaTypesIterator() {}

SctxInScopeSchemaTypesIteratorState::SctxInScopeSchemaTypesIteratorState() {}

SctxInScopeSchemaTypesIteratorState::~SctxInScopeSchemaTypesIteratorState() {}


void SctxInScopeSchemaTypesIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxInScopeSchemaTypesIterator::getNameAsString() const {
  return "fn-zorba-sctx:in-scope-schema-types";
}
// </SctxInScopeSchemaTypesIterator>


// <SctxInscopeVariablesIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxInscopeVariablesIterator)

void SctxInscopeVariablesIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxInscopeVariablesIterator, SctxInscopeVariablesIteratorState>*)this);
}


void SctxInscopeVariablesIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxInscopeVariablesIterator::~SctxInscopeVariablesIterator() {}

SctxInscopeVariablesIteratorState::SctxInscopeVariablesIteratorState() {}

SctxInscopeVariablesIteratorState::~SctxInscopeVariablesIteratorState() {}


void SctxInscopeVariablesIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxInscopeVariablesIterator::getNameAsString() const {
  return "fn-zorba-sctx:in-scope-variables";
}
// </SctxInscopeVariablesIterator>


// <SctxOptionIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxOptionIterator)

void SctxOptionIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxOptionIterator, PlanIteratorState>*)this);
}


void SctxOptionIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxOptionIterator::~SctxOptionIterator() {}


zstring SctxOptionIterator::getNameAsString() const {
  return "fn-zorba-sctx:option";
}
// </SctxOptionIterator>


// <SctxOrderingModeIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxOrderingModeIterator)

void SctxOrderingModeIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxOrderingModeIterator, PlanIteratorState>*)this);
}


void SctxOrderingModeIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxOrderingModeIterator::~SctxOrderingModeIterator() {}


zstring SctxOrderingModeIterator::getNameAsString() const {
  return "fn-zorba-sctx:ordering-mode";
}
// </SctxOrderingModeIterator>


// <SctxStaticallyKnownCollationsIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxStaticallyKnownCollationsIterator)

void SctxStaticallyKnownCollationsIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxStaticallyKnownCollationsIterator, SctxStaticallyKnownCollationsIteratorState>*)this);
}


void SctxStaticallyKnownCollationsIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxStaticallyKnownCollationsIterator::~SctxStaticallyKnownCollationsIterator() {}

SctxStaticallyKnownCollationsIteratorState::SctxStaticallyKnownCollationsIteratorState() {}

SctxStaticallyKnownCollationsIteratorState::~SctxStaticallyKnownCollationsIteratorState() {}


void SctxStaticallyKnownCollationsIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxStaticallyKnownCollationsIterator::getNameAsString() const {
  return "fn-zorba-sctx:statically-known-collations";
}
// </SctxStaticallyKnownCollationsIterator>


// <SctxStaticallyKnownDocumentsIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxStaticallyKnownDocumentsIterator)

void SctxStaticallyKnownDocumentsIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxStaticallyKnownDocumentsIterator, SctxStaticallyKnownDocumentsIteratorState>*)this);
}


void SctxStaticallyKnownDocumentsIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxStaticallyKnownDocumentsIterator::~SctxStaticallyKnownDocumentsIterator() {}

SctxStaticallyKnownDocumentsIteratorState::SctxStaticallyKnownDocumentsIteratorState() {}

SctxStaticallyKnownDocumentsIteratorState::~SctxStaticallyKnownDocumentsIteratorState() {}


void SctxStaticallyKnownDocumentsIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxStaticallyKnownDocumentsIterator::getNameAsString() const {
  return "fn-zorba-sctx:statically-known-documents";
}
// </SctxStaticallyKnownDocumentsIterator>


// <SctxStaticallyKnownDocumentTypeIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxStaticallyKnownDocumentTypeIterator)

void SctxStaticallyKnownDocumentTypeIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxStaticallyKnownDocumentTypeIterator, PlanIteratorState>*)this);
}


void SctxStaticallyKnownDocumentTypeIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxStaticallyKnownDocumentTypeIterator::~SctxStaticallyKnownDocumentTypeIterator() {}


zstring SctxStaticallyKnownDocumentTypeIterator::getNameAsString() const {
  return "fn-zorba-sctx:statically-known-document-type";
}
// </SctxStaticallyKnownDocumentTypeIterator>


// <SctxStaticallyKnownNamespaceBindingIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxStaticallyKnownNamespaceBindingIterator)

void SctxStaticallyKnownNamespaceBindingIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxStaticallyKnownNamespaceBindingIterator, PlanIteratorState>*)this);
}


void SctxStaticallyKnownNamespaceBindingIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxStaticallyKnownNamespaceBindingIterator::~SctxStaticallyKnownNamespaceBindingIterator() {}


zstring SctxStaticallyKnownNamespaceBindingIterator::getNameAsString() const {
  return "fn-zorba-sctx:statically-known-namespace-binding";
}
// </SctxStaticallyKnownNamespaceBindingIterator>


// <SctxStaticallyKnownNamespacesIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxStaticallyKnownNamespacesIterator)

void SctxStaticallyKnownNamespacesIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxStaticallyKnownNamespacesIterator, SctxStaticallyKnownNamespacesIteratorState>*)this);
}


void SctxStaticallyKnownNamespacesIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxStaticallyKnownNamespacesIterator::~SctxStaticallyKnownNamespacesIterator() {}

SctxStaticallyKnownNamespacesIteratorState::SctxStaticallyKnownNamespacesIteratorState() {}

SctxStaticallyKnownNamespacesIteratorState::~SctxStaticallyKnownNamespacesIteratorState() {}


void SctxStaticallyKnownNamespacesIteratorState::init(PlanState& planState) {
  PlanIteratorState::init(planState);
}

zstring SctxStaticallyKnownNamespacesIterator::getNameAsString() const {
  return "fn-zorba-sctx:statically-known-namespaces";
}
// </SctxStaticallyKnownNamespacesIterator>


// <SctxXPath10CompatModeIterator>
SERIALIZABLE_CLASS_VERSIONS(SctxXPath10CompatModeIterator)

void SctxXPath10CompatModeIterator::serialize(::zorba::serialization::Archiver& ar)
{
  serialize_baseclass(ar,
  (NaryBaseIterator<SctxXPath10CompatModeIterator, PlanIteratorState>*)this);
}


void SctxXPath10CompatModeIterator::accept(PlanIterVisitor& v) const
{
  if (!v.hasToVisit(this))
    return;

  v.beginVisit(*this);

  std::vector<PlanIter_t>::const_iterator lIter = theChildren.begin();
  std::vector<PlanIter_t>::const_iterator lEnd = theChildren.end();
  for ( ; lIter != lEnd; ++lIter ){
    (*lIter)->accept(v);
  }

  v.endVisit(*this);
}

SctxXPath10CompatModeIterator::~SctxXPath10CompatModeIterator() {}


zstring SctxXPath10CompatModeIterator::getNameAsString() const {
  return "fn-zorba-sctx:xpath10-compatibility-mode";
}
// </SctxXPath10CompatModeIterator>



}


