#ifndef SECONDMONSTER_H
#define SECONDMONSTER_H

#include "monster.h"

class SecondMonster : public Monster
{
    Q_OBJECT
public:
    SecondMonster(QObject*parent=nullptr);
    SecondMonster(int x, int y, int width,int height, QObject* parent = nullptr);
};

#endif // SECONDMONSTER_H
