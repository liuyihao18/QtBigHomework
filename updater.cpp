#include "updater.h"
#include <QDebug>

Updater::Updater(QObject *parent) : QObject(parent)
{

}

Updater::Updater(int fps, QObject *parent)
    :QObject(parent), fps(fps), judge_unit(1), jumping(false), jumpTimer(this)
{
    jumpTimer.setInterval(0);
    // 连接跳跃计时器的timeout()信号
    connect(&jumpTimer,SIGNAL(timeout()),this,SLOT(jumpOver()));
}

bool Updater::updatePlayer(Player *player, CollisionInspector &ci, const QSet<int> &pressedKeys)
{
    if(!player){
        return false;
    }
    bool moved = false;

    // 玩家的大小
    int width = player->width();
    int height = player->height();

    // 移动速度
    int unit_speed = player->getMoveSpeed() * fps / 1000;
    //    qDebug() << player->getRect().topLeft() << player->getRect().bottomRight();

    // 跳跃
    if(pressedKeys.contains(Qt::Key_K)||pressedKeys.contains(Qt::Key_W)||pressedKeys.contains(Qt::Key_Up)){
        // 禁止多次跳跃与空中跳跃
        if(!jumping&&ci.isOnGround(player->getRect())){
            jumping = true;
            jumpTimer.setInterval(player->getJumpTime());
            jumpTimer.start();
        }
    }

    for(int i=1;i<=unit_speed;i+=judge_unit){
        // 重力和跳跃移动
        player->updatePos(jumping,judge_unit);
        if(!ci.isInScene(player->getTempPos())){
            player->returnOriginPos();
            player->reduceHP(player->getFallDownHPReduce());
            return true;
        }
        if(!ci.isCollide(player->getTempPos())){
            player->confirmPos();
            moved = true;
        }else{
            player->cancelPos();
        }

        // 键盘控制左右运动
        int new_x = player->x();
        int new_y = player->y();
        if((pressedKeys.contains(Qt::Key_A)||pressedKeys.contains(Qt::Key_Left))){
            if(ci.isInScene(QRect(new_x-judge_unit,new_y,width,height))
                    &&!ci.isCollide(QRect(new_x-judge_unit,new_y,width,height))){
                new_x -= judge_unit;
                moved = true;
                player->moveRect(new_x, new_y);
            }
        }
        if((pressedKeys.contains(Qt::Key_D)||pressedKeys.contains(Qt::Key_Right))){
            if(ci.isInScene(QRect(new_x+judge_unit,new_y,width,height))
                    &&!ci.isCollide(QRect(new_x+judge_unit,new_y,width,height))){
                new_x += judge_unit;
                moved = true;
                player->moveRect(new_x, new_y);
            }
        }
        ci.dealWithPlayerCollision(player);
    }
    return moved;
}

void Updater::jumpOver()
{
    jumping = false;
    jumpTimer.stop();
}
