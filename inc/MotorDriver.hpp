/** @file MotorDriver.hpp
 *  Description placeholder.
 *
 *  @authors Meelik Kiik
 *  @version 0.2
 */

#ifndef TUUM_MOTDRV_H
#define TUUM_MOTDRV_H

#include <iostream>

#include "RTX485.hpp"

namespace tuum { namespace hal {

  class MotorDriver : public RTX485::Device
  {
  public:
    MotorDriver(int, int);

    void sendcmd(std::string);

    std::string readLine();

    void setSpeed(int);
    void stop();

  private:
    int m_id, m_port;
  };

}}

#endif
