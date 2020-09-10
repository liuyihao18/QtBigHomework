#include "collisioninspector.h"
#include <cmath>
#include <QDebug>

CollisionInspector::CollisionInspector(QObject *parent) : QObject(parent)
{}

// 构造函数，加入sceneinfo结构体
CollisionInspector::CollisionInspector(const SceneInfo& sceneinfo,
                                       QObject         *parent)
    : QObject(parent), sceneinfo(sceneinfo)
{}

// 返回碰撞检测的窗口宽度
int CollisionInspector::width() const
{
    return sceneinfo.m_width;
}

// 设置宽度
void CollisionInspector::setWidth(int width)
{
    sceneinfo.m_width = width;
}

// 返回碰撞检测的窗口宽度
int CollisionInspector::height() const
{
    return sceneinfo.m_height;
}

// 设置高度
void CollisionInspector::setHeight(int height)
{
    sceneinfo.m_height = height;
}

// 是否可以被放置
bool CollisionInspector::canAddInScene(const QRect& rect) const
{
    // 判断在窗口内部
    if (!QRect(0, 0, width() + 1902, height() + 1002).contains(rect)) {
        return false;
    }

    // 判断不会和其他组件碰撞
    for (auto iter = sceneinfo.allWidgets->begin();
         iter != sceneinfo.allWidgets->end(); ++iter) {
        if ((*iter)->getRect().intersects(rect)) {
            return false;
        }
    }
    return true;
}

// 返回是否在场景中（弱判断）
bool CollisionInspector::isInScene(const QRect& rect) const
{
    if ((rect.left() < 0) || (rect.right() > width())) {
        return false;
    }

    if (rect.top() > height()) {
        return false;
    }
    return true;
}

// 返回是否在场景中（强判断）
bool CollisionInspector::isStrictInScene(const QRect& rect) const
{
    return QRect(0, 0, width(), height()).contains(rect);
}

// 返回是否与地形发生碰撞
bool CollisionInspector::isCollideTerrain(const QRect& rect) const
{
    for (auto iter = sceneinfo.terrains->begin();
         iter != sceneinfo.terrains->end(); ++iter) {
        if ((*iter)->isShow()) {
            if ((*iter)->getRect().intersects(rect)) {
                return true;
            }
        }
    }
    return false;
}

// 返回是否与陷阱发生碰撞
bool CollisionInspector::isCollideTrap(const QRect& rect) const
{
    for (auto iter = sceneinfo.traps->begin(); iter != sceneinfo.traps->end();
         ++iter) {
        if ((*iter)->isShow()) {
            if ((*iter)->getRect().intersects(rect)) {
                return true;
            }
        }
    }
    return false;
}

// 返回是否与怪物发生碰撞
bool CollisionInspector::isCollideMonster(const QRect& rect) const
{
    for (auto iter = sceneinfo.monsters->begin();
         iter != sceneinfo.monsters->end(); ++iter) {
        if ((*iter)->isShow()) {
            if ((*iter)->getRect().intersects(rect)) {
                return true;
            }
        }
    }
    return false;
}

// 返回是否和Buff发生碰撞
bool CollisionInspector::isCollideBuffs(const QRect& rect) const
{
    for (auto iter = sceneinfo.buffs->begin(); iter != sceneinfo.buffs->end();
         ++iter) {
        if ((*iter)->isShow()) {
            if ((*iter)->getRect().intersects(rect)) {
                return true;
            }
        }
    }
    return false;
}

// 返回是否和分数物体发生碰撞
bool CollisionInspector::isCollideValues(const QRect& rect) const
{
    for (auto iter = sceneinfo.values->begin(); iter != sceneinfo.values->end();
         ++iter) {
        if ((*iter)->isShow()) {
            if ((*iter)->getRect().intersects(rect)) {
                return true;
            }
        }
    }
    return false;
}

// 返回飞行砖块是否可以以移动
bool CollisionInspector::canFlyingBrickMove(BaseObject *object) const
{
    FlyingBrick *flyingBrick = dynamic_cast<FlyingBrick *>(object);

    if (flyingBrick) {
        for (auto iter = sceneinfo.allWidgets->begin();
             iter != sceneinfo.allWidgets->end(); ++iter) {
            if (((*iter) != object) && (*iter)->isShow()) {
                if ((*iter)->getRect().intersects(flyingBrick->getTempPos())) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

// 返回是否在天空中
bool CollisionInspector::isInSky(const QRect& rect) const
{
    return !isOnGround(rect);
}

// 返回是否在地上(弱判断）
bool CollisionInspector::isOnGround(const QRect& rect) const
{
    for (auto iter = sceneinfo.terrains->begin();
         iter != sceneinfo.terrains->end(); ++iter) {
        // 偏移1像素判断，三点判断
        if ((*iter)->isShow()) {
            if ((*iter)->getRect().contains(QPoint(rect.left(),
                                                   rect.bottom() + 1))
                || (*iter)->getRect().contains(QPoint(rect.left() + rect.width() /
                                                      2, rect.bottom() + 1))
                || (*iter)->getRect().contains(QPoint(rect.right(),
                                                      rect.bottom() + 1))) {
                return true;
            }
        }
    }
    return false;
}

// 返回是否在地上(强判断）
bool CollisionInspector::isStrictOnGround(const QRect& rect) const
{
    // 偏移1像素判断
    QPoint bottomLeft = QPoint(rect.bottomLeft().x(), rect.bottomLeft().y() + 1);
    QPoint bottomRight =
        QPoint(rect.bottomRight().x(), rect.bottomRight().y() + 1);
    bool bottomLeftIn = false;
    bool bottomRightIn = false;

    for (auto iter = sceneinfo.terrains->begin();
         iter != sceneinfo.terrains->end(); ++iter) {
        if ((*iter)->isShow()) {
            if ((*iter)->getRect().contains(bottomLeft)) {
                bottomLeftIn = true;
            }

            if ((*iter)->getRect().contains(bottomRight)) {
                bottomRightIn = true;
            }
        }

        if (bottomLeftIn && bottomRightIn) {
            return true;
        }
    }
    return bottomLeftIn && bottomRightIn;
}

// 返回玩家是否处于飞行砖块上
bool CollisionInspector::isPlayerOnFlyingBrick(FlyingBrick *flyingBrick) const
{
    Player *player = (*sceneinfo.player);
    QRect   rect = player->getRect();

    if (flyingBrick->getRect().contains(QPoint(rect.left() + rect.width() * 0.5,
                                               rect.bottom() + 1))) {
        return true;
    }
    return false;
}

// 返回是否游戏过关
bool CollisionInspector::isGameSuccess() const
{
    // 是否达到终点
    if ((*sceneinfo.player) && (*sceneinfo.goal)) {
        // 判断终点进行体积缩小判定
        QRect goalRect = (*(sceneinfo.goal))->getRect();
        goalRect.setWidth(goalRect.width() * 0.5);
        goalRect.setHeight(goalRect.height() * 0.5);
        goalRect.moveTo(goalRect.x() + goalRect.width() * 0.5,
                        goalRect.y() + goalRect.height() * 0.5);

        if (goalRect.intersects((*sceneinfo.player)->getRect())) {
            return true;
        }
    }
    return false;
}

// 返回是否游戏结束
bool CollisionInspector::isGmaeOver() const
{
    if ((*sceneinfo.player) && ((*sceneinfo.player)->getHP() <= 0)) {
        return true;
    }
    return false;
}

// 处理玩家有关的碰撞
bool CollisionInspector::dealWithPlayerCollision() const
{
    bool dealt = false;
    Player *player = (*sceneinfo.player);
    QRect   rect = (*sceneinfo.player)->getRect();

    if (player && player->isShow()) {
        // 判断地形，弹簧和可破坏砖块
        for (auto iter = sceneinfo.terrains->begin();
             iter != sceneinfo.terrains->end(); ++iter) {
            if ((*iter)->isShow()) {
                if ((*iter)->metaObject()->className() == QString("Spring")) {
                    if ((*iter)->getRect().contains(QPoint(rect.left(),
                                                           rect.bottom() + 1))
                        || (*iter)->getRect().contains(QPoint(rect.left() +
                                                              rect.width() / 2,
                                                              rect.bottom() + 1))
                        || (*iter)->getRect().contains(QPoint(rect.right(),
                                                              rect.bottom() +
                                                              1))) {
                        player->jump(true);
                        dealt = true;
                    }
                }

                if ((*iter)->metaObject()->className() ==
                    QString("DestructibleBrick")) {
                    if ((*iter)->getRect().contains(QPoint(rect.left() +
                                                           player->width() / 2,
                                                           rect.top() - 1))) {
                        static_cast<DestructibleBrick *>(*iter)->collide();
                        player->jumpOver();
                        player->addPoins(
                            static_cast<DestructibleBrick *>(*iter)->getPoints());
                        dealt = true;
                    }
                }
            }
        }

        // 陷阱扣血
        for (auto iter = sceneinfo.traps->begin(); iter != sceneinfo.traps->end();
             ++iter) {
            if ((*iter)->isShow()) {
                if ((*iter)->getRect().intersects(rect)) {
                    player->reduceHP((*iter)->getHPReduce());
                    dealt = true;
                }
            }
        }

        // 怪物扣血
        for (auto iter = sceneinfo.monsters->begin();
             iter != sceneinfo.monsters->end(); ++iter) {
            if ((*iter)->isShow()) {
                if ((*iter)->getRect().intersects(rect)) {
                    player->reduceHP((*iter)->getHPReduce());
                    dealt = true;
                }
            }
        }

        // 加Buff
        for (auto iter = sceneinfo.buffs->begin(); iter != sceneinfo.buffs->end();
             ++iter) {
            if ((*iter)->isShow()) {
                if ((*iter)->getRect().intersects(rect)) {
                    (*iter)->hide();
                    player->addBuff((*iter)->metaObject()->className());
                    dealt = true;
                }
            }
        }

        // 加分数
        for (auto iter = sceneinfo.values->begin();
             iter != sceneinfo.values->end(); ++iter) {
            if ((*iter)->isShow()) {
                if ((*iter)->getRect().intersects(rect)) {
                    (*iter)->hide();
                    player->addPoins((*iter)->getValue());
                    dealt = true;
                }
            }
        }
    }
    return dealt;
}

// 主动陷阱在靠近人物的时候触发
bool CollisionInspector::dealWithActiveTrap() const
{
    bool dealt = false;
    Player *player = (*sceneinfo.player);

    for (auto iter = sceneinfo.traps->begin(); iter != sceneinfo.traps->end();
         ++iter) {
        if (dynamic_cast<ActiveTrap *>(*iter)) {
            if (distance((*iter)->getRect(), player->getRect()) < 150) {
                (*iter)->show();
                dealt = true;
            } else {
                (*iter)->hide();
            }
        }
    }
    return dealt;
}

// 处理飞行物的碰撞问题
bool CollisionInspector::dealWithFlyingProp(FlyingProp *flyingProp) const
{
    bool dealt = false;

    // 玩家发射的子弹
    if (dynamic_cast<MagicBullet *>(flyingProp)) {
        for (auto iter = sceneinfo.monsters->begin();
             iter != sceneinfo.monsters->end(); ++iter) {
            if ((*iter)->isShow()) {
                if ((*iter)->getRect().intersects(flyingProp->getRect())) {
                    (*iter)->reduceHP(flyingProp->getHPReduce());

                    if ((*iter)->getHP() == 0) {
                        (*sceneinfo.player)->addPoins(20);
                    }
                    dealt = true;
                }
            }
        }
    }

    // 其他怪物发射的子弹
    else if (*sceneinfo.player &&
             (dynamic_cast<Arrow *>(flyingProp) ||
              dynamic_cast<FireBall *>(flyingProp))) {
        if ((*sceneinfo.player)->getRect().intersects(flyingProp->getRect())) {
            (*sceneinfo.player)->reduceHP(flyingProp->getHPReduce());
            dealt = true;
        }
    }
    return dealt;
}

// 根据位置获得物体的指针
BaseObject * CollisionInspector::getWidgetFromPos(int x, int y) const
{
    for (auto iter = sceneinfo.allWidgets->begin();
         iter != sceneinfo.allWidgets->end(); ++iter) {
        if ((*iter)->getRect().contains(QPoint(x, y))) {
            return *iter;
        }
    }
    return nullptr;
}

// 返回两个矩形的距离
int CollisionInspector::distance(const QRect& rect1, const QRect& rect2) const
{
    return sqrt((rect1.x() - rect2.x()) * (rect1.x() - rect2.x()) +
                (rect1.y() - rect2.y()) * (rect1.y() - rect2.y()));
}
