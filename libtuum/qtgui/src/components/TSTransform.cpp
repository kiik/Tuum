/** @file TSTansform.cpp
 *  @brief 3D Transform component implementation.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#include "components/TSTransform.hpp"

namespace tuum { namespace ts {

  TSOType Tansform::type;

  Tansform::Tansform() {

  }

  TSOType* Tansform::getType() const {
    return &Tansform::type;
  }

}}
