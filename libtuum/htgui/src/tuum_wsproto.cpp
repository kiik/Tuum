
#include "tuum_wsproto.hpp"

namespace tuum { namespace wsocs {

  const char* WSProtocol::JSON_CMD_TAG = "c";

  WSProtocol::cmd_map_t WSProtocol::gCmdMap = {
    {"drv", ECMD_Drive},
  };

  WSProtocol::WSProtocol() {

  }

  WSProtocol::cmd_t WSProtocol::parseCommand(const std::string& in) {
    auto it = WSProtocol::gCmdMap.find(in);
    if(it == WSProtocol::gCmdMap.end()) return WSProtocol::ECMD_None;
    return it->second;
  }

  int WSProtocol::recv(Packet _dat) {

  }

  int WSProtocol::validate(Packet* p) {

  }

  int WSProtocol::route(Packet* p) {

  }

}}
