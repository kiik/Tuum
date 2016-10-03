/**
 *  @file Goal.cpp
 *  Goal class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.2
 *  @date 2 December 2015
 */

#include "Goal.hpp"

#include "tuum_platform.hpp"


namespace tuum {

  Goal::Goal(Goal &other):
    Entity(*other.getTransform(), other.getBlob()),
    Rectangle(other.getWidth(), other.getLength())
  {
    // Nothing to do here
  }

  Goal::Goal(const Transform transform, Blob *blob, const double &width, const double &length):
    Entity(transform, blob),
    Rectangle(width, length)
  {
    // Nothing to do here
  }

  bool Goal::isAlly() const {
    std::string pattern = tuum::gC.getStr("Pattern.AllyGoal");
    if (pattern == std::string("Y")) {
      return blob->isYellow();
    } else {
      return blob->isBlue();
    }
  }

  bool Goal::isOpponent() const {
    std::string pattern = tuum::gC.getStr("Pattern.OpponentGoal");
    if (pattern == std::string("Y")) {
      return blob->isYellow();
    } else {
      return blob->isBlue();
    }
  }

}
