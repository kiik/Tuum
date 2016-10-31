/** @file vision_feat.hpp
 *  @brief Vision features extraction module.
 *
 * @authors Meelik Kiik
 * @date 27. October 2016
 * @version 0.1
 */

#ifndef VISION_FEAT_H
#define VISION_FEAT_H

#include "tuum_vision.hpp"

#include "vision_data.hpp"

//TODO: Generic feature specification system.
namespace tuum { namespace vision {

  int parse_balls(const PixelGeometry&, PixelFeatures&);
  int parse_goals(const PixelGeometry&, PixelFeatures&);
  int parse_robots(const PixelGeometry&, PixelFeatures&);

}}

#endif
