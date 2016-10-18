/**
 * @file V4L2CameraBase.hpp
 * CameraBase class
 * Class for communication with the robot's cameras, based on the V4L2 API.
 * The video capture example provided with the V4L2 API has been used as a
 * model for the class.
 *
 * @authors Ants-Oskar Mäesalu
 * @version 0.1
 */

#include <fcntl.h>              // File control operations (open)
#include <sys/stat.h>           // File characteristics header (stat)
#include <sys/ioctl.h>          // I/O control device header (ioctl)
#include <sys/mman.h>           // Memory management declarations (mmap)
#include <unistd.h>             // OS API header (close)
#include <cstring>              // C string header (memset, strerror)
#include <stdexcept>            // Exception header (runtime_error)
#include <linux/videodev2.h>    // V4L2 header

#include <iostream> // TODO: Remove

#include "V4L2Camera.hpp"       // The class header


namespace tuum { namespace hal {

  CameraBase::CameraBase(const std::string &device, const int &width, const int &height):
    m_device(device), m_width(width), m_height(height),
    m_fd(-1)
  {

  }

  CameraBase::~CameraBase()
  {
    closeDevice();
  }

  std::string CameraBase::getDevice() const { return m_device; }

  int CameraBase::getWidth() const { return m_width; }
  int CameraBase::getHeight() const { return m_height; }

  void CameraBase::vidioc_enuminput(int fd)
  {
      int err;
      struct v4l2_input input;
      CLEAR(input);

      input.index = 0;
      while ((err = ioctl(fd, VIDIOC_ENUMINPUT, &input)) == 0) {
        /*
          qDebug() << "input name =" << (char *)input.name
                   << " type =" << input.type
                   << " status =" << input.status
                   << " std =" << input.std;
        */
          input.index++;
      }
  }

  int CameraBase::openDevice() {
    struct stat status;

    // Get device file status.
    // Upon successful completion, 0 shall be returned. Otherwise, -1 shall be
    // returned and errno set to indicate the error.
    if (stat(m_device.c_str(), &status) == -1)
      throw std::runtime_error(m_device + ": cannot identify! " +
                               std::to_string(errno) + ": " +
                               std::strerror(errno));

    // Test if the device file is a character special file. The test returns a
    // non-zero value if the test is true; 0 if the test is false.
    if (!S_ISCHR(status.st_mode))
      throw std::runtime_error(m_device + " is no device");

    // Try to open the device.
    // Upon successful completion, the open function shall open the file and
    // return a non-negative integer representing the lowest numbered unused file
    // descriptor. Otherwise, -1 shall be returned and errno set to indicate the
    // error. No files shall be created or modified if the function returns -1.
    // O_RDWR sets the file to be open for reading and writing.
    // O_NONBLOCK sets the function to return without blocking for the device to
    // be ready or available.
    if ((m_fd = open(m_device.c_str(), O_RDWR | O_NONBLOCK, 0)) == -1)
      throw std::runtime_error(m_device + ": cannot open! " + std::to_string(errno) + ": " + std::strerror(errno));

    return 0;
  }

  int CameraBase::initFormat() {
    struct v4l2_format format;
    CLEAR(format);

    // Assign a format suitable for our application to the camera device.
    // TODO: Check data integrity

    // Type of the data stream - buffer of a video capture stream.
    format.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    // Image width in pixels.
    format.fmt.pix.width       = m_width;
    // Image height in pixels.
    format.fmt.pix.height      = m_height;
    // The pixel format or type of compression, set by the application.
    // YUYV is a packed format with 1/2 horizontal chroma resolution, also known
    // as YUV 4:2:2. In this format each four bytes is two pixels. Each four bytes
    // is two Y's, a Cb and a Cr. Each Y goes to one of the pixels, and the Cb and
    // Cr belong to both pixels.
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    // Video images are typically interlaced. Applications can request to capture
    // or output only the top or bottom field, or both fields interlaced or
    // sequentially stored in one buffer or alternating in separate buffers.
    // Drivers return the actual field order selected.
    // TODO: Deinterlace video to remove motion artifacts from data.
    format.fmt.pix.field       = V4L2_FIELD_INTERLACED;

    // Try to set the format according to our specifications. On success, 0 is
    // returned; on error -1 and the errno variable is set appropriately.
    if (xioctl(m_fd, VIDIOC_S_FMT, &format) == -1)
     throw std::runtime_error("VIDIOC_S_FMT");

    // VIDIOC_S_FMT may change resolution width and height.
    m_width = format.fmt.pix.width;
    m_height = format.fmt.pix.height;

    m_stride = format.fmt.pix.bytesperline;

    return 0;
  }

  int CameraBase::initBuffer() {
    // V4L2 buffer request structure
    struct v4l2_requestbuffers request;

    CLEAR(request);

    request.count = 4;
    request.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    request.memory = V4L2_MEMORY_MMAP;

    if (xioctl(m_fd, VIDIOC_REQBUFS, &request) == -1) {
      if (errno == EINVAL) {
        throw std::runtime_error(m_device + " does not support memory mapping");
      } else {
        throw std::runtime_error("VIDIOC_REQBUFS");
      }
    }

    if (request.count < 2) {
      throw std::runtime_error(std::string("Insufficient buffer memory on ") + m_device);
    }

    m_bfs = (data_buf_t*)calloc(request.count, sizeof(*m_bfs));

    if (!m_bfs) {
      throw std::runtime_error("Out of memory");
    }

    struct v4l2_buffer buffer;
    for(numberOfBuffers = 0; numberOfBuffers < request.count; ++numberOfBuffers) {
      CLEAR(buffer);

      buffer.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      buffer.memory      = V4L2_MEMORY_MMAP;
      buffer.index       = numberOfBuffers;

      if (xioctl(m_fd, VIDIOC_QUERYBUF, &buffer) == -1)
        throw std::runtime_error("VIDIOC_QUERYBUF");

      m_bfs[numberOfBuffers].size = buffer.length;
      m_bfs[numberOfBuffers].data =
        mmap(NULL /* start anywhere */,
             buffer.length,
             PROT_READ | PROT_WRITE /* required */,
             MAP_SHARED /* recommended */,
             m_fd, buffer.m.offset);

      if (m_bfs[numberOfBuffers].data == MAP_FAILED)
        throw std::runtime_error("mmap");
    }
  }

  int CameraBase::startCapture()
  {
    unsigned int i;
    enum v4l2_buf_type type;

    struct v4l2_buffer buf;
    for (i = 0; i < numberOfBuffers; ++i) {
      CLEAR(buf);

      buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      buf.memory = V4L2_MEMORY_MMAP;
      buf.index = i;

      if (xioctl(m_fd, VIDIOC_QBUF, &buf) == -1)
        throw std::runtime_error("VIDIOC_QBUF");
    }

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (xioctl(m_fd, VIDIOC_STREAMON, &type) == -1)
      throw std::runtime_error("VIDIOC_STREAMON");

    return 0;
  }

  size_t CameraBase::frameRead() {
    struct v4l2_buffer buffer;
    CLEAR(buffer);

    buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buffer.memory = V4L2_MEMORY_MMAP;

    if (xioctl(m_fd, VIDIOC_DQBUF, &buffer) == -1) {
      switch (errno) {
        case EAGAIN:
          return -1;
        case EIO:
          /* Could ignore EIO, see spec. */
          /* fall through */
        default:
          throw std::runtime_error("VIDIOC_DQBUF");
      }
    }

    assert(buffer.index < numberOfBuffers);

    if (xioctl(m_fd, VIDIOC_QBUF, &buffer) == -1)
        throw std::runtime_error("VIDIOC_QBUF");

    return buffer.index;
  }

  int CameraBase::captureFrame(ImageStream* out)
  {
    size_t timeout = 1000;
    while (true) {
      fd_set m_fds;
      struct timeval timeValue;

      FD_ZERO(&m_fds);
      FD_SET(m_fd, &m_fds);

      /* Timeout. */
      timeValue.tv_sec = timeout;
      timeValue.tv_usec = 0;

      int returnValue = select(m_fd + 1, &m_fds, NULL, NULL, &timeValue);

      if (returnValue == -1) {
        if (errno == EINTR)
          continue;
        throw std::runtime_error("select");
      }

      if (returnValue == 0) {
        throw std::runtime_error(m_device + ": select timeout");
      }

      int index = frameRead();
      if (index > 0) {
        formatFrame((uint8_t*)m_bfs[index].data, (uint8_t*)out->getBack()->data, m_width, m_height, m_stride);
        out->swap();
        return 0;
      }
    }

    return -1;
  }

  int CameraBase::stopCapture()
  {
    int a, ret;

    log("Stream off!!");

    a = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(m_fd, VIDIOC_STREAMOFF, &a);
    if (ret < 0) {
      log("VIDIOC_STREAMOFF");
      return ret;
    }

    return 0;
  }

  void CameraBase::closeDevice()
  {
    // Try to close the device, based on its file descriptor
    // The close function returns -1 if the file descriptor is not a valid open
    // device file descriptor of the device.
    if (close(m_fd) == -1)
      throw std::runtime_error("Error upon closing device");

    // Reset the file descriptor to ensure it doesn't refer to any device anymore.
    m_fd = -1;
  }

  void CameraBase::chkV4L2() {
    // V4L2 capability structure
    struct v4l2_capability capabilities;

    // Query device capabilities. If the video device driver is not compatible
    // with V4L2 specification, (x)ioctl returns an EINVAL error code.
    if (xioctl(m_fd, VIDIOC_QUERYCAP, &capabilities) == -1) {
      if (errno == EINVAL)
        throw std::runtime_error(m_device + " is not a V4L2 device");
      else
        throw std::runtime_error("VIDIOC_QUERYCAP");
    }

    // Check if the device supports the Video Capture interface.
    // Video capture devices sample an analog video signal and store the digitized
    // images in memory. Today, nearly all devices can capture at full 25 or 30
    // frames/second. With this interface, applications can control the capture
    // process and move images from the driver into user space.
    if (!(capabilities.capabilities & V4L2_CAP_VIDEO_CAPTURE))
      throw std::runtime_error(m_device + " is not a video capture device");

    // Check if the device supports the streaming I/O method.
    // Streaming is an I/O method where only pointers to buffers are exchanged
    // between application and driver, the data itself is not copied.
    if (!(capabilities.capabilities & V4L2_CAP_STREAMING))
    throw std::runtime_error(m_device + " does not support streaming I/O");
  }

}}
