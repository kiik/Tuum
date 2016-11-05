
#include "rtx_cmds.hpp"
#include "protocol/rtex_DriveProtocol.hpp"

using namespace tuum::wsocs;

namespace tuum {

  DriveProtocol::DriveProtocol() {

  }

  WSProtocol::route_t DriveProtocol::getDescriptor()
  {
    WSProtocol::route_t out;
    out.key = "drv";
    out.wsp = this;
    return out;
  }

  int DriveProtocol::route(const WSProtocol::Message& m) {
    if(m.dat["c"] == "drv") {
      drive(m.dat);
    }
  }

  //TODO: Error catching
  int DriveProtocol::drive(json dat) {
    tuum::cmds::drive(dat["s"], dat["d"].get<float>() / 1000.0, dat["r"]);
  }

}
