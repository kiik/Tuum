
#include <gtkmm.h>

#include "tuum_logger.hpp"
#include "tuum_lpx.hpp"
#include "tuum_ogl.hpp"

namespace tuum { namespace lpx {

  Glib::RefPtr<Gtk::Application> gtkApp;

  void init() {
    ogl_init();

    auto gtkApp = Gtk::Application::create();
  }

  void setup() {
    ogl_setup();
  }

  void process() {
    ogl_process();
  }

}}
