#ifndef FLYINGPROP_H
#define FLYINGPROP_H

#include "baseobject.h"

class FlyingProp : public BaseObject
{
    Q_OBJECT
public:
    FlyingProp(QObject* parent = nullptr);
    FlyingProp(int x,int y,int width,int height,const QString& imgPath,QObject* parent=nullptr);

};

#endif // FLYINGPROP_H
