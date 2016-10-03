#include <cstdlib>
#include <iostream>
#include <string>

#include "application.hpp"

#include "rtx_ctl.hpp"

#include "hal.hpp"

#include "tuum_communication.hpp"

using namespace std;
using namespace tuum;
using namespace hal;
using namespace comm;

namespace usr {

  int main(int argc, char* argv[]) {
    RTXLOG("Running hardware modules tests...", LOG_INFO);

    hal::setup();

    bool running = true;
    while(running) {
      hal::process();
    }

    RTXLOG("Hardware modules tests done.\n", LOG_INFO);
    return 0;
  }

}
