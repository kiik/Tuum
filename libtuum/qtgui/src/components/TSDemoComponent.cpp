/** @file TSDemoComponent.hpp
 *  @brief Tuum scene demo component.
 *
 *  @author Meelik Kiik
 *  @date 26. May 2016
 *  @version 0.1
 */

#include <iostream>

#include "TuumScene.hpp"
#include "components/TSDemoComponent.hpp"

namespace tuum { namespace ts {

  TSOType DemoComponent::type;

  DemoComponent::DemoComponent() {
    ngSpeed = 360.0f / 4.0f;
  }

  DemoComponent::~DemoComponent() {

  }

  void DemoComponent::update() {
    transform->rotate(ngSpeed*TuumScene::timeDelta, QVector3D(1.0f, 0.5f, 1.0f));
  }

  TSOType* DemoComponent::getType() const {
    return &DemoComponent::type;
  }

}}
