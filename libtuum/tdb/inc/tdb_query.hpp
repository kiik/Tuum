
#ifndef TDB_QUERY_H
#define TDB_QUERY_H

#include "tdb_types.hpp"

namespace tuum { namespace db {

  class query_t
  {
  public:

    query_t(value_t);

    query_t* filter(value_map);

    int all();

    int compile();
    int execute();
    int run();

  protected:
    value_set m_fields;
    value_t   m_table;
    value_map m_filters;

    std::string _q = "", _d = "";
  };

}}

#endif
