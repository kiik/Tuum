
#ifndef TUUM_FILE_H
#define TUUM_FILE_H

#include "platform.hpp"

namespace tuum {

  class File
  {
  public:
    enum Type {
      T_None,
      T_Disk,
      T_Asset,
      T_Dbase,
    };

    enum Mode {
      M_Read,
      M_Write,
      M_Append,
    };

    struct file_t {
      std::string path;
      Type type;

      file_t():
        path(""), type(Type::T_Disk)
      {

      }

      file_t(std::string p, Type t)
      {
        path = p;
        type = t;
      }

      bool isValid() {
        if(path == "") return false;
        if(type == Type::T_None) return false;
        return true;
      }

      const char* Path() { return path.c_str(); }
    };

    File();
    File(file_t&);
    ~File();

    virtual int init(file_t&);
    virtual void deinit();

    virtual int read(std::string&);
    virtual int write(const std::string&, const Mode& = Mode::M_Write);
    virtual int edit(const std::string&, const size_t&, const Mode& = Mode::M_Write);

  protected:
    file_t m_file;
    std::string m_data;
  };

}

#endif
