#ifndef MOVETHING_H
#define MOVETHING_H

#include "direction.h"
#include <QRect>

class MoveThing {
public:

    MoveThing();
    MoveThing(int x,
              int y,
              int width,
              int height,
              int directio_n,
              int _moveSpeed);
    virtual void         initialize();
    virtual void         returnOriginPos();
    virtual void         updatePos(int judge_unit);
    virtual void         confirmPos();
    virtual void         cancelPos();
    virtual void         needToChangeMove();
    virtual const QRect& getTempPos();
    int                  getDirection() const;
    void                 setDirection(int directio_n);
    int                  getMoveSpeed() const;

protected:

    int directio_n;
    int _originDirection;
    int _moveSpeed;
    QRect _tempPos;
};

#endif // MOVETHING_H
