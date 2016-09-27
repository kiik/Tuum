#ifndef RTX_VISION_RESPONSE_H
#define RTX_VISION_RESPONSE_H

#include <QtQuick/QQuickItem>

#include "TuumScene.hpp"

#include "tuum_visioning.hpp"

using namespace tuum::ts;

namespace tuum { namespace gui {

  class VisionResponse : public QQuickItem
  {
    Q_OBJECT
    Q_PROPERTY(bool play READ play WRITE setPlay NOTIFY playChanged)

  public:
    explicit VisionResponse(QQuickItem *parent = 0);
    ~VisionResponse();

    bool play() const { return mPlay; }
    void setPlay(bool);

    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

  signals:
    void playChanged(bool);

  public slots:
    void sync();
    void cleanup();

  private slots:
    void handleWindowChanged(QQuickWindow*);

  private:
    TuumScene *mScene;

    bool mPlay;
  };

}}

#endif // RTX_VISION_RESPONSE_H
