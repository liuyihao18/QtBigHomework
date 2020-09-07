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
    bool isInScene(const QRect& rect) const; // 返回是否在场景中（天空无限）
    bool isStrictInScene(const QRect& rect) const; // 返回是否在场景中（天空有限）
    bool isCollideTerrain(const QRect& rect) const; // 返回是否发生碰撞
    bool isCollideExcept(const QRect& rect, BaseObject* object) const; // 返回是否和除了某个类之外的东西碰撞
    bool isInSky(const QRect& rect) const; // 返回是否在天空中
    bool isOnGround(const QRect& rect) const; // 返回是否在地上
    bool dealWithPlayerCollision(Player* player); // 处理玩家有关的碰撞
    BaseObject* getWidgetFromPos(int x,int y); // 返回指定位置的组件

protected:
    SceneInfo sceneinfo;

signals:
    void gameSuccess();
};

#endif // COLLISIONINSPECTOR_H
