#include "gif.h"

Gif::Gif(const QString &imgPath,bool once) :_gifImg(imgPath),_frameNum(0),_frameCount(_gifImg.frameCount()),_once(once)
{

}

const QImage& Gif::getImage(bool paused, bool returnOrigin)
{
    if(returnOrigin){
        _frameNum = 0;
        _gifImg.jumpToFrame(_frameNum);
    }
    else{if(!paused){
            _gifImg.jumpToFrame(_frameNum++);
            if(_frameNum>=_frameCount){
                if(!_once){
                    _frameNum = 0;
                }else{
                    _frameNum--;
                }
            }
        }
    }
    _currentImg = _gifImg.currentImage();
    return _currentImg;
}

