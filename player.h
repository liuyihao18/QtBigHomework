#ifndef PLAYER_H
#define PLAYER_H

#include "role.h"

class Player : public Role
{
    Q_OBJECT
public:
    Player(QObject* parent = nullptr);
    Player(int x,int y, int width,int height, QObject* parent=nullptr);
    int getJumpTime() const;
    int getDownSpeed() const;
    int getUpSpeed() const;
    void updatePos(bool jumping, int judge_unit);
    void confirmPos();
    void cancelPos();

protected:
    int down_speed;
    int up_speed;
    int jump_time;

};

#endif // PLAYER_H
