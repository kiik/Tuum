/** @file TSObjectBase.hpp
 *  @brief Tuum Scene objects' base class.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#ifndef TS_OBJECT_BASE_H
#define TS_OBJECT_BASE_H

namespace tuum { namespace ts {

  class TSEntity;

  struct TSOType {};

  class TSOBase {
  public:
    virtual void update() {};
    virtual void render() {};
    virtual void draw() {};

    virtual TSOType* getType() const = 0;
  };

}}

#endif
