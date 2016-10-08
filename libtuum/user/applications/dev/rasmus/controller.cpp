#include <iostream>
//#include "STM.hpp"
#include "controller.hpp"
#include <chrono>

namespace tuum {

  int getCurrentTime(){
    using namespace std::chrono;

    auto epoch = high_resolution_clock::from_time_t(0);
    auto now   = high_resolution_clock::now();
    int mseconds = duration_cast<milliseconds>(now - epoch).count();
    return mseconds;
  }

  int MyController::run(){

    int startTime = getCurrentTime();
    bool isPrinted = false;

    while(true) {

      int currentTime = getCurrentTime();
      int timeElapsed = currentTime - startTime;

      if(timeElapsed % 1000 == 0 && !isPrinted){
        isPrinted = true;
        std::cout << "It's just a prank, bro!" << std::endl;
      }
      if(isPrinted && !(timeElapsed % 1000 == 0)){
        isPrinted = false;
      }

    }
    return 0;
  }

  void MyController::init() {

  }

  bool MyController::isRunnable() {
    return true;
  }

}
