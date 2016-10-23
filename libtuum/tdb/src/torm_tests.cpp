
#include "torm_tests.hpp"

namespace tuum { namespace db {

  int run_orm_tests() {
    DB_SAFE();

    tuum::db::FileORM file;
    tuum::db::value_map flt = {{"path", "assets/test2.ppl"}};

    file.setPath("assets/test2.ppl");
    file.setData("HEADER\nBODY\nCONTENTS");

    //add(&file);

    Query::row_t res;
    auto q = file.query()->filter(flt);

    if(q->exec(res) < 0) {
      RTXLOG("Query tests failed!", LOG_ERR);
    } else {
      printf("Results: %lu\n", res.size());

      /*
      auto dat = res;
      for(auto row = dat.begin(); row != dat.end(); row++) {
        printf("ROW:\n");
        auto r = *row;
        for(auto col = r.begin(); col != r.end(); col++) {
          printf("%s => %s\n", col->first.c_str(), col->second.c_str());
        }
        printf("\n");
      }*/

      auto r = res;
      for(auto col = r.begin(); col != r.end(); col++) {
        printf("%s => %s\n", col->first.c_str(), col->second.c_str());
      }
      printf("\n");

      RTXLOG("Query tests passed.");
    }

    return 0;
  }

}}
