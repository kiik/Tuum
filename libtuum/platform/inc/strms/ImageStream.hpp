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
    ImageStream(const img_prop_t&);

    int init(const img_prop_t&);

    const img_prop_t& getFormat() { return m_iprop; }

    const image_t& getFrame();
    image_t getFrameCopy();

    int read(image_t);

  protected:
    img_prop_t m_iprop;
  };

}

#endif
