
#include <iostream>
#include <sqlite3.h>

#include "tuum_logger.hpp"
#include "tuum_db.hpp"
#include "tuum_orm.hpp"

using namespace std;

namespace tuum { namespace db {

  const char* DB_FILE = "data.db";

  sqlite3 *gHandle = nullptr;

  static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;

    for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    return 0;
  }

  bool isReady() {
    if(gHandle == nullptr) return false;
    return true;
  }

  int open() {
    int res;
    res = sqlite3_open(DB_FILE, &gHandle);

    if(res) {
      RTXLOG(format("Can't open database: %s\n", sqlite3_errmsg(gHandle)), LOG_ERR);
      return -1;
    }

    return 0;
  }

  int close() {
    sqlite3_close(gHandle);
    gHandle = nullptr;
    return 0;
  }

  int init_tables() {
    char* zErrMsg = 0;
    sqlite3* db = gHandle;
    int rc;
    char* sql = "CREATE TABLE IF NOT EXISTS FILES("  \
          "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
          "PATH           TEXT    NOT NULL," \
          "DATA           TEXT    NOT NULL );";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }

    return 0;
  }

  int init() {
    open();
    init_tables();
    RTXLOG("Database ready.");

    run_orm_tests();

    close();

    return 0;
  }

}}
