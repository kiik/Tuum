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

#include "tuum_logger.hpp"

namespace tuum {

  struct img_prop_t {
    size_t width, height,
           stride, bytesPerPixel;

    size_t getSize() {
      return width * height * bytesPerPixel;
    }

  };

  extern int bf_id_seq;

  struct buf_base_t
  {
    int m_id = 0;

    void *data = nullptr;
    size_t size = 0;

    buf_base_t():
      data(nullptr), size(0)
    {

    }

    ~buf_base_t() {
      deinit();
    }

    template<typename T = uint8_t>
    void init(size_t s) {
      if(size != s) {
        deinit();
        data = new T[s];
      }

      size = s;
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
      paste(*out);
    }

    void paste(buf_base_t& out) {
      out.init(size);
      memcpy((uint8_t*)out.data, (uint8_t*)data, size);
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
    img_prop_t frm;
    size_t id;

    img_buf_t():
      frm({0, 0, 0, 0}),
      id(0)
    {

    }

    img_buf_t(size_t size):
      frm({0, 0, 0, 0}),
      id(0)
    {
      init(size);
    }

    img_buf_t(const img_prop_t& _frm):
      frm(_frm)
    {
      init(frm.getSize());
    }

    void setFormat(const img_prop_t& _frm) { frm = _frm; }
    void setFormat(const img_buf_t& in) { frm = in.frm; }

    void paste(img_buf_t& in) {
      buf_base_t::paste(in);
      in.setFormat(frm);
      in.m_id = m_id;
      in.id = id;
    }

    size_t getSize() { return frm.getSize(); }

  };

  typedef std::shared_ptr<buf_base_t> buffer_base_t;
  typedef std::shared_ptr<buf_t> buffer_t;
  typedef std::shared_ptr<img_buf_t> image_t;

  typedef buf_t data_buf_t;

  namespace Env {

    static int spawnBuffer(buffer_t& buf, size_t s = 0) {
      buf = std::make_shared<buf_t>(s);
      return 0;
    }

    static int spawnBuffer(image_t& buf, size_t s = 0) {
      buf = std::make_shared<img_buf_t>(s);
      return 0;
    }

  }

  typedef image_t Frame; // Deprecated

}

#endif
