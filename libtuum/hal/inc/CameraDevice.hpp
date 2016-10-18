/** @file Camera.hpp
 *  Description placeholder.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 */

#ifndef RTX_CAMERA_DEV_H
#define RTX_CAMERA_DEV_H

namespace tuum { namespace hal {

  class Camera;

  class CameraDevice {
    public:
      virtual void setup() = 0;
      virtual void process() = 0;

      virtual void begin() = 0;
      virtual void loop() = 0;
      virtual void end() = 0;

  };

}};

#endif // RTX_CAMERA_DEV_H
