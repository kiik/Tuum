/** @file StreamBase.hpp
 *  @brief Base streaming class.
 *
 * @authors Meelik Kiik
 * @date 18. October 2016
 * @version 0.1
 */

#ifndef TUUM_SBASE_H
#define TUUM_SBASE_H

#include "tuum_logger.hpp"
#include "tuum_buff.hpp"

namespace tuum {

  template<typename T>
  class StreamBase
  {
  public:
    StreamBase();
    ~StreamBase();

    int init(size_t);
    void deinit();

    virtual void postInit() {};
    virtual void postDeinit() {};

    int write(void*, size_t);
    void swap();

    size_t getSize();

    T getFront();
    T getBack();

    T* getStream();

  protected:
    T m_b1, m_b2;
    T m_fr, m_bk;

    size_t m_size, m_progress;
    bool m_init;
  };

  template<typename T>
  StreamBase<T>::StreamBase():
    m_b1(nullptr), m_b2(nullptr),
    m_size(0), m_progress(0),
    m_init(false)
  {

  }

  template<typename T>
  StreamBase<T>::~StreamBase()
  {
    deinit();
  }

  template<typename T>
  int StreamBase<T>::init(size_t size) {
    if(m_init) return -1;
    m_init = true;

    m_size = size;
    Env::spawnBuffer(m_b1, m_size);
    Env::spawnBuffer(m_b2, m_size);
    m_fr = m_b1;
    m_bk = m_b2;

    postInit();
    return 0;
  }

  template<typename T>
  void StreamBase<T>::deinit() {
    if(!m_init) return;
    m_init = false;

    m_size = 0;
    m_progress = 0;
    postDeinit();
  }

  template<typename T>
  int StreamBase<T>::write(void* ptr, size_t len) {
    size_t lim = m_size - m_progress;
    if(len > lim) {
      RTXLOG("stream buffer overflow!", LOG_ERR);
      len = lim;
    }

    memcpy((uint8_t*)ptr, (m_bk + m_progress), len);
    m_progress += len;

    if(m_progress >= m_size) swap();
    return 0;
  }

  template<typename T>
  void StreamBase<T>::swap() {
    if(m_fr == m_b1) {
      m_fr = m_b2;
      m_bk = m_b1;
    } else {
      m_fr = m_b1;
      m_bk = m_b2;
    }

    m_progress = 0;
  }

  template<typename T>
  size_t StreamBase<T>::getSize() { return m_size; }

  template<typename T>
  T StreamBase<T>::getFront() { return m_fr; }

  template<typename T>
  T StreamBase<T>::getBack() { return m_bk; }

  template<typename T>
  T* StreamBase<T>::getStream() { return &m_fr; }

}

#endif
