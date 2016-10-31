/** @file tuum_vision.cpp
 *  @brief Vision library interface module.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 27. October 2016
 */

#include "vision_geom.hpp"
#include "vision_feat.hpp"
#include "vision_data.hpp"

#include "tuum_vision.hpp"

namespace tuum { namespace vision {

  int parseGeometry(const image_t in, PixelGeometry& out)
  {
    int res;
    res = parse_blobs(in, out);
    if(res < 0) return -1;

    res = parse_lines(in, out);
    if(res < 0) return -2;

    res = parse_corners(in, out);
    if(res < 0) return -3;

    return 0;
  }

  int parseFeatures(const PixelGeometry& in, PixelFeatures& out)
  {
    int res;
    res = parse_balls(in, out);
    if(res < 0) return -1;

    res = parse_goals(in, out);
    if(res < 0) return -2;

    res = parse_robots(in, out);
    if(res < 0) return -3;

    return 0;
  }

}}
