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

#include "debugger/debugger_serverimpl.h"

#include <iostream>
#include <memory>
#include <fstream>
#include <boost/bind.hpp>
#include <zorba/zorba.h>

#include "debugger/socket.h"
#include "debugger/message_factory.h"

#include "context/static_context.h"

#include "runtime/fncontext/FnContextImpl.h"
#include "runtime/core/item_iterator.h"
#include "runtime/api/runtimecb.h"
#include "runtime/api/plan_iterator_wrapper.h"
#include "runtime/util/iterator_impl.h"

#include "api/serialization/serializer.h"
#include "api/unmarshaller.h"

#include "zorbatypes/numconversions.h"

#include "common/shared_types.h"

#ifdef WIN32
#define sleep(s) Sleep(s*1000)
#endif

namespace zorba{

THREAD_RETURN_TYPE runtimeThread( void *aDebugger )
{
  ZorbaDebuggerImpl * lDebugger = (ZorbaDebuggerImpl *) aDebugger;
  lDebugger->runQuery();
  return 0;
}

ZorbaDebuggerImpl::~ZorbaDebuggerImpl()
{
  delete theRequestServerSocket;
  delete theEventSocket;
}

void ZorbaDebuggerImpl::start( void * aStore,
                               std::auto_ptr<std::istream> *aQuery,
                               std::string &aFileName,
                               unsigned short aRequestPortno,
                               unsigned short aEventPortno)
{
  TCPSocket * lSock;
  //activate the debug mode
  theDebugMode = true;
  //Set the input stream
  theQuery = aQuery;
  //Set the fileName
  theFileName = aFileName; 
  //Set the instance of Zorba
  theZorba = Zorba::getInstance( aStore );
  //Run the server 
  theRequestServerSocket = new TCPServerSocket( aRequestPortno );
  theEventPortno = aEventPortno;
  
  //Wait for a client to connect
  lSock = theRequestServerSocket->accept(); 
#ifndef NDEBUG
  std::clog << "[Server Thread] Client connected" << std::endl;
#endif
  //Try to connect to the event server 3 times
  for ( unsigned int i = 0; i < 3 && ! theEventSocket; i++ )
  {
    try
    {
      //Connect the client to the event server
      theEventSocket = new TCPSocket( "127.0.0.1", theEventPortno );
      //Wait one second before trying to reconnect
      sleep(1);
    } catch ( SocketException &e )  {
      if ( i == 2 )
      {
        std::cerr << "Couldn't connect to the debugger server event" << std::endl;
        std::cerr << e.what() << std::endl;
      }
    }
  }
  
  //Perform handshake
  handshake( lSock );
  
  //Until the query execution has ended
  while ( theStatus != QUERY_QUITED )
  {
    handleTcpClient( lSock );
  }
#ifndef NDEBUG
  std::clog << "[Server Thread] server quited" << std::endl;
#endif
  if ( theRuntimeThread != 0 ){
    theRuntimeThread->join();
  }
#ifndef NDEBUG
  std::clog << "[Server Thread] runtime thread joined" << std::endl;
#endif 
  delete lSock;
}

void ZorbaDebuggerImpl::setStatus( ExecutionStatus Status,
                                   SuspensionCause aCause ){

  if ( theStatus == QUERY_SUSPENDED && Status == QUERY_RUNNING )
  {
    theStatus = QUERY_RESUMED;
  } else {
	  theStatus = Status;
  }

  switch ( theStatus )
  {
    case QUERY_RUNNING:
      startedEvent();
      break;
    case QUERY_SUSPENDED:
      suspendedEvent( theLocation, aCause );
      break;
    case QUERY_TERMINATED:
      terminatedEvent();
      break;
    case QUERY_RESUMED:
      theStatus = QUERY_RUNNING;
      resumedEvent();
      break;
  }
}

void ZorbaDebuggerImpl::sendEvent( AbstractCommandMessage * aMessage )
{
    Length length;
    Byte * lMessage = aMessage->serialize( length );
    try
    {
#ifndef NDEBUG
      std::clog << "[Server Thread] send an event: ";
      switch ( aMessage->getCommand() )
      {
        case STARTED:
          std::cerr << "started" << std::endl;
          break;
        case TERMINATED:
          std::cerr << "terminated" << std::endl;
          break;
        case SUSPENDED:
          std::cerr << "suspended" << std::endl;
          break;
        case RESUMED:
          std::cerr << "resumed" << std::endl;
          break;
        case EVALUATED:
          std::cerr << "evaluated" << std::endl;
          break;
      }
#endif
      theEventSocket->send( lMessage, length );
#ifndef NDEBUG
      std::clog << "[Server Thread] event sent" << std::endl;
#endif
    } catch( SocketException &e ) {
      std::cerr << e.what() << std::endl;
    }
    delete[] lMessage;
}


void ZorbaDebuggerImpl::startedEvent()
{
    StartedEvent lMessage;
    sendEvent( &lMessage );
}

void ZorbaDebuggerImpl::suspendedEvent( QueryLoc &aLocation, SuspensionCause aCause )
{
    SuspendedEvent lMessage( aLocation, aCause );
    sendEvent( &lMessage );
}

void ZorbaDebuggerImpl::resumedEvent()
{
    ResumedEvent * lMessage = new ResumedEvent();
    sendEvent( lMessage );
    delete lMessage;
}

void ZorbaDebuggerImpl::terminatedEvent()
{
    TerminatedEvent lMessage;
    sendEvent( &lMessage );
}

void ZorbaDebuggerImpl::runQuery()
{
  setStatus( QUERY_RUNNING );
  //reload the query
  std::ifstream * lFile = dynamic_cast< std::ifstream * >( theQuery->get() );
  if ( lFile != 0 ) {
    theQuery->reset( new std::ifstream( theFileName.c_str() ) );
  } else {
    (*theQuery)->clear();
    (*theQuery)->seekg( 0, std::ios::beg );
  }
  //Compiles the query
  XQuery_t lQuery = theZorba->createQuery();
  lQuery->setFileName( theFileName );
  Zorba_CompilerHints lCompilerHints;
  lCompilerHints.opt_level = ZORBA_OPT_LEVEL_O1;
    
  lQuery->compile( *(theQuery->get()), lCompilerHints );
  
  try
  {
    ResultIterator_t lIterator = lQuery->iterator();
    lIterator->open();

    Item lItem;
    while ( lIterator->next(lItem) &&
            theStatus != QUERY_TERMINATED &&
            theStatus != QUERY_QUITED )
    {
      std::cout << lItem.getStringValue() << std::endl;
    }
    lIterator->close();
  } catch ( StaticException& se ) {
    std::cerr << se << std::endl;
  } catch ( DynamicException& de ) {
    std::cerr << de << std::endl;
  } catch ( SystemException& se ) {
    std::cerr << se << std::endl;
  }
  setStatus( QUERY_TERMINATED );
}

bool ZorbaDebuggerImpl::isEnabled() const
{
  return theDebugMode;
}

bool ZorbaDebuggerImpl::hasToSuspend()
{
  if( theStatus == QUERY_SUSPENDED )
  {
    return true;
  }
  std::map<unsigned int, QueryLoc>::iterator it;
  for ( it = theBreakpoints.begin(); it != theBreakpoints.end(); it++ )
  {
    if ( theLocation.getLineno() == it->second.getLineno() )
    {
      setStatus( QUERY_SUSPENDED, CAUSE_BREAKPOINT );
      return true;
    }
  }
 
  std::map<unsigned int, xqpString>::iterator lIter;
  for ( lIter = theWatchpoints.begin(); lIter != theWatchpoints.end(); lIter++ )
  {
    store::Item_t lResult = fetchItem( theLocation, lIter->second, *thePlanState, 0);
    if ( lResult != 0 || lResult->getEBV() )
    {
      setStatus( QUERY_SUSPENDED, CAUSE_BREAKPOINT );
      return true;
    }
  }
  
  return false;
}

/**
 * Perform an handshake with the client.
 * Simply returns the received first 11 bytes.
 */
void ZorbaDebuggerImpl::handshake( TCPSocket * aSock )
{
  Byte * msg = new Byte[11];
  try
  {
    aSock->recv( msg, 11 );
    aSock->send( msg, 11 );
  } catch( SocketException &e ) {
    std::cerr << e.what() << std::endl;
  }
  delete[] msg;
}

/**
 * TODO: check if the client has closed the connection
 */
void ZorbaDebuggerImpl::handleTcpClient( TCPSocket * aSock )
{
    Byte * lByteMessage = 0;
    AbstractMessage * lMessage = 0;
    ReplyMessage * lReplyMessage = 0;
    Length length;
    try
    {
    lMessage = MessageFactory::buildMessage( aSock );
    
    AbstractCommandMessage * lCommandMessage = dynamic_cast< AbstractCommandMessage * > ( lMessage );
    
    if ( lCommandMessage )
    {
      //process the command message
      processMessage( lCommandMessage );
      //Send the reply message
      lReplyMessage = lCommandMessage->getReplyMessage();
      lByteMessage = lReplyMessage->serialize( length );
      aSock->send( lByteMessage, length );
    } else {
#ifndef NDEBUG
      std::cerr << "Received something wrong" << std::endl;
#endif
      //If something goes wrong, buildMessage() receive a Reply Message containing the error description
      //Send it back to the client right away
      lReplyMessage = dynamic_cast<ReplyMessage *> ( lMessage );
      if( lReplyMessage ){
        lByteMessage = lReplyMessage->serialize( length );
        aSock->send( lByteMessage, length );
      } else {
        std::cerr << "Internal error occured. Couldn't send the error message." << std::endl;
      }
    }    
  } catch ( std::exception &e ) {
    std::cerr <<  e.what() << std::endl;
  }
  if ( lByteMessage != 0 )
    delete[] lByteMessage;
  delete lMessage;
  delete lReplyMessage;
}

void ZorbaDebuggerImpl::run()
{
  theRuntimeThread = new Thread( runtimeThread, this );
}

void ZorbaDebuggerImpl::suspend()
{
  setStatus( QUERY_SUSPENDED );
}

void ZorbaDebuggerImpl::resume()
{
  if ( theStatus == QUERY_SUSPENDED )
  {
    setStatus( QUERY_RUNNING );
    theRuntimeThread->resume();
  }
}

void ZorbaDebuggerImpl::terminate()
{
  setStatus( QUERY_TERMINATED );
}

void ZorbaDebuggerImpl::quit()
{
  setStatus( QUERY_QUITED );
}

void ZorbaDebuggerImpl::eval( xqpString anExpr )
{
  if ( theStatus != QUERY_IDLE && theStatus != QUERY_TERMINATED )
  {
    xqpString lError;
    store::Item_t lResult = fetchItem( theLocation, anExpr, *thePlanState, &lError );
    xqpString lValue = fetchValue( theLocation, anExpr, *thePlanState, &lError );
    EvaluatedEvent * lMsg;
    if ( lResult != 0 )
    {
      xqpString lType( lResult->getType()->getStringValue() );
      lMsg = new EvaluatedEvent( anExpr, lValue, lType ); 
    } else {
      lMsg = new EvaluatedEvent( anExpr, lError );
    }
    sendEvent( lMsg );
    delete lMsg;
  }
}

store::Item_t ZorbaDebuggerImpl::fetchItem( const QueryLoc& loc, xqpString anExpr,
                                             PlanState& planState, xqpString *anError )
  {
    std::stringstream lOutputStream;
    
    PlanWrapperHolder eval_plan;
    std::auto_ptr< CompilerCB > ccb;
    std::auto_ptr< dynamic_context > dctx;

    checked_vector< std::string > var_keys;

    //set up eval state's ccb
    ccb.reset( new CompilerCB ( *planState.theCompilerCB ) );
    ccb->m_sctx_list.push_back( ccb->m_sctx = ccb->m_sctx->create_child_context() );

    store::Item_t lItem;
    try
    {
      dctx.reset( new dynamic_context( planState.dctx() ) );
      eval_plan.reset(
        new PlanWrapper (
          EvalIterator::compile ( ccb.get(), anExpr, theVarnames, theVartypes ),
          ccb.get(),
          dctx.get(),
          planState.theStackDepth + 1 )
        );
      eval_plan->checkDepth( loc );
   
      for (unsigned i = 0; i < theChildren.size () - 1; i++)
      {
        //reset the plan iterator for multiple execution
        theChildren[i+1]->reset(*thePlanState);
        store::Iterator_t lIter = new PlanIteratorWrapper(theChildren[i+1], *thePlanState);
        // TODO: is saving an open iterator efficient?
        // Then again if we close theChildren [1] here,
        // we won't be able to re-open it later via the PlanIteratorWrapper
        dctx->add_variable(dynamic_context::var_key(ccb->m_sctx->lookup_var(theVarnames[i])), lIter);
      }

      PlanWrapper *lIterator = eval_plan.get();
      lIterator->next(lItem);
      //while ( lIterator->next(lItem) )
      //{
      //  lOutputStream << lItem->getStringValue();
      //}
      //serializer lSerializer(0);
      //lSerializer.set_parameter("method", "xml");
      //lSerializer.set_parameter("indent", "no");
      //lSerializer.set_parameter("omit-xml-declaration", "yes");

      //eval_plan->open();
      //lSerializer.serialize( eval_plan.get(), lOutputStream );

    } catch ( error::ZorbaError& e ) {
      lOutputStream << "Error: " << error::ZorbaError::toString(e.theErrorCode) << std::endl;
      lOutputStream << "       " << e.theDescription << std::endl;
    }
    
    if ( eval_plan.get() != 0 )
    {
      eval_plan->close();
    }
    *anError = lOutputStream.str(); 
    return lItem;
  }

xqpString ZorbaDebuggerImpl::fetchValue( const QueryLoc& loc, xqpString anExpr,
                                             PlanState& planState, xqpString *anError )
  {
    std::stringstream lOutputStream;
    
    PlanWrapperHolder eval_plan;
    std::auto_ptr< CompilerCB > ccb;
    std::auto_ptr< dynamic_context > dctx;

    checked_vector< std::string > var_keys;

    //set up eval state's ccb
    ccb.reset( new CompilerCB ( *planState.theCompilerCB ) );
    ccb->m_sctx_list.push_back( ccb->m_sctx = ccb->m_sctx->create_child_context() );

    try
    {
      dctx.reset( new dynamic_context( planState.dctx() ) );
      eval_plan.reset(
        new PlanWrapper (
          EvalIterator::compile ( ccb.get(), anExpr, theVarnames, theVartypes ),
          ccb.get(),
          dctx.get(),
          planState.theStackDepth + 1 )
        );
      eval_plan->checkDepth( loc );
   
      for (unsigned i = 0; i < theChildren.size () - 1; i++)
      {
        //reset the plan iterator for multiple execution
        theChildren[i+1]->reset(*thePlanState);
        store::Iterator_t lIter = new PlanIteratorWrapper(theChildren[i+1], *thePlanState);
        // TODO: is saving an open iterator efficient?
        // Then again if we close theChildren [1] here,
        // we won't be able to re-open it later via the PlanIteratorWrapper
        dctx->add_variable(dynamic_context::var_key(ccb->m_sctx->lookup_var(theVarnames[i])), lIter);
      }

      serializer lSerializer(0);
      lSerializer.set_parameter("method", "xml");
      lSerializer.set_parameter("indent", "no");
      lSerializer.set_parameter("omit-xml-declaration", "yes");

      //eval_plan->open();
      lSerializer.serialize( eval_plan.get(), lOutputStream );

    } catch ( error::ZorbaError& e ) {
      std::stringstream lError;
      lError << "Error: " << error::ZorbaError::toString(e.theErrorCode) << std::endl;
      lError << "       " << e.theDescription << std::endl;
      *anError = lError.str();
    }
    
    if ( eval_plan.get() != 0 )
    {
      eval_plan->close();
    }
    return xqpString( lOutputStream.str() );
  }



void ZorbaDebuggerImpl::processMessage(AbstractCommandMessage * aMessage)
{
  switch( aMessage->getCommandSet() )
  {
    case EXECUTION:
    {
      switch( aMessage->getCommand() )
      {
        case RUN:
        {
#ifndef NDEBUG
          RunMessage * lMessage = dynamic_cast<RunMessage *> ( aMessage );
          assert( lMessage );
#endif
          run();
          break;
        }
        case SUSPEND:
        {
#ifndef NDEBUG
          SuspendMessage * lMessage = dynamic_cast<SuspendMessage *> ( aMessage );
          assert( lMessage );
#endif
          suspend();
          break;
        }
        case RESUME:
        {
#ifndef NDEBUG
          ResumeMessage * lMessage = dynamic_cast<ResumeMessage*> ( aMessage );
          assert( lMessage );
#endif
          resume();
          break;
        }
        case QUIT:
        {
#ifndef NDEGUB
          QuitMessage * lMessage = dynamic_cast<QuitMessage *>( aMessage );
          assert( lMessage );
#endif
          quit();
          break;
        }
        case TERMINATE:
        {
#ifndef NDEBUG
          TerminateMessage * lMessage = dynamic_cast<TerminateMessage *> ( aMessage );
          assert( lMessage );
#endif
          terminate();
          break;
        }
        case STEP:
        {
#ifndef NDEBUG
          StepMessage * lMessage = dynamic_cast<StepMessage *> ( aMessage );
          assert( lMessage );
          processMessage( lMessage );
#else
          processMessage( static_cast<StepMessage *> ( aMessage ));
#endif
          break;
        }
        default: throw InvalidCommandException("Internal Error. Command not implemented for execution command set .");
    }
      break;
    case BREAKPOINTS:
    {
      switch( aMessage->getCommand() )
      {
        case SET:
        {
          SetMessage * lMessage;
#ifndef NDEBUG
          lMessage = dynamic_cast< SetMessage * > ( aMessage );
          assert( lMessage );
#else
          lMessage =  static_cast< SetMessage * > ( aMessage );
#endif
          std::map<unsigned int, QueryLoc> locations = lMessage->getLocations();
          std::map<unsigned int, QueryLoc>::iterator it;
          for ( it = locations.begin(); it != locations.end(); it++ )
          {
            theBreakpoints.insert( std::make_pair( it->first, it->second ) ); 
          }
          
          std::map<unsigned int, xqpString> exprs = lMessage->getExprs();
          std::map<unsigned int, xqpString>::iterator lIt;
          for ( lIt = exprs.begin(); lIt != exprs.end(); lIt++ )
          {
            theWatchpoints.insert( std::make_pair( lIt->first, lIt->second ) ); 
          }
          break;
        }
        case CLEAR:
        {
          ClearMessage * lMessage;
#ifndef NDEBUG
          lMessage = dynamic_cast< ClearMessage * > ( aMessage );
          assert( lMessage );
#else
          lMessage =  static_cast< ClearMessage * > ( aMessage );
#endif
          std::vector<unsigned int>::iterator it;
          std::vector<unsigned int> ids = lMessage->getIds();
          for ( it = ids.begin(); it != ids.end(); it++ )
          {
            std::map<unsigned int, QueryLoc>::iterator
            lIter = theBreakpoints.find( *it );
            if ( lIter !=  theBreakpoints.end() )
            {
              theBreakpoints.erase( lIter );
            } else {
              std::map<unsigned int, xqpString>::iterator lIter2 =
              theWatchpoints.find( *it );
              if ( lIter2 != theWatchpoints.end() ) {
                theWatchpoints.erase( lIter2 );
              }
            }
          }
          break;
        }
        default: throw InvalidCommandException("Internal Error. Command not implemented for breakpoints command set.");
      }
    }
      break;
    case ENGINE_EVENT:
    case STATIC:
    case DYNAMIC:
    {
      switch ( aMessage->getCommand() )
      {
        case EVAL:
        {
          EvalMessage * lMessage;
#ifndef NDEBUG
          lMessage = dynamic_cast< EvalMessage * > ( aMessage );
          assert( lMessage );
#else
          lMessage = static_cast< EvalMessage * > ( aMessage );
#endif
          eval( lMessage->getExpr() );
          break;
        }
        case VARIABLES:
        {
          VariableMessage * lMessage;
#ifndef NDEBUG
          lMessage = dynamic_cast< VariableMessage * > ( aMessage );
#else
          lMessage = static_cast< VariableMessage * > ( aMessage );
#endif
          checked_vector<xqtref_t>::iterator it;
          for( unsigned i = 0; i<theVarnames.size(); i++ )
          {
            xqpString lName(theVarnames.at(i)->getStringValue());
            xqpString lType;
            if( theVartypes.at(i) != 0 )
            {
              lType = theVartypes.at(i)->toString();
            } else {
              lType = "[XS_UNTYPED]";
            }
            lMessage->addLocal( lName, lType );
          }
          break;
        }
        default: throw InvalidCommandException("Internal Error. Command not implemented for dynamic command set.");
      }
    }
    break;
    default:
      throw InvalidCommandException("Internal Error. CommandSet not implemented.");
  }
}
};
}//end of namespace

