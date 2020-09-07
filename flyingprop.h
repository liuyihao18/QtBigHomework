#ifndef FLYINGPROP_H
#define FLYINGPROP_H

#include "baseobject.h"
#include "movething.h"

class FlyingProp : public BaseObject, public MoveThing
{
    Q_OBJECT
public:
    FlyingProp(QObject* parent = nullptr);
};

#endif // FLYINGPROP_H
