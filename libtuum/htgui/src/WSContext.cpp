
#include "WSContext.hpp"

namespace tuum { namespace wsocs {

    WSContext::WSContext():
      c_id_seq(1)
    {

    }

    WSContext::ctx_t WSContext::createContext()
    {
      WSContext::ctx_t out = std::make_shared<WSContext::_ctx>();
      out->id = c_id_seq++;
      return out;
    }

    int WSContext::insert(WSContext::ctx_t in)
    {
      m_clients[in->id] = in;
      return 0;
    }

    int WSContext::find(WSContext::id_t id)
    {
      auto it = m_clients.find(id);
      if(it == m_clients.end()) return -1;
      return 0;
    }

    int WSContext::find(WSContext::id_t id, WSContext::ctx_t& out)
    {
      auto it = m_clients.find(id);
      if(it == m_clients.end()) return -1;

      out = it->second;
      return 0;
    }

}}
