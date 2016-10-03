/** @file TSEntityManager.hpp
 *  @brief Tuum scene 3D entity manager.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#ifndef TS_ENTMAN_H
#define TS_ENTMAN_H

#include <glm/glm.hpp>

#include "3dcore/TSEntity.hpp"

namespace tuum { namespace ts {

  class EntityManager {
  public:
    EntityManager();

    static TSEntity* createObject();

  };

}}

#endif
