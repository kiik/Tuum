/** @file application.cpp
 *  Vision testing application.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 21 November 2015
 */

#include "application.hpp"
#include "GUI.hpp"

#include <thread>
#include <iostream> // TODO: Remove

using namespace std;
using namespace tuum;

static void run(GUI *gui) {
  bool running = true;
  while(running) {
    tuum::hal::process();

    Visioning::process();
    Navigation::preProcess();
    Localization::process();

    gui->updateFrame();
  }
}

namespace usr {

  int main(int argc, char *argv[]) {
    printf("main(): Tuum vision test application.\n");

    // Initialise constants
    tuum::init(argc, argv);

    // Initialize hardware
    tuum::hal::setup();

    // Initialize system modules
    Visioning::setup();
    Localization::setup();

    GUI gui(argc, argv, hal::hw.getFrontCamera());

    std::thread applicationThread(run, &gui);

    applicationThread.detach();

    return gui.run();
  }

}
