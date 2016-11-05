
#ifndef RTX_UI_H
#define RTX_UI_H

#include "json.hpp"

#include "tuum_wsproto.hpp"

#include "WebSocketServer.hpp"

#include "protocol/rtex_DriveProtocol.hpp"

using namespace tuum::wsocs;

namespace tuum { namespace gui {

  class RobotexUIServer : public wsocs::WebSocketServer
  {
  public:
    RobotexUIServer();

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
    void onMessage(WSProtocol::Message);

  private:
    DriveProtocol mDrvProtocol;

  };

}}

#endif
