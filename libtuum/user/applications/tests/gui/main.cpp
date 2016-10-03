
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include "htgui.hpp"

#include "application.hpp"

using namespace tuum;

namespace usr {

  void sys_init() {
    tuum::hal::setup();
    //Visioning::setup();
  }

  void sys_main() {
    while(1) {
      tuum::hal::process();
      //Visioning::process();
    }
  }

  int main(int argc, char* argv[]) {
    sys_init();

    //boost::thread workerThread(sys_main);
    tuum::gui::startup(argc, argv); //htgui runs in separate thread

    while(1) {
      sys_main();
    }

    return 0;
  }

}
