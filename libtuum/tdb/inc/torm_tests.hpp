
#ifndef TORM_TESTS_H
#define TORM_TESTS_H

#include "tuum_orm.hpp"

namespace tuum { namespace db {

  class FileORM : public Model
  {
  public:
    FileORM():
      m_id("id"),
      m_path("path"), m_data("data")
    {
      Model::init();
    };

    std::string getPath() { return m_path.get(); }
    std::string getData() { return m_data.get(); }

    void setPath(std::string v) { m_path.set(v); }
    void setData(std::string v) { m_data.set(v); }

  protected:
    Column<sql::Integer> m_id;
    Column<sql::Text> m_path;
    Column<sql::Text> m_data;

  public:
    const std::string __table__() const { return std::string("files"); }

    value_map __row__() {
      value_map out;
      //if(m_id.assigned)
      //  out[m_id.name] = m_id.value;

      if(m_path.assigned)
        out[m_path.name] = m_path.value;

      if(m_path.assigned)
        out[m_data.name] = m_data.value;

      return out;
    }
  };

  int run_orm_tests();

}}

#endif
