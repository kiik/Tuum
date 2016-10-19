
#include "tuum_wsocs.hpp"

namespace tuum { namespace wsocs {

  bool running = true;
  boost::thread* wsSrvThread;

  const int WSOCS_SRV_N = 1;
  WebSocketServer* wsock_srvs[WSOCS_SRV_N];


  //FIXME: Generate callbacks per-server instance.
  int cb_http_proxy(lws *wsi, lws_callback_reasons reason,
                  void *user, void *in, size_t len) {
    if(wsock_srvs[0] != nullptr) wsock_srvs[0]->cb_http(wsi, reason, user, in, len);
  }

  int cb_wsjs_proxy(lws *wsi, lws_callback_reasons reason,
                  void *user, void *in, size_t len) {
    if(wsock_srvs[0] != nullptr) wsock_srvs[0]->cb_wsjs(wsi, reason, user, in, len);
  }

  int cb_wsbin_proxy(lws *wsi, lws_callback_reasons reason,
                  void *user, void *in, size_t len) {
    if(wsock_srvs[0] != nullptr) wsock_srvs[0]->cb_wsbin(wsi, reason, user, in, len);
  }

  lws_protocols gProtocols[] = {
    {
      "http-only",
      cb_http_proxy,
      sizeof(size_t),
    },
    {
      "ws-json",
      cb_wsjs_proxy,
      0
    },
    {
      "ws-binary",
      cb_wsbin_proxy,
      0
    },
    {
      NULL, NULL, 0
    }
  };

  int register_server(WebSocketServer* srv) {
    for(int i=0; i < WSOCS_SRV_N; i++) {
      if(wsock_srvs[i] != nullptr) continue;
      wsock_srvs[i] = srv;
      return 1;
    }

    return -1;
  }

  int setup() {
    for(int i=0; i < WSOCS_SRV_N; i++) wsock_srvs[i] = nullptr;
  }

  void process() {
    while(running) {
      for(int i=0; i < WSOCS_SRV_N; i++) {
        if(wsock_srvs[i] != nullptr) wsock_srvs[i]->process();
      }
    }
  }

  int start() {
    if(wsSrvThread == nullptr)
      wsSrvThread = new boost::thread(&process);
  }

}}
