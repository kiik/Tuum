/** @file TSMaterial.hpp
 *  @brief Tuum scene material class.
 *
 *  @author Meelik Kiik
 *  @date 26. May 2016
 *  @version 0.1
 */

#ifndef TS_MATERIAL_H
#define TS_MATERIAL_H

#include <QtQuick/QSGTexture>

#include "3dcore/TSObjectBase.hpp"
#include "3dcore/TSMesh.hpp"
#include "3dcore/TSShader.hpp"

namespace tuum { namespace ts {

  class Material : public TSOBase
  {
  public:
    Material();
    ~Material();

    int init();

    int initCtx(Shader::attr_ctx);
    int loadCtx(Shader::attr_ctx);
    int clearCtx(Shader::attr_ctx);

    Shader* getShader() { return m_shader; }

    TSOType* getType() const;
    static TSOType type;

  private:
    //TODO: Textures, other additional shader components....
    Shader* m_shader;

    QOpenGLTexture* tex;

  };

}}

#endif
