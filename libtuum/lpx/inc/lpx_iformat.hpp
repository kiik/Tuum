
#ifndef TUUM_LPX_H
#define TUUM_LPX_H

#include <memory>

#include <glib.h>
#include <gdkmm/pixbuf.h>

#include "Camera.hpp"

namespace tuum { namespace lpx {

  typedef std::shared_ptr<buf_t> buffer_t;

  typedef Frame img_buf_t;
  typedef Glib::RefPtr<Gdk::Pixbuf> img_t;

  buffer_t rgb_to_jpg(const img_buf_t&);

}}

#endif
