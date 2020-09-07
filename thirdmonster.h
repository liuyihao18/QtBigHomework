#ifndef THIRDMONSTER_H
#define THIRDMONSTER_H

#include "monster.h"

class ThirdMonster : public Monster
{
    Q_OBJECT
public:
    ThirdMonster(QObject* parent=nullptr);
    ThirdMonster(int x,int y, int width, int height, QObject* parent=nullptr);
};

#endif // THIRDMONSTER_H
