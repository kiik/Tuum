
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/asio.hpp>

#include <gdk/gdk.h>

#include "tuum_lpx.hpp"
#include "tuum_visioning.hpp"

//#include "tuum-v9.hpp"

#include "application.hpp"

using namespace boost;
using namespace boost::asio;
using namespace boost::system;
using namespace tuum;

namespace usr {

  void sys_init() {
    tuum::hal::setup();

    tuum::lpx::init();
    tuum::lpx::setup();

    tuum::Visioning::setup();
  }

  void sys_main() {
    while(1) {
      tuum::hal::process();
      tuum::lpx::process();

      tuum::Visioning::process();
    }
  }

  int main(int argc, char* argv[]) {
    sys_init();

    //tuum::v9::setup();

    while(1) {
      sys_main();
    }

    return 0;
  }

}
