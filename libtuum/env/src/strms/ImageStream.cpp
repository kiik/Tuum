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
    m_iprop({0, 0, 0, 0})
  {

  }

  ImageStream::ImageStream(const img_prop_t& iprop)
  {
    init(iprop);
  }

  int ImageStream::init(const img_prop_t& iprop)
  {
    m_iprop = iprop;
    int res = StreamBase<image_t>::init(m_iprop.getSize());
    if(res < 0) return res;

    m_b1->setFormat(m_iprop);
    m_b2->setFormat(m_iprop);
    return res;
  }

  int ImageStream::initBuf(image_t& in)
  {
    in->init(getSize());
    in->setFormat(m_iprop);
    return 0;
  }

  const image_t& ImageStream::getFrame()
  {
    return m_fr;
  }

  image_t ImageStream::getFrameCopy()
  {
    image_t out(new img_buf_t(m_iprop));

    if(!m_init) {
      memset(out->data, 255, m_size);
    } else {
      std::shared_ptr<buf_base_t> src = m_fr, dst = out;
      src->paste(&(*dst));
    }

    out->setFormat(m_iprop);
    out->id = getSeq();

    return out;
  }

  int ImageStream::read(image_t out) {
    out->init(getSize());
    out->setFormat(m_iprop);
    out->id = getSeq();

    return StreamBase<image_t>::read(out->data, out->size);
  }

}
