
#ifndef RTX_TSMESH_H
#define RTX_TSMESH_H

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <glm/glm.hpp>
#include <GL/glu.h>

#include "3dcore/TSObjectBase.hpp"
#include "3dcore/TSShader.hpp"

namespace tuum { namespace ts {

  const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

  typedef GLfloat  vx_size_t;
  typedef GLushort vx_id_t;

  class Mesh;

  struct Vertex {
    glm::vec3 pos;
    glm::vec2 uv;
    glm::vec3 nrm;

    Vertex(glm::vec3 p, glm::vec2 t, glm::vec3 n) {
      pos = p; uv = t; nrm = n;
    }
  };

  typedef std::vector<Vertex> VertexSet;
  typedef std::vector<vx_id_t> VxIndexSet;
  typedef std::vector<Mesh*> MeshSet;

  class Mesh : public TSOBase
  {
  public:
    Mesh();
    ~Mesh();

    int init();
    int deinit();

    void render();

    int getAttrCtx(Shader::attr_ctx&);

    VertexSet* getVertices() { return &m_verts; }
    VxIndexSet* getIndices() { return &m_indices; }

    int bind();
    int release();

    void debugPrint();

    TSOType* getType() const;
    static TSOType type;

    static int ai_createFromMesh(const aiMesh*, Mesh*&);
    static int ai_loadFromScene(const aiScene*, MeshSet&);

  protected:
    VertexSet   m_verts;
    VxIndexSet  m_indices;

  private:
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer* m_vxbo;
    QOpenGLBuffer* m_indbo;

    bool m_loaded;

  protected:

    template<typename e_size_t>
    int initBuffer(QOpenGLBuffer::Type type, QOpenGLBuffer*& buf,
                          e_size_t* ptr, unsigned int count,
                          bool sdraw = false) {
      buf = new QOpenGLBuffer(type);
      if(!buf->create()) return -1;

      if(sdraw) buf->setUsagePattern(QOpenGLBuffer::StaticDraw);
      if(!buf->bind()) return -2;

      buf->allocate(ptr, count * sizeof(e_size_t));
      buf->release();
      return 0;
    }
  };

}}

#endif // TS_MESH_H
