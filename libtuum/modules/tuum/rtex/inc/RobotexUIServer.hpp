
#ifndef RTX_UI_H
#define RTX_UI_H

#include "WebSocketServer.hpp"

namespace tuum { namespace gui {

  class RobotexUIServer : public wsocs::WebSocketServer
  {
  public:

    // Standard ABI
    enum ECommand {
      None    = 0,
      DBG     = 1,
      URI     = 2,

      CMD_N,
    };

  protected:
    void onGet();

    void onConnect();
    void onMessage(lws*, void*, size_t);

  };

}}

#endif
