

#ifndef TUUM_WSPROTO_H
#define TUUM_WSPROTO_H

#include <string>
#include <sstream>
#include <map>

#include <libwebsockets.h>
#include "json.hpp"

#include "platform.hpp"

using json = nlohmann::json;

namespace tuum { namespace wsocs {

  class WSProtocol {
  public:
    typedef unsigned char* data_t;
    typedef uint16_t msg_id_t;

    struct route_t {
      size_t id = 0;
      std::string uri = "";
      WSProtocol* wsp = nullptr;
    };

    typedef std::map<std::string, route_t> route_map_t;

    struct Message {
      json dat;
      lws* res; // Response write handle

      std::string getURI() {
        return dat[WSProtocol::JSON_URI_TAG];
      }

      //std::string getRaw()
    };


    // Binary interface structures
    struct Packet {
      void* ptr;
      size_t len;
    };

    struct __attribute__((packed)) Request {
      msg_id_t id;
      uint8_t cmd;

      void* getData() { return (&(this->cmd)) + 1; }
    };

    struct __attribute__((packed)) Response {
      msg_id_t id;
    };

    struct __attribute__((packed)) Event {
      char* name, *data;

      std::string getData() {
        std::stringstream out;
        out << name << '\n'<< data << '\n';
        return out.str();
      }
    };
    // ****

    WSProtocol();

    int recv(Packet);

    int validate(Packet*);

    //int route(Packet*);
    virtual int route(const Message&);

    virtual route_t getDescriptor();

    size_t add(route_t);
    void remove(size_t);

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

    static int emit(lws *wsi, Event ev) {
      std::string data = ev.getData();
      size_t len = data.size();

      data_t buf = (data_t)malloc(LWS_SEND_BUFFER_PRE_PADDING + len + LWS_SEND_BUFFER_POST_PADDING);

      data_t dst = &buf[LWS_SEND_BUFFER_PRE_PADDING];
      memcpy(dst, data.c_str(), len);

      lws_write(wsi, &buf[LWS_SEND_BUFFER_PRE_PADDING], len, LWS_WRITE_BINARY);
      free(buf);

      return 0;
    }

  public:
    static const char* JS_URI;
    static const char* JS_CMD;

  private:
    size_t route_id_seq;
    WSProtocol::route_map_t mRouteMap;

  };

}}

#endif
