/** @file Transform.cpp
 *  Object positional transform state class implementation.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 19. November 2015
 */

#ifndef RTX_TRANSFORM_H
#define RTX_TRANSFORM_H

#include <string>
#include <math.h>

#include "Vec.hpp"

namespace tuum {

  struct Transform {
    Vec2i pos;
    double o;

    Transform();

    Transform(const int, const int);
    Transform(const Vec2i);

    Transform(const int, const int, const double);
    Transform(const Vec2i, const double);

    void setPosition(const int, const int);
    void setPosition(const Vec2i);
    void setOrientation(const double);

    Vec2i getPosition();
    double getOrientation();

    int getX();
    int getY();

    double distanceTo(Vec2i);

    Vec2i operator-(int);
    Transform operator-(Transform);

    std::string toString();
  };

}

#endif // RTX_TRANSFORM_H
