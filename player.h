#ifndef PLAYER_H
#define PLAYER_H

#include "role.h"
#include "launcher.h"

class Player : public Role, public Launcher
{
    Q_OBJECT
public:
    Player(QObject* parent = nullptr);
    Player(int x,int y, int width,int height, QObject* parent=nullptr);
    int getPoints() const;
    void addPoins(int point);
    void reducePoints(int point);
    void addBuff(const QString& buffName);
    int getFallDownHPReduce() const;
    int getJumpTime() const;
    int getDownSpeed() const;
    int getUpSpeed() const;
    void jump(bool springJump = false);
    void updatePos(int judge_unit) override;
    void initialize() override;
    FlyingProp* emitFlyingProp() override;

protected:
    int points;
    int downSpeed;
    int upSpeed;
    int jumpTime;
    int fallDownHPReduce;
    bool canAttack;
    bool jumping;
    QTimer jumpTimer;

public slots:
    void jumpOver();
};

#endif // PLAYER_H
