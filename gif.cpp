#include "gif.h"

Gif::Gif(const QString &imgPath,bool once) :gifImg(imgPath),frameNum(0),frameCount(gifImg.frameCount()),once(once)
{

}

const QImage& Gif::getImage(bool paused, bool returnOrigin)
{
    if(returnOrigin){
        frameNum = 0;
        gifImg.jumpToFrame(frameNum);
    }
    else{if(!paused){
            gifImg.jumpToFrame(frameNum++);
            if(frameNum>=frameCount){
                if(!once){
                    frameNum = 0;
                }else{
                    frameNum--;
                }
            }
        }
    }
    currentImg = gifImg.currentImage();
    return currentImg;
}

