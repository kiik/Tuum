
#include <gtkmm.h>

#include "tuum_logger.hpp"

#include "tuum_db.hpp"
#include "tuum_ogl.hpp"
#include "tuum_lpx.hpp"
#include "tuum_fs.hpp"

namespace tuum { namespace lpx {

  Glib::RefPtr<Gtk::Application> gtkApp;

  void init() {
    ogl_init();

    auto gtkApp = Gtk::Application::create();
    db::init();

    run_file_tests();
  }

  void setup() {
    ogl_setup();
  }

  void process() {
    ogl_process();
  }

}}
