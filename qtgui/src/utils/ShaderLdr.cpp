/** @file ShaderLdr.cpp
 *  @brief Primitive shader loader implementation.
 *
 *  @author Meelik Kiik
 *  @date 30. May 2016
 *  @version 0.1
 */

#include <iostream>

#include "tuum_logger.hpp"
#include "utils/ShaderLdr.hpp"

using namespace tuum;
using namespace tuum::ts;

namespace shldr {

  const char SPACE_START = '{';
  const char SPACE_END   = '}';

  const char* PROGRAM_BEGIN = "GLSLPROGRAM";
  const char* PROGRAM_END   = "ENDGLSL";

  const char* SHADER_VERT = "[Vertex]";
  const char* SHADER_FRAG = "[Fragment]";

  enum ProgramE {
    PE_NONE,
    PE_VERT,
    PE_FRAG,
  };

  int parse_program(shader_data_t& obj_data, char* buf) {
    std::string glsl;
    int res;
    ProgramE program_space = PE_NONE;

    while(1) {
      fgets(buf, 256*2, obj_data.file);

      if(feof(obj_data.file)) {
        RTXLOG("Unexpected end of file.", LOG_ERR);
        return -1;
      }

      if(strstr(buf, PROGRAM_END)) return 0;

      else if(strstr(buf, SHADER_VERT)) {
        program_space = PE_VERT;
      } else if(strstr(buf, SHADER_FRAG)) {
        program_space = PE_FRAG;
      } else {
        switch(program_space) {
          case PE_VERT:
            obj_data.vert += buf;
            break;
          case PE_FRAG:
            obj_data.frag += buf;
            break;
        }
      }
    }

  }

  int parse_subshader(shader_data_t& obj_data, char* buf) {
    bool entry = true;
    int l = 0, res;

    while(l >= 0) {
      res = fscanf(obj_data.file, "%s", buf);

      if(res == 0 || res == EOF) {
        RTXLOG("Unexpected end of file.", LOG_ERR);
        return -1;
      }

      switch(l) {
        case 0:
          if(buf[0] == SPACE_END) {
            if(entry) {
              RTXLOG(format("Expected initializer before '%s' token", buf), LOG_ERR);
              return -2;
            }

            return 0;
          }

          if(buf[0] == SPACE_START) l++;
          else {
            RTXLOG(format("Unexpected symbol '%s'!", buf), LOG_ERR);
            return -3;
          }
          break;
        case 1: // SubShader space
          if(entry) entry = false;

          if(buf[0] == SPACE_END) l--;
          else if(strcmp(buf, PROGRAM_BEGIN) == 0) {
            if(parse_program(obj_data, buf) < 0) return -4;
          } else {
            RTXLOG(format("Unexpected symbol '%s'!", buf), LOG_ERR);
            return -5;
          }
          break;
      }
    }

    return 0;
  }

  int parse_shader(shader_data_t& obj_data, char* buf) {
    if(fscanf(obj_data.file, "%s", buf) == 0) return -1;

    if(buf[0] == SPACE_END) {
      RTXLOG(format("Unexpected symbol '%s'!", buf), LOG_ERR);
      return -1;
    }

    if(fscanf(obj_data.file, "%s", buf) == 0) return -2;
    if(strcmp(buf, "SubShader") != 0) {
      RTXLOG(format("Unexpected symbol '%s', expecting object!", buf), LOG_ERR);
      return -3;
    }

    if(parse_subshader(obj_data, buf) < 0) return -4;

    return 0;
  }

  int parse_file(const char* path, shader_data_t& obj_data) {
    obj_data.file = fopen(path, "r");
    if(obj_data.file == NULL ) {
      printf("Impossible to open the file !\n");
      return -1;
    }

    char buf[256*2];
    bool shader_present = false;
    while(1) {
      int res = fscanf(obj_data.file, "Shader \"%s\"", buf);
      if(res == 0 || res == EOF) {
        if(!shader_present) return -1;
        return 0;
      }

      std::string data = buf;
      obj_data.name = data.substr(0, data.size() - 1);

      res = parse_shader(obj_data, buf);
      if(res < 0) {
        RTXLOG(format("'parse_shader' exited with error code %i.", res), LOG_ERR);
        return -2;
      } else {
        if(!shader_present) shader_present = true;
      }
    }

    fclose(obj_data.file);
    return 0;
  }

  int validate_shader_data(shader_data_t obj_data) {

    return 0;
  }

  int load_shader(const char* fp, shader_data_t& data) {
    if(parse_file(fp, data) < 0) return -1;
    return 0;
  }

}
