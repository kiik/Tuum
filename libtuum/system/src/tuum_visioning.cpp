/** @file tuum_vision.cpp
 *  @brief Vision system implementation.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 27. October 2016
 */

#include "mathematicalConstants.hpp"

#include "tuum_logger.hpp"
#include "tuum_ogl.hpp"
#include "tuum_ogl_core.hpp"

#include "Perspective.hpp"

#include "tuum_visioning.hpp"
#include "tuum_localization.hpp"

using namespace tuum::hal;

namespace tuum {

  const char* DEF_PPL_SIMPL = "./assets/simplify.ppl";
  const char* DEF_PPL_IMFORM = "./assets/imformat.ppl";

  const char* DEF_PPL_BLOBS  = "./assets/blobs.ppl";
  const char* DEF_PPL_GEOM = "./assets/geometry.ppl";

  vision::LayoutLoader* gLdr = create_layout_loader();

  Visioning::Visioning():
    m_cam_N(1), m_lid(0)
  {
    for(size_t i=0; i < m_cam_N; i++) {
      m_inpStreams[i] = nullptr;
      m_format[i] = nullptr;
    }
  }

  void Visioning::init() {
    Env::spawnBuffer(m_iFrame);
    Env::spawnBuffer(m_oFrame);

    m_inpStreams[0] = hal::hw.getCamera()->getStream();
    m_inpStreams[0]->initBuf(m_iFrame);
    m_inpStreams[0]->initBuf(m_oFrame);
    auto iprop = hal::hw.getCamera()->getFormat();

    m_format[0] = new TxFormat(iprop.width, iprop.height, GL_RGB, GL_UNSIGNED_BYTE);
    m_tex = new Texture(*m_format[0]);

    gLdr->addRequiredElement("inputFormat", *m_format[0]);

    m_plSimplify.use(gLdr);
    m_plImFormat.use(gLdr);
    //m_plGeom.use(gLdr);

    m_plSimplify.load(DEF_PPL_SIMPL, "SimplifyPipe");
    m_plImFormat.load(DEF_PPL_IMFORM, "ImFormatPipe");
    //m_plGeom.load(DEF_PPL_GEOM);

    RTXLOG("Ready.");
  }

  void Visioning::run() {
    if(nextFrame() > 0) {
      //if(!pplIsReady()) return -2;
      doFramePass();
    }
  }

  bool Visioning::pplIsReady() {
    if(!m_plSimplify.isReady()) return false;
    if(!m_plImFormat.isReady()) return false;
    //if(!m_plGeom.isReady()) return false;
    return true;
  }

  int Visioning::nextFrame() {
    uint8_t i = 0; //TODO: Multiple camera support
    if(m_inpStreams[i] == nullptr) return -1;

    while(!m_iFrameLock.try_lock()) {}; //TODO: Timeout

    ImageStream* strm = m_inpStreams[i];
    strm->read(m_iFrame);

    int res;
    if(m_iFrame->id != m_lid) res = 1;
    else res = 0;
    m_lid = m_iFrame->id;

    m_iFrameLock.unlock();
    return res;
  }

  int Visioning::readFrame(image_t& out) {
    while(!m_oFrameLock.try_lock()) {};
    m_oFrame->paste(*out);
    m_oFrameLock.unlock();
    return 0;
  }

  int Visioning::doFramePass()
  {
    Pipeline *ppl, *nppl;
    try
    {
      size_t id;
      while(!m_iFrameLock.try_lock()) {};
      m_tex->write(m_iFrame->data, GL_RGB, GL_UNSIGNED_BYTE);
      id = m_iFrame->id;
      m_iFrameLock.unlock();

      ppl = m_plSimplify.get();
      (*ppl) << (*m_tex) << Pipeline::Process;

      nppl = m_plImFormat.get();
      (*nppl) << ppl->out(0) << Pipeline::Process;
      ppl = nppl;

      //nppl = m_plGeom.get();
      //(*nppl) << ppl->out(0) << ppl->out(1) << Pipeline::Process;
      //ppl = nppl;

      while(!m_oFrameLock.try_lock()) {};
      ppl->out(0).read(m_oFrame->data);
      m_oFrame->id = id;
      m_oFrameLock.unlock();

      return 1;
    } catch(Glip::Exception& e) {
      std::cerr << e.what() << std::endl;
      return -3;
    }

    return 0;
  }

  void Visioning::setup() {
    if(gVision == nullptr) {
      gVision = new Visioning();
      gVision->init();
    }
  }

  void Visioning::process() {
    if(gVision != nullptr) gVision->run();
  }

  Visioning* gVision = nullptr;

}
