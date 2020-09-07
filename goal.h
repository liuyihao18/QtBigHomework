#ifndef GOAL_H
#define GOAL_H

#include "baseobject.h"

class Goal : public BaseObject
{
    Q_OBJECT
public:
    Goal(QObject* parent = nullptr);
    Goal(int x,int y,int width,int height,QObject* parent);
};

#endif // GOAL_H
