
#ifndef TUUM_CAMERA_H
#define TUUM_CAMERA_H

#include <boost/thread/mutex.hpp>

#include "tuum_platform.hpp"

#include "V4L2Camera.hpp"

namespace tuum { namespace hal {

  static void conv_YCbCr_to_RGB(const uint8_t* src, uint8_t* dest, int width, int height)
  {
    int j;
    while (--height >= 0) {
      for (j = 0; j < width; ++j) {
        // Y:  src[0]
        // Cb: src[1]
        // Cr: src[2]
        // Red
        *dest++ = CLIP(1.164 * (src[0] - 16) + 1.596 * (src[2] - 128));
        // Green
        *dest++ = CLIP(1.164 * (src[0] - 16) - 0.813 * (src[2] - 128) - 0.391 * (src[1] - 128));
        // Blue
        *dest++ = CLIP(1.164 * (src[0] - 16) + 2.018 * (src[1] - 128));
        src += 3;
      }
    }
  }

  static image_t toRGB(const image_t& in) {
    image_t out(new img_buf_t(in->frm));
    conv_YCbCr_to_RGB((uint8_t*)in->data, (uint8_t*)out->data, in->frm.width, in->frm.height);
    return out;
  }


  class Camera : public CameraBase, public CameraDevice
  {
  public:
    Camera(const std::string&, int, int);

    void setup();
    void process();

    void begin();
    void loop();
    void end();

    image_t getFrame();
    ImageStream* getStream();

  private:
    ImageStream m_stream;
    boost::mutex m_lock;

  };

}}

#endif
