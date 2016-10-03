/** @file TuumScene.hpp
 *  @brief Tuum 3D scene class.
 *
 *  @author Meelik Kiik
 *  @date 24. May 2016
 *  @version 0.1
 */

#ifndef RTX_TSCENE_H
#define RTX_TSCENE_H

#include <vector>

#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <QtQuick/QSGGeometryNode>
#include <QtQuick/QQuickWindow>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

#include "hal.hpp"

#include "Entity.hpp"

#include "tuum_visioning.hpp"

#include "3dcore/TSEntity.hpp"

namespace tuum { namespace ts {

  typedef std::vector<TSEntity*> TSEntitySet;

  class TuumScene : public QThread, protected QOpenGLFunctions
  {
    Q_OBJECT
  public:
    TuumScene(QObject *parent = 0);
    ~TuumScene();

    int init();

    void updateTimedelta();
    bool FPSLimit();
    bool processLimit();

    void startScene();
    void stopScene();

    void setWindow(QQuickWindow *window) { mWindow = window; }
    void handleWindowChanged(int, int, int);

    bool isReady() { return m_loaded; }

    void update();
    void render();

    void run();

    void demoPaint();

    static double timeDelta;

  public slots:
    void paint();

  private:
    TSEntitySet mObjects;

    QQuickWindow *mWindow;
    QSize m_viewPortSize;

    bool m_running;
    QMutex m_wait_mutex;
    QWaitCondition m_wait;

    bool m_loaded;
    int x, y, w, h, p_h;
    unsigned long int lastTimeDeltaMoment, fpsLimitMoment, procLimitMoment;
  };

}}

#endif // RTX_QSVIDEO_H
