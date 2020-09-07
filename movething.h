#ifndef MOVETHING_H
#define MOVETHING_H

#include <QRect>

class MoveThing
{
public:
    MoveThing();
    MoveThing(int x,int y, int width,int height, int move_speed);
    virtual void initialize();
    virtual void returnOriginPos();
    virtual void updatePos(int judge_unit);
    virtual void confirmPos();
    virtual void cancelPos();
    virtual const QRect& getTempPos();
    int getMoveSpeed() const;

protected:
    int move_speed;
    QRect tempPos;
};

#endif // MOVETHING_H
