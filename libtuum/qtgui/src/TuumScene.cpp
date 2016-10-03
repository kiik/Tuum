/** @file TuumScene.hpp
 *  @brief Tuum 3D scene class implementation.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#include <iostream>
#include <QtQuick/qquickwindow.h>

#include "components/TSMeshFilter.hpp"
#include "components/TSMeshRenderer.hpp"
#include "components/TSCamera.hpp"
#include "components/TSDemoComponent.hpp"

#include "TSResourceManager.hpp"
#include "TSEntityManager.hpp"

#include "TuumScene.hpp"

namespace tuum { namespace ts {

  double TuumScene::timeDelta;

  Mesh* mesh = nullptr;

  TuumScene::TuumScene(QObject *parent):
    QThread(parent), m_running(true), m_loaded(false),
    x(0), y(0), w(480), h(360), p_h(360),
    lastTimeDeltaMoment(0), fpsLimitMoment(0), procLimitMoment(0)
  {
    std::cout << "TuumScene()" << std::endl;
  }

  TuumScene::~TuumScene()
  {
    for(auto & obj : mObjects) {
      delete obj;
    }
  }

  int TuumScene::init() {
    if(m_loaded) return 0;

    initializeOpenGLFunctions();

    ResourceManager::loadShaders();
    auto set = ResourceManager::getShaderList();

    id_t id = 0;
    for(auto it = set->begin(); it != set->end(); it++) {
      RTXLOG(format("<Shader #%i, '%s'>", it->second->id, it->second->fp));
      id = it->first;
    }

    if(id != 0) {
      Shader* sh = ResourceManager::getShader(id);
      if(sh) {
        RTXLOG("Test shader loaded.");
        delete sh;
      } else {
        RTXLOG("Test shader load failed!");
      }
    }

    Camera::setupMainCamera();

    // Create demo
    Entity* ent = new Entity();

    TSEntity* obj = EntityManager::createObject();
    obj->setProjectionTarget(ent);

    MeshFilter* c = obj->getComponent<MeshFilter>();
    if(c) {
      std::cout << c->name() << std::endl;
      Mesh* m = ResourceManager::loadMesh("./assets/models/cube.obj");
      if(m) c->setMesh(m);
      else RTXLOG(format("Mesh load failed. (%i)", m == nullptr), LOG_ERR);
    }
    obj->addComponent(new DemoComponent());

    mObjects.push_back(obj);

    m_loaded = true;
    return 0;
  }

  void TuumScene::startScene()
  {
    std::cout << "startScene()" << std::endl;
    m_running = true;
    m_wait.wakeAll();

    lastTimeDeltaMoment = millis();
  }

  void TuumScene::stopScene()
  {
    std::cout << "stopScene()" << std::endl;
    m_running = false;
  }

  void TuumScene::updateTimedelta() {
    unsigned long int t = millis();
    TuumScene::timeDelta = double(t - lastTimeDeltaMoment) / 1000.0f;

    lastTimeDeltaMoment = t;
  }

  long double frame_period = (1000.0f / 30.0f);
  long double process_period = (1.0f);

  bool TuumScene::FPSLimit() {
    unsigned long int t = millis();
    unsigned long int dT = t - fpsLimitMoment;
    if(dT < frame_period) {
      return true;
    }
    //std::cout << "dT: " << dT << "; Tmin: " << frame_period << std::endl;
    //std::cout << "t: " << t << "; l_tD: " << l_tD << std::endl;

    fpsLimitMoment = t;
    return false;
  }

  bool TuumScene::processLimit() {
    unsigned long int t = millis();
    unsigned long int dT = t - procLimitMoment;
    if(dT < process_period) {
      return true;
    }
    //std::cout << "dT: " << dT << "; Tmin: " << process_period << std::endl;
    //std::cout << "t: " << t << "; last_moment: " << procLimitMoment << std::endl;

    procLimitMoment = t;
    return false;
  }

  void TuumScene::run()
  {
    while(true) {
      if(m_running) {
        if(m_loaded) {
          update();
        }
      }
    }
  }

  void TuumScene::update()
  {
    if(processLimit()) return;
    updateTimedelta();
    for(auto & obj : mObjects) {
      obj->update();
    }
  }

  void TuumScene::render()
  {
    for(auto & obj : mObjects) {
      obj->render();
    }
  }

  void TuumScene::demoPaint() {
    auto fn = QOpenGLContext::currentContext()->functions();
    fn->glViewport(x, y, w, h);
    fn->glEnable(GL_SCISSOR_TEST);
    fn->glScissor(x, y, w, h);

    fn->glClearColor(166.0f/255.0f, 107.0f/255.0f, 190.0f/255.0f, 1);
    fn->glEnable(GL_DEPTH_TEST);
    fn->glEnable(GL_CULL_FACE);

    fn->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render();

    fn->glDisable(GL_SCISSOR_TEST);
  }

  long int last_fps_sample = 0;
  int frames[3] = {0, 0, 0};
  int frame_ix = 0;
  int frameAvg = 0, fpsTarget = 30;

  void TuumScene::paint()
  {
    if(FPSLimit()) return;

    frames[frame_ix]++;
    if(millis() - last_fps_sample >= 1000) {
      int v = (frames[0] + frames[1] + frames[2]) / 3.0f;
      std::cout << "FPS: " << v << std::endl;
      last_fps_sample = millis();
      frame_ix = (frame_ix + 1) % 3;
      frames[frame_ix] = 0;

      if(abs(frameAvg - v) < 10) {
        int dF = fpsTarget - v;
        if(abs(dF) > 6) {
          frame_period += -1.0f*dF*0.2f;
        }

      }

      frameAvg = v;
    }

    mWindow->resetOpenGLState();
    demoPaint();
    mWindow->update();
    mWindow->resetOpenGLState();
  }

  void TuumScene::handleWindowChanged(int W, int H, int p_H) {
    w = W; h = H; p_h = p_H;
    y = p_H - h;
  }

}}
