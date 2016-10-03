
#include <QtQuick/qquickwindow.h>
#include <QtQuick/QSGNode>

#include "VisionResponse.hpp"

using namespace tuum::ts;

namespace tuum { namespace gui {

  VisionResponse::VisionResponse(QQuickItem *parent)
    : QQuickItem(parent), mPlay(false), mScene(0)
  {
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);

    connect(this, &QQuickItem::windowChanged, this, &VisionResponse::handleWindowChanged);

    mScene = new TuumScene(this);
    mScene->start();
  }

  VisionResponse::~VisionResponse()
  {

  }

  void VisionResponse::mousePressEvent(QMouseEvent * event)
  {
    printf("Press");
  }

  void VisionResponse::mouseReleaseEvent(QMouseEvent * event)
  {
    printf("Release");
  }

  void VisionResponse::setPlay(bool value)
  {
    if (mPlay == value)
      return;

    if (value)
      mScene->startScene();
    else
      mScene->stopScene();

    mPlay = value;
    emit playChanged(value);
  }

  void VisionResponse::handleWindowChanged(QQuickWindow *win)
  {
    if (win) {
      connect(win, &QQuickWindow::beforeSynchronizing, this, &VisionResponse::sync, Qt::DirectConnection);
      connect(win, &QQuickWindow::sceneGraphInvalidated, this, &VisionResponse::cleanup, Qt::DirectConnection);
      if(mScene) mScene->handleWindowChanged(width(), height(), parentItem()->height());
      win->setClearBeforeRendering(false);
    }
  }

  void VisionResponse::sync()
  {
    if(!mScene->isReady()) {
      mScene->init();
    }

    connect(window(), &QQuickWindow::beforeRendering, mScene, &TuumScene::paint, Qt::DirectConnection);
    mScene->setWindow(window());
  }

  void VisionResponse::cleanup()
  {
    if (mScene) {
      delete mScene;
      mScene = 0;
    }
  }

}}
