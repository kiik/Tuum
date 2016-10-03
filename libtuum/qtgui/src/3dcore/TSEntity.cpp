
#include <iostream>

#include <QtGui/QOpenGLFunctions>
#include <QtOpenGL/QtOpenGL>

#include "3dcore/TSEntity.hpp"
#include "3dcore/TSComponent.hpp"

namespace tuum { namespace ts {

  TSOType TSEntity::type;

  TSEntity::TSEntity():
    mEntity(nullptr)
  {
    m_transform.setToIdentity();
  }

  TSEntity::~TSEntity() {
    for(auto c : m_components) delete c;
  }

  void TSEntity::update() {
    for(auto c : m_components) {
      c->update();
    }
  }

  void TSEntity::render() {
    for(auto c : m_components) {
      c->render();
    }
  }

  void TSEntity::setProjectionTarget(Entity* ent) {
    mEntity = ent;
  }

  void TSEntity::addComponent(Component* c) {
    c->assignTo(this);
    m_components.push_back(c);
  }

  void TSEntity::removeComponent(Component* c) {
    //TODO
  }

  TSOType* TSEntity::getType() const {
    return &TSEntity::type;
  }

}}
