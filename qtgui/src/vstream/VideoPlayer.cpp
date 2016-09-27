
#include <iostream>

#include <QtQuick/QSGNode>

#include "vstream/VideoPlayer.hpp"

namespace tuum { namespace gui {

  VideoPlayer::VideoPlayer(QQuickItem *parent)
    : QQuickItem(parent), mPlay(false), mBoundChanged(true), mTextureChanged(true)
  {
    setFlag(ItemHasContents, true);
    connect(this, &VideoPlayer::xChanged, this, &VideoPlayer::boundChanged);
    connect(this, &VideoPlayer::yChanged, this, &VideoPlayer::boundChanged);
    connect(this, &VideoPlayer::widthChanged, this, &VideoPlayer::boundChanged);
    connect(this, &VideoPlayer::heightChanged, this, &VideoPlayer::boundChanged);

    mCamera = new QSVideoRenderer(this);

    connect(mCamera, &QSVideoRenderer::imageChanged, this, &VideoPlayer::textureChanged);
    mCamera->start();
  }

  VideoPlayer::~VideoPlayer()
  {

  }

  void VideoPlayer::setPlay(bool value)
  {
    if (mPlay == value)
      return;

    if (value)
      mCamera->startStream();
    else
      mCamera->stopStream();

    mPlay = value;
    emit playChanged(value);
  }

  void VideoPlayer::boundChanged()
  {
    mBoundChanged = true;
    update();
  }

  void VideoPlayer::textureChanged()
  {
    mTextureChanged = true;
    update();
  }

  QSGNode *VideoPlayer::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
  {
    QSGGeometryNode *node;

    if (!oldNode) node = mCamera->createNode();
    else node = static_cast<QSGGeometryNode *>(oldNode);

    if (mBoundChanged) {
      mCamera->updateGeometry(0, 0, width(), height());
      mBoundChanged = false;
      node->markDirty(QSGNode::DirtyGeometry);
    }

    if (mTextureChanged) {
      mCamera->updateMaterial();
      mTextureChanged = false;
      node->markDirty(QSGNode::DirtyMaterial);
    }

    return node;
  }

}}
