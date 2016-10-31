
#ifndef TUUM_MODULE_H
#define TUUM_MODULE_H

#include "tuum_logger.hpp"

namespace tuum {

  class ProgramModule {
  public:
    typedef size_t id_t;

    static id_t id_seq;

    ProgramModule():
      m_id(id_seq++)
    {

    }

    virtual int init() {
      RTXLOG(format("Virtual '%s' instance initialized.", toString().c_str()));
      return 0;
    }

    virtual int setup() { return 0; }
    virtual int process() { return 0; }

    virtual int run() {
      if(init() < 0) return -1;
      if(setup() < 0) return -2;
      return process();
    }

    id_t getId() { return m_id; }

    std::string toString() { return format("<ProgramModule %i>", m_id); }

  protected:
    id_t m_id;
  };

}

#endif
