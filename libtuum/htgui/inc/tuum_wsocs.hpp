
#ifndef TUUM_WSOCS_PROXY_H
#define TUUM_WSOCS_PROXY_H

#include <boost/thread.hpp>
#include <libwebsockets.h>

#include "WebSocketServer.hpp"

namespace tuum { namespace wsocs {

  int cb_http_proxy(lws *wsi, lws_callback_reasons reason,
                  void *user, void *in, size_t len);
  int cb_wsoc_proxy(lws *wsi, lws_callback_reasons reason,
                  void *user, void *in, size_t len);

  extern lws_protocols gProtocols[];

  const lws_extension gExts[] = {
    { NULL, NULL, NULL /* terminator */ }
  };

}}

#include "WebSocketServer.hpp"

namespace tuum { namespace wsocs {

  extern boost::thread* wsSrvThread;

  int register_server(WebSocketServer*);

  int setup();
  int start();

  void process();

}}

#endif
