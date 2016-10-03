/** @file TSResourceManager.hpp
 *  @brief Tuum scene 3D resources manager implementation.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include "tuum_logger.hpp"
#include "utils/ObjLoader.hpp"
#include "utils/ShaderLdr.hpp"

#include "TSResourceManager.hpp"

namespace tuum { namespace ts {

  ResourceListing ResourceManager::meshes;
  ResourceListing ResourceManager::shaders;

  id_t resource_t::id_seq = 1;

  ResourceManager::ResourceManager() {

  }

  Mesh* ResourceManager::loadMesh(const char* fp) {
    RTXLOG(format("Load '%s'", fp));
    //Mesh* m = mdl::obj::load_model(fp);

    bool Ret = false;
    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(fp, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    Mesh* m = nullptr;
    if (pScene) {
      MeshSet meshes;
      if(Mesh::ai_loadFromScene(pScene, meshes) < 0) {
        RTXLOG(format("Mesh scene load failed. ('%s')", fp));
        return nullptr;
      }
      if(meshes.size() <= 0) {
        RTXLOG(format("No mesh data found. ('%s')", fp));
        return nullptr;
      }

      m = meshes[1]; // TODO: Use all meshes
    } else {
      printf("Error parsing '%s': '%s'\n", fp, Importer.GetErrorString());
      return nullptr;
    }

    RTXLOG(format("Mesh '%s' loaded. (%i, %i)", fp, meshes.size(), m == nullptr));
    return m;
  }

  int ResourceManager::loadMeshes() {

  }

  int ResourceManager::loadShaders() {
    path p("./assets/shaders");

    try {
      if (exists(p)) {
        if (is_regular_file(p))
          std::cout << p << " size is " << file_size(p) << '\n';

        else if (is_directory(p))
        {
          std::cout << p << " is a directory containing:\n";

          for (directory_entry& x : directory_iterator(p)) {
            auto fp = x;
            if(fp.path().string().rfind(".shader") != -1) {
              std::cout << "    " << fp << '\n';
              resource_t* shader = new resource_t(fp.path().filename().string(), fp.path().string(), &Shader::type);
              shaders[shader->id] = shader;
            }
          }
        }
        else
          std::cout << p << " exists, but is not a regular file or directory\n";
      }
      else
        std::cout << p << " does not exist\n";
    }

    catch (const filesystem_error& ex)
    {
      std::cout << ex.what() << '\n';
    }

  }

  Shader* ResourceManager::getDefaultShader() {
    return getShader(1);
  }

  ResourceListing* ResourceManager::getMeshList() {
    return &meshes;
  }

  ResourceListing* ResourceManager::getShaderList() {
    return &shaders;
  }

  TSOBase* create_object(TSOType* type, const char* fp) {
    if(&Shader::type == type) return new Shader(fp);
    if(&Mesh::type == type) return new Mesh();

    RTXLOG("Unknown resource.", LOG_ERR);
    return nullptr;
  }

  Mesh* ResourceManager::getMesh(id_t id) {
    return (Mesh*)create_object(meshes[id]->type, meshes[id]->fp.c_str());
  }

  Shader* ResourceManager::getShader(id_t id) {
    if(shaders.find(id) == shaders.end()) return nullptr;
    return (Shader*)create_object(shaders[id]->type, shaders[id]->fp.c_str());
  }

}}
