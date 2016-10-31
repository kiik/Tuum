
#include "ppl/PipeBase.hpp"

#include "tuum_logger.hpp"
#include "tuum_ogl_core.hpp"

namespace tuum { namespace vision {

  LayoutLoader* create_layout_loader() {
    LayoutLoader* ldr = new LayoutLoader();
    Glip::Modules::LayoutLoaderModule::addBasicModules(*ldr);
    return ldr;
  }

  int PipeBase::load(const char* path, const char* ppl_name) {
    if(mLdr == nullptr) {
      RTXLOG("No loader setup.", LOG_ERR);
      return -1;
    }

    if(m_glPipe != nullptr) delete(m_glPipe);
    m_glPipe = mLdr->getPipeline(path, ppl_name);

    RTXLOG(format("Loaded '%s' from '%s'", ppl_name, path), LOG_DEBUG);
    return 0;
  }

}}
