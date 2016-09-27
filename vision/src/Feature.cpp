/**
 * @file Feature.cpp
 * Field feature seen on the camera.
 *
 * @authors Ants-Oskar Mäesalu
 * @version 0.1
 */

#include "Feature.hpp"


namespace tuum {

  Feature::Feature(const Feature &other):
    distance{other.getDistance()},
    angle{other.getAngle()},
    type{other.getType()}
  {
    // Nothing to do here
  }

  Feature::Feature(const unsigned int &distance, const double &angle,
                   const FeatureType &type):
    distance{distance},
    angle{angle},
    type{type}
  {
    // Nothing to do here
  }

  Feature::~Feature() {
    // Nothing to do here
  }

  std::pair<unsigned int, double> Feature::getDeltaVector() const {
    return std::pair<unsigned int, double>(distance, angle);
  }

  unsigned int Feature::getDistance() const {
    return distance;
  }

  double Feature::getAngle() const {
    return angle;
  }

  FeatureType Feature::getType() const {
    return type;
  }

  void Feature::setDistance(const unsigned int &distance) {
    this->distance = distance;
  }

  void Feature::setAngle(const double &angle) {
    this->angle = angle;
  }

  void Feature::setType(const FeatureType &type) {
    this->type = type;
  }

  bool Feature::isBlob() const {
    return type == BLOB;
  }

  bool Feature::isLine() const {
    return type == LINE;
  }

  bool Feature::isCorner() const {
    return type == CORNER;
  }

};
