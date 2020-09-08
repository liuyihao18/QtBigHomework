#ifndef GIF_H
#define GIF_H

#include <QMovie>

class Gif
{
public:
    Gif(const QString& imgPath,bool once = false);
    const QImage& getImage();

protected:
    QMovie gifImg;
    QImage currentImg;
    int frameNum;
    int frameCount;
    bool once;
};

#endif // GIF_H
