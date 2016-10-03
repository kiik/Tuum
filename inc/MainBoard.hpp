
#ifndef TUUM_MAINBOARD_H
#define TUUM_MAINBOARD_H

#include "platform.hpp"

#include "RTX485.hpp"

namespace tuum { namespace hal {

  class MainBoard : public RTX485::Device {
  private:
    bool m_ballSensorState;
    bool m_dribblerState;
    bool m_coilKickActive;

    unsigned short m_coilChargeLevel;

    Timer m_coilKickCharge;
    Timer m_coilKickCooldown;
    bool m_coilKickStrong;

    Timer m_updateTimer;

  public:
    MainBoard();

    void init(RTX485::WriteHandle wHandle, RTX485::SignalService sigRegister);
    void signal(RTX485::Message);

    void run();

    bool getBallSensorState();

    void senseBall();
    void chargeCoil();
    void releaseCoil();
    void startDribbler();
    void stopDribbler();

    void coilKick();
    void doCoilKick();
    void doWeakCoilKick();

  };

}}

#endif // RTX_MAINBOARD_H
