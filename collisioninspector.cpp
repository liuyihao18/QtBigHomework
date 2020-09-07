#include "collisioninspector.h"
#include <QDebug>

CollisionInspector::CollisionInspector(QObject *parent) : QObject(parent)
{

}

CollisionInspector::CollisionInspector(const SceneInfo& sceneinfo, QObject* parent)
    :QObject(parent), sceneinfo(sceneinfo)
{

}

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

// 返回是否在场景中
bool CollisionInspector::isInScene(const QRect &rect) const
{
    if(rect.x()<0||rect.x()+rect.width()>width()){
        return false;
    }
    if(rect.y()>height()){
        return false;
    }
    return true;
}

// 返回是否发生碰撞
bool CollisionInspector::isCollide(const QRect &rect) const
{
    for(auto iter = sceneinfo.terrains->begin();iter!=sceneinfo.terrains->end();++iter){
        if((*iter)->isShow()){
            if((*iter)->getRect().intersects(rect)){
                return true;
            }
        }
    }
    return false;
}

// 返回是否在天空中
bool CollisionInspector::isInSky(const QRect &rect) const
{
    return !isOnGround(rect);
}

// 返回是否在地上
bool CollisionInspector::isOnGround(const QRect &rect) const
{
    for(auto iter = sceneinfo.terrains->begin();iter!=sceneinfo.terrains->end();++iter){
        // 偏移1像素判断
        if((*iter)->isShow()){
            if((*iter)->getRect().contains(QPoint(rect.bottomLeft().x(),rect.bottomLeft().y()+1))
                    ||(*iter)->getRect().contains(QPoint(rect.bottomRight().x(),rect.bottomRight().y()+1))){
                return true;
            }
        }
    }
    return false;
}

bool CollisionInspector::dealWithPlayerCollision(Player* player)
{
    bool collision = false;
    if(player){
        if(*(sceneinfo.goal)){
            if((*(sceneinfo.goal))->getRect().contains(player->getRect())){
                emit gameSuccess();
                return true;
            }
        }
        for(auto iter=sceneinfo.traps->begin();iter!=sceneinfo.traps->end();++iter){
            if((*iter)->isShow()){
                if((*iter)->getRect().intersects(player->getRect())){
                    player->reduceHP((*iter)->getHPReduce());
                }
            }
        }
        for(auto iter=sceneinfo.monsters->begin();iter!=sceneinfo.monsters->end();++iter){
            if((*iter)->isShow()){
                if((*iter)->getRect().intersects(player->getRect())){
                    player->reduceHP((*iter)->getHPReduce());
                }
            }
        }
        for(auto iter=sceneinfo.buffs->begin();iter!=sceneinfo.buffs->end();++iter){
            if((*iter)->isShow()){
                if((*iter)->getRect().intersects(player->getRect())){
                    (*iter)->hide();
                    player->addBuff((*iter)->metaObject()->className());
                }
            }
        }
        for(auto iter=sceneinfo.values->begin();iter!=sceneinfo.values->end();++iter){
            if((*iter)->isShow()){
                if((*iter)->getRect().intersects(player->getRect())){
                    (*iter)->hide();
                    player->addPoins((*iter)->getValue());
                }
            }
        }
    }
    return collision;
}
