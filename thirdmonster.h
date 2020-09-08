#ifndef THIRDMONSTER_H
#define THIRDMONSTER_H

#include "monster.h"

class ThirdMonster : public Monster
{
    Q_OBJECT
public:
    ThirdMonster(QObject* parent=nullptr);
    ThirdMonster(int x,int y, int width, int height, QObject* parent=nullptr);
    void updatePos(int judge_unit) override;

protected:
    int m_num;
    static int num;
};

#endif // THIRDMONSTER_H
