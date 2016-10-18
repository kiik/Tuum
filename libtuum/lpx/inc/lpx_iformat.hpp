
#ifndef TUUM_LPX_H
#define TUUM_LPX_H

#include <glib.h>
#include <gdkmm/pixbuf.h>

#include "Camera.hpp"

namespace tuum { namespace lpx {

  typedef Frame img_buf_t;
  typedef Glib::RefPtr<Gdk::Pixbuf> img_t;

  img_t rgb_to_jpg(img_buf_t);

}}

#endif
