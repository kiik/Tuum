
#include "rtex.h"

#include "tuum_platform.hpp"

#include "htgui.hpp"
#include "RobotexUIServer.hpp"

#include "application.hpp"

tuum::gui::RobotexUIServer uiSrv;

int ui_init(int argc, char* argv[]) {
  tuum::gui::startup(argc, argv);

  if(uiSrv.init() < 0) return -1;
  if(tuum::gui::register_server(&uiSrv) < 0) return -2;

  return 0;
}

int main(int argc, char* argv[]) {
  if(tuum::init(argc, argv) < 0) return -1;

  if(ui_init(argc, argv) < 0) RTXLOG("UI initialization failed!", LOG_ERR);

  int res = usr::main(argc, argv);
  if(res < 0) return res;

  if(usr::gTuumProgram != nullptr)
    return usr::gTuumProgram->run();
}
