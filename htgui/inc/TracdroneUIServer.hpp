
#ifndef TDR_UI_H
#define TDR_UI_H

#include "WebSocketServer.hpp"

namespace tuum { namespace gui {

  class TracdroneUIServer : public wsocks::WebSocketServer
  {
  public:

    // Standard ABI
    enum TDRCommands {
      TDR_CMD_NONE    = 0,
      TDR_SET_SPEED   = 1,
      TDR_GET_SPEED   = 2,
      TDR_SET_VALVES  = 3,
      TDR_GET_VALVES  = 4,

      TDR_GET_GPS     = 5,
      TDR_GET_IMU     = 6,
      TDR_GET_BAT     = 7,
      TDR_GET_LDR     = 8,

      TDR_DRIVE       = 9,
      TDR_MOVE        = 10,

      TDR_CMODE       = 11,
      TDR_DO_CLB      = 12,

      TDR_GET_HYD     = 13,

      TDR_CMD_N,
    };

  protected:
    void onGet();

    void onConnect();
    void onMessage(lws*, void*, size_t);

  };

}}

#endif
