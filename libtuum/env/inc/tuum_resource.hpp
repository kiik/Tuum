
#ifndef TUUM_RESOURCE_H
#define TUUM_RESOURCE_H

#include <string>

namespace tuum { namespace rsc {

  class Dynamic
  {
  public:
    Dynamic():
      m_data("")
    {

    }

    int load(std::string path)
    {
      return -1;
    }

    virtual void onLoad() {};

    std::string& getContent() { return m_data; }

  private:
    std::string m_data;
  };

}}

#endif
