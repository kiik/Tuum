/** @file tuum_platform.cpp
 *  General application dependencies module.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 27. November 2015
 */

#include <string>
#include <iostream>

#include <boost/program_options.hpp>

#include "tuum_platform.hpp"

using namespace boost::program_options;

namespace tuum {

  Configuration gC;
  variables_map vm;

  const char  OPT_GUI[]   = "gui";
  const char* OPT_GUI_E[] = {"rem", "loc"};
  enum OPT_GUI_T {
    GUI_REMOTE = 0,
    GUI_LOCAL  = 1,
  };

  const char OPT_CONFIG[] = "config";
  const char OPT_DEF_CONFIG[] = "config.ini";

  int options_factory(int argc, char *argv[]) {
    options_description desc{"Options"};
    desc.add_options()
      ("help,h", "Produce help messages")
      (OPT_CONFIG, value<std::string>()->default_value(OPT_DEF_CONFIG), "Configuration file")
      (OPT_GUI, value<std::string>(), "Run graphical interface");

    store(parse_command_line(argc, argv, desc), vm);

    try {
      notify(vm);
    } catch (std::exception& e) {
      RTXLOG(e.what(), LOG_ERR);
      return 1;
    }
    return 0;
  }

  int process_options() {
    std::string buf;

    buf = vm["config"].as<std::string>();
    if(gC.init(buf) < 0) return -1;
    //RTXLOG("Configuration file not found!", LOG_ERR);

    if(vm.count(OPT_GUI)) {
      buf = vm[OPT_GUI].as<std::string>();

      if(buf == OPT_GUI_E[GUI_REMOTE]) {
        RTXLOG("Remote GUI", LOG_DEBUG);
      } else if(buf == OPT_GUI_E[GUI_LOCAL]) {
        RTXLOG("Local GUI", LOG_DEBUG);
      } else {

        RTXLOG(format("Unknown option '%s' at '--gui'", buf), LOG_ERR);
      }
    }

    return 0;
  }

  int init(int argc, char *argv[]) {
    if(options_factory(argc, argv)) return -1;
    if(process_options() < 0) return -2;
    return 0;
  }

}


namespace usr {

  tuum::ProgramModule* gTuumProgram = nullptr;

}
