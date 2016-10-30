/** @file tuum_navigation.hpp
 *  Navigation system interface.
 *
 *  @authors Meelik Kiik
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.2
 *  @date 2 December 2015
 */

#ifndef RTX_NAVIGATION_H
#define RTX_NAVIGATION_h

#include "rtxmath.hpp"

#include "Ball.hpp"
#include "Goal.hpp"
#include "Robot.hpp"

namespace tuum { namespace Navigation {

  void preProcess();

  int countValidBalls();

  Transform calcBallPickupPos(Transform*);
  Transform calcGoalPos(Transform*);
  
  Vec2i calcGoalShootPos(Transform*);

  Ball* getNearestBall();

  Goal* getOpponentGoal();

  Goal* getAllyGoal();

  Robot* getAlly();

}}

#endif // RTX_NAVIGATION_H
