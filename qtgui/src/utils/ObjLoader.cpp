
#include <iostream>

#include "utils/ObjLoader.hpp"

namespace mdl { namespace obj {

  bool parse_line(const char* header, obj_data_t& obj_data) {
    if ( strcmp(header, "v") == 0 )
    {
      glm::vec3 vertex;
      fscanf(obj_data.file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
      obj_data.vertices.push_back(vertex);
    }
    else if ( strcmp(header, "vt") == 0 )
    {
      glm::vec2 uv;
      fscanf(obj_data.file, "%f %f\n", &uv.x, &uv.y );
      obj_data.uvs.push_back(uv);
    }
    else if ( strcmp(header, "vn") == 0 )
    {
      glm::vec3 normal;
      fscanf(obj_data.file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
      obj_data.normals.push_back(normal);
    }
    else if ( strcmp(header, "f") == 0 )
    {
      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(obj_data.file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
      if (matches != 9){
          printf("File can't be read by our simple parser : ( Try exporting with other options )\n");
          return false;
      }

      obj_data.vertexIndices.push_back(vertexIndex[0] - 1);
      obj_data.vertexIndices.push_back(vertexIndex[1] - 1);
      obj_data.vertexIndices.push_back(vertexIndex[2] - 1);
      obj_data.uvIndices    .push_back(uvIndex[0] - 1);
      obj_data.uvIndices    .push_back(uvIndex[1] - 1);
      obj_data.uvIndices    .push_back(uvIndex[2] - 1);
      obj_data.normalIndices.push_back(normalIndex[0] - 1);
      obj_data.normalIndices.push_back(normalIndex[1] - 1);
      obj_data.normalIndices.push_back(normalIndex[2] - 1);
    }

    return true;
  }

  bool parse_file(const char* path, obj_data_t& obj_data) {
    obj_data.file = fopen(path, "r");
    if(obj_data.file == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }

    while(1) {
      char header[128];

      int res = fscanf(obj_data.file, "%s", header);
      if (res == EOF) break;
      else {
        if(!parse_line(header, obj_data)) return false;
      }
    }

    return true;
  }

  Mesh* process_data(obj_data_t data) {
    uint32_t i, j, k;
    Mesh* m = new Mesh();

    VertexSet*  verts = m->getVertices();
    VxIndexSet* inds  = m->getIndices();

    unsigned int face_n = data.vertexIndices.size() / 3;

    for(i=0; i < face_n; i++) {
      unsigned int ix = i*3;
      //printf("%u\n", ix);

      for(j=0; j < 3; j++) {
        k = ix + j;
        glm::vec3 vx = data.vertices[data.vertexIndices[k]];
        glm::vec2 uv = data.uvs[data.uvIndices[k]];
        glm::vec3 nm = data.normals[data.normalIndices[k]];

        verts->push_back(Vertex(vx, uv, nm));
        inds->push_back(k);

        //printf("(%i)[%i %i %i] - ", k, data.vertexIndices[k], data.uvIndices[k], data.normalIndices[k]);
        //printf("<vx %f,%f,%f>, <uv %f,%f>, <nm %f,%f,%f>\n", vx.x, vx.y, vx.z, uv.x, uv.y, nm.x, nm.y, nm.z);
      }
    }

    return m;
  }

  Mesh* load_model(const char* path) {
    setlocale(LC_NUMERIC, "C");
    obj_data_t obj_data;
    if(!parse_file(path, obj_data)) return nullptr;

    return process_data(obj_data);
  }

}}
