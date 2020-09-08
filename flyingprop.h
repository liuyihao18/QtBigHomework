#ifndef FLYINGPROP_H
#define FLYINGPROP_H

#include "baseobject.h"
#include "hpreducer.h"

class FlyingProp : public BaseObject, public HPReducer
{
    Q_OBJECT
public:
    FlyingProp(QObject* parent = nullptr);
    FlyingProp(int x,int y,int width,int height,const QString& imgPath,int moveSpeed,int HPReduce, QObject* parent=nullptr);
    int getMoveSpeed() const;

protected:
    int moveSpeed;

};

#endif // FLYINGPROP_H
