#ifndef FIRSTMONSTER_H
#define FIRSTMONSTER_H

#include "monster.h"

// 第一种怪物
class FirstMonster : public Monster
{
    Q_OBJECT
public:
    FirstMonster(QObject *parent=nullptr);
    FirstMonster(int x,int y, int width,int height,  QObject* parent=nullptr);
};

#endif // FIRSTMONSTER_H
