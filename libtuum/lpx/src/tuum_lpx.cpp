
#include <gtkmm.h>

#include "tuum_lpx.hpp"

namespace tuum { namespace lpx {

  Glib::RefPtr<Gtk::Application> gtkApp;

  void init() {
    auto gtkApp = Gtk::Application::create();
  }

  void setup() {

  }

  void process() {

  }

}}
