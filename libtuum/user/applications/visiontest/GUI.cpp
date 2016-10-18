/**
 *  @file GUI.cpp
 *  Vision testing application GUI interface class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 21 November 2015
 */

#include "GUI.hpp"

#include "cameraConstants.hpp"

#include <iostream> // TODO: Remove

using namespace tuum::hal;

namespace tuum {

  GUI::GUI(int &argc, char *argv[], Camera *camera) {
    // Attach command line parameters
    this->argc = argc;
    this->argv = argv;

    // Attach camera information
    this->camera = camera;

    // Create gtkmm application
    gtkApplication = Gtk::Application::create(argc, argv);

    // Create window
    window = new MainWindow(this);

    // Create initial image
    initialiseImage();

    window->initialise();
  }

  GUI::~GUI() {
    // TODO: Delete window?
  }

  void GUI::initialiseImage() {
    image = Gdk::Pixbuf::create_from_file("frame.ppm"); // TODO: Remove association with files
    //image = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, false, 8, (int) image->get_width(), (int) image->get_height());
  }

  Glib::RefPtr<Gtk::Application> GUI::getGtkApplication() const {
    return gtkApplication;
  }

  MainWindow* GUI::getWindow() const {
    return window;
  }

  Camera* GUI::getCamera() const {
    return camera;
  }

  Frame* GUI::getFrame() {
    return &frame;
  }

  Glib::RefPtr<Gdk::Pixbuf> GUI::getImage() const {
    return image;
  }

  int GUI::run() {
    // Show windows and return when closed
    return gtkApplication->run(*window);
  }

  bool GUI::updateFrame() {
    //while(camera->requestFrame(frame) < 0) {};
    frame = camera->getFrame();
    rgbFrame = toRGB(frame);
    image = Gdk::Pixbuf::create_from_data((const guint8*) rgbFrame.data, Gdk::COLORSPACE_RGB, false, 8, (int) rgbFrame.width, (int) rgbFrame.height, (int) rgbFrame.width * 3);
    window->getImageArea()->queue_draw();
    return true;
  }

}
