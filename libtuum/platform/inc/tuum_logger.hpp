/** @file   tuum_logger.hpp
 *  @brief  Simple logging interface.
 *
 *  @author Meelik Kiik (kiik.meelik@gmail.com)
 *  @date   July, 2015
 */

#ifndef TUUM_LOGGER_H
#define TUUM_LOGGER_H

#include <string>
#include <iostream>

#include "platform.t.hpp"

#define RTX_LOGGING

#define LOG_DEBUG gLogger.DEBUG
#define LOG_INFO gLogger.INFO
#define LOG_WARN gLogger.WARN
#define LOG_ERR gLogger.ERR

static std::string mcr_mod_name(const std::string& fn)
{
  int end = fn.find("(");
  int start   = fn.find(" ");

  int nsp = fn.rfind("::", end), nsp2 = 0;
  if(nsp != -1) {
    nsp2 = fn.rfind("::", nsp - 2);
    if(nsp2 != -1) start = nsp2 + 1;
    else start = nsp + 1;
  }

  return fn.substr(start + 1, end - start - 1);
}

#define __CLASS_NAME__ mcr_mod_name(__PRETTY_FUNCTION__)

/* START VA_SELECT */
#define CAT(S1, S2) S1 ## S2
#define SELECT( NAME, NUM ) CAT( NAME ## _, NUM )

#define GET_COUNT( _1, _2, _3, _4, _5, _6 /* ad nauseam */, COUNT, ... ) COUNT
#define VA_SIZE( ... ) GET_COUNT( __VA_ARGS__, 6, 5, 4, 3, 2, 1 )

#define VA_SELECT( NAME, ... ) SELECT( NAME, VA_SIZE(__VA_ARGS__) )(__VA_ARGS__)
/* END VA_SELECT */

#ifdef RTX_LOGGING
#define RTXLOG( ... ) VA_SELECT( _RTXLOG, __VA_ARGS__ )
#define _RTXLOG_1(msg) gLogger.mod_log(__CLASS_NAME__, msg, LOG_INFO)
#define _RTXLOG_2(msg, lev) gLogger.mod_log(__CLASS_NAME__, msg, lev)
#define _RTXLOG_3(nsp, msg, lev) gLogger.mod_log(nsp, msg, lev)
#else
#undef RTXLOG
#define RTXLOG( ... )
#endif

class TuumLogger
{
public:
  enum log_t {
    DEBUG = 0,
    INFO,
    WARN,
    ERR,
    LNONE
  };

  void setLogLevel(log_t);

  void beginLevelMarker(log_t);
  void endLevelMarker(log_t);

  void setColor(int);
  void clearColor();

  void mod_log(const char*, const char*, log_t=INFO);
  void mod_log(const std::string, const char*, log_t=INFO);
  void mod_log(const std::string, const std::string, log_t=INFO);

  static std::string get_llev_string(log_t lev) {
    switch(lev) {
      case DEBUG:
        return std::string("DBG");
      case INFO:
        return std::string("INFO");
        break;
      case WARN:
        return std::string("WARN");
        break;
      case ERR:
        return std::string("ERR");
        break;
    }
    return std::string("?");
  }

  TuumLogger();
private:
  log_t log_level;

  uint32_t flush_delay;
};

/** Global logger handle **/
extern TuumLogger gLogger;

#endif // TUUM_LOGGER_H
