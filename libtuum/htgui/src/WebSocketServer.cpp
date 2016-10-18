
#include <gdkmm/pixbuf.h>
#include <glib.h>
#include <gtkmm.h>

#include "WSProtocol.hpp"

#include "hal.hpp"
#include "lpx_iformat.hpp"

#include "tuum_wsocs.hpp"

using namespace tuum::lpx;

namespace tuum { namespace wsocs {

  typedef uint8_t* data_t;

  size_t lframe = 0;
  size_t t0 = 0;
  float dt = 0;

  Frame frame;
  bool done = false;


  size_t read_data_stream(size_t lid, Frame& out) {
    auto camera = hal::hw.getCamera();

    if(!done) {
      frame = camera->getFrame();
      done = true;
    }

    //if(frame.id == lid) return 0;

    out = hal::toRGB(frame);

    return frame.id;
  }

  void fps() {
    size_t t1 = millis();
    dt = dt * 0.7 + (t1-t0) * 0.3;
    printf("FPS=%f.0\n", 1000.0 / dt);
    t0 = t1;
  }

  const char* mjpeg_head = "HTTP/1.1 200 OK\nCache-Control: no-store, no-cache, must-revalidate, pre-check=0, post-check=0, max-age=0\nConnection: close\nContent-Type: multipart/x-mixed-replace;boundary=--FRAME--\nExpires: Mon, 3 Jan 2000 12:34:56 GMT\nPragma: no-cache\n\n";

  const char* mjpeg_boundary = "\n--FRAME--\n";

  void http_mjpeg_headers(lws *wsi) {
    lws_write(wsi, (unsigned char*)mjpeg_head, strlen(mjpeg_head), LWS_WRITE_HTTP);
  }

  void http_mjpeg_stream(lws *wsi) {
    Frame frm;

    size_t fid = read_data_stream(lframe, frm);
    if(fid <= 0) return;
    lframe = fid;
    fps();

    buffer_t img = lpx::rgb_to_jpg(frm);
    delete(frm.data);

    lws_write(wsi, (unsigned char*)mjpeg_boundary, strlen(mjpeg_boundary), LWS_WRITE_HTTP);

    size_t len = img->size;
    std::stringstream head;
    head << "X-Timestamp: " << millis() << std::endl;
    head << "Content-Length: " << len << std::endl;
    head << "Content-Type: " << "image/jpeg" << std::endl;
    head << std::endl; // End of header
    std::string _head = head.str();

    lws_write(wsi, (unsigned char*)(_head.c_str()), _head.size(), LWS_WRITE_HTTP);
    lws_write(wsi, (unsigned char*)img->data, len, LWS_WRITE_HTTP);
  }

  WebSocketServer::WebSocketServer():
    m_port(8080), m_opts(0),
    m_iface(nullptr), m_ctx(nullptr),
    m_cert_path(nullptr), m_key_path(nullptr),
    m_protocols(nullptr), m_exts(nullptr)
  {
    int v = 0;
    char** argv = nullptr;
  }

  WebSocketServer::~WebSocketServer() {
    lws_context_destroy(m_ctx);
  }

  int WebSocketServer::init() {
    if(loadProtocols() < 0) return -1;

    memset(&m_info, 0, sizeof(m_info));
    m_info.port = m_port;
    m_info.iface = m_iface;
    m_info.protocols = gProtocols;
    m_info.extensions = gExts;
    m_info.ssl_cert_filepath = NULL;
    m_info.ssl_private_key_filepath = NULL;
    m_info.gid = -1;
    m_info.uid = -1;
    m_info.options = m_opts;

    RTXLOG("Creating wsoc context...", LOG_INFO);
    m_ctx = lws_create_context(&m_info);

    if(m_ctx == nullptr){
      RTXLOG("libwebsocket init failed!", LOG_ERR);
      return -2;
    }

    return 0;
  }

  int WebSocketServer::loadProtocols() {
    return 0;
  }

  void WebSocketServer::process() {
    bool running = true;
    while(running) {
      lws_service(m_ctx, 0);
    }
  }

  int WebSocketServer::cb_http(lws *wsi, lws_callback_reasons reason,
                  void *user, void *in, size_t len)
  {
    switch(reason) {
      case LWS_CALLBACK_HTTP:
        printf("[WSS:cb_http]New connection.\n");
        http_mjpeg_headers(wsi);
        lws_callback_on_writable(wsi);
        return 0;
      case LWS_CALLBACK_HTTP_FILE_COMPLETION:
        return 0;
      case LWS_CALLBACK_HTTP_WRITEABLE:
        http_mjpeg_stream(wsi);
        lws_callback_on_writable(wsi);
        return 0;
      case LWS_CALLBACK_FILTER_NETWORK_CONNECTION:
        return 0;
      default:
        break;
    }

    return 0;
  }

  int WebSocketServer::cb_wsoc(lws *wsi, lws_callback_reasons reason,
                  void *user, void *in, size_t len)
  {
    uint8_t *raw = (uint8_t*)in;
    switch(reason) {
      case LWS_CALLBACK_ESTABLISHED:
        printf("[WSS:cb_wsoc]Connection established.\n");
        onConnect();
        //lws_callback_on_writable(wsi);
        break;
      case LWS_CALLBACK_RECEIVE:
        onMessage(wsi, in, len);
        break;
      case LWS_CALLBACK_SERVER_WRITEABLE:
        {
          //WSProtocol::Event ev;

          /*
          ev.name = new char[8];
          ev.data = new char[7];
          strcpy(ev.name, "message");
          strcpy(ev.data, "123456");
          printf("DBG: %s, %s\n", ev.name, ev.data);
          */

        }
        lws_callback_on_writable(wsi);
        break;
    }

    return 0;
  }

}}
