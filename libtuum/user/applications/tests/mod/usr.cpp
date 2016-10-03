
#include "tuum_logger.hpp"

#include "ResourceNetwork.hpp"

#include "usr.hpp"

namespace usr {

  int ModularityTestProgram::init() {

  }

  int ModularityTestProgram::setup() {

  }

  int ModularityTestProgram::process() {
    RTXLOG("Test");
    tuum::rnet_test();
  }

}
