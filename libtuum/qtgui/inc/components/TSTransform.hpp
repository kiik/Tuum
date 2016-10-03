/** @file TSTansform.hpp
 *  @brief 3D Transform component.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#ifndef TS_TRANSFORM_H
#define TS_TRANSFORM_H

#include "3dcore/TSObjectBase.hpp"

namespace tuum { namespace ts {

  class Tansform {
  public:

    Tansform();

    static TSOType type;
    virtual TSOType* getType() const;
  private:

  };

}}

#endif
