/** @file htgui.cpp
 *  UI module interface.
 *
 *  @authors Meelik Kiik
 *  @version 0.2
 *  @date 10. September 2016
 */

#include "htgui.hpp"

namespace tuum { namespace gui {

  int startup(int argc, char *argv[])
  {
    tuum::wsocks::setup();
    tuum::wsocks::start();

    return 0;
  }

}}
