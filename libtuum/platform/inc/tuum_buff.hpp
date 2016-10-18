/** @file tuum_buff.hpp
 *  @brief Buffer-type data structures.
 *
 * @authors Meelik Kiik
 * @date 18. October 2016
 * @version 0.1
 */

#ifndef TUUM_IBUF_H
#define TUUM_IBUF_H

#include <memory>
#include <cstring>

namespace tuum {

  extern int bf_id_seq;

  struct buf_base_t
  {
    int m_id;

    void *data;
    size_t size;

    buf_base_t():
      data(nullptr), size(0)
    {

    }

    ~buf_base_t() {
      deinit();
    }

    template<typename T = uint8_t>
    void init(size_t s) {
      deinit();
      size = s;
      data = new T[size];
      m_id = bf_id_seq++;
    }

    void deinit() {
      if(data != nullptr) {
        delete((uint8_t*)data);
        data = nullptr;
        size = 0;
      }
    }

    template<typename T = uint8_t>
    T* getValue() {
      return (T*)data;
    }

    void paste(buf_base_t* out) {
      memcpy((uint8_t*)out->data, (uint8_t*)data, size);
    }

  };

  struct buf_t : public buf_base_t
  {
    buf_t()
    {

    }

    buf_t(size_t s)
    {
      init(s);
    }

  };

  struct img_buf_t : public buf_base_t
  {
    size_t width, height;
    size_t stride;
    size_t id;

    img_buf_t():
      width(0), height(0), stride(0),
      id(0)
    {

    }

    img_buf_t(size_t size):
      width(0), height(0), stride(0),
      id(0)
    {
      init(size);
    }

    img_buf_t(size_t w, size_t h, size_t s = 3):
      width(w), height(h), stride(s)
    {
      init(w * h * s);
    }

    void setDimensions(size_t w, size_t h, size_t s) {
      width = w;
      height = h;
      stride = s;
    }

    void setDimensions(const img_buf_t& in) {
      width = in.width;
      height = in.height;
      stride = in.stride;
    }

  };

  typedef std::shared_ptr<buf_base_t> buffer_base_t;
  typedef std::shared_ptr<buf_t> buffer_t;
  typedef std::shared_ptr<img_buf_t> image_t;

  typedef buf_t data_buf_t;

  namespace Env {

    static int spawnBuffer(buffer_t& buf, size_t s) {
      buf = std::make_shared<buf_t>(s);
      return 0;
    }

    static int spawnBuffer(image_t& buf, size_t s) {
      buf = std::make_shared<img_buf_t>(s);
      return 0;
    }

  }

  typedef image_t Frame; // Deprecated

}

#endif
