/** @file Hardware.cpp
 *  Platform Hardware class implementation.
 *
 *  @authors Ants-Oskar Mäesalu, Kristjan Kanarbik, Meelik Kiik
 *  @version 0.1
 *  @date 5 December 2015
 */

#include <iostream>
#include <fstream>

#include "tuum_platform.hpp"

#include "Hardware.hpp"

namespace tuum { namespace hal {

  const RTX485::DeviceID RTX_MAIN_BOARD_ID = 0;

  Hardware::Hardware():
    m_frontCamera(nullptr),
    m_backCamera(nullptr)
  {

  }

  void Hardware::init() {
    std::ifstream frontCameraDevice(gC.getStr("Vision.FirstCamera"));
    if (frontCameraDevice.good())
      m_frontCamera = new Camera(gC.getStr("Vision.FirstCamera"), CAMERA_WIDTH, CAMERA_HEIGHT);
    if(m_frontCamera != nullptr) m_frontCamera->setup();

    std::ifstream backCameraDevice(gC.getStr("Vision.SecondCamera"));
    if (backCameraDevice.good())
      m_backCamera = new Camera(gC.getStr("Vision.SecondCamera"), CAMERA_WIDTH, CAMERA_HEIGHT);

    if(gC.getStr("HW.Active") == "Y") {
      printf("[Hardware::init]Loading hardware...\n");
      HWBus.init(gC.getStr("HWBus.Port").c_str(), gC.getInt("HWBus.Baud"));
      //m_refereeListener.init(gC.getStr("RefModule.Port").c_str(), gC.getInt("RefModule.Baud"));

      m_motorControl.init(hw_bus_write);
      //m_mainBoard.init(hw_bus_write, hw_bus_register);
    } else {
      printf("[Hardware::init]Hardware not active.\n");
    }
  }

  void Hardware::setup() {
  }

  void Hardware::process() {
    if(m_frontCamera != nullptr) m_frontCamera->process();

    m_mainBoard.run();
  }

  Camera* Hardware::getCamera() {
    return m_frontCamera;
  }

  Camera* Hardware::getFrontCamera() {
    return m_frontCamera;
  }

  Camera* Hardware::getBackCamera() {
    return nullptr;//m_backCamera;
  }

  MainBoard* Hardware::getMainBoard() {
    return &m_mainBoard;
  }

  MotorControl* Hardware::getMotorControl() {
    return &m_motorControl;
  }

  RefereeListener* Hardware::getRefListener() {
    return &m_refereeListener;
  }

}}
