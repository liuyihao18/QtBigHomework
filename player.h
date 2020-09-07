#ifndef PLAYER_H
#define PLAYER_H

#include "role.h"

class Player : public Role
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
    void jump(int springJumpTime = 0);
    void updatePos(int judge_unit) override;
    void initialize() override;

protected:
    int points;
    int downSpeed;
    int upSpeed;
    int jumpTime;
    int fallDownHPReduce;
    bool canAttack;
    bool jumping;
    QTimer jumpTimer;

protected slots:
    void jumpOver();
};

#endif // PLAYER_H
