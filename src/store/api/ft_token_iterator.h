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

#ifndef ZORBA_FT_TOKEN_ITERATOR_H
#define ZORBA_FT_TOKEN_ITERATOR_H

#include <vector>

#include "store/api/ft_token.h"
#include "zorbatypes/rchandle.h"
#include "zorbaerrors/Assert.h"

namespace zorba {

class FTTokenIterator;
typedef rchandle<FTTokenIterator> FTTokenIterator_t;

/**
 * An <code>FTTokenIterator</code> iterates over a sequence of full-text
 * tokens.
 */
class ZORBA_DLL_PUBLIC FTTokenIterator : public SimpleRCObject {
public:
  typedef unsigned index_t;

  /**
   * A <code>Mark</code> holds the position state of an iterator.
   */
  class Mark : public SimpleRCObject {
  protected:
    Mark() { }
  };
  typedef rchandle<Mark> Mark_t;

  /**
   * Destroys this iterator.
   */
  virtual ~FTTokenIterator() { }

  /**
   * The index of the beginning token.
   *
   * @return Returns said index.
   */
  virtual index_t begin() const = 0;

  /**
   * Clones this iterator.
   *
   * @return Returns said clone.
   */
  virtual FTTokenIterator_t clone() const = 0;

  /**
   * Checks whether there are any tokens to iterate over.
   *
   * @return Returns <code>true</code> only if there are no tokens to iterate
   * over.
   */
  virtual bool empty() const = 0;

  /**
   * One greater than the index of the ending token.
   *
   * @return Returns said index.
   */
  virtual index_t end() const = 0;

  /**
   * Checks whether there is a next token.
   *
   * @return Returns <code>true</code> only if there is a next token.
   */
  virtual bool hasNext() const = 0;

  /**
   * Obtains the next token and advances the iterator.
   *
   * @param ppToken A pointer to the next token is put here; may be null to
   * advance the iterator only.
   * @return Returns <code>true</code> only if there is a next token.
   */
  virtual bool next( FTToken const **ppToken = 0 ) = 0;

  /**
   * Gets the current position.
   *
   * @return Returns said position.
   */
  virtual Mark_t pos() const = 0;

  /**
   * Sets the current position.
   *
   * @param mark The position to set this iterator to.
   */
  virtual void pos( Mark_t const &mark ) = 0;

  /**
   * Resets this iterator to the beginning.
   */
  virtual void reset() = 0;

};

} // namespace zorba
#endif  /* ZORBA_FT_TOKEN_ITERATOR_H */
/* vim:set et sw=2 ts=2: */
