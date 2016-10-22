
#ifndef TUUM_DB_H
#define TUUM_DB_H

#include "platform.hpp"

class sqlite3;


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
 int i;

 for(i=0; i<argc; i++){
  printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
 }
 printf("\n");

 return 0;
}

namespace tuum { namespace db {

  extern sqlite3* gHandle;

  int init();

  bool isReady();

}}

#define DB_SAFE() if(!tuum::db::isReady()) return -1;

#endif
