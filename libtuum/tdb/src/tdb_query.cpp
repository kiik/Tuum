
#include <sqlite3.h>

#include "tuum_db.hpp"

#include "tdb_query.hpp"

namespace tuum { namespace db {

  query_t::query_t(value_t tbl):
    m_table(tbl)
  {

  }

  query_t* query_t::filter(value_map in) {
    m_filters.insert(in.begin(), in.end());
    return this;
  }

  int query_t::all() {
    return run();
  }

  int query_t::compile() {
    _q = "SELECT * FROM files WHERE path = 'assets/test2.ppl';";
    return 0;
  }

  int query_t::execute() {
    sqlite3* db = gHandle;
    char *zErrMsg = 0;
    int rc;

    const char* data = "Callback function called";

    rc = sqlite3_exec(db, _q.c_str(), callback, (void*)data, &zErrMsg);
    if(rc != SQLITE_OK) {
      RTXLOG(format("SQL error: %s\n", zErrMsg), LOG_ERR);
      sqlite3_free(zErrMsg);
      return -1;
    }

    return 0;
  }

  int query_t::run() {
    if(!isReady()) return -1;

    if(compile() < 0) return -2;
    if(execute() < 0) return -3;

    return 0;
  }

}}
