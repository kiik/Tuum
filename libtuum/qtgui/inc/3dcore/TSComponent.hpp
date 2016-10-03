/** @file TSComponent.hpp
 *  @brief Tuum scene object component base.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#ifndef TS_COMPONENT_H
#define TS_COMPONENT_H

#include <string>
#include <typeinfo>

#include "3dcore/TSObjectBase.hpp"
#include "3dcore/TSEntity.hpp"

namespace tuum { namespace ts {

 /*
  template< typename TARGET >
  class Reflection {
    static int type() {
      static const int id = reinterpret_cast<int>(typeid(TARGET).name());
      return id;
    }

    static const char* cname() {
      return typeid(TARGET).name();
    }
  };
  */

  class Component : public TSOBase {
  public:

    std::string name() const { return typeid(*this).name(); }

    void assignTo(TSEntity* target) {
      sceneEntity = target;
      transform   = target->getTransform();

      setup();
    }

    virtual int setup() {};

    /** Component getter proxy **/
    template<class T>
    T* getComponent() {
      return sceneEntity->getComponent<T>();
    }

    virtual TSOType* getType() const = 0;

  protected:
    TSEntity* sceneEntity;

    QMatrix4x4* transform;
  };

}}

#endif
