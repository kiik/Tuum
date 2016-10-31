/** @file tuum_physics.hpp
 *  Physics system interface
 *
 *  @authors Ants-Oskar Mäesalu, Meelik Kiik
 *  @version 0.1
 *  @date 3. December 2015
*/

#ifndef TUUM_SYS_PHYSICS_H
#define TUUM_SYS_PHYSICS_H

#include "tuum_entities.hpp"
#include "tuum_visioning.hpp"

namespace tuum {

  class Physics
  {

    static Entity* rayCast(Visioning::Context, const double&, const double& = 0);

  };

}

#endif
