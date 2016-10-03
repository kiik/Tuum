/** @file   tuum_logger.cpp
 *  @brief  TuumLogger implementation.
 *
 *  @author Meelik Kiik (kiik.meelik@gmail.com)
 *  @date   July, 2015
 */

#include <iostream>

#include "platform.hpp"
#include "tuum_logger.hpp"


TuumLogger::TuumLogger() {
  log_level = DEBUG;
}

void TuumLogger::setLogLevel(log_t l) { log_level = l; }

void TuumLogger::beginLevelMarker(log_t lev) {
  int color = 0;
  switch(lev) {
    case ERR:
      color = 91;
      break;
    case INFO:
      color = 32;
      break;
    case WARN:
      color = 93;
      break;
    default:
      return;
  }

  setColor(color);
}

void TuumLogger::endLevelMarker(log_t lev) {
  clearColor();
}

void TuumLogger::mod_log(const std::string nsp, const std::string msg, log_t lev) {
#ifdef RTX_LOGGING
  mod_log(nsp.c_str(), msg.c_str(), lev);
#endif
}

void TuumLogger::mod_log(const std::string nsp, const char* msg, log_t lev) {
#ifdef RTX_LOGGING
  mod_log(nsp.c_str(), msg, lev);
#endif
}

void TuumLogger::mod_log(const char* nsp, const char* msg, log_t lev) {
#ifdef RTX_LOGGING
  if(lev < log_level) return;

  printf("%lu:", millis());

  beginLevelMarker(lev);
  std::cout << get_llev_string(lev);
  endLevelMarker(lev);

  printf(":");
  setColor(96);
  printf("%s", nsp);
  clearColor();

  printf(": %s\n", msg);
#endif
}

void TuumLogger::setColor(int c) {
  printf("\033[%im", c);
}

void TuumLogger::clearColor() {
  printf("\033[0m");
}

/** Global logging object **/
TuumLogger gLogger;
