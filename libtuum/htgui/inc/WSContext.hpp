
#ifndef TUUM_WSCTX_H
#define TUUM_WSCTX_H

#include <map>
#include <memory>

#include <libwebsockets.h>

namespace tuum { namespace wsocs {

  class WSContext
  {
  public:
    typedef size_t id_t;

    struct _ctx {
      id_t id;
    };

    typedef std::shared_ptr<_ctx> ctx_t;
    typedef std::map<id_t, ctx_t> clients_t;

    WSContext();

    ctx_t createContext();

    int insert(ctx_t);

    int find(id_t);
    int find(id_t, ctx_t&);

  private:
    clients_t m_clients;
    id_t c_id_seq;
  };

}}

#endif
