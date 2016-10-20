
#include <iostream>
#include <cmath>

#include "tuum_logger.hpp"

#include "MotorControl.hpp"

namespace tuum { namespace hal {

  const char CMD_MOTOR_SPEED[] = "sd";

  MotorControl::MotorControl():
    RTX485::Device::Device()
  {

  }

  void MotorControl::init(RTX485::WriteHandle wHandle) {
    int id_seq, ix;
    for(ix=0, id_seq=1; ix < MOTOR_COUNT; ix++, id_seq++) {
      m_motorIDs[ix] = id_seq;
    }

    RTX485::Device::init(wHandle);

    RTXLOG("Ready.");
  }


  std::string MotorControl::getSpeedCmd(int v) {
    std::stringstream out;
    out << CMD_MOTOR_SPEED;
    out << v;
    return out.str();
  }

  void MotorControl::omniDrive(float spd, float dir, float rot) {
    /**
    int spd1 = speed * sin(angle + M_PI / 4.0) + rot;
    int spd2 = speed * -sin(angle - M_PI / 4.0) + rot;
    int spd3 = speed * -sin(angle + M_PI / 4.0) + rot;
    int spd4 = speed * sin(angle - M_PI / 4.0) + rot;

    int speeds[4] = {spd1, spd2, spd3, spd4};
    for (int ix=0; ix < MOTOR_COUNT; ix++) {
      send({m_motorIDs[ix], getSpeedCmd(speeds[ix])});
      usleep(10);
    }*/

    // cm / s, radians, deg / s
    send({1, format("om,%.2f,%.2f,%.2f", (spd / 10.0), dir, rot)});
  }

  void MotorControl::stop() {
    for (int ix=0; ix < MOTOR_COUNT; ix++) {
      send({m_motorIDs[ix], getSpeedCmd(0)});
      usleep(10);
    }
  }

}}
