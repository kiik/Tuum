
#ifndef USR_H
#define USR_H

#include "application.hpp"

#include "hal.hpp"

#include "ProgramModule.hpp"

namespace usr {

  class ModularityTestProgram : public tuum::ProgramModule {

    int init();
    int setup();
    int process();

  };

}

#endif
