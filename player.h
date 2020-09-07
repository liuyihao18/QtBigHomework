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
    void updatePos(bool jumping, int judge_unit);
    void confirmPos() override;
    void cancelPos() override;
    void initialize() override;

protected:
    int points;
    int downSpeed;
    int upSpeed;
    int jumpTime;
    int fallDownHPReduce;
    bool canAttack;
};

#endif // PLAYER_H
