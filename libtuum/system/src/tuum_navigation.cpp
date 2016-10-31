/** @file tuum_navigation.cpp
 *  Navigation system implementation.
 *
 *  @authors Meelik Kiik
 *  @authros Ants-Oskar Mäesalu
 *  @version 0.2
 *  @date 2 December 2015
 */

#include "syscore/MotionData.hpp"

#include "tuum_platform.hpp"

#include "tuum_visioning.hpp"
#include "tuum_localization.hpp"
#include "tuum_motion.hpp"

#include "tuum_navigation.hpp"

// TODO: Obstacle avoidance
// TODO: Pathfinding
// TODO: No out of bounds transform target
namespace tuum {

  Navigation::Navigation(Visioning* vision):
    mVision(vision)
  {

  }

  void Navigation::init() {

  }

  void Navigation::run() {

  }

  void Navigation::updateEntities() {
    /*
    Visioning::BallSet balls = *(Visioning::ballDetect.getEntities());
    Vision::LineSet lines = Vision::getLines();
    for(Visioning::BallSet::iterator ball = balls.begin(); ball != balls.end(); ++ball) {

      // Check whether the current ball is in a goal

      // Check whether the ball is in the blue goal
      if (Visioning::blueGoal != nullptr) {

        // Check whether the ball blob is in the blue goal blob, and set the
        // ball object's parameter correspondingly
        if ((*ball)->getBlob()->isIn(*(Visioning::blueGoal->getBlob()))) {
          (*ball)->setInGoal(true);
        } else {
          (*ball)->setInGoal(false);
        } // TODO: Check if we need to do this in some situations, or if it
        // would cause problems
        // Currently, it is only implemented because of not enough tests - we do
        // not want to lose balls because they have appeared to be in a goal
        // (when they actually weren't).

      }

      // Check whether the ball is in the yellow goal
      if (Visioning::yellowGoal != nullptr) {

        // Check whether the ball blob is in the yellow goal blob, and set the
        // ball object's parameter correspondingly
        if ((*ball)->getBlob()->isIn(*(Visioning::yellowGoal->getBlob()))) {
          (*ball)->setInGoal(true);
        } else {
          (*ball)->setInGoal(false);
        } // TODO: Check if we need to do this in some situations, or if it
        // would cause problems
        // Currently, it is only implemented because of not enough tests - we do
        // not want to lose balls because they have appeared to be in a goal
        // (when they actually weren't).

      }

      // TODO: Check that the ball is not outside of a line
      for (Vision::LineSet::iterator line = lines.begin(); line != lines.end(); ++line) {

        // TODO: Check if the ball is on the other side of the current line

        // TODO: Use goals' lower bounds for checking, too, if outer lines can
        // not be detected otherwise

      }

    }
    */
  }

  int Navigation::countValidBalls() {
    /*
    int i = 0;
    for(auto& b : *Visioning::ballDetect.getEntities()) {
      if(b->isValid()) i++;
    }
    */
    return 0;
  }

  //TODO: position to relative position
  Transform Navigation::calcBallPickupPos(Transform* bt) {
    Vec2f avf = (bt->getPosition() - Localization::getTransform()->getPosition()).getNormalized();
    Transform t((*bt) - (avf*Motion::VLS_DIST.mn).toInt());
    return t;
  }

  Vec2i Navigation::calcGoalShootPos(Transform* t) {
    /*Transform me = Localization::getTransform();
    Vec2i me_p = me.getPosition();
    Vec2i g_p = t->getPosition();

    Transform target;
    // 400, 0 (n => )
    if(me_p.distanceTo(g_p) > 360) {
      target = g_p - 300;
    } else {
      //target =
    }

    return target;*/
  }

  Ball* Navigation::getNearestBall() {
    BallDetect* balls = mVision->get<BallDetect>();
    if(balls == nullptr) return nullptr;

    Ball* ball = nullptr;

    Transform* t = Localization::getTransform();
    double d = 1000000.0, _d;

    for(auto b : *balls->getEntities()) {
      if(!b->isValid()) continue;
      _d = t->distanceTo(b->getTransform()->getPosition());

      if(_d < d) {
        d = _d;
        ball = b;
      }
    }
    return ball;
  }

  Goal* Navigation::getOpponentGoal() {
    /*
    if(gC.getStr("Pattern.OpponentGoal") == "B")
      return Visioning::blueGoal;
    else
      return Visioning::yellowGoal;
    */

    return nullptr;
  }

  Robot* Navigation::getAlly() {
    RobotDetect* robots = mVision->get<RobotDetect>();
    if(robots == nullptr) return nullptr;

    for(auto& r : *robots->getEntities())
      if(r->isAlly()) return r;

    return nullptr;
  }

  void Navigation::setup(Visioning* vision) {
    if(gNavigation == nullptr) return;

    gNavigation = new Navigation(vision);
    gNavigation->init();
  }

  void Navigation::preProcess() {
    if(gNavigation == nullptr) return;
    gNavigation->updateEntities();
  }

  void Navigation::process() {
    if(gNavigation == nullptr) return;
    gNavigation->run();
  }

  Navigation* gNavigation = nullptr;

}
