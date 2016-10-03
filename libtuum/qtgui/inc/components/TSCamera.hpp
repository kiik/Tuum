/** @file  TSCamera.hpp
 *  @brief Tuum scene camera class.
 *
 *  @author Meelik Kiik
 *  @date 26. May 2016
 *  @version 0.1
 */

#ifndef TS_CAMERA_H
#define TS_CAMERA_H

#include "3dcore/TSComponent.hpp"

#define TS_DEF_FOV 45.0
#define TS_DEF_ASPECT qreal(640) / qreal(480)
#define TS_DEF_FNEAR 3.0
#define TS_DEF_FFAR  7.0

namespace tuum { namespace ts {

  class Camera : public Component
  {
  public:
    Camera();

    int init(qreal = TS_DEF_FOV, qreal = TS_DEF_ASPECT, qreal = TS_DEF_FNEAR, qreal = TS_DEF_FFAR);

    QMatrix4x4 getWorldToCameraMx();
    QMatrix4x4 getProjectionMx();
    QMatrix4x4 getMVP();

    // Viewport setup
    static int setupMainCamera();

    // Global camera
    static Camera* main;

    static TSOType type;
    TSOType* getType() const;

  private:
    QMatrix4x4 view_mx;
    QMatrix4x4 proj_mx;

    qreal m_fov, m_aspect, m_zNear, m_zFar;
  };

}}

#endif // YUV2RGB_MATERIAL_H
