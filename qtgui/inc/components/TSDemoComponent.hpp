/** @file TSDemoComponent.hpp
 *  @brief Tuum scene demo component.
 *
 *  @author Meelik Kiik
 *  @date 26. May 2016
 *  @version 0.1
 */

#ifndef TS_DEMO_COMPONENT_H
#define TS_DEMO_COMPONENT_H

#include "3dcore/TSComponent.hpp"

namespace tuum { namespace ts {

  class DemoComponent : public Component
  {
  public:
    DemoComponent();
    ~DemoComponent();

    void update();

    static TSOType type;
    TSOType* getType() const;

  private:
    float ngSpeed;
  };

}}

#endif // TS_DEMO_COMPONENT_H
