/**
 * @file main.cpp
 * Color calibration application main module.
 *
 * @authors Ants-Oskar Mäesalu
 * @version 0.1
 */

#include <gtkmm/application.h>
#include <thread>
#include <ctime> // For calculating FPS

#include <iostream> // TODO: Remove

#include "hal.hpp"

#include "MainWindow.hpp"

using namespace tuum;


static void process(MainWindow *window) {
  unsigned int frameCounter = 0;
  clock_t startTime = clock();
  clock_t lastTime = startTime;
  while (true) {
    clock_t currentTime = clock();
    if (float(currentTime - lastTime) / CLOCKS_PER_SEC > 1) {
      //std::cout << "FPS: " << frameCounter << std::endl;
      frameCounter = 0;
      lastTime = currentTime;
    }
    if (window->updateFrame()) {
      frameCounter++;
    }
  }
}

int main(int argc, char *argv[]) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

  // Initialise constants
  tuum::init(argc, argv);

  // Initialise hardware
  tuum::hal::setup();

  MainWindow window(hal::hw.getFrontCamera()); // TODO: Add back camera, too

  std::thread frameThread(process, &window);
  frameThread.detach();

  // Show windows and return when closed
  return app->run(window);
}
