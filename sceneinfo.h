#ifndef SCENEINFO_H
#define SCENEINFO_H

#include "scenewidgets.h"

struct SceneInfo{
    int m_width; // 保存窗口宽度
    int m_height; // 保存窗口高度
    Player** player; // 地图的角色指针
    Goal** goal;
    QSet<Terrain*>* terrains; // 地图的地形指针
    QSet<Trap*>* traps; // 地图的陷阱指针
    QSet<Monster*>* monsters; // 地图的怪物指针
    QSet<Buff*>* buffs; // 地图的Buff指针
    QSet<Values*>* values; // 地图的分数物体指针
    SceneInfo() = default;
    SceneInfo(int m_width,int m_height,Player** player,Goal** goal,QSet<Terrain*>* terrains,
              QSet<Trap*>* traps,QSet<Monster*>* monsters,QSet<Buff*>* buffs,QSet<Values*>* values)
        :m_width(m_width),m_height(m_height),player(player),goal(goal),terrains(terrains),traps(traps),monsters(monsters),
          buffs(buffs),values(values){}
};

#endif // SCENEINFO_H
