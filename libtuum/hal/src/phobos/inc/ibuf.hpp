#ifndef TUUM_IBUF_H
#define TUUM_IBUF_H

namespace tuum {

  /**
    Camera image buffer structure.
  */
  struct data_buf_t {
    void *data;
    size_t size;
  };

  struct Frame {
    unsigned char   *data;
    size_t width, height, size;
    size_t id;
  };

}

#endif
