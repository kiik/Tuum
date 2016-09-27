/** @file TSMeshRenderer.hpp
 *  @brief Mesh renderer component.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#ifndef TS_MESH_RENDERER_H
#define TS_MESH_RENDERER_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "3dcore/TSMaterial.hpp"
#include "3dcore/TSComponent.hpp"

namespace tuum { namespace ts {

  class MeshRenderer : public Component {
  public:
    MeshRenderer();

    int setup();

    void render();

    int initContext(Mesh*);
    int setupContext(Mesh*);
    int unloadContext(Mesh*);

    void setMaterial(Material* mat) { m_mat = mat; }
    Material* getMaterial() { return m_mat; }

    static TSOType type;
    TSOType* getType() const;

  protected:
    int renderMesh(Mesh*);

  private:
    Material* m_mat;

    Shader::attr_ctx ctx;
    bool m_ready;
  };

}}

#endif
