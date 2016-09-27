/** @file htgui.hpp
 *  HTTP based GUI module interface.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 10. September 2016
 */

#include <iostream>

#include "wsocs.hpp"
#include "htgui.hpp"

namespace tuum { namespace gui {

  TracdroneUIServer uiSrv;

  int run(int argc, char *argv[])
  {
    tuum::wsocks::setup();

    int res = -1;
    if(uiSrv.init() >= 0) {
      res = tuum::wsocks::register_server(&uiSrv);
      if(res < 0) {
        RTXLOG("UI Server registering failed!", LOG_ERR);
      }
    }

    if(res >= 0) tuum::wsocks::start();

    return 0;
  }

}}
