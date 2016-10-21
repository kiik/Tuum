
#ifndef TUUM_OGL_H
#define TUUM_OGL_H

#include "tuum_buff.hpp"
#include "tuum_streams.hpp"

namespace tuum { namespace lpx {

  int ogl_init();

  void ogl_setup();
  void ogl_process();

  int ogl_test();

  void ogl_set_input(ImageStream*);
  int ogl_read_frame(image_t&);

  int pipeline_pass(image_t&);

}}

#endif
