/** @file ImageStream.cpp
 *  @brief Generic image stream implementation.
 *
 * @authors Meelik Kiik
 * @date 18. October 2016
 * @version 0.1
 */

#include "strms/ImageStream.hpp"

namespace tuum {

  ImageStream::ImageStream():
    m_width(0), m_height(0), m_stride(0)
  {

  }

  ImageStream::ImageStream(size_t w, size_t h, size_t s)
  {
    init(w, h, s);
  }

  int ImageStream::init(size_t w, size_t h, size_t s)
  {
    m_width = w;
    m_height = h;
    m_stride = s;
    int res = StreamBase<image_t>::init(w * h * s);
    if(res < 0) return res;

    m_b1->setDimensions(w, h, s);
    m_b2->setDimensions(w, h, s);
    return res;
  }

  const image_t& ImageStream::getFrame()
  {
    return m_fr;
  }

  image_t ImageStream::getFrameCopy()
  {
    image_t out(new img_buf_t(m_width, m_height, m_stride));

    if(!m_init) {
      memset(out->data, 255, m_size);
    } else {
      std::shared_ptr<buf_base_t> src = m_fr, dst = out;
      src->paste(&(*dst));
    }

    return out;
  }

}
