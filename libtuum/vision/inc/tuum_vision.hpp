/** @file tuum_vision.hpp
 *  @brief Vision library interface module.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 27. October 2016
 */

#ifndef TUUM_VISION_H
#define TUUM_VISION_H

#include "tuum_buff.hpp"

#include "vision_data.hpp"

namespace tuum { namespace vision {

  int parseGeometry(const image_t, PixelGeometry&);
  int parseFeatures(PixelGeometry&, PixelFeatures&);

}}

#endif
