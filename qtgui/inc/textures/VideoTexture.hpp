#ifndef VIDEO_TEXTURE_H
#define VIDEO_TEXTURE_H

#include <QtGui/QOpenGLTexture>
#include <QtQuick/QSGTexture>

namespace tuum { namespace gui {

  class VideoTexture : public QSGTexture
  {
  public:
    VideoTexture(int width, int height);
    virtual ~VideoTexture();

    virtual void bind() { glBindTexture(GL_TEXTURE_2D, mTexture); }
    virtual bool hasAlphaChannel() const { return false; }
    virtual bool hasMipmaps() const { return false; }
    virtual int textureId() const { return mTexture; }
    virtual QSize textureSize() const { return QSize(mWidth, mHeight); }

    void updateFrame(void *data);

  private:
    int mWidth;
    int mHeight;
    GLuint mTexture;
  };
}}

#endif // VIDEO_TEXTURE_H
