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

// 是否可以被放置
bool CollisionInspector::canAddInScene(const QRect &rect) const
{
    if(!QRect(0,0,width(),height()).contains(rect)){
        return false;
    }
    for(auto iter = sceneinfo.allWidgets->begin();iter!=sceneinfo.allWidgets->end();++iter){
        if((*iter)->getRect().intersects(rect)){
            return false;
        }
    }
    return true;
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

bool CollisionInspector::isStrictInScene(const QRect &rect) const
{
    if(rect.x()<0||rect.x()+rect.width()>width()){
        return false;
    }
    if(rect.y()>height()||rect.y()+rect.height()>height()){
        return false;
    }
    return true;
}

// 返回是否发生碰撞
bool CollisionInspector::isCollideTerrain(const QRect &rect) const
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

// 返回是否和除了某个东西之外的东西碰撞
bool CollisionInspector::isCollideExcept(const QRect &rect, BaseObject* object) const
{
    for(auto iter = sceneinfo.allWidgets->begin();iter!=sceneinfo.allWidgets->end();++iter){
        if((*iter)!=object &&(*iter)->isShow()){
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
            QRect goalRect = (*(sceneinfo.goal))->getRect();
            goalRect.setWidth(goalRect.width()*0.5);
            goalRect.setHeight(goalRect.height()*0.5);
            goalRect.moveTo(goalRect.x()+goalRect.width()*0.5,goalRect.y()+goalRect.height()*0.5);
            if(goalRect.intersects(player->getRect())){
                emit gameSuccess();
                return true;
            }
        }
        for(auto iter=sceneinfo.terrains->begin();iter!=sceneinfo.terrains->end();++iter){
            if((*iter)->metaObject()->className()==QString("Spring")){
                if((*iter)->getRect().contains(QPoint(player->getRect().bottomLeft().x(),player->getRect().bottomLeft().y()+1))
                        ||(*iter)->getRect().contains(QPoint(player->getRect().bottomRight().x(),player->getRect().bottomRight().y()+1))){
                    player->jump(600);
                }
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

BaseObject *CollisionInspector::getWidgetFromPos(int x, int y)
{
    for(auto iter = sceneinfo.allWidgets->begin();iter!=sceneinfo.allWidgets->end();++iter){
        if((*iter)->getRect().contains(QPoint(x,y))){
            return *iter;
        }
    }
    return nullptr;
}
