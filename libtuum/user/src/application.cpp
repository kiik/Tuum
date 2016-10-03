/** @file application.cpp
 *  Default tuum system application.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 2. November 2015
 */

#include "application.hpp"
#include <iostream>

using namespace std;
using namespace tuum;

namespace usr {

  int main(int argc, char* argv[]) {
    printf("main(): Default tuum application.\n");

    // Initialize hardware
    tuum::hal::setup();

    // Initialize system modules
    Visioning::setup();
    Localization::setup();
    Motion::setup();

    bool running = true;
    while(running) {
      tuum::hal::process();

      Visioning::process();
      Localization::process();
      Motion::process();
    }

    return 0;
  }

}
