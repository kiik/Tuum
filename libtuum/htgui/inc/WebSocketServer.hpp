
#ifndef TUUM_WSOCS_H
#define TUUM_WSOCS_H

#include <libwebsockets.h>

#include "tuum_platform.hpp"

namespace tuum { namespace wsocs {

  class WebSocketServer
  {
  public:
    WebSocketServer();
    ~WebSocketServer();

    int init();
    void process();

    int cb_http(lws *wsi, lws_callback_reasons reason,
                    void *user, void *in, size_t len);

    int cb_wsoc(lws *wsi, lws_callback_reasons reason,
                    void *user, void *in, size_t len);

  private:
    int m_port, m_opts;

    const char *m_iface,
               *m_cert_path,
               *m_key_path;

    struct lws_context *m_ctx;
    struct lws_context_creation_info m_info;

    struct lws_protocols *m_protocols;
    struct lws_extension *m_exts;

    int loadProtocols();

  public:
    virtual void onGet() {};

    virtual void onConnect() {};
    virtual void onMessage(lws *wsi, void* in, size_t len) {};
  };

}}

#endif // TUUM_WSOCS_H
