
#ifndef TDB_TYPES_H
#define TDB_TYPES_H

#include <string>
#include <vector>
#include <map>

namespace tuum { namespace db {

  typedef std::string value_t;
  typedef std::vector<value_t> value_set;
  typedef std::map<value_t, value_t> value_map;

  namespace sql {
    typedef std::string Text;
    typedef int Integer;
  }

}}

#endif
