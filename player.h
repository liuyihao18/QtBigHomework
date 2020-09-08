#ifndef PLAYER_H
#define PLAYER_H

#include "role.h"
#include "launcher.h"
#include "magicbullet.h"

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
    void setFallDownHPReduce(int fallDownHPReduce);
    int getJumpTime() const;
    void setJumpTime(int jumpTime);
    void refreshUpSpeed();
    int getDownSpeed() const;
    int getOriginDownSpeed() const;
    void setDownSpeed(int downSpeed);
    void refreshDownSpeed();
    int getUpSpeed() const;
    int getOriginUpSpeed() const;
    void setUpSpeed(int upSpeed);
    void jump(bool springJump = false);
    bool ifCanAttack() const;
    int getMoveSpeed() const;
    void updatePos(int judge_unit) override;
    void initialize() override;
    FlyingProp* launchFlyingProp() override;

protected:
    int points;
    int downSpeed;
    int originDownSpeed;
    int upSpeed;
    int originUpSpeed;
    int jumpTime;
    int fallDownHPReduce;
    bool canAttack;
    bool jumping;
    QTimer jumpTimer;
    QTimer launchTimer;

public slots:
    void jumpOver();
    void launchOver();
};

#endif // PLAYER_H
