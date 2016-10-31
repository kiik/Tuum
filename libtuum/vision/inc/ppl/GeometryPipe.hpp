
#ifndef TUUM_GEOMPIPE_H
#define TUUM_GEOMPIPE_H

#include "tuum_ogl.hpp"

#include "ppl/PipeBase.hpp"

namespace tuum { namespace vision {

  class GeometryPipe : public PipeBase
  {
  public:
    GeometryPipe();

    int init();

    int pass(image_t&);
  };

}}

#endif
