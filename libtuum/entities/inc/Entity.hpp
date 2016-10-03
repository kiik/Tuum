/** @file Entity.hpp
 *  Entity class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @authors Meelik Kiik
 *  @version 0.3
 *  @date 3 December 2015
 */

#ifndef RTX_ENTITY_H
#define RTX_ENTITY_H

#include <string>

#include "rtxmath.hpp"

#include "Blob.hpp"
#include "Color.hpp"

namespace tuum {

  /**
   *  class KalmanFilterObject
   *    KalmanState m_kfState[2]; // Last, current states
   *    ...?
   *
   *    void kPredict() // Velocity projection
   *    void kSense(Transform newMeasurement) // Velocity change from measurements
   *    void kEvaluate() // Updates m_kfState
   *    Transform kalmanProcess() // runs filter methods and returns probable new Transform
   *
   *  class Entity : KalmanFilterObject
   *    update(Transform transform):
   *      transform = this->kalmanProcess(Transform)
   *      ...
   *
   */

  class Entity {

    public:
      static unsigned int newID();

      Entity();
      Entity(const Entity&);

      // By position
      Entity(const Vec2i, Blob*);
      Entity(const int, const int, Blob*);

      // By position & orientation
      Entity(Transform, Blob*);
      Entity(Transform, Blob&);
      Entity(Transform, bool, Blob*);
      Entity(const int, const int, const double, Blob*);

      unsigned int getID();
      int getHealth();

      Transform* getTransform();

      void update(Transform); // Heal
      void update(Blob*);
      void update(Blob&);
      void update(); // Decay

      Blob* getBlob() const;
      Color getColor() const;

      bool isBall() const;
      bool isGoal() const;
      bool isRobot() const;

      std::string toString();

    protected:
      Blob *blob;

    private:
      static unsigned int id_seq;

      Transform m_transform;

      unsigned int id;
      int m_health = 0;

  };

}

#endif // RTX_ENTITY_H
