
#include "lpx_iformat.hpp"

namespace tuum { namespace lpx {

  buffer_t rgb_to_jpg(const img_buf_t& buf) {
    img_t img = Gdk::Pixbuf::create_from_data((const guint8*)buf.data, Gdk::COLORSPACE_RGB, false, 8, (int) buf.width, (int)buf.height, (int)buf.width * 3);
    buffer_t out(new buf_t());

    img->save_to_buffer(out->getValue<gchar*&>(), out->size, "jpeg");

    return out;
  }

}}
