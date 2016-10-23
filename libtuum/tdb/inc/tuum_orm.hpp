
#ifndef TUUM_ORM_H
#define TUUM_ORM_H

#include "tuum_db.hpp"

#include "tdb_query.hpp"

namespace tuum { namespace db {

  class Model
  {
  public:
    Model() {};

    void init() {
      _query.init(__table__());
    }

    query_t* query() { return &_query; }

  public:
    virtual const std::string __table__() const { return ""; };
    virtual value_map __row__() { return value_map(); }

  protected:
    query_t _query;
  };


  class SQLColumn
  {
  public:
    value_t name;
    bool assigned = false;

    SQLColumn() {};
  };

  template<typename T>
  class Column : public SQLColumn
  {
  public:
    T value;

    Column(value_t field) {
      name = field;
    }

    void set(T v) {
      value = v;
      if(!assigned) assigned = true;
    }

    T get() { return value; }

    void reset(T v) {
      value = v;
      assigned = false;
    }

  };

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

  int add();

  int run_orm_tests();

}}

#endif
