
#include <memory>

#include <GL/glew.h>
#include <GL/glut.h>

#include "GLFW/glfw3.h"
#include "GLIPLib.hpp"
#include "Modules/FFT.hpp"

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

#include "cameraConstants.hpp"

#include "tuum_logger.hpp"
#include "platform.hpp"

#include "tuum_buff.hpp"
#include "hal.hpp"
#include "tuum_ogl.hpp"

using namespace Glip;
using namespace Glip::CoreGL;
using namespace Glip::Modules;
using namespace Glip::CorePipeline;

namespace tuum { namespace lpx {

  size_t width = CAMERA_WIDTH, height = CAMERA_HEIGHT;

  GLFWwindow* gWindow = nullptr;
  LayoutLoader gLoader;

  HdlTextureFormat streamFormat(width, height, GL_RGB, GL_UNSIGNED_BYTE);

  GeometryInstance* quad;

  HdlTexture* streamTexture;

  ImageStream* inputStream = nullptr;
  image_t processedFrame;
  boost::mutex outputFrameLock;

  Pipeline* pipe_testPipeline;

  size_t t0 = 0, dt = 0, printT = 0;

  void fps() {
    size_t t1 = millis();
    dt = dt * 0.7 + (t1-t0) * 0.3;
    //printf("FPS=%f.0\n", 1000.0 / dt);

    t0 = t1;

    if(t1 > printT) {
      std::cout << (1000.0 / dt) << std::endl;
      printT = t1 + 1000;
    }
  }

  void windowResize(GLFWwindow* win, int width, int height) {
    glViewport(0,0,width,height);
  }

  int ogl_init() {
    if(!glfwInit()) {
      RTXLOG("Failed to start GLFW.", LOG_ERR);
      return -1;
    }

    //glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, 0);

    gWindow = glfwCreateWindow(width,height, "libtuum::lpx", NULL, NULL);
    if(!gWindow) {
      glfwTerminate();
      RTXLOG("Failed to open GLFW window.", LOG_ERR);
      return -2;
    }

    glfwSetWindowSizeCallback(gWindow, windowResize);
    glfwMakeContextCurrent(gWindow);

    std::cout << "Vendor name   : " << HandleOpenGL::getVendorName() << std::endl;
    std::cout << "Renderer name : " << HandleOpenGL::getRendererName() << std::endl;
    std::cout << "GL version    : " << HandleOpenGL::getVersion() << std::endl;
    std::cout << "GLSL version  : " << HandleOpenGL::getGLSLVersion() << std::endl;

    HandleOpenGL::init();

    Glip::Modules::LayoutLoaderModule::addBasicModules(gLoader);


    return 0;
  }

  boost::thread* oglThr = nullptr;

  void pipe_proc() {
    glfwMakeContextCurrent(gWindow);

    while(1) {
      if(inputStream != nullptr) {
        while(!outputFrameLock.try_lock()) {};
        inputStream->read(processedFrame);
        processedFrame->id = inputStream->getSeq();
        lpx::pipeline_pass(processedFrame);

        outputFrameLock.unlock();
        //TODO: write to 'processedFrame'
      }
    }
  }

  void ogl_set_input(ImageStream* in) {
    inputStream = in;
  }

  void ogl_setup() {
    auto iprop = hal::hw.getCamera()->getFormat();
    width = iprop.width;
    height = iprop.height;

    quad = new GeometryInstance(GeometryPrimitives::StandardQuad(), GL_STATIC_DRAW_ARB);
    streamTexture = new HdlTexture(streamFormat);

    gLoader.addRequiredElement("inputFormat", streamFormat);
    pipe_testPipeline = gLoader.getPipeline("./assets/test.ppl", "TestPipeline");

    Env::spawnBuffer(processedFrame);

    if(oglThr == nullptr) {
      oglThr = new boost::thread(&pipe_proc);
    }

  }

  void ogl_process() {

  }


  int ogl_read_frame(image_t& out) {
    while(!outputFrameLock.try_lock()) {};
    processedFrame->paste(*out);
    outputFrameLock.unlock();
    return 0;
  }

  int pipeline_pass(image_t& io) {
    try
    {
      glClear(GL_COLOR_BUFFER_BIT);
      glLoadIdentity();

      streamTexture->write(io->data, GL_RGB, GL_UNSIGNED_BYTE);
      (*pipe_testPipeline) << (*streamTexture) << Pipeline::Process;
      pipe_testPipeline->out(0).read(io->data);
      //pipe_testPipeline->out(0).bind();

      //quad->draw();
      //glfwSwapBuffers(gWindow);
      //fps();
    }
    catch(Glip::Exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  }

}}
