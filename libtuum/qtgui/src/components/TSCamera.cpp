/** @file  TSCamera.cpp
 *  @brief Tuum scene camera implementation.
 *
 *  @author Meelik Kiik
 *  @date 26. May 2016
 *  @version 0.1
 */

#include "components/TSCamera.hpp"

namespace tuum { namespace ts {

  TSOType Camera::type;
  Camera* Camera::main;

  int Camera::setupMainCamera() {
    Camera::main = new Camera();
    Camera::main->init();
  }

  Camera::Camera() {

  }

  int Camera::init(qreal fov, qreal aspect, qreal zNear, qreal zFar) {
    m_fov = fov; m_aspect = aspect; m_zNear = zNear; m_zFar = zFar;

    view_mx.setToIdentity();
    view_mx.translate(0.5f, -0.5f, -5.0f);
    proj_mx.setToIdentity();
    proj_mx.perspective(fov, aspect, zNear, zFar);
  }

  QMatrix4x4 Camera::getWorldToCameraMx() {
    // return sceneObject->transform
    return view_mx;
  }

  QMatrix4x4 Camera::getProjectionMx() {
    return proj_mx;
  }

  QMatrix4x4 Camera::getMVP() {
    return proj_mx * view_mx; // * model_mx
  }

  TSOType* Camera::getType() const {
    return &Camera::type;
  }

}}
