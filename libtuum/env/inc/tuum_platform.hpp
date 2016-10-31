/** @file tuum_platform.hpp
 *  General application dependencies module.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 27. November 2015
 */

#ifndef TUUM_PLATFORM_H
#define TUUM_PLATFORM_H

#include "tuum_logger.hpp"
#include "tuum_configuration.hpp"

#include "ProgramModule.hpp"

#include "motion.hpp"

namespace tuum {

  // Global configuration object
  extern Configuration gC;

  int init(int argc, char *argv[]);

}

namespace usr {

  extern tuum::ProgramModule* gTuumProgram;

}

#endif
