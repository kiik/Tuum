/** @file Vec.hpp
 *  Mathemathical vectors.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 19. November 2015
 */

#ifndef RTX_VEC_H
#define RTX_VEC_H

#include <iostream>
#include <sstream>

namespace tuum {

  template<typename T>
  struct Vec2D {
    T x; T y;

    void rotate(double alpha) {
      Vec2D v;
      v.x = x * cos(alpha) + y * -sin(alpha);
      v.y = x * sin(alpha) + y * cos(alpha);
      x = v.x; y = v.y;
    }

    void normalizeTo(double value) {
      double s = abs(x) + abs(y);
      if(s == 0) return;
      x /= s;
      y /= s;
    }

    double getMagnitude() {
      if(x == 0.0 && y == 0.0) return 0.0;
      return sqrt(pow(x, 2) + pow(y, 2));
    }

    double distanceTo(Vec2D<T> t) {
      Vec2D<T> vec = {t.x - x, t.y - y};
      return vec.getMagnitude();
    }

    double getOrientation() {
      double o = atan2(y, x);
      return o;
    }

    Vec2D<double> getNormalized() {
      double s = abs(x) + abs(y);
      if(s == 0) return Vec2D<double>({0, 0});
      return Vec2D<double>({(double)x / s, (double)y / s});
    }

    //FIXME:
    void extend(T val) {
      int sign = x < 0 ? -1 : 1;
      x += val*sign;
      sign = y < 0 ? -1 : 1;
      y += val*sign;
    }

    void scale(double val) {
      x *= val; y*= val;
    }

    Vec2D<int> toInt() {
      return Vec2D<int>({(int)x, (int)y});
    }

    Vec2D<T> operator+(Vec2D<T> vec) {
      return Vec2D<T>({x + vec.x, y + vec.y});
    }

    Vec2D<T> operator-(Vec2D<T> vec) {
      return Vec2D<T>({x - vec.x, y - vec.y});
    }

    Vec2D<T> operator*(T val) {
      return Vec2D<T>({(T)(x*val), (T)(y*val)});
    }


    //FIXME:
    static Vec2D<T> fromOrientation(double o, T mag = 100) {
      return Vec2D<T>({mag*(T)acos(o), mag*(T)(asin(o))});
    }

    std::string toString() {
      std::stringstream out;
      out << "<Vec2D "
          << x << ", "
          << y << ">";
      return out.str();
    }
  };

  template<typename T>
  struct Vec3D {
    T x; T y; T z;
  };

  typedef Vec2D<int> Vec2i;
  typedef Vec3D<int> Vec3i;

  typedef Vec2D<double> Vec2f;
  typedef Vec3D<double> Vec3f;
}

#endif // RTX_VEC_H
