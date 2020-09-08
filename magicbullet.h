#ifndef MAGICBULLET_H
#define MAGICBULLET_H

#include "flyingprop.h"

class MagicBullet : public FlyingProp
{
    Q_OBJECT
public:
    MagicBullet(QObject* parent=nullptr);
    MagicBullet(int x,int y,int width,int height,QObject* parent=nullptr);
};

#endif // MAGICBULLET_H
