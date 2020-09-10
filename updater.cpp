#include "updater.h"
#include <QDebug>

Updater::Updater(QObject *parent) : QObject(parent)
{}

Updater::Updater(int fps, QObject *parent)
    : QObject(parent), fps(fps), judge_unit(1)
{}

// 收集需要的信息进行更新
void Updater::updateAll(Player                   *player,
                        const QSet<MoveThing *> & movethings,
                        const QSet<Launcher *>  & launchers,
                        QSet<FlyingProp *>      & flyingProps,
                        const CollisionInspector& ci,
                        const QSet<int>         & pressedKeys)
{
    updateMoveThings(player, movethings, ci);
    updateLaunchers(launchers, flyingProps);

    if (player) {
        updatePlayer(player, flyingProps, ci, pressedKeys);
    }
    updateFlyingProps(flyingProps, ci);

    if (ci.isGameSuccess()) {
        emit playSuccessMusic();
        emit gameSuccess();
    }

    if (ci.isGmaeOver()) {
        emit playGameOverMusic();
        emit gameOver();
    }
}

// 更新玩家的信息
void Updater::updatePlayer(Player                   *player,
                           QSet<FlyingProp *>      & flyingProps,
                           const CollisionInspector& ci,
                           const QSet<int>         & pressedKeys)
{
    // 玩家的大小
    int width = player->width();
    int height = player->height();

    // 移动速度
    int unit_speed = player->getMoveSpeed() * fps / 1000;

    //    qDebug() << player->getRect().topLeft() <<
    // player->getRect().bottomRight();

    // 跳跃
    if (pressedKeys.contains(Qt::Key_K) || pressedKeys.contains(Qt::Key_2)) {
        // 禁止多次跳跃与空中跳跃
        if (ci.isOnGround(player->getRect())) {
            player->jump();
            emit playJumpMusic();
        }
    }

    // 快速向下
    if (pressedKeys.contains(Qt::Key_L) || pressedKeys.contains(Qt::Key_3)) {
        player->setDownSpeed(3 * player->getOriginDownSpeed());
        player->jumpOver();
    } else {
        player->refreshDownSpeed();
    }

    for (int i = 1; i <= unit_speed; i += judge_unit) {
        // 重力和跳跃移动
        player->updatePos(judge_unit);

        if (!ci.isInScene(player->getTempPos())) {
            player->returnOriginPos();
            player->reduceHP(player->getFallDownHPReduce());
            return;
        }

        if (!ci.isCollideTerrain(player->getTempPos())) {
            player->confirmPos();
        } else {
            player->cancelPos();
        }

        // 键盘调整人物朝向
        if ((pressedKeys.contains(Qt::Key_W) || pressedKeys.contains(Qt::Key_Up))
            && (pressedKeys.contains(Qt::Key_D) ||
                pressedKeys.contains(Qt::Key_Right))) {
            player->setDirection(UpRight);
        }
        else if ((pressedKeys.contains(Qt::Key_S) ||
                  pressedKeys.contains(Qt::Key_Down))
                 && (pressedKeys.contains(Qt::Key_D) ||
                     pressedKeys.contains(Qt::Key_Right))) {
            player->setDirection(DownRight);
        }
        else if ((pressedKeys.contains(Qt::Key_W) ||
                  pressedKeys.contains(Qt::Key_Up))
                 && (pressedKeys.contains(Qt::Key_A) ||
                     pressedKeys.contains(Qt::Key_Left))) {
            player->setDirection(UpLeft);
        }
        else if ((pressedKeys.contains(Qt::Key_S) ||
                  pressedKeys.contains(Qt::Key_Down))
                 && (pressedKeys.contains(Qt::Key_A) ||
                     pressedKeys.contains(Qt::Key_Left))) {
            player->setDirection(DownLeft);
        }
        else if (pressedKeys.contains(Qt::Key_D) ||
                 pressedKeys.contains(Qt::Key_Right)) {
            player->setDirection(Right);
        }
        else if (pressedKeys.contains(Qt::Key_A) ||
                 pressedKeys.contains(Qt::Key_Left)) {
            player->setDirection(Left);
        }
        else if (pressedKeys.contains(Qt::Key_W) ||
                 pressedKeys.contains(Qt::Key_Up)) {
            player->setDirection(Up);
        }
        else if (pressedKeys.contains(Qt::Key_S) ||
                 pressedKeys.contains(Qt::Key_Down)) {
            player->setDirection(Down);
        }

        // 键盘控制左右运动
        int new_x = player->x();
        int new_y = player->y();

        if (pressedKeys.contains(Qt::Key_A) ||
            pressedKeys.contains(Qt::Key_Left)) {
            if (ci.isInScene(QRect(new_x - judge_unit, new_y, width, height))
                && !ci.isCollideTerrain(QRect(new_x - judge_unit, new_y, width,
                                              height))) {
                new_x -= judge_unit;
                player->moveRect(new_x, new_y);
            }
        }

        if (pressedKeys.contains(Qt::Key_D) ||
            pressedKeys.contains(Qt::Key_Right)) {
            if (ci.isInScene(QRect(new_x + judge_unit, new_y, width, height))
                && !ci.isCollideTerrain(QRect(new_x + judge_unit, new_y, width,
                                              height))) {
                new_x += judge_unit;
                player->moveRect(new_x, new_y);
            }
        }

        // 发射子弹
        if (player->ifCanAttack() &&
            (pressedKeys.contains(Qt::Key_J) ||
             pressedKeys.contains(Qt::Key_1))) {
            FlyingProp *flyingprop = player->launchFlyingProp();

            if (flyingprop) {
                emit playLaunchMusic();
                flyingProps.insert(flyingprop);
            }
        }

        // 处理事件
        ci.dealWithPlayerCollision();
        ci.dealWithActiveTrap();
    }
}

// 更新会移动的东西
void Updater::updateMoveThings(Player                   *player,
                               const QSet<MoveThing *> & movethings,
                               const CollisionInspector& ci)
{
    for (auto iter = movethings.begin(); iter != movethings.end(); ++iter) {
        int unit_speed = (*iter)->getMoveSpeed() * fps / 1000;

        for (int i = 1; i <= unit_speed; i += judge_unit) {
            // 动态多态性，不同对象进行不同的更新
            (*iter)->updatePos(judge_unit);

            // 不严格在场景内则回退
            if (!ci.isStrictInScene((*iter)->getTempPos())) {
                (*iter)->cancelPos();
                (*iter)->needToChangeMove();
                continue;
            }

            // 飞行砖块的判断
            if (dynamic_cast<FlyingBrick *>((*iter))) {
                FlyingBrick *flyingBrick = dynamic_cast<FlyingBrick *>((*iter));

                if (!ci.canFlyingBrickMove(flyingBrick)) {
                    flyingBrick->cancelPos();
                    flyingBrick->needToChangeMove();
                    continue;
                } else {
                    flyingBrick->confirmPos();

                    // 人随砖走
                    if (player && ci.isPlayerOnFlyingBrick(flyingBrick)) {
                        int new_x = player->x();
                        int new_y = player->y();
                        new_x = flyingBrick->isReverse() ? new_x -
                                judge_unit : new_x + judge_unit;

                        if (!ci.isCollideTerrain(QRect(new_x, new_y,
                                                       player->width(),
                                                       player->height()))) {
                            player->moveRect(new_x, new_y);
                        }
                    }
                }
            }

            // 第一类怪物
            if (dynamic_cast<FirstMonster *>(*iter)) {
                FirstMonster *firstMonster = dynamic_cast<FirstMonster *>(*iter);

                if (ci.isCollideTerrain(firstMonster->getTempPos()) ||
                    !ci.isStrictOnGround(firstMonster->getTempPos())) {
                    firstMonster->cancelPos();
                    firstMonster->needToChangeMove();
                    continue;
                } else {
                    firstMonster->confirmPos();
                }
            }

            // 第二类怪物
            if (dynamic_cast<SecondMonster *>(*iter)) {
                SecondMonster *secondMonster =
                    dynamic_cast<SecondMonster *>(*iter);

                if (ci.isCollideTerrain(secondMonster->getTempPos()) ||
                    secondMonster->isUpToMaxUpHeight()) {
                    secondMonster->cancelPos();
                    secondMonster->needToChangeMove();
                    continue;
                } else {
                    secondMonster->confirmPos();
                }
            }

            // 第三类怪物
            if (dynamic_cast<ThirdMonster *>(*iter)) {
                ThirdMonster *thirdMonster = dynamic_cast<ThirdMonster *>(*iter);

                if (ci.isCollideTerrain(thirdMonster->getTempPos())) {
                    thirdMonster->cancelPos();
                } else {
                    thirdMonster->confirmPos();
                }
            }
        }
    }
}

// 更新发射者的发射状态
void Updater::updateLaunchers(const QSet<Launcher *>& launchers,
                              QSet<FlyingProp *>    & flyingProps)
{
    for (auto iter = launchers.begin(); iter != launchers.end(); ++iter) {
        FlyingProp *flyingprop = (*iter)->launchFlyingProp();

        if (flyingprop) {
            flyingProps.insert(flyingprop);
        }
    }
}

// 更新飞行物
void Updater::updateFlyingProps(QSet<FlyingProp *>      & flyingProps,
                                const CollisionInspector& ci)
{
    for (auto iter = flyingProps.begin(); iter != flyingProps.end(); ++iter) {
        int unit_speed = (*iter)->getMoveSpeed() * fps / 1000;

        for (int i = 1; i <= unit_speed; i += judge_unit) {
            (*iter)->updatePos(judge_unit);

            if (!ci.isStrictInScene((*iter)->getTempPos()) ||
                ci.isCollideTerrain((*iter)->getTempPos())) {
                delete (*iter);
                flyingProps.erase(iter);
                break;
            } else {
                (*iter)->confirmPos();
            }

            if (ci.dealWithFlyingProp(*iter)) {
                delete (*iter);
                flyingProps.erase(iter);
                break;
            }
        }
    }
}
