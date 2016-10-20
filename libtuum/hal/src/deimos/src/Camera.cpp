
#include "Camera.hpp"

namespace tuum { namespace hal {

  Camera::Camera(const std::string& device = gC.getStr("Vision.FirstCameraBase"), int w = CAMERA_WIDTH, int h = CAMERA_HEIGHT):
    CameraBase(device, w, h)
  {

  }

  void Camera::setup() {
    if(openDevice() < 0) {
      RTXLOG(":V4L2Camera::setup: Error - 'openDevice()'!", LOG_ERR);
      return;
    }

    chkV4L2();

    if(initFormat() < 0) {
      RTXLOG(":V4L2Camera::setup: Error - 'initFormat()'!", LOG_ERR);
      return;
    }

    if(initBuffer() < 0) {
      RTXLOG(":V4L2Camera::setup: Error - 'initBuffer()'!", LOG_ERR);
      return;
    }

    m_stream.init(m_oprop);

    if(startCapture() < 0) {
      RTXLOG(":V4L2Camera::setup: Error - 'startCapture()'!", LOG_ERR);
      return;
    }
  }

  void Camera::process() {
    while(!m_lock.try_lock()) {};
    int res = captureFrame(&m_stream);
    if(res >= 0) {
      m_stream.incSeq();
    } else {
      RTXLOG(tuum::format(":Camera::process: Error - 'captureFrame' code %i\n", res), LOG_ERR);
    }
    m_lock.unlock();
  }

  image_t Camera::getFrame() {
    while(!m_lock.try_lock()) {};
    m_lock.unlock();
    return m_stream.getFrame();
  }

  ImageStream* Camera::getStream() {
    while(!m_lock.try_lock()) {};
    m_lock.unlock();
    return &m_stream;
  }

  void Camera::begin() {

  }

  void Camera::loop() {

  }

  void Camera::end() {

  }

}}
