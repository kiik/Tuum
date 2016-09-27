/** @file TSResourceManager.hpp
 *  @brief Tuum scene 3D resources manager.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#ifndef RTX_RESMAN_H
#define RTX_RESMAN_H

#include <glm/glm.hpp>

#include "3dcore/TSObjectBase.hpp"
#include "3dcore/TSMesh.hpp"

namespace tuum { namespace ts {

  typedef unsigned int id_t;

  /**
   *  Contains relation between a file and an object
   */
  struct resource_t {
    static id_t id_seq;
    id_t id;

    std::string name;
    std::string fp;

    TSOType* type;
    TSOBase* obj;

    resource_t(std::string n, std::string f, TSOType* t) {
      id = resource_t::id_seq++;
      name = n;
      fp = f;
      type = t;
    }
  };

  typedef std::map<id_t, resource_t*> ResourceListing;

  class ResourceManager
  {
  public:
    ResourceManager();

    static Mesh* loadMesh(const char*);

    static Mesh* loadDefaultMesh();
    static Mesh* loadDemoMesh();

    static Shader* getDefaultShader();

    static int loadMeshes();
    static int loadShaders();

    static ResourceListing* getMeshList();
    static ResourceListing* getShaderList();

    static Mesh*   getMesh(id_t);
    static Shader* getShader(id_t);

  private:
    static ResourceListing meshes;
    static ResourceListing shaders;
  };

}}

#endif
