/** @file application.cpp
 *  Robotex Teamfootball application.
 *
 *  @authors Meelik Kiik
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 3 December 2015
 */

#include <thread>
#include <iostream> // TODO: Remove

#include "application.hpp"
#include "rtx_fb.hpp"

using namespace std;
using namespace tuum;


int main(int argc, char *argv[]) {
  printf("main(): Tuum Robotex 1vs1 application.\n");
  tuum::init(argc, argv);
  tuum::hal::setup();

  Visioning::setup();
  Localization::setup();
  Motion::setup();

  FBLogic::setup();

  bool running = true;
  while(running) {
    hal::process();

    Visioning::process();
    Navigation::preProcess();

    Localization::process();

    Motion::process();

    FBLogic::process();
  }

  return 0;
}
