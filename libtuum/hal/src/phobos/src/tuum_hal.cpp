/** @file tuum_hal.cpp
 *  Hardware platform module.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 */

#include "tuum_hal.hpp"

namespace tuum { namespace hal {

  Hardware hw;

  Timer senseTimer;

  void setup() {
    hw.init();

    senseTimer.setPeriod(3000);
    senseTimer.start();
  }


  void process() {
    if(senseTimer.isTime()) {
      hw.getMainBoard()->senseBall();
      senseTimer.start();
    }
    hw.run();
  }

}}
