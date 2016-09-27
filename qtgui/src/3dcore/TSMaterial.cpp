/** @file TSMaterial.hpp
 *  @brief Tuum scene material class. Handles shader related settings.
 *
 *  @author Meelik Kiik
 *  @date 26. May 2016
 *  @version 0.1
 */

#include <iostream>

#include "tuum_logger.hpp"
#include "TSResourceManager.hpp"

#include "3dcore/TSMaterial.hpp"

namespace tuum { namespace ts {

  TSOType Material::type;

  Material::Material():
    tex(nullptr), m_shader(nullptr)
  {

  }

  int Material::init() {
    if(!m_shader) m_shader = ResourceManager::getDefaultShader();
    if(!m_shader) {
      RTXLOG("Shader load failed!", LOG_ERR);
      return -1;
    }

    if(m_shader->init() < 0) {
      RTXLOG("Shader init failed!", LOG_ERR);
      return -2;
    }

    tex = new QOpenGLTexture(QImage(QString("./assets/img/Cube.png")).mirrored());
    if(!tex->create()) {
      RTXLOG("Texture load failed!", LOG_ERR);
      return -2;
    }

    RTXLOG(format("Texture loaded; id %i.", tex->textureId()), LOG_DEBUG);

    RTXLOG("Material initialized.");
    return 0;
  }

  Material::~Material() {
    if(tex) delete tex;
  }

  int Material::initCtx(Shader::attr_ctx ctx) {
    ctx.tex = tex;
    return m_shader->initAttributes(ctx);
  }

  int Material::loadCtx(Shader::attr_ctx ctx) {
    m_shader->bind();
    ctx.tex = tex;
    if(m_shader->setupAttributes(ctx) < 0) return -1;
    return 0;
  }

  int Material::clearCtx(Shader::attr_ctx ctx) {
    m_shader->release();
    return 0;
  }

  TSOType* Material::getType() const {
    return &Material::type;
  }

  /*
  int Material::compare(const QSGMaterial *o) const
  {
    Q_ASSERT(o && type() == o->type());
    const Material *other = static_cast<const Material *>(o);
    return m_texture->textureId() - other->texture()->textureId();
  }
  */

}}
