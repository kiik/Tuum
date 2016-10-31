/** @file vision_geom.hpp
 *  @brief Vision pixel geometry extraction module.
 *
 * @authors Meelik Kiik
 * @date 27. October 2016
 * @version 0.1
 */

#ifndef VISION_GEOM_H
#define VISION_GEOM_H

#include "tuum_buff.hpp"

#include "vision_data.hpp"

namespace tuum { namespace vision {

  int parse_blobs(const image_t, vision::PixelGeometry&);
  int parse_lines(const image_t, PixelGeometry&);
  int parse_corners(const image_t, PixelGeometry&);

}}

#endif
