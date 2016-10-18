
#include "lpx_iformat.hpp"

namespace tuum { namespace lpx {

  img_t rgb_to_jpg(img_buf_t buf) {
    return Gdk::Pixbuf::create_from_data((const guint8*)buf.data, Gdk::COLORSPACE_RGB, false, 8, (int) buf.width, (int)buf.height, (int)buf.width * 3);
  }

}}
