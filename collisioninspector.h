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
    bool isInScene(const QRect& rect) const; // 返回是否在场景中
    bool isCollide(const QRect& rect) const; // 返回是否发生碰撞
    bool isInSky(const QRect& rect) const; // 返回是否在天空中
    bool isOnGround(const QRect& rect) const; // 返回是否在地上
    bool dealWithCollision() const; // 处理所有的碰撞

protected:
    SceneInfo sceneinfo;

signals:

};

#endif // COLLISIONINSPECTOR_H
