/** @file tuum_localization.hpp
 *  Localization system interface.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 */

#include "loc.hpp"

#ifndef RTX_SYS_LOC_H
#define RTX_SYS_LOC_H

namespace tuum { namespace Localization {

  void setup();
  void process();

  void testSequence();

  Transform* getTransform();

  Transform toAbsoluteTransform(const int,const double);

}}

#endif // RTX_SYS_LOC_H
