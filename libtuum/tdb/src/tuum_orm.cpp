
#include <memory>
#include <vector>
#include <sstream>
#include <map>
#include <sqlite3.h>

#include "tuum_logger.hpp"
#include "tuum_orm.hpp"
#include "tuum_db.hpp"

namespace tuum { namespace db {

  int add(Model* m)
  {
    if(m->__table__() == "") return -1;

    value_map dat = m->__row__();

    RTXLOG("TODO:", LOG_ERR);

    std::stringstream columns;
    std::stringstream values;

    columns << '(';
    values << '(';
    const char DELIMIT = ',';

    bool delim = false;
    for(auto it = dat.begin(); it != dat.end(); it++) {
      if(delim) {
        columns << DELIMIT;
        values << DELIMIT;
      } else {
        delim = true;
      }

      printf("FIELD: %s => %s\n", it->first.c_str(), it->second.c_str());
      columns << it->first;

      //TODO: Type handling
      values << '\'' << it->second << '\'';
    }

    columns << ')';
    values << ')';

    std::stringstream sql;

    sql << "INSERT INTO " << m->__table__() << ' ';
    sql << columns.str() << " VALUES " << values.str() << ';';
    RTXLOG(sql.str());

    char* zErrMsg = 0;
    sqlite3* db = gHandle;
    int rc;

    rc = sqlite3_exec(db, sql.str().c_str(), callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }

    return 0;
  }

}}
