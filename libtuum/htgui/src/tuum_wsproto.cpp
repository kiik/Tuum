
#include "tuum_wsproto.hpp"

namespace tuum { namespace wsocs {

  const char* WSProtocol::JSON_CMD_TAG = "c";

  WSProtocol::cmd_map_t WSProtocol::gCmdMap = {
    // Manual drive control
    {"drv", ECMD_Drive},

    // Vision
    //{"vis", ECMD_Vision}, // {c: 'vis', s: 'CAM0'}

    // Filesystem
    //{"fs", ECMD_Filesys}, // {c: 'fs', 'fn': '...', ['data': '...']}
  };

  WSProtocol::WSProtocol():
    route_id_seq(1)
  {

  }

  WSProtocol::cmd_t WSProtocol::parseCommand(const std::string& in) {
    auto it = WSProtocol::gCmdMap.find(in);
    if(it == WSProtocol::gCmdMap.end()) return WSProtocol::ECMD_None;
    return it->second;
  }

  int WSProtocol::recv(Packet _dat) {

  }

  int WSProtocol::validate(Packet* p) {
    //TODO
  }

  /*
  int WSProtocol::route(Packet* p) {

  }*/

  int WSProtocol::route(const Message& m) {
    key_t key = m.dat["c"];

    auto it = mRouteMap.find(key);
    if(it == mRouteMap.end()) {
      RTXLOG(format("Unknown '%s'!", key), LOG_ERR);
      return -1;
    }

    it->second.wsp->route(m);
    return 1;
  }

  size_t WSProtocol::add(route_t ro)
  {
    if(ro.key == "") return 0;

    ro.id = route_id_seq++;
    mRouteMap[ro.key] = ro;

    RTXLOG(format("Registered '%s', id=%lu.", ro.key, ro.id));
    return ro.id;
  }

  void WSProtocol::remove(size_t id)
  {
    //TODO:
  }

  WSProtocol::route_t WSProtocol::getDescriptor() {
    route_t ro;
    return ro;
  }


}}
