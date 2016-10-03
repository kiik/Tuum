/**
 *  @file Application.cpp
 *  Color calibration application class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 17 November 2015
 */

#include "Application.hpp"

#include "cameraConstants.hpp"

#include <gtkmm.h>
#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <gdkmm/pixbuf.h>
#include <glibmm/refptr.h>
#include <glibmm/fileutils.h>

#include <fstream>
#include <iostream> // TODO: Remove


namespace tuum {

  Application::Application(int &argc, char *argv[], Camera *camera):
    mask(8, CAMERA_WIDTH, CAMERA_HEIGHT),
    filter(8)
  {
    // Attach command line parameters
    this->argc = argc;
    this->argv = argv;

    // Attach camera information
    this->camera = camera;

    // Initialise modes
    modes = {"Ball", "Blue goal", "Yellow goal", "Field", "White line", "Black line", "Checkerboard white", "Checkerboard black"}; // TODO: Read from file
    mode = 0;

    // Initialise properties
    playing = true;
    masking = false;

    // Create gtkmm application
    gtkApplication = Gtk::Application::create(argc, argv);
    std::cout << "1" << std::endl;

    // Create window
    window = new MainWindow(this);
    std::cout << "2" << std::endl;

    // Create initial image
    initialiseImage();
    std::cout << "3" << std::endl;

    window->initialise();
    std::cout << "4" << std::endl;
  }

  Application::~Application() {
    std::cout << "5" << std::endl;
    // TODO: delete window;
    std::cout << "6" << std::endl;
  }

  void Application::initialiseImage() {
    image = Gdk::Pixbuf::create_from_file("frame.ppm"); // TODO: Remove association with files
    //image = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, false, 8, (int) image->get_width(), (int) image->get_height());
  }

  Glib::RefPtr<Gtk::Application> Application::getGtkApplication() const {
    return gtkApplication;
  }

  MainWindow* Application::getWindow() const {
    return window;
  }

  Camera* Application::getCamera() const {
    return camera;
  }

  Frame* Application::getFrame() {
    return &frame;
  }

  Glib::RefPtr<Gdk::Pixbuf> Application::getImage() const {
    return image;
  }

  bool Application::isPlaying() const {
    return playing;
  }

  bool Application::isMasking() const {
    return masking;
  }

  const std::vector<std::string>& Application::getModes() {
    return modes;
  }

  unsigned int Application::getMode() const {
    return mode;
  }

  Mask* Application::getMask() {
    return &mask;
  }

  Filter* Application::getFilter() {
    return &filter;
  }

  void Application::setPlaying(const bool &value) {
    if (value) {
      setMasking(false);
      filter.addBuffersToFilter();
    }
    window->setPlaying(value);
    playing = value;
  }

  void Application::setMasking(const bool &value) {
    if (value) {
      if (!isMasking()) {
        setPlaying(false);
      }
    } else {
      mask.reset();
      window->getMaskingArea()->resetDrawingModes();
    }
    masking = value;
  }

  void Application::setMode(const unsigned int &value) {
    mode = value;
  }

  void Application::sendMasksToFilter() {
    filter.addMasksToBuffers(frame, mask.getAdditionValues(), mask.getRemovalValues());
  }

  void Application::readFilterFromFile(const std::string &fileName) {
    // TODO
  }

  void Application::saveFilterToFile(const std::string &fileName) {
    // TODO: Refactor filter transformation instructions
    setPlaying(true);
    setPlaying(false);

    // Output information to file
    std::ofstream outputFile(fileName);
    outputFile << filter.getString();
    outputFile.close();
  }

  int Application::run() {
    std::cout << "Running application..." << std::endl;
    // Show windows and return when closed
    return gtkApplication->run(*window);
  }

  bool Application::updateFrame() {
    std::cout << "Application->updateFrame()" << std::endl;
    if (!playing) {
      return false;
    }
    frame = camera->getFrame();
    rgbFrame = toRGB(frame);
    // TODO: window->updateFrame(&frame, &rgbFrame);
    window->getMaskingArea()->redraw();
    window->getPreviewArea()->queue_draw();
    return true;
  }

}
