/** @file ImageStream.hpp
 *  @brief Generic image stream class.
 *
 * @authors Meelik Kiik
 * @date 18. October 2016
 * @version 0.1
 */

#ifndef TUUM_IMSTREAM_H
#define TUUM_IMSTREAM_H

#include <cstring>
#include <stdint.h>

#include "StreamBase.hpp"

namespace tuum {

  class ImageStream : public StreamBase<image_t>
  {
  public:
    ImageStream();
    ImageStream(size_t, size_t, size_t = 3);

    int init(size_t, size_t, size_t);

    size_t getWidth() { return m_width; }
    size_t getHeight() { return m_height; }
    size_t getStride() { return m_stride; }

    size_t getSeq() { return m_seq; }
    void incSeq() { m_seq++; }

    const image_t& getFrame();
    image_t getFrameCopy();

  protected:
    size_t m_width, m_height, m_stride;
    size_t m_seq;
  };

}

#endif
