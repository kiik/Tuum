#ifndef RTX_VIDEO_PLAYER_H
#define RTX_VIDEO_PLAYER_H

#include <QtQuick/QQuickItem>

#include "QSVideoRenderer.hpp"

namespace tuum { namespace gui {

  class VideoPlayer : public QQuickItem
  {
    Q_OBJECT
    Q_PROPERTY(bool play READ play WRITE setPlay NOTIFY playChanged)
  public:
    explicit VideoPlayer(QQuickItem *parent = 0);
    ~VideoPlayer();

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    bool play() const { return mPlay; }
    void setPlay(bool);

  signals:
    void playChanged(bool);

  private slots:
    void textureChanged();
    void boundChanged();

  private:
    QSVideoRenderer *mCamera;

    bool mPlay;
    bool mBoundChanged;
    bool mTextureChanged;
  };

}}

#endif // VIDEO_PLAYER_H
