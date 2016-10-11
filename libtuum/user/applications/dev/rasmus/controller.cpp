
#include <iostream>

#include "controller.hpp"

namespace tuum {

  MyController::MyController(Context _ctx, std::string input):
    m_tekst(input), ctx(_ctx)
  {

  }

  int MyController::run(){
    std::cout << m_tekst << std::endl;

    if(std::string(m_tekst) == "C2") {
      ctx.stm->setup();
    }

    return 0;
  }

  void MyController::init() {

  }

  bool MyController::isRunnable() {
    return true;
  }

}
