
#ifndef TDB_QUERY_H
#define TDB_QUERY_H

//#include <boost/variant.hpp>

#include "tdb_types.hpp"

namespace tuum { namespace db {

  class query_t
  {
  public:
    typedef std::string sql_t;

    typedef value_map row_t;
    typedef std::vector<row_t> rows_t;

    //typedef boost::variant<rows_t, row_t> result_t;

    query_t();
    query_t(value_t);
    ~query_t();

    void init(value_t);

    query_t* filter(value_map);

    int exec(rows_t&);
    int exec(row_t&);

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
    rows_t _d;
  };

  typedef query_t Query;

}}

#endif
