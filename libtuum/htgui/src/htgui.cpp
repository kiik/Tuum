/** @file htgui.cpp
 *  UI module interface.
 *
 *  @authors Meelik Kiik
 *  @version 0.2
 *  @date 10. September 2016
 */

#include "htgui.hpp"

namespace tuum { namespace gui {

  int register_server(wsocs::WebSocketServer* srv) {
    return wsocs::register_server(srv);
  }

  int startup(int argc, char *argv[])
  {
    wsocs::setup();
    wsocs::start();

    return 0;
  }

}}
