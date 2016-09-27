/** @file TSEntity.hpp
 *  @brief Tuum scene 3D object representation.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#ifndef TS_ENTITY_H
#define TS_ENTITY_H

#include <vector>

#include "Entity.hpp"

// Tuum Scene includes
#include "3dcore/TSObjectBase.hpp"
#include "3dcore/TSMaterial.hpp"

#include "components/TSTransform.hpp"

namespace tuum { namespace ts {

  class Component;

  typedef std::vector<Component*> ComponentSet;

  /** @name TSEntity
   *  @brief Tuum Scene 3D object class
   */
  class TSEntity : public TSOBase
  {
  public:
    TSEntity();
    ~TSEntity();

    void update();
    void render();

    void setProjectionTarget(Entity*);

    QMatrix4x4* getTransform() { return &m_transform; }

    void addComponent(Component*);
    void removeComponent(Component*);

    TSOType* getType() const;
    static TSOType type;

    template<class T>
    T* getComponent();

  private:
    Entity* mEntity;

    QMatrix4x4 m_transform;

    ComponentSet m_components;
  };

  template<class T>
  T* TSEntity::getComponent() {
    if(m_components.size() == 0) return nullptr;

    for (TSOBase* c : m_components) {
      TSOType* t = c->getType();
      if(t == &T::type) return dynamic_cast<T*>(c);
    }
    return nullptr;
  }

}}

#endif // TS_ENTITY_H
