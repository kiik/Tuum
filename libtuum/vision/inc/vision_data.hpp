/** @file vision_data.hpp
 *  @brief Vision data structures.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 27. October 2016
 */

#ifndef TUUM_VISION_DATA_H
#define TUUM_VISION_DATA_H

#include <vector>

#include "Blob.hpp"
#include "Color.hpp"
#include "Feature.hpp"

namespace tuum { namespace vision {

  typedef std::vector<Blob> BlobSet;
  typedef std::vector<Feature> FeatureSet;

  typedef FeatureSet LineSet;
  typedef FeatureSet CornerSet;

  struct PixelGeometry {
    BlobSet blobs;
    LineSet lines;
    CornerSet corners;
  };

  struct PixelFeatures {
    int _placeholder;
  };

}}

#endif
