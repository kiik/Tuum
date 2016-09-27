/** @file TSShader.hpp
 *  @brief Tuum scene shader class.
 *
 *  @author Meelik Kiik
 *  @date 26. May 2016
 *  @version 0.1
 */

#ifndef TS_SHADER_H
#define TS_SHADER_H

#include <string>
#include <QtQuick/QSGMaterial>

#include <QtGui/QOpenGLTexture>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLBuffer>

#include "3dcore/TSObjectBase.hpp"

namespace tuum { namespace ts {

  class Shader : public TSOBase
  {
  public:
    struct attr_ctx {
      QOpenGLVertexArrayObject* vao;

      QOpenGLBuffer* vertices;
      QOpenGLBuffer* indices;

      QOpenGLTexture* tex;

      QMatrix4x4 mvp;

      void reset() {
        vertices = nullptr;
        indices  = nullptr;
        vao = nullptr;

        mvp.setToIdentity();
      }
    };

    Shader();
    Shader(const char*);

    ~Shader();

    int initAttributes(const attr_ctx);
    int setupAttributes(const attr_ctx);

    int loadSource(const char*);

    int init();

    //int setVertices();
    //int setUVs();

    void bind();
    void release();

    QOpenGLShaderProgram* getProgram();

    TSOType* getType() const;
    static TSOType type;

  private:
    QOpenGLShaderProgram* m_program;

    /** TODO: Dynamic attributes **/
    int atrb_vertices;
    int atrb_coords;
  };

}}

#endif // TS_SHADER_H
