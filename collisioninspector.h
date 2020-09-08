#ifndef COLLISIONINSPECTOR_H
#define COLLISIONINSPECTOR_H

#include "sceneinfo.h"
#include <QObject>
#include <QRect>
#include <QSet>

class CollisionInspector : public QObject
{
    Q_OBJECT
public:
    explicit CollisionInspector(QObject *parent = nullptr);
    CollisionInspector(const SceneInfo& sceneinfo, QObject* parent = nullptr);
    int width() const; // 返回碰撞检测的窗口宽度
    void setWidth(int width); // 设置宽度
    int height() const; // 返回碰撞检测的窗口宽度
    void setHeight(int height); // 设置高度
    bool canAddInScene(const QRect& rect) const; // 返回是否可以被放置
    bool isInScene(const QRect& rect) const; // 返回是否在场景中（弱判断）
    bool isStrictInScene(const QRect& rect) const; // 返回是否在场景中（强判断）
    bool isCollideTerrain(const QRect& rect) const; // 返回是否与地形发生碰撞
    bool isCollideTrap(const QRect& rect) const; // 返回是否与陷阱发生碰撞
    bool isCollideMonster(const QRect& rect) const; // 返回是否与怪物发生碰撞
    bool isCollideBuffs(const QRect& rect) const; // 返回是否与Buff发生碰撞
    bool isCollideValues(const QRect& rect) const; // 返回是否与分数物体发生碰撞
    bool canFlyingBrickMove(BaseObject* object) const; // 返回是否和除了某个东西之外的东西碰撞
    bool isInSky(const QRect& rect) const; // 返回是否在天空中
    bool isOnGround(const QRect& rect) const; // 返回是否在地上(弱判断）
    bool isStrictOnGround(const QRect& rect) const; // 返回是否在地上(强判断）
    bool isPlayerOnFlyingBrick(FlyingBrick* flyingBrick) const; // 返回玩家是否处于飞行砖块上
    bool dealWithPlayerCollision(); // 处理玩家有关的碰撞
    bool dealWithActiveTrap(); // 处理主动陷阱出现的问题
    bool dealWithFlyingProp(FlyingProp* flyingProp); // 处理飞行道具有关的问题
    BaseObject* getWidgetFromPos(int x,int y); // 返回指定位置的组件

protected:
    SceneInfo sceneinfo;
    int distance(const QRect& rect1, const QRect& rect2) const; // 返回两个矩形之间的位置

signals:
    void gameSuccess();
};

#endif // COLLISIONINSPECTOR_H
