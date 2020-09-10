#ifndef THIRDMONSTER_H
#define THIRDMONSTER_H

#include "monster.h"
#include "launcher.h"
#include "fireball.h"

class ThirdMonster : public Monster, public Launcher {
    Q_OBJECT

public:

    ThirdMonster(QObject *parent = nullptr);
    ThirdMonster(int      x,
                 int      y,
                 int      width,
                 int      height,
                 QObject *parent = nullptr);
    void        updatePos(int judge_unit) override;
    FlyingProp* launchFlyingProp() override;

protected:

    static int Num;
    int _num;
    int _originMoveSpeed;
    QTimer _launchTimer;

protected slots:

    void launchOver();
};

#endif // THIRDMONSTER_H
