
#include <sstream>
#include <fstream>

#include "tuum_logger.hpp"
#include "fs/tuum_file.hpp"

namespace tuum {

  File::File()
  {

  }

  File::File(file_t& file) {
    init(file);
  }

  File::~File() {
    deinit();
  }

  int File::init(file_t& file)  {
    if(!file.isValid()) return -1;
    m_file = file;

    printf("new File(%s, %i)\n", m_file.Path(), m_file.type);
    return 0;
  }

  void File::deinit() {
    m_file = {"", File::T_None};
  }

  int File::read(std::string& out)
  {
    if(!m_file.isValid()) return -1;

    std::ifstream ifs(m_file.path);
    out.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    return 0;
  }

  int File::write(const std::string& in, const Mode& mode)
  {
    if(!m_file.isValid()) return -1;

    switch(mode) {
      case Mode::M_Write:
      {
        std::ofstream ofs(m_file.path);
        ofs << in;
        break;
      }
      case Mode::M_Append:
      default:
      {
        std::ofstream ofs(m_file.path, std::fstream::app);
        ofs << in;
        break;
      }
    }

    return 0;
  }

  int File::edit(const std::string& in, const size_t& cursor, const Mode& mode)
  {
    if(!m_file.isValid()) return -1;
    std::fstream f;

    switch(mode) {
      case Mode::M_Write:
      {
        f.open(m_file.path);

        f.seekg(0, f.end);
        printf("dbg: %i\n", f.tellp());

        f.seekp(cursor, std::ios_base::beg);
        printf("dbg: %i\n", f.tellp());

        f << in;

        break;
      }
      case Mode::M_Append:
      default:
      {
        f.open(m_file.path);

        f.seekg(0, f.end);
        size_t f_size = f.tellg();

        size_t len = f_size - cursor;
        char* buf = new char[len];

        f.seekp(cursor, std::ios_base::beg);
        f.read(buf, len);

        f.seekp(cursor, std::ios_base::beg);
        f << in << buf;

        delete(buf);
        break;
      }
    }

    return 0;
  }

}
