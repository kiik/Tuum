/** @file htgui.hpp
 *  UI module interface.
 *
 *  @authors Meelik Kiik
 *  @version 0.2
 *  @date 10. September 2016
 */

#ifndef TUUM_HTG_H
#define TUUM_HTG_H

#include "tuum_wsocs.hpp"

namespace tuum { namespace gui {

  int register_server(wsocs::WebSocketServer*);

  int startup(int = 0, char*[] = nullptr);

}}


#endif // TUUM_HTG_H
