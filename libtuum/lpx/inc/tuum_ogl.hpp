
#ifndef TUUM_OGL_H
#define TUUM_OGL_H

#include "tuum_buff.hpp"
#include "tuum_streams.hpp"

namespace Glip {
  namespace Modules {
    class LayoutLoader;
  }

  namespace CorePipeline {
    class Pipeline;
  }

  namespace CoreGL {
    class HdlTexture;
    class HdlTextureFormat;
  }
}

using namespace Glip::Modules;
using namespace Glip::CorePipeline;

namespace tuum { namespace lpx {

  int ogl_init();

  void ogl_setup();
  void ogl_process();

  int ogl_test();

  void ogl_set_input(ImageStream*);
  int ogl_read_frame(image_t&);

  int pipeline_pass(image_t&);

  LayoutLoader* ogl_get_loader();

}}

#endif
