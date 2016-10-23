
#ifndef TDB_QUERY_H
#define TDB_QUERY_H

#include "tdb_types.hpp"

namespace tuum { namespace db {

  class query_t
  {
  public:
    typedef std::string sql_t;
    typedef std::vector<value_map> result_t;

    query_t();
    query_t(value_t);

    void init(value_t);

    query_t* filter(value_map);

    int all(result_t&);
    int first(result_t&);

    int compile();
    int execute();
    int run();

    int hook(int, char**, char**);

    static int query_callback(void *target, int argc, char** argv, char **coln){
      query_t* t = reinterpret_cast<query_t*>(target);
      return t->hook(argc, argv, coln);
    }

  public:
    value_set m_fields;
    value_t   m_table;
    value_map m_filters;

    sql_t _q = "";
    result_t _d;
  };

  typedef query_t Query;

}}

#endif
