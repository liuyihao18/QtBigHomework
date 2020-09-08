#ifndef SECONDMONSTER_H
#define SECONDMONSTER_H

#include "monster.h"

class SecondMonster : public Monster
{
    Q_OBJECT
public:
    SecondMonster(QObject*parent=nullptr);
    SecondMonster(int x, int y, int width,int height, QObject* parent = nullptr);
    bool isUpToMaxUpHeight() const;
    void updatePos(int judge_unit) override;
    void needToChangeMove() override;

protected:
    bool reverse;
    int upHeight;
    int maxUpHeight;

};

#endif // SECONDMONSTER_H
