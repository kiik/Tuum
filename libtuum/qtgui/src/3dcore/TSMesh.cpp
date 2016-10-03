
#include <iostream>

#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <QtGui/QOpenGLFunctions>
#include <GL/glut.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3.h>

#include "tuum_logger.hpp"

#include "3dcore/TSMesh.hpp"

namespace tuum { namespace ts {

  TSOType Mesh::type;

  Mesh::Mesh():
    m_loaded(false), m_vao(nullptr)
  {

  }

  Mesh::~Mesh()
  {
    deinit();
  }

  int Mesh::init() {
    if(m_loaded) return 0;
    int res = 0;

    m_vao = new QOpenGLVertexArrayObject();
    if(!m_vao->create()) return -1;
    m_vao->bind();

    if(m_verts.size() > 0) {
      res = initBuffer<Vertex>(QOpenGLBuffer::VertexBuffer, m_vxbo, &m_verts.front(), m_verts.size(), true);
      if(res < 0 || !m_vxbo->isCreated()) return -10;
      RTXLOG("vertices loaded");
    }

    if(m_indices.size() > 0) {
      res = initBuffer<vx_id_t>(QOpenGLBuffer::IndexBuffer, m_indbo, &m_indices.front(), m_indices.size());
      if(res < 0 || !m_indbo->isCreated()) return -20;
      RTXLOG("indices loaded");
    }

    m_vao->release();

    m_loaded = true;
    RTXLOG("Mesh buffers initialized");
    debugPrint();

    return 0;
  }

  int Mesh::deinit() {
    std::cout << "Mesh buffers DEINIT" << std::endl;
    if(!m_loaded) return 0;

    m_vxbo->destroy();
    m_indbo->destroy();
    return -1;
  }

  void Mesh::render() {
    QOpenGLContext::currentContext()->functions()->glDrawElements(GL_TRIANGLE_STRIP, m_indices.size(), GL_UNSIGNED_SHORT, 0);

    //glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  int Mesh::getAttrCtx(Shader::attr_ctx& ctx) {
    if(m_vxbo->isCreated())  ctx.vertices = m_vxbo;
    if(m_indbo->isCreated()) ctx.indices  = m_indbo;
    ctx.vao = m_vao;
  }

  int Mesh::bind() {
    if(!m_loaded) return -1;
    m_vao->bind();
    return 0;
  }

  int Mesh::release() {
    if(!m_loaded) return -1;
    m_vao->release();
    return 0;
  }

  void Mesh::debugPrint() {
    std::cout << "Verts: " << m_verts.size()
              << ", indices: " << m_indices.size()
              << std::endl;
  }

  TSOType* Mesh::getType() const {
    return &Mesh::type;
  }


  int Mesh::ai_createFromMesh(const aiMesh* m, Mesh*& out) {
    VertexSet*  verts   = out->getVertices();
    VxIndexSet* indices = out->getIndices();

    for (unsigned int i = 0 ; i < m->mNumVertices ; i++) {
      const aiVector3D* pPos = &(m->mVertices[i]);
      const aiVector3D* pNormal = &(m->mNormals[i]) ? &(m->mNormals[i]) : &Zero3D;
      const aiVector3D* pTexCoord = m->HasTextureCoords(0) ? &(m->mTextureCoords[0][i]) : &Zero3D;

      Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
             glm::vec2(pTexCoord->x, pTexCoord->y),
             glm::vec3(pNormal->x, pNormal->y, pNormal->z));

      verts->push_back(v);
    }

    for (unsigned int i = 0 ; i < m->mNumFaces ; i++) {
      const aiFace& Face = m->mFaces[i];
      assert(Face.mNumIndices == 3);

      for(unsigned int j = 0; j < 3; j++) {
        indices->push_back(Face.mIndices[j]);
        printf("%i ", Face.mIndices[j]);
      }
      printf("\n");
    }

    return 0;
  }

  int Mesh::ai_loadFromScene(const aiScene* s, MeshSet& out) {
    RTXLOG(format("Loading %i meshes, %i materials...", s->mNumMeshes, s->mNumMaterials), LOG_DEBUG);
    out.resize(s->mNumMeshes);
    //m_Textures.resize(pScene->mNumMaterials);

    for (unsigned int i = 0 ; i < s->mNumMeshes ; i++) {
      const aiMesh* ai_mesh = s->mMeshes[i];
      Mesh* mesh = new Mesh();
      if(ai_createFromMesh(ai_mesh, mesh) >= 0) {
        out.push_back(mesh);
      } else {
        RTXLOG(format("Mesh creation failed at #%i", i), LOG_ERR);
        delete mesh;
        return -1;
      }
    }

    return 0;
  }

}}
