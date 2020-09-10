#ifndef GIF_H
#define GIF_H

#include <QMovie>

class Gif {
public:

    Gif(const QString& imgPath,
        bool           _once = false);
    const QImage& getImage(bool paused = false,
                           bool returnOrigin = false);

protected:

    QMovie _gifImg;
    QImage _currentImg;
    int _frameNum;
    int _frameCount;
    bool _once;
};

#endif // GIF_H
