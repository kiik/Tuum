/** @file Camera.hpp
 *  Description placeholder.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 */

#ifndef RTX_CAMERA_H
#define RTX_CAMERA_H

namespace tuum { namespace hal {

  class Camera;

  class CameraDevice {
    public:
      virtual void init() = 0;
      //virtual void dispose();

      virtual void process() = 0;

      virtual void begin() = 0;
      virtual void loop() = 0;
      virtual void end() = 0;

      virtual bool getFrame(int&) = 0;  // Frame read function
  };

}};

#endif // RTX_CAMERA_H
