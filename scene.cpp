#include "scene.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>

// 初始化映射集
void Scene::makeName2Num()
{
    name2num["Player"] = ClassName::Player; // 玩家
    name2num["Rock"] = ClassName::Rock; // 岩石
    name2num["FloorGrass"] = ClassName::FloorGrass; // 草坪
    name2num["Spring"] = ClassName::Spring; // 弹簧
    name2num["FlyingBrick"] = ClassName::FlyingBrick; // 飞行砖块
    name2num["DestructibleBrick"] = ClassName::DestructibleBrick; // 可被破坏的岩石
    name2num["ArrowTerrain"] = ClassName::ArrowTerrain; // 弓箭陷阱
    name2num["ActiveTrap"] = ClassName::ActiveTrap; // 主动触发式陷阱
    name2num["PassiveTrap"] = ClassName::PassiveTrap; // 被动触发式陷阱
    name2num["FirstMonster"] = ClassName::FirstMonster; // 第一种怪物
    name2num["SecondMonster"] = ClassName::SecondMonster; // 第二种怪物
    name2num["ThirdMonster"] = ClassName::ThirdMonster; // 第三种怪物
    name2num["MushroomBuff"] = ClassName::MushroomBuff; // 蘑菇Buff
    name2num["FlowerBuff"] = ClassName::FlowerBuff; // 花朵Buff
    name2num["Gold"] = ClassName::Gold; // 金币
    name2num["Goal"] = ClassName::Goal; // 终点
}

// 构造连接
void Scene::makeConnection()
{
    // 通关连接
    connect(&updater,SIGNAL(gameSuccess()),this,SLOT(gameSuccess()));
    // 失败连接
    connect(&updater,SIGNAL(gameOver()),this,SLOT(gameOver()));
}

// 初始化场景
void Scene::initialize()
{
    // 如果存在角色指针，则删除置空
    if(player){
        //  delete player;
        player = nullptr;
    }
    // 如果存在终点指针，则删除置空
    if(goal){
        // delete goal;
        goal = nullptr;
    }
    // 如果存在临时指针，则删除置空
    if(temp){
        delete temp;
        temp = nullptr;
    }
    // 删除所有信息
    for(auto iter=allWidgets.begin();iter!=allWidgets.end();++iter){
        delete *iter;
    }
    allWidgets.clear();
    // 清空各指针数组
    terrains.clear();
    traps.clear();
    monsters.clear();
    buffs.clear();
    values.clear();
    flyingProps.clear();
    moveThings.clear();
    launchers.clear();
}

// 绘图事件，绘制场景的各种东西
void Scene::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QFont font("华文新魏",32,QFont::Bold,false);
    p.setFont(font);
    // 绘制背景
    p.drawPixmap(QRect(0,0,width(),height()),QPixmap::fromImage(background.getImage(gameState==Editing)));
    switch (gameState) {
    case Loading:
        p.drawPixmap(QRect(0,0,width(),height()),QPixmap::fromImage(loader.getImage()));
        break;
    case Gaming:
    case Editing:
        // 绘制终点
        if(goal&&goal->isShow()){
            p.drawPixmap(goal->getRect(),QPixmap::fromImage(goal->getImage()));
        }
        // 绘制地形
        for(auto iter=terrains.begin();iter!=terrains.end();++iter){
            if((*iter)->isShow()){
                p.drawPixmap((*iter)->getRect(),QPixmap::fromImage((*iter)->getImage()));
            }
        }
        // 绘制陷阱
        for (auto iter=traps.begin();iter!=traps.end();++iter){
            if((*iter)->isShow()){
                p.drawPixmap((*iter)->getRect(),QPixmap::fromImage((*iter)->getImage()));
            }
        }
        // 绘制Buff
        for (auto iter=buffs.begin();iter!=buffs.end();++iter){
            if((*iter)->isShow()){
                p.drawPixmap((*iter)->getRect(),QPixmap::fromImage((*iter)->getImage()));
            }
        }
        // 绘制分数
        for (auto iter=values.begin();iter!=values.end();++iter){
            if((*iter)->isShow()){
                p.drawPixmap((*iter)->getRect(),QPixmap::fromImage((*iter)->getImage()));
            }
        }
        // 绘制怪物
        for (auto iter=monsters.begin();iter!=monsters.end();++iter){
            if((*iter)->isShow()){
                p.drawPixmap((*iter)->getRect(),QPixmap::fromImage((*iter)->getImage()));
            }
        }
        // 绘制角色
        if(player&&player->isShow()){
            p.drawPixmap(player->getRect(),QPixmap::fromImage(player->getImage()));
        }
        // 绘制飞行物
        for (auto iter=flyingProps.begin();iter!=flyingProps.end();++iter){
            if((*iter)->isShow()){
                p.drawPixmap((*iter)->getRect(),QPixmap::fromImage((*iter)->getImage()));
            }
        }
        // 绘制临时指针，当且仅当存在并且需要显示时
        if(temp && isShowChooseWidget){
            p.drawPixmap(temp->getRect(),QPixmap::fromImage(temp->getImage()));
        }
        // 绘制文字
        if(player){
            // 绘制人物生命
            p.drawText(QRect(100,10,200,50),QString::number(player->getHP()));
            // 绘制游戏分数
            p.drawText(QRect(300,10,200,50),QString::number(player->getPoints()));
        }else{
            // 绘制人物生命
            p.drawText(QRect(100,10,200,50),QString("???"));
            // 绘制游戏分数
            p.drawText(QRect(300,10,200,50),QString("???"));
        }
        // 绘制游戏时间
        if(gameState==Gaming){
            p.drawText(QRect(width()-200,10,200,50),QString::number(clock()-gameTime)+"ms");
        }
        break;
    case Success:
        break;
    case GameOver:
        break;
    case Rank:
        font.setPointSize(20);
        p.setFont(font);
        p.drawText(QRect(width()/2-300,250-60,200,60),"日期");
        p.drawText(QRect(width()/2-100,250-60,150,60),"时间");
        p.drawText(QRect(width()/2+50,250-60,50,60),"分数");
        p.drawText(QRect(width()/2+100,250-60,100,60),"通关时间");
        for(int i = 0;i<(10>rankinfos.size()?rankinfos.size():10);i++){
            p.drawText(QRect(width()/2-300,250+60*i,200,60),rankinfos[i].date);
            p.drawText(QRect(width()/2-100,250+60*i,150,60),rankinfos[i].time);
            p.drawText(QRect(width()/2+50,250+60*i,50,60),rankinfos[i].point);
            p.drawText(QRect(width()/2+100,250+60*i,100,60),rankinfos[i].passTime);
        }
        break;
    default:
        break;
    }
}

// 鼠标进入事件，在Edit模式下，将显示临时指针的内容
void Scene::enterEvent(QEvent *event)
{
    switch(gameState){
    case Loading:
        break;
    case Gaming:
        break;
    case Editing:
            isShowChooseWidget = true;
        break;
    default:
        break;
    }
    QWidget::enterEvent(event);
}

// 鼠标离开事件，在Edit模式下，将不显示显示临时指针的内容
void Scene::leaveEvent(QEvent *event)
{
    switch(gameState){
    case Loading:
        break;
    case Gaming:
        break;
    case Editing:
        isShowChooseWidget = false;
        break;
    default:
        break;
    }
    QWidget::enterEvent(event);
}

// 鼠标移动事件，在Edit模式下，追踪临时指针内容的位置
void Scene::mouseMoveEvent(QMouseEvent *event)
{
    switch(gameState){
    case Loading:
        break;
    case Gaming:
        break;
    case Editing:
        if(temp){
            temp->moveRect(event->pos().x()-temp->width()/2,event->pos().y()-temp->height()/2);
        }
        break;
    default:
        break;
    }
    QWidget::mouseMoveEvent(event);
}

// 鼠标施放事件，在Edit模式下，左键表示放下部件、右键表示取消/删除
void Scene::mouseReleaseEvent(QMouseEvent *event)
{
    if(loading){
        return;
    }
    switch(gameState){
    case Loading:
        if(event->button()==Qt::LeftButton){
            if(QRect(888*width()/1902,510*height()/1002,230*width()/1902,40*height()/1002).contains(event->pos())){
                emit chooseSceneFile();
            }
            if(QRect(888*width()/1902,580*height()/1002,230*width()/1902,40*height()/1002).contains(event->pos())){
                emit newSceneFile();
            }
            if(QRect(888*width()/1902,650*height()/1002,230*width()/1902,40*height()/1002).contains(event->pos())){
                gameState = Rank;
                readRankFile();
            }
        }
        break;
    case Gaming:
        break;
    case Editing:
        if(event->button()==Qt::RightButton){
            if(temp){
                delete temp;
                temp = nullptr;
                emit clearChooseSceneWidget(); // 发出信号，通知主窗口取消组件工具栏的选择
            } else {
                deleteSceneWidget(event->x(),event->y()); // 删除鼠标位置的部件
            }
        }
        if(event->button()==Qt::LeftButton){
            if(temp){
                addSceneWidget(event->x(),event->y()); // 将临时指针的内容放置在地图上
            } else {
                moveSceneWidget(event->x(),event->y()); // 取出点击的物体
            }
        }
        mouseMoveEvent(event); // 触发一次mouseMoveEvent事件，保证图形位置正确
        break;
    default:
        break;
    }
    QWidget::mouseReleaseEvent(event);
}

// 窗口大小发生改变事件
void Scene::resizeEvent(QResizeEvent *)
{
    m_width = width();
    m_height = height();
    ci.setWidth(width());
    ci.setHeight(height());
}

// 增加组件
void Scene::addSceneWidget(int x, int y)
{
    if (!temp){
        return;
    }

    temp->moveRect(temp->x()/placeAcc*placeAcc,(temp->y()+placeAcc/2)/placeAcc*placeAcc);
    // 如果这个释放的位置没有东西，则加入，并且再次新建，保证创建的连续性
    if(ci.canAddInScene(temp->getRect())){
        // qDebug()<<"("<<x/map_unit<<", "<<y/map_unit<<")插入"<<temp->metaObject()->className();
        temp->setOrigin(temp->x(),temp->y());
        allWidgets.insert(temp);
        switch(name2num[temp->metaObject()->className()]){
        case ClassName::None:break;
        case ClassName::Player:
            // 如果原来有玩家，则删除
            if(player){
                allWidgets.remove(player);
                delete player;
            }
            player = static_cast<Player*>(temp);
            temp = new Player(x+1, y+1,map_unit-2,map_unit-2, this);
            break;
        case ClassName::Rock:
            terrains.insert(static_cast<Rock*>(temp));
            temp = new Rock(x,y,map_unit,map_unit,this);
            break;
        case ClassName::FloorGrass:
            terrains.insert(static_cast<FloorGrass*>(temp));
            temp = new FloorGrass(x,y,map_unit,map_unit,this);
            break;
        case ClassName::Spring:
            terrains.insert(static_cast<Spring*>(temp));
            temp = new Spring(x,y,map_unit,map_unit,this);
            break;
        case ClassName::FlyingBrick:
            terrains.insert(static_cast<FlyingBrick*>(temp));
            moveThings.insert(static_cast<FlyingBrick*>(temp));
            temp = new FlyingBrick(x,y,map_unit,map_unit,this);
            break;
        case ClassName::DestructibleBrick:
            terrains.insert(static_cast<DestructibleBrick*>(temp));
            temp = new DestructibleBrick(x,y,map_unit,map_unit,this);
            break;
        case ClassName::ArrowTerrain:
            terrains.insert(static_cast<ArrowTerrain*>(temp));
            launchers.insert(static_cast<ArrowTerrain*>(temp));
            temp = new ArrowTerrain(x,y,map_unit,map_unit,this);
            break;
        case ClassName::ActiveTrap:
            traps.insert(static_cast<ActiveTrap*>(temp));
            temp = new ActiveTrap(x,y,map_unit,map_unit,this);
            break;
        case ClassName::PassiveTrap:
            traps.insert(static_cast<PassiveTrap*>(temp));
            temp = new PassiveTrap(x,y,map_unit,map_unit,this);
            break;
        case ClassName::FirstMonster:
            monsters.insert(static_cast<FirstMonster*>(temp));
            moveThings.insert(static_cast<FirstMonster*>(temp));
            temp = new FirstMonster(x,y,map_unit,map_unit,this);
            break;
        case ClassName::SecondMonster:
            monsters.insert(static_cast<SecondMonster*>(temp));
            moveThings.insert(static_cast<SecondMonster*>(temp));
            temp = new SecondMonster(x,y,map_unit,map_unit,this);
            break;
        case ClassName::ThirdMonster:
            monsters.insert(static_cast<ThirdMonster*>(temp));
            moveThings.insert(static_cast<ThirdMonster*>(temp));
            launchers.insert(static_cast<ThirdMonster*>(temp));
            temp = new ThirdMonster(x,y,map_unit,map_unit,this);
            break;
        case ClassName::MushroomBuff:
            buffs.insert(static_cast<MushroomBuff*>(temp));
            temp = new MushroomBuff(x,y,map_unit,map_unit,this);
            break;
        case ClassName::FlowerBuff:
            buffs.insert(static_cast<FlowerBuff*>(temp));
            temp = new FlowerBuff(x,y,map_unit,map_unit,this);
            break;
        case ClassName::Gold:
            values.insert(static_cast<Gold*>(temp));
            temp = new Gold(x,y,map_unit,map_unit,this);
            break;
        case ClassName::Goal:
            // 如果有终点，则删除
            if(goal){
                allWidgets.remove(goal);
                delete goal;
            }
            goal = static_cast<Goal*>(temp);
            temp = new Goal(x, y,map_unit,map_unit, this);
            break;
        default:
            break;
        }
        if(isMovingThing){
            delete temp;
            temp = nullptr;
        }
    }
}

// 擦除地图组件
void Scene::eraseSceneWidget(BaseObject* object)
{
    // 将组件从组件库中去除
    switch(name2num[object->metaObject()->className()]){
    case ClassName::None:break;
    case ClassName::Player:
        player = nullptr;
        break;
    case ClassName::Rock:
    case ClassName::FloorGrass:
    case ClassName::Spring:
    case ClassName::DestructibleBrick:
        terrains.remove(static_cast<Terrain*>(object));
        break;
    case ClassName::FlyingBrick:
        terrains.remove(static_cast<Terrain*>(object));
        moveThings.remove(static_cast<FlyingBrick*>(object));
        break;
    case ClassName::ArrowTerrain:
        terrains.remove(static_cast<ArrowTerrain*>(object));
        launchers.remove(static_cast<ArrowTerrain*>(object));
        break;
    case ClassName::ActiveTrap:
        traps.remove(static_cast<ActiveTrap*>(object));
        break;
    case ClassName::PassiveTrap:
        traps.remove(static_cast<PassiveTrap*>(object));
        break;
    case ClassName::FirstMonster:
    case ClassName::SecondMonster:
        monsters.remove(static_cast<Monster*>(object));
        moveThings.remove(static_cast<Monster*>(object));
        break;
    case ClassName::ThirdMonster:
        monsters.remove(static_cast<ThirdMonster*>(object));
        moveThings.remove(static_cast<ThirdMonster*>(object));
        launchers.remove(static_cast<ThirdMonster*>(object));
        break;
    case ClassName::MushroomBuff:
    case ClassName::FlowerBuff:
        buffs.remove(static_cast<Buff*>(object));
        break;
    case ClassName::Gold:
        values.remove(static_cast<Gold*>(object));
        break;
    case ClassName::Goal:
        goal = nullptr;
        break;
    default:
        break;
    }
}

// 删除原先的地图组件
void Scene::deleteSceneWidget(int x, int y)
{
    BaseObject* object = ci.getWidgetFromPos(x,y);
    if(object){
        eraseSceneWidget(object);
        allWidgets.remove(object);
        delete object;
    }
}

// 移动原先的地图组件
void Scene::moveSceneWidget(int x, int y)
{
    if(temp){
        return;
    }

    BaseObject* object = ci.getWidgetFromPos(x,y);
    // 如果这个位置有物体，则取出
    if(object){
        eraseSceneWidget(object);
        temp = object;
        allWidgets.remove(temp);
        if(temp){
            if(mapFromGlobal(cursor().pos()).x()>0&&mapFromGlobal(cursor().pos()).y()>0){
                isShowChooseWidget = true;
                temp->moveRect(mapFromGlobal(cursor().pos()).x()-temp->width()/2,mapFromGlobal(cursor().pos()).y()-temp->height()/2);
            }
        }
        isMovingThing = true;
    }
}

// 读取排名
void Scene::readRankFile()
{
    rankinfos.clear();
    QFile file(rankFile);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        QString date,time,point,passTime;
        while(!in.atEnd()){
            in>>date>>time>>point>>passTime;
            if(!date.isEmpty()&&!time.isEmpty()&&!point.isEmpty()&&!passTime.isEmpty()){
                rankinfos.append(RankInfo(date,time,point,passTime));
            }
        }
        file.close();
    }
}

// 写入排名
void Scene::writeRankFile()
{
    QFile file(rankFile);
    if(file.open(QIODevice::Append)){
        QTextStream out(&file);
        if(player){
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<" "<<player->getPoints()<<" "<<QString::number(clock()-gameTime)+"ms"<<endl;
        }
        file.close();
    }
}

// 更新场景事件，使用Updater类
void Scene::updateScene(const QSet<int>& pressedKeys)
{
    if(gameState==Gaming){
        updater.updateAll(player,moveThings,launchers,flyingProps,ci,pressedKeys);
    }
    else if(gameState==Editing){
        // 鼠标是否显示
        if(temp){
            setCursor(Qt::BlankCursor);
        }else{
            setCursor(Qt::ArrowCursor);
        }
    }
    update();
}

// 选择的场景组件，生成临时变量
void Scene::chooseSceneWidget(bool isChoose, const QString & className)
{
    if(gameState!=Editing){
        return;
    }

    // 如果是选中触发，则删除原来的临时指针，创建新的临时指针，否则直接删除临时指针
    delete temp;
    temp = nullptr;
    if(isChoose){
        switch(name2num[className]){
        case ClassName::Player:
            temp = new Player(0,0,map_unit-2,map_unit-2,this);
            break;
        case ClassName::Rock:
            temp = new Rock(0,0,map_unit,map_unit,this);
            break;
        case ClassName::FloorGrass:
            temp = new FloorGrass(0,0,map_unit,map_unit,this);
            break;
        case ClassName::Spring:
            temp = new Spring(0,0,map_unit,map_unit,this);
            break;
        case ClassName::FlyingBrick:
            temp = new FlyingBrick(0,0,map_unit,map_unit,this);
            break;
        case ClassName::DestructibleBrick:
            temp = new DestructibleBrick(0,0,map_unit,map_unit,this);
            break;
        case ClassName::ArrowTerrain:
            temp = new ArrowTerrain(0,0,map_unit,map_unit,this);
            break;
        case ClassName::ActiveTrap:
            temp = new ActiveTrap(0,0,map_unit,map_unit,this);
            break;
        case ClassName::PassiveTrap:
            temp = new PassiveTrap(0,0,map_unit,map_unit,this);
            break;
        case ClassName::FirstMonster:
            temp = new FirstMonster(0,0,map_unit,map_unit,this);
            break;
        case ClassName::SecondMonster:
            temp = new SecondMonster(0,0,map_unit,map_unit,this);
            break;
        case ClassName::ThirdMonster:
            temp = new ThirdMonster(0,0,map_unit,map_unit,this);
            break;
        case ClassName::MushroomBuff:
            temp = new MushroomBuff(0,0,map_unit,map_unit,this);
            break;
        case ClassName::FlowerBuff:
            temp = new FlowerBuff(0,0,map_unit,map_unit,this);
            break;
        case ClassName::Gold:
            temp = new Gold(0,0,map_unit,map_unit,this);
            break;
        case ClassName::Goal:
            temp = new Goal(0,0,map_unit,map_unit,this);
            break;
        default:
            break;
        }
        // 移动到正确的坐标
        if(temp){
            if(mapFromGlobal(cursor().pos()).x()>0&&mapFromGlobal(cursor().pos()).y()>0){
                isShowChooseWidget = true;
                temp->moveRect(mapFromGlobal(cursor().pos()).x()-temp->width()/2,mapFromGlobal(cursor().pos()).y()-temp->height()/2);
            }
        }
        isMovingThing = false;
    }else{
        emit clearChooseSceneWidget();
    }
}

// 加载结束
void Scene::loadOver()
{
    loading = false;
}

// 新建场景，调用初始化函数
void Scene::newScene()
{
    initialize();
}

// 加载场景
void Scene::loadScene(const QString &scenePath)
{
    initialize(); // 先进行初始化
    //    qDebug()<<"open";
    QFile file(scenePath);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString className; // className
    int x, y, width ,height; // x, y坐标与长宽
    while(!in.atEnd()){
        in>>className>>x>>y>>width>>height;
        // 如果这个位置可以放进去
        if(ci.canAddInScene(QRect(x,y,width,height))){
            BaseObject* newObject = nullptr; // 指针数组中的信息
            switch (name2num[className]) {
            case ClassName::None:break;
            case ClassName::Player:
                player = new Player(x+1,y+1,width-2,height-2,this);
                newObject = player;
                break;
            case ClassName::Rock:
                newObject = new Rock(x,y,width,height,this);
                terrains.insert(static_cast<Rock*>(newObject));
                break;
            case ClassName::FloorGrass:
                newObject = new FloorGrass(x,y,width,height,this);
                terrains.insert(static_cast<FloorGrass*>(newObject));
                break;
            case ClassName::Spring:
                newObject = new Spring(x,y,width,height,this);
                terrains.insert(static_cast<Spring*>(newObject));
                break;
            case ClassName::FlyingBrick:
                newObject = new FlyingBrick(x,y,width,height,this);
                terrains.insert(static_cast<FlyingBrick*>(newObject));
                moveThings.insert(static_cast<FlyingBrick*>(newObject));
                break;
            case ClassName::DestructibleBrick:
                newObject = new DestructibleBrick(x,y,width,height,this);
                terrains.insert(static_cast<DestructibleBrick*>(newObject));
                break;
            case ClassName::ArrowTerrain:
                newObject = new ArrowTerrain(x,y,width,height,this);
                terrains.insert(static_cast<ArrowTerrain*>(newObject));
                launchers.insert(static_cast<ArrowTerrain*>(newObject));
                break;
            case ClassName::ActiveTrap:
                newObject = new ActiveTrap(x,y,width,height,this);
                traps.insert(static_cast<ActiveTrap*>(newObject));
                break;
            case ClassName::PassiveTrap:
                newObject = new PassiveTrap(x,y,width,height,this);
                traps.insert(static_cast<PassiveTrap*>(newObject));
                break;
            case ClassName::FirstMonster:
                newObject = new FirstMonster(x,y,width,height,this);
                monsters.insert(static_cast<FirstMonster*>(newObject));
                moveThings.insert(static_cast<FirstMonster*>(newObject));
                break;
            case ClassName::SecondMonster:
                newObject = new SecondMonster(x,y,width,height,this);
                monsters.insert(static_cast<SecondMonster*>(newObject));
                moveThings.insert(static_cast<SecondMonster*>(newObject));
                break;
            case ClassName::ThirdMonster:
                newObject = new ThirdMonster(x,y,width,height,this);
                monsters.insert(static_cast<ThirdMonster*>(newObject));
                moveThings.insert(static_cast<ThirdMonster*>(newObject));
                launchers.insert(static_cast<ThirdMonster*>(newObject));
                break;
            case ClassName::MushroomBuff:
                newObject = new MushroomBuff(x,y,width,height,this);
                buffs.insert(static_cast<MushroomBuff*>(newObject));
                break;
            case ClassName::FlowerBuff:
                newObject = new FlowerBuff(x,y,width,height,this);
                buffs.insert(static_cast<FlowerBuff*>(newObject));
                break;
            case ClassName::Gold:
                newObject = new Gold(x,y,width,height,this);
                values.insert(static_cast<Gold*>(newObject));
                break;
            case ClassName::Goal:
                goal = new Goal(x,y,width,height,this);
                newObject = goal;
                break;
            default:
                QMessageBox::warning(this,"Warning","场景文件有奇怪的东西！");
            }
            if(newObject){
                allWidgets.insert(newObject); // 保存到指针数组中
            }
        }
    }
    file.close();
}

// 保存场景
void Scene::saveScene(const QString &scenePath)
{
    //    qDebug() << "save";
    QFile file(scenePath);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    // 保存地图所有组件信息
    for(auto iter=allWidgets.begin();iter!=allWidgets.end();++iter){
        out << (*iter)->metaObject()->className()<< " "<<(*iter)->originX()<<" "<<(*iter)->originY()
            <<" "<<(*iter)->width()<<" "<<(*iter)->height()<<endl;
    }
    file.close();
}

// 重载游戏
void Scene::gameReload()
{
    // 人物初始化
    if(player){
        player->initialize();
    }

    //删除临时指针
    if(temp){
        delete temp;
        temp = nullptr;
    }

    // 移动物体初始化
    for(auto iter=moveThings.begin();iter!=moveThings.end();++iter){
        (*iter)->initialize();
    }

    // 重新显示
    for(auto iter=allWidgets.begin();iter!=allWidgets.end();++iter){
        (*iter)->show();
    }

    // 删除飞行道具
    for(auto iter=flyingProps.begin();iter!=flyingProps.end();++iter){
        delete *iter;
    }
    flyingProps.clear();
}

// 游戏开始
void Scene::gameStart()
{
    gameReload();
    gameTime = clock();
    // 小提示
    if(player==nullptr&&goal==nullptr){
        QMessageBox::information(this,"Info","请放置你的人物和目的地哟~");
    }
    else if(player==nullptr){
        QMessageBox::information(this,"Info","请放置你的人物哟~");
    } else if(goal==nullptr){
        QMessageBox::information(this,"Info","请放置你的目的地哟~");
    }
}

// 游戏重新开始
void Scene::gameRestart()
{
    if(gameState==Gaming){
        gameStart();
    }
}

// SLOT，过关
void Scene::gameSuccess()
{
    writeRankFile();
    QMessageBox::information(this,"Congratulation","恭喜过关！");
    gameStart();
    emit clearKeyPressed();
}

// SLOT，游戏结束
void Scene::gameOver()
{
    QMessageBox::information(this,"Sorry","游戏结束！");
    gameStart();
    emit clearKeyPressed();
}

// 构造函数，初始化
Scene::Scene(QWidget *parent) : QWidget(parent),gameState(Loading),m_width(1902),m_height(1002),map_unit(50),placeAcc(0.5*map_unit),
    fps(16),loading(true), gameTime(0),background(":/images/background/images/background/background.gif"),
    loader(":/images/background/images/background/loader.gif",true),
    player(nullptr),goal(nullptr), temp(nullptr),
    ci(SceneInfo(m_width,m_height,&player,&goal,&allWidgets,&terrains,&traps,&monsters,&buffs,&values,&flyingProps)), updater(fps, this),
    rankFile("./rank/rank.rank"),
    isShowChooseWidget(false),isMovingThing(false)
{
    resize(m_width,m_height); // 重构大小
    setMouseTracking(true); // 鼠标追踪
    makeName2Num(); // 初始化映射
    makeConnection(); // 初始化连接
    // loadScene("./scene/test.scene");
}

// 析构函数，释放空间
Scene::~Scene()
{
    saveScene("./scene/temp.scene");
    for(auto iter=allWidgets.begin();iter!=allWidgets.end();++iter){
        delete *iter;
    }
}

// 返回帧率
int Scene::getFPS() const
{
    return fps;
}

// 返回游戏状态
int Scene::getGameState() const
{
    return gameState;
}

// 设置游戏状态
void Scene::setGameState(int gameState)
{
    this->gameState = gameState;
    switch (gameState) {
    case Loading:
        initialize();
        isShowChooseWidget = false;
        isMovingThing = false;
        break;
    case Gaming:
        gameStart();
        isShowChooseWidget = false;
        isMovingThing = false;
        break;
    case Editing:
        gameReload();
        break;
    default:
        break;
    }
}

