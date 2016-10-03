/** @file TSMeshRenderer.cpp
 *  @brief Mesh renderer component implementation.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#include <iostream>

#include "tuum_logger.hpp"

#include "components/TSMeshFilter.hpp"
#include "components/TSMeshRenderer.hpp"
#include "components/TSCamera.hpp"

namespace tuum { namespace ts {

  TSOType MeshRenderer::type;

  MeshRenderer::MeshRenderer():
    m_ready(false)
  {
    m_mat = new Material();
    ctx.reset();
  }

  int MeshRenderer::setup() {
    if(m_ready) return 0;

    if(m_mat->init() < 0) return -1;

    MeshFilter* f = getComponent<MeshFilter>();
    if(f) {
      Mesh* m = f->getMesh();
      if(m) {
        initContext(m);
      }
    }

    m_ready = false;
    return 0;
  }

  void MeshRenderer::render() {
    if(!m_ready) return;

    MeshFilter* f = getComponent<MeshFilter>();
    if(f) {
      if(!m_mat) return;
      Mesh* m = f->getMesh();

      if(setupContext(m) >= 0) {
        m->render();
        unloadContext(m);
      }
    }
  }

  int MeshRenderer::initContext(Mesh* m) {
    RTXLOG("Loading...");
    if(m->getAttrCtx(ctx) < 0) return -2;
    ctx.mvp = Camera::main->getMVP() * *transform;

    if(m_mat->initCtx(ctx) < 0) return -3;
    m_ready = true;
    return 0;
  }

  int MeshRenderer::setupContext(Mesh* m) {
    if(m->bind() < 0) return -1;

    if(m->getAttrCtx(ctx) < 0) return -2;
    ctx.mvp = Camera::main->getMVP() * *transform;

    if(m_mat->loadCtx(ctx) < 0) return -3;
    return 0;
  }

  int MeshRenderer::unloadContext(Mesh* m) {
    m_mat->clearCtx(ctx);
    ctx.reset();
    m->release();
    return 0;
  }

  TSOType* MeshRenderer::getType() const {
    return &MeshRenderer::type;
  }

}}
