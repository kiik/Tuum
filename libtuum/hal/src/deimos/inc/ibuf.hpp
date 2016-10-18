#ifndef TUUM_IBUF_H
#define TUUM_IBUF_H

namespace tuum {

  /**
    Camera image buffer structure.
  */
  struct buf_t {
    void *data;
    size_t size;

    template<typename T>
    T getValue() {
      return (T)data;
    }

    buf_t():
      data(nullptr), size(0)
    {

    }

    ~buf_t() {
      if(data != nullptr) {
        delete(getValue<uint8_t*>());
        data = nullptr;
        size = 0;
      }
    }

  };

  typedef buf_t data_buf_t;

  struct Frame {
    unsigned char   *data;
    size_t width, height, size;
    size_t id;
  };

}

#endif
