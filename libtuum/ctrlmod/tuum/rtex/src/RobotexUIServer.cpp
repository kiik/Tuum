
#include "hal.hpp"

#include "RobotexUIServer.hpp"

namespace tuum { namespace gui {

  void RobotexUIServer::onGet()
  {

  }

  void RobotexUIServer::onConnect()
  {

  }


  // Tuum Websocket Protocol
  class WSProtocol {
  public:
    typedef unsigned char* data_t;
    typedef uint16_t mid_t;

    struct __attribute__((packed)) Request {
      mid_t id;
      uint8_t cmd;

      void* getData() { return (&(this->cmd)) + 1; }
    };

    struct __attribute__((packed)) Response {
      mid_t id;
    };

    template<typename T>
    static int send(lws *wsi, Request*& req, T dat) {
      Response res;
      res.id = req->id;

      int len = sizeof(res) + sizeof(dat);

      data_t buf = (data_t)malloc(LWS_SEND_BUFFER_PRE_PADDING + len + LWS_SEND_BUFFER_POST_PADDING);

      data_t dst = &buf[LWS_SEND_BUFFER_PRE_PADDING];
      memcpy(dst, (data_t)&res, sizeof(res));
      dst += sizeof(res);
      memcpy(dst, (data_t)&dat, sizeof(dat));

      lws_write(wsi, &buf[LWS_SEND_BUFFER_PRE_PADDING], len, LWS_WRITE_BINARY);
      free(buf);

      return 0;
    }

  };

  struct CModeData {
    uint8_t manual = 1;
  };


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

}}
