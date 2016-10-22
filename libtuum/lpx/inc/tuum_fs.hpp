
#ifndef TUUM_FS_H
#define TUUM_FS_H

#include "tuum_file.hpp"

namespace tuum {

  File* NewFile(std::string path, File::Type type = File::T_Disk);

  int run_file_tests();

}

#endif
