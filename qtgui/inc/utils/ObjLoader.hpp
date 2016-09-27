
#ifndef RTX_OBJLOADER_H
#define RTX_OBJLOADER_H

#include <vector>
#include <string>
#include <cstdio>
#include <cstring>

#include "3dcore/TSMesh.hpp"

using namespace tuum::ts;

namespace mdl { namespace obj {

  struct obj_data_t {
    FILE* file;

    std::vector< unsigned short > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;
  };

  Mesh* load_model(const char* path);

}}

#endif
