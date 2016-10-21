

#ifndef TUUM_LPX_H
#define TUUM_LPX_H

#include "tuum_buff.hpp"

namespace tuum { namespace lpx {

  int pipeline_pass(image_t);

  void init();
  void setup();
  void process();

}}

#endif
