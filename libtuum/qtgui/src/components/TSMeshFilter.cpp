/** @file TSMeshFilter.cpp
 *  @brief Mesh filter component implementation.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#include "tuum_logger.hpp"

#include "3dcore/TSObjectBase.hpp"
#include "3dcore/TSComponent.hpp"

#include "components/TSMeshFilter.hpp"
#include "components/TSMeshRenderer.hpp"

namespace tuum { namespace ts {

  TSOType MeshFilter::type;

  MeshFilter::MeshFilter():
    mesh(nullptr)
  {

  }

  Mesh* MeshFilter::getMesh() { return mesh; };

  void MeshFilter::setMesh(Mesh* m) {
    mesh = m;

    int res = m->init();
    if(res < 0) {
      RTXLOG(format("Mesh initialization returned with error code '%i'", res), LOG_ERR);
    }

    MeshRenderer* r = getComponent<MeshRenderer>();
    if(r) {
      r->initContext(m);
    }
  }

  TSOType* MeshFilter::getType() const {
    return &MeshFilter::type;
  }

}}
