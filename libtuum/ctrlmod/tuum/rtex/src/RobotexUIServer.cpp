
#include "hal.hpp"

#include "RobotexUIServer.hpp"

#include "rtx_cmds.hpp"

using namespace tuum::wsocs;

namespace tuum { namespace gui {

  RobotexUIServer::RobotexUIServer():
    WebSocketServer()
  {
    size_t id = proto()->add(mDrvProtocol.getDescriptor());
  }

  void RobotexUIServer::onGet()
  {

  }

  void RobotexUIServer::onConnect()
  {

  }

  void RobotexUIServer::onMessage(lws *wsi, void *in, size_t len)
  {
    WSProtocol::Request* req = (WSProtocol::Request*)in;

    switch(req->cmd) {
      case ECommand::URI:
        printf("[WSUI]TODO: URI - ResourceNetwork requests\n");
        break;
      default:
        if((req->cmd != ECommand::None) && (req->cmd < ECommand::CMD_N)) {
          printf("[WSUI]Warning: unhandled command '%i'!\n", req->cmd);
        }
        break;
    }
  }

  void RobotexUIServer::onMessage(WSProtocol::Message ms)
  {
    auto it = ms.dat.find(WSProtocol::JSON_CMD_TAG);
    if(it == ms.dat.end()) return;
    if(!it.value().is_string()) return;

    proto()->route(ms); //TODO: Error handling
  }

}}
