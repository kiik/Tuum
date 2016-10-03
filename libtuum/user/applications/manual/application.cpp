
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include "application.hpp"

using namespace tuum;

namespace usr {

  void sys_init() {
    tuum::hal::setup();
  }

  void sys_main() {
    while(1) {
      tuum::hal::process();
    }
  }

  int main(int argc, char* argv[]) {
    sys_init();

    while(1) {
      sys_main();
    }

    return 0;
  }

}
