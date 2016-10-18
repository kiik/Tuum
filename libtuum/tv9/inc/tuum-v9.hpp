/** @file tuum-v9.hpp
 *  Tuum scripting module 'v9'.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 4. October 2016
 */

#ifndef TUUM_V9_H
#define TUUM_V9_H

#include "ModuleContext.hpp"

namespace tuum { namespace v9 {

  void setup();

  int _ctx_hook(ModuleContext*);
  int _ctx_init(ModuleContext*&);

  namespace test {

    int v9_init();

    int process();

  }

}}

#endif // TUUM_V9_H
