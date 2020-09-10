#ifndef FLYINGPROP_H
#define FLYINGPROP_H

#include "baseobject.h"
#include "hpreducer.h"
#include "movething.h"

class FlyingProp : public BaseObject, public HPReducer, public MoveThing {
    Q_OBJECT

public:

    FlyingProp(QObject *parent = nullptr);
    FlyingProp(int            x,
               int            y,
               int            width,
               int            height,
               const QString& imgPath,
               int            directio_n,
               int            moveSpeed,
               int            _HPReduce,
               QObject       *parent = nullptr);
    void updatePos(int judge_unit) override;
    void confirmPos() override;
    void cancelPos() override;
};

#endif // FLYINGPROP_H
