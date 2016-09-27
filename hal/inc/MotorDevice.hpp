/** @file MotorDevice.hpp
 *  Base motor control interface.
 *
 *  @authors Meelik Kiik
 *  @date 10. September 2016
 *  @version 0.1
 */

#ifndef TUUM_MOTCTL_H
#define TUUM_MOTCTL_H

namespace tuum { namespace hal {

  class MotorDevice
  {
  public:

    virtual int init() {};
    virtual void process() {};

    virtual void stop() {};

  };

}}

#endif  // TUUM_MOTCTL_H
