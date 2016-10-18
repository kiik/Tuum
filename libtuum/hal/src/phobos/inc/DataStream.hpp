
#ifndef TUUM_DSTREAM_H
#define TUUM_DSTREAM_H

#include <cstring>
#include <stdint.h>

#include "ibuf.hpp"

namespace tuum {

  class DataStream
  {
  public:
    DataStream();
    ~DataStream();

    int init(size_t);
    void deinit();

    int write(void*, size_t);

    template<typename T>
    T* getData() { return m_fr; }

  protected:
    void swap();

  private:
    uint8_t *m_fr, *m_bk;
    size_t m_size, m_progress;
    bool m_init;
  };

}

#endif
