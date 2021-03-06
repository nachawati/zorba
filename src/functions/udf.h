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
#pragma once
#ifndef ZORBA_FUNCTIONS_UDF
#define ZORBA_FUNCTIONS_UDF

#include "functions/cacheable_function.h"
#include "store/api/item_handle.h"

//#include "compiler/expression/expr_base.h"


namespace zorba
{
  class expr;

/*******************************************************************************
  A udf with params $x1, $x2, ..., $xn and a body_expr is translated into a
  flwor expr:

  let $x1 := $x1_, $x2 := $x2_, ..., $xn := $xn_
  return body_expr

  The internally generated vars $x1_, ..., $xn_ are not registered in any sctx,
  but they are registered in the udf obj instead (theArgVars data member).

  A call to a udf is translated the same way as a call to a built-in function,
  i.e., an fo_expr is created that points to the udf obj and also has a vector
  of pointers to the arg exprs appearing in the function call.

  theLoc:
  -------
  The query location where this udf is declared at.

  theBodyExpr:
  ------------
  The expr tree representing what this function is doing. It is the result of
  translating the udf declaration (so for a udf with one or more params, it is
  the flwor expr described above). Note: translation of udf declarations
  includes normalization and optimization of the expr tree.

  theArgVars:
  -----------
  The internally generated arg vars (the $xi_ vars described above)

  theScriptingKind:
  -----------------
  The declared scripting kind of this udf. Notice that the getScriptingKind
  method will return the declared kind if the body is NULL, but after the body
  has been translated, it will return the kind of the body expr.

  theIsLeaf:
  ----------
  True if this udf does not invoke any other udfs

  thePlan:
  --------

  thePlanStateSize:
  -----------------

  theArgVarsRefs:
  ---------------
  For each arg var, this vector stores the LetVarIterators that represent the
  references to that var within the udf body. If there are more than one
  references of an arg var, these references are "mutually exclusive", ie,
  at most one of the references will actually be reached during each particular
  execution of the body.

********************************************************************************/
class user_function : public cacheable_function
{
public:
  typedef std::vector<LetVarIter_t> ArgVarRefs;

private:
  CompilerCB                * theCCB;

  unsigned short              theScriptingKind;

  expr                      * theBodyExpr;
  std::vector<var_expr*>      theArgVars;

  std::vector<unsigned char>  theIgnoresSortedNodes;
  std::vector<unsigned char>  theIgnoresDuplicateNodes;
  std::vector<unsigned char>  theMustCopyInputNodes;
  std::vector<unsigned char>  thePropagatesInputNodes;

  bool                        theIsExiting;
  bool                        theIsLeaf;

  std::vector<user_function*> theMutuallyRecursiveUDFs;
  std::vector<fo_expr*>       theRecursiveCalls;

  bool                        theIsOptimized;

  PlanIter_t                  thePlan;
  uint32_t                    thePlanStateSize;
  std::vector<ArgVarRefs>     theArgVarsRefs;

public:
  SERIALIZABLE_CLASS(user_function)
  user_function(::zorba::serialization::Archiver& ar);
  void serialize(::zorba::serialization::Archiver& ar);

public:
  user_function(
      const QueryLoc& loc,
      static_context* sctx,
      const signature& sig,
      expr* expr_body,
      unsigned short scriptingKind,
      CompilerCB* compilerCB);

  virtual ~user_function();

  //xqtref_t getUDFReturnType(static_context* sctx) const;

  bool isExiting() const { return theIsExiting; }

  void setExiting(bool v) { theIsExiting = v; }

  void setLeaf(bool v) { theIsLeaf = v; }

  bool isLeaf() const { return theIsLeaf; }

  void setBody(expr* body);

  expr* getBody() const;

  virtual TypeManager* getTypeManager();

  void setScriptingKind(unsigned short k);

  csize numArgs() const { return theArgVars.size(); }

  void setArgVars(std::vector<var_expr*>& args);

  const std::vector<var_expr*>& getArgVars() const;

  var_expr* getArgVar(csize i) const { return theArgVars[i]; }

  void addMutuallyRecursiveUDFs(
      const std::vector<user_function*>& udfs,
      const std::vector<user_function*>::const_iterator& cycle);

  void addRecursiveCall(fo_expr* call);

  const std::vector<fo_expr*>& getRecursiveCalls() const { return theRecursiveCalls; }

  bool isMutuallyRecursiveWith(const user_function* udf);

  bool isRecursive() const;

  void setOptimized(bool v) { theIsOptimized = v; }

  bool isOptimized() const { return theIsOptimized; }

  void optimize();

  PlanIter_t getPlan(uint32_t& planStateSize, ulong nextVarId);
  PlanIter_t const& getPlan() const { return thePlan; }

  void invalidatePlan();

  PlanIter_t codegen(
        CompilerCB* cb,
        static_context* sctx,
        const QueryLoc& loc,
        std::vector<PlanIter_t>& argv,
        expr& ann) const;

  // The next 6 methods are virtual methods of class function, which are redefined here

  unsigned short getScriptingKind() const;

  bool dereferencesNodes() const;

  bool constructsNodes() const;

  bool accessesDynCtx() const;

  bool mustCopyInputNodes(expr* fo, csize input) const;

  bool propagatesInputNodes(expr* fo, csize input) const;

  BoolAnnotationValue ignoresSortedNodes(expr* fo, csize input) const;

  BoolAnnotationValue ignoresDuplicateNodes(expr* fo, csize input) const;

  // Runtime-related methods

  void setPlaneStateSize(uint32_t size) { thePlanStateSize = size; }

  const std::vector<ArgVarRefs>& getArgVarsRefs() const;

  virtual void useDefaultCachingSettings();
};


} /* namespace zorba */
#endif

/*
 * Local variables:
 * mode: c++
 * End:
 */
/* vim:set et sw=2 ts=2: */
