
#include "tuum_fs.hpp"

#include "tuum_file.hpp"
#include "tuum_dbfile.hpp"

namespace tuum {

  File* NewFile(std::string path, File::Type type)
  {
    File::file_t ft;
    ft = {path, type};

    switch(type) {
      case File::T_Disk:
        return new File(ft);
      case File::T_Dbase:
        return new DBFile(ft);
    }

    return new File(ft);
  }

  int run_file_tests() {
    File* pipe_src = NewFile("assets/test2.ppl", File::T_Dbase);

    pipe_src->write("DATA\n", File::M_Append);

    std::string source = "YYY";
    if(pipe_src->edit(source, 5, File::M_Append) < 0) {
      RTXLOG("File write test failed!", LOG_ERR);
    } else {
      RTXLOG("File write test success.");
    }

    if(pipe_src->read(source) < 0) {
      RTXLOG("File read test failed!", LOG_ERR);
    } else {
      printf("\"%s\"\n", source.c_str());
      RTXLOG("File read test success.");
    }

    delete(pipe_src);
  }

}
