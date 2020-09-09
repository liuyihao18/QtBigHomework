#ifndef UPDATER_H
#define UPDATER_H

#include "scenewidgets.h"
#include "collisioninspector.h"
#include <QObject>
#include <QMap>
#include <QTimer>

class Updater : public QObject
{
    Q_OBJECT
public:
    explicit Updater(QObject *parent = nullptr);
    Updater(int fps, QObject *parent = nullptr);
    void updateAll(Player* player, const QSet<MoveThing*>& movethings,const QSet<Launcher*>& launchers, QSet<FlyingProp*>& flyingProps,const CollisionInspector& ci, const QSet<int>& pressedKeys); // 更新场景中的东西
    void updatePlayer(Player* player, QSet<FlyingProp*>& flyingProps, const CollisionInspector& ci, const QSet<int>& pressedKeys); // 更新玩家的位置
    void updateMoveThings(Player* player, const QSet<MoveThing*>& movethings, const CollisionInspector& ci); // 更新其他移动物体的位置
    void updateLaunchers(const QSet<Launcher*>& launchers, QSet<FlyingProp*>& flyingProps); // 更新发射者的发射状态
    void updateFlyingProps(QSet<FlyingProp*>& flyingProps,const CollisionInspector& ci); // 更新飞行物的位置

protected:
    int fps; // 帧率
    int judge_unit; // 判断精度


signals:
    void gameSuccess(); // 游戏过关信号
    void gameOver(); // 游戏结束信号
    void playJumpMusic(); // 播放跳跃音乐
    void playLaunchMusic(); // 播放发射子弹音乐
};

#endif // UPDATER_H
