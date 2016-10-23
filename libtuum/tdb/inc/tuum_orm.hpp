
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

  int add();

}}

#endif
