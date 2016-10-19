
#include "hal.hpp"

#include "RobotexUIServer.hpp"

#include "rtx_cmds.hpp"

using namespace tuum::wsocs;

namespace tuum { namespace gui {

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

  void RobotexUIServer::onMessage(lws *wsi, json data)
  {
    auto it = data.find(WSProtocol::JSON_CMD_TAG);
    if(it == data.end()) return;
    if(!it.value().is_string()) return;

    std::string str = it.value();
    WSProtocol::cmd_t cmd = WSProtocol::parseCommand(str);
    if(cmd == WSProtocol::ECMD_None) return;

    //RTXLOG(format("'onMessage'"), LOG_DEBUG);
    route(cmd, data);
  }

  void RobotexUIServer::route(WSProtocol::cmd_t cmd, json data)
  {
    switch(cmd) {
      case WSProtocol::ECMD_Drive:
      {
        tuum::cmds::drive(data["s"], data["d"].get<float>() / 1000.0, data["r"]);
        break;
      }
      case WSProtocol::ECMD_None:
      default:
        break;
    }
  }

}}
