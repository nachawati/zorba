
#ifndef ZORBA_ERROR_ALERTS_11_JULY_2007
#define ZORBA_ERROR_ALERTS_11_JULY_2007


///Daniel T @ IPDEVEL
/*
	Implementing error/warning alert.

	These include xquery errors and zorba errors, fatal errors and notification alerts..

*/

#include <string>

#include "errors.h"
#include "xqp_exception.h"
#include "compiler/parser/location.hh"

//using namespace std;


namespace xqp {

class ZorbaErrorAlerts 
{

public:
  /**
   *  @param ecode One of predefined error codes in errors.h
   *  @param etype One of predefined error types in errors.h
   *  @param loc   If NULL location will be taken from current iterator from zorba object
   *  @param continue_execution If true, the error is recoverable and execution can continue; otherwise the error is fatal and an exception is thrown.
   *
   */
	static void error_alert(
        const error_messages::errcode ecode,
        error_messages::error_type etype,
        const yy::location *ploc = NULL,
        bool continue_execution = false,
				const std::string param1 = "",
        const std::string param2 = "");


	static void warning_alert(
        const error_messages::warning_code,
        const yy::location *ploc = NULL,
        const std::string param1 = "",
        const std::string param2 = "");


	static void notify_event(
        const error_messages::NotifyEvent_code notif_event,
        const std::string param1 = "",
        const std::string param2 = "");


	///return the index of the option chosen by user
	static int ask_user(
        const error_messages::AskUserString_code ask_string,
        const error_messages::AskUserStringOptions_code ask_string_options,
        const std::string param1 = "",
        const std::string param2 = "");


};


////define some macros to catch the __FILE__ and __LINE__ where the error is fired
#ifdef _DEBUG
extern const char*		g_error_in_file;
extern int						g_error_at_line;

#define		ZORBA_ERROR_ALERT				\
				g_error_in_file = __FILE__;  g_error_at_line = __LINE__; \
				ZorbaErrorAlerts::error_alert

#define		ZORBA_WARNING_ALERT		\
				g_error_in_file = __FILE__;  g_error_at_line = __LINE__; \
				ZorbaErrorAlerts::warning_alert

#define		ZORBA_NOTIFY_EVENT		\
				g_error_in_file = __FILE__;  g_error_at_line = __LINE__; \
				ZorbaErrorAlerts::notify_event


#else ///ifdef _DEBUG

#define		ZORBA_ERROR_ALERT				\
				ZorbaErrorAlerts::error_alert

#define		ZORBA_WARNING_ALERT		\
				ZorbaErrorAlerts::warning_alert

#define		ZORBA_NOTIFY_EVENT		\
				ZorbaErrorAlerts::notify_event


#endif ///ifdef _DEBUG


}

#endif


/*
 * Local variables:
 * mode: c++
 * End:
 */
