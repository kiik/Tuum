/** @file Configuration.cpp
 *  Configuration class implementation.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 27. November 2015
 */

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "tuum_logger.hpp"
#include "tuum_configuration.hpp"

namespace tuum {

  Configuration::Configuration() {

  }

  int Configuration::init(std::string fn) {
    RTXLOG(format("Loading: %s.", fn), LOG_DEBUG);

    try {
      boost::property_tree::ini_parser::read_ini(fn, pt);
      printf("INIT LOADED.\n");
    } catch (std::exception& e) {
      RTXLOG(e.what(), LOG_ERR);
      return -1;
    }
    return 0;
  }

  int Configuration::getInt(std::string k) {
    return pt.get<int>(k);
  }

  std::string Configuration::getStr(std::string k) {
    return pt.get<std::string>(k);
  }

}
