/**
 *  @file GUI.hpp
 *  Vision testing application GUI interface class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 21 November 2015
 */

#ifndef RTX_APPLICATIONS_VISION_TEST_GUI_H
#define RTX_APPLICATIONS_VISION_TEST_GUI_H

#include <vector>
#include <string>

#include "hal.hpp"
#include "rtxvision.h"
#include "tuum_visioning.hpp"

#include "MainWindow.hpp"

using namespace tuum::hal;

namespace tuum {

  class GUI {

    public:
      GUI(int&, char**, Camera*);
      virtual ~GUI();

      Glib::RefPtr<Gtk::Application> getGtkApplication() const;
      MainWindow* getWindow() const;

      Camera* getCamera() const;
      Frame* getFrame();

      Glib::RefPtr<Gdk::Pixbuf> getImage() const;

      int run();
      bool updateFrame();

    private:
      int argc;
      char **argv;

      Glib::RefPtr<Gtk::Application> gtkApplication;
      MainWindow *window;

      Camera *camera;
      Frame frame;
      Frame rgbFrame;

      Glib::RefPtr<Gdk::Pixbuf> image;

      void initialiseImage();

  };

}

#endif // RTX_APPLICATIONS_VISION_TEST_GUI_H
