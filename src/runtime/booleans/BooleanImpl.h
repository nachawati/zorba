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
#ifndef ZORBA_BOOLEAN_IMPL_H
#define ZORBA_BOOLEAN_IMPL_H

#include "zorbatypes/xqpstring.h"

#include "common/shared_types.h"
#include "runtime/base/unarybase.h"
#include "runtime/base/binarybase.h"
#include "runtime/base/narybase.h"
#include "runtime/booleans/compare_types.h"

namespace zorba
{

  class RuntimeCB; // TODO we should have a shared_runtime_types.h
  class GenericCast;

  /*______________________________________________________________________
  |
  | 15.1.1 fn:boolean
  | fn:boolean($arg as item()*) as xs:boolean
  |
  | Computes the effective boolean value of the sequence $arg.
  |_______________________________________________________________________*/
class FnBooleanIterator : public UnaryBaseIterator<FnBooleanIterator, PlanIteratorState>
{
private:
  bool theNegate;

 public:
  FnBooleanIterator ( const QueryLoc& loc, PlanIter_t& aIter, bool aNegate = false );

  virtual ~FnBooleanIterator();

  /**
   * Static function which computes the effective boolean value of a passed iterator.
   *
   * @param loc location of the iterator which invokes this function
   * @param planState
   * @param iterator
   * @param negate optinal parameter which negates the effective boolean value (default == false)
   * @return effective boolean value
   */
  static bool effectiveBooleanValue (
        const QueryLoc& loc,
        PlanState& planState,
        const PlanIterator* ,
        bool negate = false);

  bool nextImpl(store::Item_t& result, PlanState& planState) const;
  
  virtual void accept(PlanIterVisitor&) const;
};

  
class LogicIterator : public BinaryBaseIterator<LogicIterator, PlanIteratorState>
{
public:
  enum LogicType {
    AND, OR
  };
    
 private:
  LogicType theLogicType;
      
 public:
  LogicIterator ( const QueryLoc& loc, PlanIter_t aChild0, PlanIter_t aChild1, LogicType aLogicType);
  virtual ~LogicIterator();
      
  bool nextImpl(store::Item_t& result, PlanState& planState) const;
  
  virtual void accept(PlanIterVisitor&) const;
}; /* class LogicIterator */
  

class CompareIterator : public BinaryBaseIterator<CompareIterator, PlanIteratorState>
{
private:
  CompareConsts::CompareType theCompType;

public:
  CompareIterator (
        const QueryLoc& loc,
        PlanIter_t theChild0,
        PlanIter_t theChild1,
        CompareConsts::CompareType aCompType );

  virtual ~CompareIterator();

  bool nextImpl(store::Item_t& result, PlanState& planState) const;
      
  bool isValueComparison() const
  {
    bool retVal = false;
    switch(theCompType)
    {
    case CompareConsts::VALUE_EQUAL:
    case CompareConsts::VALUE_NOT_EQUAL:
    case CompareConsts::VALUE_LESS:
    case CompareConsts::VALUE_LESS_EQUAL:
    case CompareConsts::VALUE_GREATER:
    case CompareConsts::VALUE_GREATER_EQUAL:
      retVal = true;
      break;
    default:
      retVal = false;
      break;
    }
    return retVal;
  }

  bool isGeneralComparison() const
  {
    bool retVal = false;
    switch(theCompType)
    {
    case CompareConsts::GENERAL_EQUAL:
    case CompareConsts::GENERAL_NOT_EQUAL:
    case CompareConsts::GENERAL_LESS:
    case CompareConsts::GENERAL_LESS_EQUAL:
    case CompareConsts::GENERAL_GREATER:
    case CompareConsts::GENERAL_GREATER_EQUAL:
      retVal = true;
      break;
    default:
      retVal = false;
      break;
    }
    return retVal;
  }

  bool isNodeComparison() const
  {
    bool retVal = false;
    switch(theCompType)
    {
    case CompareConsts::NODE_EQUAL:
    case CompareConsts::NODE_NOT_EQUAL:
      retVal = true;
      break;
    default:
      retVal = false;
      break;
    }
    return retVal;
  }

  virtual void accept(PlanIterVisitor&) const;
    
     
 public:
  /**
   * Compares two items (without castings and promotions which are used in general 
   * and value comparison).
   * @param item0 
   * @param item1 
   * @param aCollation optional collation parameter (passed as pointer to make it possible to be set to 0)
   * @return -1, if item0 &lt; item1
   *          0, if item0 == item1
   *          1, if item0 &gt; item1
   *          2, if item0 not equal, not bigger, not smaller item1 (special case when an Item has the value NaN)
   *         -2, if it is not possible to compare the values the two passed items
   */
  static int8_t compare(
        RuntimeCB* aRuntimeCB,
        const store::Item_t& aItem0,
        const store::Item_t& aItem1, 
        XQPCollator* aCollation = 0);

  /**
   * Value comparison of the passed two items with the operator 
   * which is defined in the CompareIterator object.
   *
   * @param item0 
   * @param item1 
   * @param aCompType
   * @param aCollation optional collation parameter
   * @return 
   */
  static bool valueComparison(const QueryLoc &,
                              RuntimeCB* aRuntimeCB,
                              const store::Item_t& aItem0,
                              const store::Item_t& aItem1, 
                              CompareConsts::CompareType aCompType,
                              XQPCollator* aCollation = 0);
      
  /**
   * General comparison of the passed two items with the operator 
   * which is defined in the CompareIterator object.
   *
   * @param item0 
   * @param item1 
   * @param aCompType
   * @param aCollation optional collation parameter
   * @return 
   */
  static bool generalComparison(const QueryLoc &,
                                RuntimeCB*     aRuntimeCB,
                                const store::Item_t& aItem0,
                                const store::Item_t& aItem_1,
                                CompareConsts::CompareType aCompType,
                                XQPCollator*   aCollation = 0);
  
  /**
   * Value Equal on the passed items
   * @param aItem0 
   * @param aItem1 
   * @param aCollation optional collation parameter (passed as pointer to make it possible to be set to 0)
   * @return 0 (equal), 1 (not equal), -2 (value equal not possible)
   */
  static int8_t valueEqual(
        RuntimeCB*     aRuntimeCB,
        const store::Item_t& aItem0,
        const store::Item_t& aItem1, 
        XQPCollator*   aCollation = 0);
      
  /**
   * General Equal on the passed items
   * @param aItem0 
   * @param aItem1 
   * @param aCollation options collation parameter (passed as pointer to make it possible to be set to 0)
   * @return 0 (equal), 1 (not equal), -2 (general equal not possible)
   */
  static int8_t generalEqual(
        RuntimeCB*     aRuntimeCB,
        const store::Item_t& aItem0,
        const store::Item_t& aItem1, 
        XQPCollator*   aCollation = 0);
      
  /**
   * Value Comparison on the passed items
   * @param aItem0 
   * @param aItem1 
   * @param aCollation options collation parameter (passed as pointer to make it possible to be set to 0)
   * @return -1 (smaller), 0 (equal), 1 (bigger), 
   *          2 (not equal, not bigger, not smaller), -2 (value comparison not possible)
   */
  static int8_t valueCompare(
        RuntimeCB* aRuntimeCB,
        const store::Item_t& aItem0,
        const store::Item_t& aItem1, 
        XQPCollator* aCollation = 0);
      
  /**
   * General Comparison on the passed items
   * @param aItem0 
   * @param aItem1 
   * @param aCollation options collation parameter (passed as pointer to make it possible to be set to 0)
   * @return -1 (smaller), 0 (equal), 1 (bigger), 
   *          2 (not equal, not bigger, not smaller), -2 (general comparison not possible)
   */
  static int8_t generalCompare(
        RuntimeCB* aRuntimeCB,
        const store::Item_t& aItem0,
        const store::Item_t& aItem1, 
        XQPCollator* aCollation = 0);
      
  /**
   * Checks if the two passed items contains the same value (without castings and promotions which are used in general 
   * and value comparison).
   * @param item0 
   * @param item1 
   * @param aCollation options collation parameter (passed as pointer to make it possible to be set to 0)
   * @return  0, if item0 == item1
   *          1, if item0 != item1
   *         -2, if it is not possible to compare the values of the passed items
   */
  static int8_t equal(
        RuntimeCB* aRuntimeCB,
        const store::Item_t& aItem0,
        const store::Item_t& aItem1, 
        XQPCollator* aCollation = 0);
      
private:
  static void valueCasting(
        RuntimeCB*     aRuntimeCB, 
        const store::Item_t& aItem0,
        const store::Item_t& aItem1,
        store::Item_t&       castItem0,
        store::Item_t&       castItem1);

  static void generalCasting(
        RuntimeCB*     aRuntimeCB, 
        const store::Item_t& aItem0,
        const store::Item_t& aItem1,
        store::Item_t&       castItem0,
        store::Item_t&       castItem1);

  static bool boolResult(const QueryLoc &,
                         RuntimeCB* aRuntimeCB, 
                         int8_t aCompValue,
                         CompareConsts::CompareType aCompType);
}; /* class CompareIterator */


NARY_ITER(OpIsSameNodeIterator); 

NARY_ITER(OpNodeBeforeIterator);

NARY_ITER(OpNodeAfterIterator);

}

#endif

/*
 * Local variables:
 * mode: c++
 * End:
 */
