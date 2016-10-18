/** @file MotorDriver.cpp
 *  Description placeholder.
 *
 *  @authors Meelik Kiik
 *  @version 0.2
 */

#include <iostream>

#include "MotorDriver.hpp"

namespace tuum { namespace hal {

  MotorDriver::MotorDriver(int id, int port) {
    m_id = id;
    m_port = port;
  }

  void MotorDriver::sendcmd(std::string cmd) {
    //write(m_port, cmd.c_str(), cmd.size());
  }

  std::string MotorDriver::readLine() {
    int res;
    char buf[255];
    res = read(m_port,buf,255);
    return buf;
  }

  void MotorDriver::setSpeed(int newSpeed) {
    //std::string speedcmd = std::to_string(motorid) + ":sd" + std::to_string(newSpeed) + "\n";
    //write(m_port, speedcmd.c_str(), speedcmd.size());
  }

  void MotorDriver::stop() {
    //std::string speedcmd = std::to_string(motorid) + ":sd" + std::to_string(0) + "\n";
    //write(m_port, speedcmd.c_str(), speedcmd.size());
  }

}}
