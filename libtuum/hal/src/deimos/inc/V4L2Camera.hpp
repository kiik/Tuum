/** @file V4L2CameraBase.hpp
 *  @brief V4L2 driver interface in the form of a base 'Camera' class.
 *
 *  @authors Meelik Kiik
 *  @date 21. October 2016
 *  @version 0.1
 */

#ifndef RTX_V4L2_CAMERA_H
#define RTX_V4L2_CAMERA_H

#include <string>

#include <sys/ioctl.h>
#include <linux/videodev2.h>

#include "cameraConstants.hpp"    // CameraBase constants

#include "tuum_logger.hpp"
#include "tuum_buff.hpp"
#include "tuum_streams.hpp"
#include "tuum_platform.hpp"

#include "CameraDevice.hpp"

#define CLEAR(x) memset(&(x), 0, sizeof(x))

#define CLIP(color) (unsigned char)(((color) > 0xFF) ? 0xff : (((color) < 0) ? 0 : (color)))


/**
  Handles ioctl function calls. Calls the ioctl multiple times until the ioctl
  function returns an appropriate response.
  If the ioctl function returns -1, either it failed because of a reasonable
  argument, or it failed because of some blocking function. In this piece of
  software, only the first option is considered to be an appropriate response
  upon failure.
  The first argument must be an open file descriptor.
  The second argument is a device-dependent request code.
  The third argument is an untyped pointer to memory.
  Usually, on success zero is returned.  A few ioctl requests use the return
  value as an output parameter and return a nonnegative value on success. On
  error, -1 is returned, and errno is set appropriately.
*/
static int xioctl(int m_fd, unsigned long int request, void *arg) {
  int result;
  do {
    // The ioctl function manipulates the underlying device parameters of
    // special files. Many operating characteristics of character special files
    // (in this case, the video device file) may be controlled with ioctl
    // requests.  The file descriptor used as the first argument of the function
    // must be an open file descriptor.
    result = ioctl(m_fd, request, arg);
  } while (result == -1 && errno == EINTR);
  return result;
}

// Deinterlace
static void formatFrame(const unsigned char *source, unsigned char *destination,
                        int width, int height, int stride) {
  while (--height >= 0) {
    for (int i = 0; i < width - 1; i += 2) {
      for (int j = 0; j < 2; ++j) {
        *destination++ = source[j * 2];
        *destination++ = source[1];
        *destination++ = source[3];
      }
      source += 4;
    }
    source += stride - width * 2;
  }
}

namespace tuum { namespace hal {

  class CameraBase
  {
  private:
    static const int CAPTURE_MAX_BUFFER = 5;

  public:
    CameraBase(const std::string&, const size_t&, const size_t&);
    virtual ~CameraBase();

    std::string getDevice() const;

    size_t getWidth() const;
    size_t getHeight() const;

    img_prop_t getFormat() const;

    struct buf_info {
      int index;
      unsigned int length;
      void *start;
    };

    struct video_dev {
      int fd;
      int cap_width, cap_height;
      struct buf_info buff_info[CAPTURE_MAX_BUFFER];
      int numbuffer;
    };

    typedef std::function<void (video_dev*, v4l2_buffer*)> CaptureCallback;

  protected:
    std::string m_device;
    img_prop_t m_iprop, m_oprop;

    int m_fd;
    buf_t *m_bfs;

    unsigned int numberOfBuffers;
    size_t stride;

    void vidioc_enuminput(int fd);

    void log(std::string msg) {};
    void log(char* msg) {};
    void log(const char* msg) {};

  protected:
    int openDevice();

    int initFormat();
    int initBuffer();
    int startCapture();

    int captureFrame(ImageStream*);
    int stopCapture();
    void closeDevice();

    void chkV4L2();

  private:
    size_t frameRead();
  };

}}

#endif // RTX_V4L2_CAMERA_H
