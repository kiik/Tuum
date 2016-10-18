
#ifndef TUUM_CAMERA_H
#define TUUM_CAMERA_H

#include <boost/thread/mutex.hpp>

#include "tuum_platform.hpp"

#include "V4L2Camera.hpp"

namespace tuum { namespace hal {

  static void convertYCbCrtoRGB(const unsigned char *src, unsigned char *dest,
                                 int width, int height)
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

  static Frame toRGB(const Frame &frame) {
    Frame rgbFrame;
    rgbFrame.data = (unsigned char *) malloc(frame.size * sizeof(char));

    std::copy(frame.data, frame.data + frame.size, rgbFrame.data);

    rgbFrame.width = frame.width;
    rgbFrame.height = frame.height;
    rgbFrame.size = frame.size;

    convertYCbCrtoRGB((unsigned char *) frame.data,
                             rgbFrame.data,
                             rgbFrame.width,
                             rgbFrame.height);
    return rgbFrame;
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

    const Frame& getFrame();
    int requestFrame(Frame&);

  private:
    Frame m_frame;
    boost::mutex m_lock;

  };

}}

#endif
