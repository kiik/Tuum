
#ifndef TUUM_DBFILE_H
#define TUUM_DBFILE_H

#include "tuum_file.hpp"

namespace tuum {

  class DBFile : public File
  {
  public:
    DBFile(file_t&);
    ~DBFile();

    int init(file_t&);
    void deinit();

    int read(std::string&);
    int write(const std::string&, const Mode& = Mode::M_Write);
    int edit(const std::string&, const size_t&, const Mode& = Mode::M_Write);

  };

}

#endif
