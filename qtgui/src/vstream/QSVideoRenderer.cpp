
#include <iostream>

#include <QtCore/QDebug>
#include <QtQuick/QSGGeometryNode>

#include "materials/YUV2RGBMaterial.hpp"
#include "vstream/QSVideoRenderer.hpp"

namespace tuum { namespace gui {

  QSVideoRenderer::QSVideoRenderer(QObject *parent)
      : QThread(parent), m_texture(0),
        m_running(false), m_node(0)
  {
    m_camera = hal::hw.getCamera();
  }

  QSVideoRenderer::~QSVideoRenderer()
  {

  }

  QSGGeometryNode *QSVideoRenderer::createNode()
  {
    QSGGeometry *geometry;
    ImageStream* m_image = m_camera->getStream();

    if (!m_texture)
      m_texture = new VideoTexture(m_image->getWidth(), m_image->getHeight());

    if (!m_node) {
      m_node = new QSGGeometryNode();
      geometry = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 4);
      geometry->setDrawingMode(GL_TRIANGLE_STRIP);
      m_node->setGeometry(geometry);
      m_node->setFlag(QSGNode::OwnsGeometry);

      YUV2RGBMaterial *material = new YUV2RGBMaterial;
      material->setTexture(m_texture);
      m_node->setMaterial(material);
      m_node->setFlag(QSGNode::OwnsMaterial);
    }

    return m_node;
  }

  void QSVideoRenderer::updateGeometry(qreal x, qreal y, qreal width, qreal height)
  {
    QSGGeometry::TexturedPoint2D *vertices = m_node->geometry()->vertexDataAsTexturedPoint2D();

    vertices[0].x = x;
    vertices[0].y = y + height;
    vertices[0].tx = 0;
    vertices[0].ty = 1;

    vertices[1].x = x;
    vertices[1].y = y;
    vertices[1].tx = 0;
    vertices[1].ty = 0;

    vertices[2].x = x + width;
    vertices[2].y = y + height;
    vertices[2].tx = 1;
    vertices[2].ty = 1;

    vertices[3].x = x + width;
    vertices[3].y = y;
    vertices[3].tx = 1;
    vertices[3].ty = 0;
  }

  void QSVideoRenderer::startStream()
  {
    m_running = true;
    m_wait.wakeAll();
  }

  void QSVideoRenderer::stopStream()
  {
    m_running = false;
  }

  void QSVideoRenderer::run()
  {
    if (m_camera->openDevice() < 0) return;
    if (m_camera->startCapture() < 0) return;

    int ret;
    while (1) {
      ret = m_camera->captureFrame([this](hal::Camera::video_dev* dev, v4l2_buffer* buf) {
        updateTexture((uchar*)dev->buff_info[buf->index].start, dev->cap_width, dev->cap_height);
      });

      if(ret < 0) break;
    }

    m_camera->stopCapture();
    m_camera->closeDevice();
  }

  void QSVideoRenderer::updateTexture(const uchar *data, int width, int height)
  {
    if (!m_running) return;

    textureProcess(data, width, height);

    ImageStream* m_image = m_camera->getStream();
    m_image->swapImage();

    emit imageChanged();
  }

  void QSVideoRenderer::updateMaterial()
  {
    ImageStream* m_image = m_camera->getStream();
    m_texture->updateFrame(m_image->getFrontImage());
  }

  void QSVideoRenderer::textureProcess(const uchar *data, int width, int height)
  {
    ImageStream* m_image = m_camera->getStream();
    m_image->yuyv2rgb(data, width, height);
  }

}}
