/** @file DataStream.hpp
 *  @brief Generic data stream class.
 *
 * @authors Meelik Kiik
 * @date 18. October 2016
 * @version 0.1
 */

#ifndef TUUM_DSTREAM_H
#define TUUM_DSTREAM_H

#include <cstring>
#include <stdint.h>

#include "tuum_buff.hpp"

#include "StreamBase.hpp"

namespace tuum {

  class DataStream : public StreamBase<buffer_t>
  {
  public:
    DataStream();
    ~DataStream();

    buffer_t getData() { return m_fr; }
  };

}

#endif
