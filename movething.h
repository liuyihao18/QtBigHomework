#ifndef MOVETHING_H
#define MOVETHING_H

#include "direction.h"
#include <QRect>

class MoveThing
{
public:
    MoveThing();
    MoveThing(int x,int y, int width,int height, int direction, int move_speed);
    virtual void initialize();
    virtual void returnOriginPos();
    virtual void updatePos(int judge_unit);
    virtual void confirmPos();
    virtual void cancelPos();
    virtual void needToChangeMove();
    virtual const QRect& getTempPos();
    int getDirection() const;
    int getMoveSpeed() const;

protected:
    int direction;
    int originDirection;
    int move_speed;
    QRect tempPos;

};

#endif // MOVETHING_H
