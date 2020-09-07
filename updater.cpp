#include "updater.h"
#include <QDebug>

Updater::Updater(QObject *parent) : QObject(parent)
{

}

Updater::Updater(int fps, QObject *parent)
    :QObject(parent), fps(fps), judge_unit(1)
{

}

void Updater::updateAll(Player *player, const QSet<MoveThing *> &movethings, const QSet<FlyingProp *> &flyingProps, CollisionInspector &ci, const QSet<int> &pressedKeys)
{
    updateMoveThings(movethings,ci);
    if(player){
        updatePlayer(player,ci,pressedKeys);
    }
    updateFlyingProps(flyingProps,ci);
}

void Updater::updatePlayer(Player *player, CollisionInspector &ci, const QSet<int> &pressedKeys)
{
    // 玩家的大小
    int width = player->width();
    int height = player->height();

    // 移动速度
    int unit_speed = player->getMoveSpeed() * fps / 1000;
    //    qDebug() << player->getRect().topLeft() << player->getRect().bottomRight();

    // 跳跃
    if(pressedKeys.contains(Qt::Key_K)||pressedKeys.contains(Qt::Key_W)||pressedKeys.contains(Qt::Key_Up)){
        // 禁止多次跳跃与空中跳跃
        if(ci.isOnGround(player->getRect())){
            player->jump();
        }
    }

    for(int i=1;i<=unit_speed;i+=judge_unit){
        // 重力和跳跃移动
        player->updatePos(judge_unit);
        if(!ci.isInScene(player->getTempPos())){
            player->returnOriginPos();
            player->reduceHP(player->getFallDownHPReduce());
            return;
        }
        if(!ci.isCollideTerrain(player->getTempPos())){
            player->confirmPos();
        }else{
            player->cancelPos();
        }

        // 键盘控制左右运动
        int new_x = player->x();
        int new_y = player->y();
        if((pressedKeys.contains(Qt::Key_A)||pressedKeys.contains(Qt::Key_Left))){
            if(ci.isInScene(QRect(new_x-judge_unit,new_y,width,height))
                    &&!ci.isCollideTerrain(QRect(new_x-judge_unit,new_y,width,height))){
                new_x -= judge_unit;
                player->moveRect(new_x, new_y);
            }
        }
        if((pressedKeys.contains(Qt::Key_D)||pressedKeys.contains(Qt::Key_Right))){
            if(ci.isInScene(QRect(new_x+judge_unit,new_y,width,height))
                    &&!ci.isCollideTerrain(QRect(new_x+judge_unit,new_y,width,height))){
                new_x += judge_unit;
                player->moveRect(new_x, new_y);
            }
        }
        ci.dealWithPlayerCollision(player);
    }
}

void Updater::updateMoveThings(const QSet<MoveThing *> &movethings, CollisionInspector &ci)
{
    for(auto iter = movethings.begin();iter!=movethings.end();++iter){
        (*iter)->updatePos(judge_unit);
        if(!ci.isStrictInScene((*iter)->getTempPos())){
            (*iter)->cancelPos();
            (*iter)->needToChangeMove();
            continue;
        }
        if(dynamic_cast<FlyingBrick*>((*iter))){
            if(ci.isCollideExcept((*iter)->getTempPos(),dynamic_cast<FlyingBrick*>(*iter))){
                (*iter)->cancelPos();
                (*iter)->needToChangeMove();
                continue;
            }else{
                (*iter)->confirmPos();
            }
        }
    }
}

void Updater::updateFlyingProps(const QSet<FlyingProp *> &flyingProps, CollisionInspector &ci)
{

}
