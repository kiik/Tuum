
#include "fs/tuum_dbfile.hpp"

namespace tuum {

  DBFile::DBFile(file_t& file)
  {
    init(file);
  }

  DBFile::~DBFile()
  {

  }

  int DBFile::init(file_t& file)
  {
    m_file = file;
    RTXLOG("DBG");
  }

  void DBFile::deinit()
  {
    RTXLOG("DBG");
  }

  int DBFile::read(std::string& out)
  {
    RTXLOG("TODO READ", LOG_ERR);

    //db::value_map dat = {{"path" = m_file.path}};
    //query()->filter(dat)->first();

    return -1;
  }

  int DBFile::write(const std::string& in, const File::Mode& mode)
  {
    RTXLOG("TODO WRITE", LOG_ERR);
    return -1;
  }

  int DBFile::edit(const std::string& in, const size_t& cursor, const Mode& mode)
  {
    RTXLOG("TODO EDIT", LOG_ERR);
    return -1;
  }

}
