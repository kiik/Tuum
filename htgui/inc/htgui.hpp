/** @file htgui.hpp
 *  HTTP based GUI module interface.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 10. September 2016
 */

#ifndef TUUM_HTG_H
#define TUUM_HTG_H

#include "TracdroneUIServer.hpp"

namespace tuum { namespace gui {

  extern TracdroneUIServer uiSrv;

  int run(int, char*[]);

}}


#endif // TUUM_HTG_H
