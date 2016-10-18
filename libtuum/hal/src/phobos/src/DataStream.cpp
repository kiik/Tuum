
#include "DataStream.hpp"

namespace tuum {

  DataStream::DataStream():
    m_fr(nullptr), m_bk(nullptr),
    m_size(0), m_progress(0),
    m_init(false)
  {

  }

  DataStream::~DataStream()
  {
    deinit();
  }

  int DataStream::init(size_t size) {
    //TODO: if(m_init) ...

    m_size = size;
    m_fr = new uint8_t[m_size];
    m_bk = new uint8_t[m_size];

    m_init = true;
    return 0;
  }

  void DataStream::deinit() {
    if(!m_init) return;
    m_init = false;

    delete(m_fr);
    delete(m_bk);

    m_fr = nullptr;
    m_bk = nullptr;
    m_size = 0;
    m_progress = 0;
  }

  int DataStream::write(void* ptr, size_t len) {
    size_t lim = m_size - m_progress;
    if(len > lim) len = lim;

    memcpy((uint8_t*)ptr, (m_bk + m_progress), len);
    m_progress += len;

    if(m_progress >= m_size) swap();
    return 0;
  }

  void DataStream::swap() {
    uint8_t* ptr = m_fr;
    m_fr = m_bk;
    m_bk = ptr;

    m_progress = 0;
  }

}
