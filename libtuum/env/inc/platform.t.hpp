
#ifndef RTX_PLATFORM_T_H
#define RTX_PLATFORM_T_H

#include <boost/format.hpp>

namespace tuum {

  inline std::string _format(boost::format& f){
      return boost::str(f);
  }

  template<class T, class... Args>
  std::string _format(boost::format& f, T&& t, Args&&... args){
      return _format(f % std::forward<T>(t), std::forward<Args>(args)...);
  }

  template<typename... Arguments>
  std::string format(std::string const& fmt, Arguments&&... args)
  {
    boost::format f(fmt);
    return _format(f, std::forward<Arguments>(args)...);
  }

}

#endif
