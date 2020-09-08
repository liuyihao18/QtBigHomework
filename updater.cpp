#include "updater.h"
#include <QDebug>

Updater::Updater(QObject *parent) : QObject(parent)
{

}

Updater::Updater(int fps, QObject *parent)
    :QObject(parent), fps(fps), judge_unit(1)
{

}

// 收集需要的信息进行更新
void Updater::updateAll(Player *player, const QSet<MoveThing *> &movethings, const QSet<FlyingProp *> &flyingProps, CollisionInspector &ci, const QSet<int> &pressedKeys)
{
    updateMoveThings(player,movethings,ci);
    updateFlyingProps(flyingProps,ci);
    if(player){
        updatePlayer(player,ci,pressedKeys);
    }
}

// 更新玩家的信息
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
        ci.dealWithActiveTrap(player);
    }
}

// 更新会移动的东西
void Updater::updateMoveThings(Player* player, const QSet<MoveThing *> &movethings, CollisionInspector &ci)
{
    for(auto iter = movethings.begin();iter!=movethings.end();++iter){
        int unit_speed = (*iter)->getMoveSpeed() * fps / 1000;
        for(int i=1;i<=unit_speed;i+=judge_unit){
            // 动态多态性，不同对象进行不同的更新
            (*iter)->updatePos(judge_unit);
            // 不严格在场景内则回退
            if(!ci.isStrictInScene((*iter)->getTempPos())){
                (*iter)->cancelPos();
                (*iter)->needToChangeMove();
                continue;
            }
            // 飞行砖块的判断
            if(dynamic_cast<FlyingBrick*>((*iter))){
                FlyingBrick* flyingBrick = dynamic_cast<FlyingBrick*>((*iter));
                if(ci.isCollideExcept((*iter)->getTempPos(),flyingBrick)){
                    flyingBrick->cancelPos();
                    flyingBrick->needToChangeMove();
                    continue;
                }else{
                    flyingBrick->confirmPos();
                    // 人随砖走
                    if(ci.isPlayerOnFlyingBrick(player,flyingBrick)){
                        int new_x = player->x();
                        int new_y = player->y();
                        new_x = flyingBrick->isReverse()?new_x-judge_unit:new_x+judge_unit;
                        if(!ci.isCollideTerrain(QRect(new_x,new_y,player->width(),player->height()))){
                            player->moveRect(new_x,new_y);
                        }
                    }
                }
            }         
            // 第一类怪物
            if(dynamic_cast<FirstMonster* >(*iter)){
                FirstMonster* firstMonster = dynamic_cast<FirstMonster*>(*iter);
                if(ci.isCollideTerrain(firstMonster->getTempPos())||!ci.isStrictOnGround(firstMonster->getTempPos())){
                    firstMonster->cancelPos();
                    firstMonster->needToChangeMove();
                    continue;
                }else{
                    firstMonster->confirmPos();
                }
            }
            // 第二类怪物
            if(dynamic_cast<SecondMonster* >(*iter)){
                SecondMonster* secondMonster = dynamic_cast<SecondMonster*>(*iter);
                if(ci.isCollideTerrain(secondMonster->getTempPos())||secondMonster->isUpToMaxUpHeight()){
                    secondMonster->cancelPos();
                    secondMonster->needToChangeMove();
                    continue;
                }else{
                    secondMonster->confirmPos();
                }
            }
            // 第三类怪物
            if(dynamic_cast<ThirdMonster* >(*iter)){
                ThirdMonster* thirdMonster = dynamic_cast<ThirdMonster*>(*iter);
                if(ci.isCollideTerrain(thirdMonster->getTempPos())){
                    thirdMonster->cancelPos();
                }else{
                    thirdMonster->confirmPos();
                }
            }
        }
    }
}

// 更新飞行物
void Updater::updateFlyingProps(const QSet<FlyingProp *> &flyingProps, CollisionInspector &ci)
{

}
