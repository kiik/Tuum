
#ifndef RTEX_DRVPROTO_H
#define RTEX_DRVPROTO_H

#include "tuum_wsproto.hpp"

using namespace tuum::wsocs;

namespace tuum {

  class DriveProtocol : public WSProtocol
  {
  public:
    DriveProtocol();

    WSProtocol::route_t getDescriptor();

    int route(const WSProtocol::Message&);

    int drive(json);

  private:

  };

}

#endif
