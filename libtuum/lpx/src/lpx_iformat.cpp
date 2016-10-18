
#include "lpx_iformat.hpp"

namespace tuum { namespace lpx {

  Glib::RefPtr<Gdk::Pixbuf> img;

  image_t rgb_to_jpg(image_t in) {
    img = Gdk::Pixbuf::create_from_data((const guint8*)in->data, Gdk::COLORSPACE_RGB, false, 8, (int) in->width, (int)in->height, (int)in->width * 3);

    image_t out(new img_buf_t());
    out->setDimensions(*in);
    img->save_to_buffer((gchar*&)out->data, out->size, "jpeg");

    return out;
  }

}}
