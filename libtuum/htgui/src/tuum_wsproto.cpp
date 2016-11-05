
#include "tuum_wsproto.hpp"

namespace tuum { namespace wsocs {

  const char* WSProtocol::JSON_URI_TAG = "uri";

  WSProtocol::WSProtocol():
    route_id_seq(1)
  {

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
    std::string uri = m.dat["uri"];

    auto it = mRouteMap.find(uri);
    if(it == mRouteMap.end()) return -1;

    return it->second.wsp->route(m);
  }

  size_t WSProtocol::add(route_t ro)
  {
    if(ro.uri == "") return 0;

    ro.id = route_id_seq++;
    mRouteMap[ro.uri] = ro;

    RTXLOG(format("Registered '%s', id=%lu.", ro.uri, ro.id));
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
