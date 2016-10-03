/** @file application.cpp
 *  Hardware abstraction layer test application
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 10. September 2016
 */

#include "application.hpp"
#include <iostream>

using namespace std;
using namespace tuum;

namespace usr {

  int main(int argc, char* argv[]) {
    printf("main(): Hardware abstraction layer test application.\n");

    // Initialize hardware
    tuum::hal::setup();


    bool running = true;
    while(running) {
      tuum::hal::process();

    }

    return 0;
  }

}
