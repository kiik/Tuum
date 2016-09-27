
#include "hal.hpp"

#include "TracdroneUIServer.hpp"

namespace tuum { namespace gui {

  void TracdroneUIServer::onGet()
  {

  }

  void TracdroneUIServer::onConnect()
  {

  }


  // Tuum Websocket Protocol
  class TWSProto {
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


  void TracdroneUIServer::onMessage(lws *wsi, void *in, size_t len)
  {
    TWSProto::Request* req = (TWSProto::Request*)in;

    switch(req->cmd) {
      case TDR_SET_SPEED:
        printf("[TDR]Set speed: \n");
        break;
      case TDR_GET_VALVES:
        printf("[TDR]Get valves.\n");
        break;
      case TDR_GET_GPS:
        {
          hal::GPSData dat = hal::hw.getSensors()->getGPS();
          TWSProto::send(wsi, req, dat);
        }
        break;
      case TDR_GET_IMU:
        {
          hal::IMUData dat = hal::hw.getSensors()->getIMU();
          TWSProto::send(wsi, req, dat);
        }
        break;
      case TDR_GET_BAT:
        {
          hal::BATData dat = hal::hw.getSensors()->getBAT();
          TWSProto::send(wsi, req, dat);
        }
      case TDR_GET_LDR:
        {
          hal::LeddarData dat = hal::hw.getSensors()->getLDR();
          TWSProto::send(wsi, req, dat);
        }
        break;
      case TDR_GET_HYD:
        {
          hal::HydroData dat = hal::hw.getSensors()->getHYD();
          TWSProto::send(wsi, req, dat);
        }
        break;
      case TDR_DRIVE:
        {
          uint8_t* raw_dat = (uint8_t*)in;
          hal::MotorControl::DriveData* dat = (hal::MotorControl::DriveData*)(req->getData());
          size_t sum = sizeof(*req) + sizeof(*dat);
	  int valid = sum == len;
          if(!valid) {
            printf("cmd:TDR_DRIVE - Error: Invalid data packet (l=%lu, d=%lu).\n", len, sum);
            break;
          }

          //printf("cmd:TDR_DRIVE - pwr %i, dir %i, trn %i, dfd %i, lck %i\n", dat->pwr, dat->dir, dat->trn, dat->dfd, dat->lck);
          hal::hw.manualControl(*dat);
        }
        break;
      case TDR_MOVE:
        {
          hal::MotorControl::MotionData* dat = (hal::MotorControl::MotionData*)(req->getData());

          size_t sum = sizeof(*req) + sizeof(*dat);
	  int valid = sum == len;
          if(!valid) {
            printf("cmd:TDR_MOVE - Error: Invalid data packet (l=%lu, d=%lu).\n", len, sum);
            break;
          }

          printf("J%i\n", dat->angle);
          hal::hw.manualControl(*dat);
        }
        break;
      case TDR_CMODE:
        {
          CModeData* dat = (CModeData*)(req->getData());

          size_t sum = sizeof(*req) + sizeof(*dat);
	  int valid = sum == len;
          if(!valid) {
            printf("cmd:TDR_CMODE - Error: Invalid data packet (l=%lu, d=%lu).\n", len, sum);
          }

          printf("CMODE: manual=%i\n", dat->manual);
          hal::Hardware::EControlMode m;
          if(dat->manual == 0) m = hal::Hardware::EControlMode::AUTO;
          else m = hal::Hardware::EControlMode::MANUAL;
          hal::hw.setControlMode(m);
        }
        break;
      case TDR_DO_CLB:
        {
          hal::hw.getMotorControl()->doCalibration();
          break;
        }
        break;
      default:
        if((req->cmd != TDR_CMD_NONE) && (req->cmd < TDR_CMD_N)) {
          printf("[TDR]Warning: unhandled command '%i'!\n", req->cmd);
        }
        break;
    }
  }

}}
