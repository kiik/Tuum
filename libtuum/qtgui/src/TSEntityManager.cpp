/** @file TSEntityManager.hpp
 *  @brief Tuum scene 3D entity manager.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#ifndef TS_OBJMAN_H
#define TS_OBJMAN_H

#include <glm/glm.hpp>

#include "ts_cmps.hpp"

#include "TSEntityManager.hpp"

namespace tuum { namespace ts {

  TSEntity* EntityManager::createObject() {
    TSEntity* o = new TSEntity();

    o->addComponent(new MeshFilter());
    o->addComponent(new MeshRenderer());

    return o;
  }

}}

#endif
