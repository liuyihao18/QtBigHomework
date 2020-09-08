#ifndef THIRDMONSTER_H
#define THIRDMONSTER_H

#include "monster.h"
#include "launcher.h"
#include "fireball.h"

class ThirdMonster : public Monster, public Launcher
{
    Q_OBJECT
public:
    ThirdMonster(QObject* parent=nullptr);
    ThirdMonster(int x,int y, int width, int height, QObject* parent=nullptr);
    void updatePos(int judge_unit) override;
    FlyingProp *launchFlyingProp() override;

protected:
    static int num;
    int m_num;
    int originMoveSpeed;
    QTimer launchTimer;

protected slots:
    void launchOver();
};

#endif // THIRDMONSTER_H
