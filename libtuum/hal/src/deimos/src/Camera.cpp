
#include "Camera.hpp"

namespace tuum { namespace hal {

  Camera::Camera(const std::string& device = gC.getStr("Vision.FirstCameraBase"), int w = CAMERA_WIDTH, int h = CAMERA_HEIGHT):
    CameraBase(device, w, h)
  {

  }

  void Camera::setup() {
    if(openDevice() < 0) {
      printf(":V4L2Camera::setup: Error - 'openDevice()'!");
      return;
    }

    chkV4L2();

    if(initFormat() < 0) {
      printf(":V4L2Camera::setup: Error - 'initFormat()'!");
      return;
    }

    if(initBuffer() < 0) {
      printf(":V4L2Camera::setup: Error - 'initBuffer()'!");
      return;
    }

    m_frame.width = m_width;
    m_frame.height = m_height;
    m_frame.size = m_width * m_height * 3;
    m_frame.data = (unsigned char *)malloc(m_frame.size * sizeof(char));
    m_frame.id = 0;

    if(startCapture() < 0) {
      printf(":V4L2Camera::setup: Error - 'startCapture()'!");
      return;
    }
  }

  void Camera::process() {
    /*
    captureFrame([=](video_dev* dev, v4l2_buffer* buf) {
      m_frame.id++;
      formatFrame((uint8_t*)dev->buff_info[buf->index].start, m_frame.data, m_width, m_height, m_stride);
    });*/

    while(!m_lock.try_lock()) {};
    int res = captureFrame(m_frame);
    if(res >= 0) {
      m_frame.id++;
    } else {
      printf(":Camera::process: Error - 'captureFrame' code %i\n", res);
    }
    m_lock.unlock();
  }

  const Frame& Camera::getFrame() {
    while(!m_lock.try_lock()) {};
    m_lock.unlock();
    return m_frame;
  }

  int Camera::requestFrame(Frame& out) {
    if(!m_lock.try_lock()) return -1;
    out = m_frame;
    m_lock.unlock();
    return 0;
  }

  void Camera::begin() {

  }

  void Camera::loop() {

  }

  void Camera::end() {

  }

}}
