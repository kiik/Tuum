/** @file platform.hpp
 *  General computer-platform related functionalities.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 27. November 2015
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#include <unistd.h>
#include <stdint.h>

#include "platform.t.hpp"

size_t millis();
long long micros();

struct Timer {
  unsigned long int _start = 0;
  unsigned long int period;
  unsigned long int _end = 0;

  void start() {
    _start = millis();
    _end = _start + period;
  }

  bool isTime() {
    return millis() >= _end;
  }

  void setPeriod(uint32_t T) {
    period = T;
  }

  void trigger() {
    _end = millis();
  }

};

#include "tuum_logger.hpp"

#endif
