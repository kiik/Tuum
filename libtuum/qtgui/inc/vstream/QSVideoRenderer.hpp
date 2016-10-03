
#ifndef RTX_QSVIDEO_H
#define RTX_QSVIDEO_H

#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <QtQuick/QSGGeometryNode>

#include "hal.hpp"

#include "textures/VideoTexture.hpp"

using namespace tuum::hal;

namespace tuum { namespace gui {

  class QSVideoRenderer : public QThread
  {
    Q_OBJECT
  public:
    QSVideoRenderer(QObject *parent = 0);
    virtual ~QSVideoRenderer();

    void startStream();
    void stopStream();

    QSGGeometryNode *createNode();

    void updateGeometry(qreal x, qreal y, qreal width, qreal height);
    void updateMaterial();

    void run();

  Q_SIGNALS:
    void imageChanged();

  protected:
    void updateTexture(const uchar *data, int width, int height);
    virtual void textureProcess(const uchar *data, int width, int height);

  private:
    Camera* m_camera;

    bool m_running;
    QMutex m_wait_mutex;
    QWaitCondition m_wait;

    VideoTexture *m_texture;
    QSGGeometryNode *m_node;
  };

}}

#endif // RTX_QSVIDEO_H
