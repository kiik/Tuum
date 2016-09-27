/** @file ShaderLdr.hpp
 *  @brief Primitive shader loader.
 *
 *  @author Meelik Kiik
 *  @date 30. May 2016
 *  @version 0.1
 */

#ifndef RTX_SHADER_LOADER_H
#define RTX_SHADER_LOADER_H

#include <algorithm>
#include <functional>
#include <cctype>


#include <vector>
#include <string>
#include <cstdio>
#include <cstring>

#include "3dcore/TSShader.hpp"

using namespace tuum::ts;

namespace shldr {

  // trim from start
  static inline std::string &ltrim(std::string &s) {
          s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
          return s;
  }

  // trim from end
  static inline std::string &rtrim(std::string &s) {
          s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
          return s;
  }

  // trim from both ends
  static inline std::string &trim(std::string &s) {
          return ltrim(rtrim(s));
  }

  struct shader_data_t {
    FILE* file;

    std::string name;
    std::string vert;
    std::string frag;

    //TODO: Attributes
  };

  int load_shader(const char*, shader_data_t&);

}

#endif
