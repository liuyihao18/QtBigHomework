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
    name2num["ActiveTrap"] = ClassName::ActiveTrap; // 主动触发式陷阱
    name2num["PassiveTrap"] = ClassName::PassiveTrap; // 被动触发式陷阱
    name2num["ArrowTrap"] = ClassName::ArrowTrap; // 弓箭陷阱
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
    connect(&ci,SIGNAL(gameSuccess()),this,SLOT(gameSuccess()));
}

// 初始化场景
void Scene::initialize()
{
    // 如果存在角色指针，则删除置空
    if(player){
        // delete player; 已经在sceneMap中被删除
        player = nullptr;
    }
    // 如果存在终点指针，则删除置空
    if(goal){
        goal = nullptr;
    }
    // 如果存在临时指针，则删除置空
    if(temp){
        delete temp;
        temp = nullptr;
    }
    // 如果存在指针地图，则重置
    if(sceneMap){
        for(int i=0;i<map_width;i++){
            for(int j=0;j<map_height;j++){
                delete sceneMap[i][j];
            }
            delete[] sceneMap[i];
        }
        delete[] sceneMap;
    }
    sceneMap = new BaseObject**[map_width]();
    for(int i=0;i<map_width;i++){
        sceneMap[i]=new BaseObject*[map_height]();
    }
    // 清空各指针数组
    terrains.clear();
    traps.clear();
    monsters.clear();
    buffs.clear();
    values.clear();
    movethings.clear();
}

// 绘图事件，绘制场景的各种东西
void Scene::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    // 绘制背景
    p.drawPixmap(QRect(0,0,width(),height()),QPixmap::fromImage(background));
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
    // 绘制怪物
    for (auto iter=monsters.begin();iter!=monsters.end();++iter){
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
    // 绘制终点
    if(goal&&goal->isShow()){
        p.drawPixmap(goal->getRect(),QPixmap::fromImage(goal->getImage()));
    }
    // 绘制角色
    if(player&&player->isShow()){
        p.drawPixmap(player->getRect(),QPixmap::fromImage(player->getImage()));
    }
    // 绘制临时指针，当且仅当存在并且需要显示时
    if(temp && isShowChooseWidget){
        p.drawPixmap(temp->getRect(),QPixmap::fromImage(temp->getImage()));
    }

    QFont font("华文新魏",32,QFont::Bold,false);
    p.setFont(font);
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
    if(!isEdit){
        p.drawText(QRect(width()-200,10,200,50),QString::number(clock()-gameTime)+"ms");
    }
}

// 鼠标进入事件，在Edit模式下，将显示临时指针的内容
void Scene::enterEvent(QEvent *event)
{
    if(isEdit){
        isShowChooseWidget = true;
    }
    QWidget::enterEvent(event);
}

// 鼠标离开事件，在Edit模式下，将不显示显示临时指针的内容
void Scene::leaveEvent(QEvent *event)
{
    if(isEdit){
        isShowChooseWidget = false;
    }
    QWidget::enterEvent(event);
}

// 鼠标移动事件，在Edit模式下，追踪临时指针内容的位置
void Scene::mouseMoveEvent(QMouseEvent *event)
{
    if(isEdit){
        if(temp){
            temp->moveRect(event->pos().x()-temp->width()/2,event->pos().y()-temp->height()/2);
        }
    }
    QWidget::mouseMoveEvent(event);
}

// 鼠标施放事件，在Edit模式下，左键表示放下部件、右键表示取消/删除
void Scene::mouseReleaseEvent(QMouseEvent *event)
{
    if(isEdit){
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
    // 化为指针地图单位
    x = (x/map_unit)*map_unit;
    y = (y/map_unit)*map_unit;
    // 如果这个释放的位置没有东西，则加入，并且再次新建，保证创建的连续性
    if(!sceneMap[x/map_unit][y/map_unit]){
        // qDebug()<<"("<<x/map_unit<<", "<<y/map_unit<<")插入"<<temp->metaObject()->className();
        temp->moveRect(x,y);
        temp->setOrigin(x,y);
        sceneMap[x/map_unit][y/map_unit] = temp;

        switch(name2num[temp->metaObject()->className()]){
        case ClassName::None:break;
        case ClassName::Player:
            // 如果原来有玩家，则删除
            if(player){
                sceneMap[player->originX()/map_unit][player->originY()/map_unit] = nullptr; // 删除原来位置
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
            movethings.insert(static_cast<FlyingBrick*>(temp));
            temp = new FlyingBrick(x,y,map_unit,map_unit,this);
            break;
        case ClassName::DestructibleBrick:
            terrains.insert(static_cast<DestructibleBrick*>(temp));
            temp = new DestructibleBrick(x,y,map_unit,map_unit,this);
            break;
        case ClassName::ActiveTrap:
            traps.insert(static_cast<ActiveTrap*>(temp));
            movethings.insert(static_cast<ActiveTrap*>(temp));
            temp = new ActiveTrap(x,y,map_unit,map_unit,this);
            break;
        case ClassName::PassiveTrap:
            traps.insert(static_cast<PassiveTrap*>(temp));
            temp = new PassiveTrap(x,y,map_unit,map_unit,this);
            break;
        case ClassName::ArrowTrap:
            traps.insert(static_cast<ArrowTrap*>(temp));
            movethings.insert(static_cast<ArrowTrap*>(temp));
            temp = new ArrowTrap(x,y,map_unit,map_unit,this);
            break;
        case ClassName::FirstMonster:
            monsters.insert(static_cast<FirstMonster*>(temp));
            movethings.insert(static_cast<FirstMonster*>(temp));
            temp = new FirstMonster(x,y,map_unit,map_unit,this);
            break;
        case ClassName::SecondMonster:
            monsters.insert(static_cast<SecondMonster*>(temp));
            movethings.insert(static_cast<SecondMonster*>(temp));
            temp = new SecondMonster(x,y,map_unit,map_unit,this);
            break;
        case ClassName::ThirdMonster:
            monsters.insert(static_cast<ThirdMonster*>(temp));
            movethings.insert(static_cast<ThirdMonster*>(temp));
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
            if(goal){
                sceneMap[goal->originX()/map_unit][goal->originY()/map_unit] = nullptr; // 删除原来位置
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
void Scene::eraseSceneWidget(int x, int y)
{
    switch(name2num[sceneMap[x/map_unit][y/map_unit]->metaObject()->className()]){
    case ClassName::None:break;
    case ClassName::Player:
        player = nullptr;
        break;
    case ClassName::Rock:
    case ClassName::FloorGrass:
    case ClassName::Spring:
    case ClassName::DestructibleBrick:
        terrains.remove(static_cast<Terrain*>(sceneMap[x/map_unit][y/map_unit]));
        break;
    case ClassName::FlyingBrick:
        terrains.remove(static_cast<Terrain*>(sceneMap[x/map_unit][y/map_unit]));
        movethings.remove(static_cast<FlyingBrick*>(sceneMap[x/map_unit][y/map_unit]));
        break;
    case ClassName::ActiveTrap:
        traps.remove(static_cast<ActiveTrap*>(sceneMap[x/map_unit][y/map_unit]));
        movethings.remove(static_cast<ActiveTrap*>(sceneMap[x/map_unit][y/map_unit]));
        break;
    case ClassName::PassiveTrap:
        traps.remove(static_cast<PassiveTrap*>(sceneMap[x/map_unit][y/map_unit]));
        break;
    case ClassName::ArrowTrap:
        traps.remove(static_cast<ArrowTrap*>(sceneMap[x/map_unit][y/map_unit]));
        movethings.remove(static_cast<ArrowTrap*>(sceneMap[x/map_unit][y/map_unit]));
        break;
    case ClassName::FirstMonster:
    case ClassName::SecondMonster:
    case ClassName::ThirdMonster:
        monsters.remove(static_cast<Monster*>(sceneMap[x/map_unit][y/map_unit]));
        movethings.remove(static_cast<Monster*>(sceneMap[x/map_unit][y/map_unit]));
        break;
    case ClassName::MushroomBuff:
    case ClassName::FlowerBuff:
        buffs.remove(static_cast<Buff*>(sceneMap[x/map_unit][y/map_unit]));
        break;
    case ClassName::Gold:
        values.remove(static_cast<Gold*>(sceneMap[x/map_unit][y/map_unit]));
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
    if(sceneMap[x/map_unit][y/map_unit]){
        eraseSceneWidget(x,y);
        delete sceneMap[x/map_unit][y/map_unit];
        sceneMap[x/map_unit][y/map_unit] = nullptr;
    }
}

// 移动原先的地图组件
void Scene::moveSceneWidget(int x, int y)
{
    if(temp){
        return;
    }
    // 转变为地图坐标
    x = (x/map_unit)*map_unit;
    y = (y/map_unit)*map_unit;
    // 如果这个位置有物体，则取出
    if(sceneMap[x/map_unit][y/map_unit]){
        eraseSceneWidget(x,y);
        temp = sceneMap[x/map_unit][y/map_unit];
        sceneMap[x/map_unit][y/map_unit] = nullptr;
        if(temp){
            if(mapFromGlobal(cursor().pos()).x()>0&&mapFromGlobal(cursor().pos()).y()>0){
                isShowChooseWidget = true;
                temp->moveRect(mapFromGlobal(cursor().pos()).x()-temp->width()/2,mapFromGlobal(cursor().pos()).y()-temp->height()/2);
            }
        }
        isMovingThing = true;
    }
}

// 更新场景事件，使用Updater类
void Scene::updateScene(const QSet<int>& pressedKeys)
{
    // 非编辑模式下，会移动的物体移动
    if(!isEdit){
        if(player){
            updater.updatePlayer(player,ci,pressedKeys);
        }
        //        for(auto iter = movethings.begin();iter!=movethings.end();++iter){
        //            (*iter)->updatePos();
        //        }
    }
    update();
}

// 编辑模式
void Scene::edit(bool edit)
{
    // 接收主窗口传来的信号
    isEdit = edit;
    if(!isEdit){
        // 如果编辑模式取消了，删除临时指针的内容
        if(temp){
            delete temp;
            temp = nullptr;
        }
        // 与编辑模式有关的变量初始化
        isShowChooseWidget = false;
        isMovingThing = false;
        gameTime = clock();
    }else{
        gameReload();
    }
}

// 选择的场景组件，生成临时变量
void Scene::chooseSceneWidget(bool isChoose, const QString & className)
{
    if(!isEdit){
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
        case ClassName::ActiveTrap:
            temp = new ActiveTrap(0,0,map_unit,map_unit,this);
            break;
        case ClassName::PassiveTrap:
            temp = new PassiveTrap(0,0,map_unit,map_unit,this);
            break;
        case ClassName::ArrowTrap:
            temp = new ArrowTrap(0,0,map_unit,map_unit,this);
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

// 加载场景
void Scene::loadScene(const QString &scenePath)
{
    initialize(); // 先进行初始化
    //    qDebug()<<"open";
    QFile file(scenePath);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString className; // className
    int x, y; // x, y坐标
    while(!in.atEnd()){
        in>>className>>x>>y;
        // 转换为指针地图单位
        x = (x/map_unit)*map_unit;
        y = (y/map_unit)*map_unit;
        // 如果指针地图中此位置没有
        if(!sceneMap[x/map_unit][y/map_unit]){
            BaseObject* newObject = nullptr; // 指针数组中的信息
            switch (name2num[className]) {
            case ClassName::None:break;
            case ClassName::Player:
                player = new Player(x+1,y+1,map_unit-2,map_unit-2,this);
                newObject = player;
                break;
            case ClassName::Rock:
                newObject = new Rock(x,y,map_unit,map_unit,this);
                terrains.insert(static_cast<Rock*>(newObject));
                break;
            case ClassName::FloorGrass:
                newObject = new FloorGrass(x,y,map_unit,map_unit,this);
                terrains.insert(static_cast<FloorGrass*>(newObject));
                break;
            case ClassName::Spring:
                newObject = new Spring(x,y,map_unit,map_unit,this);
                terrains.insert(static_cast<Spring*>(newObject));
                break;
            case ClassName::FlyingBrick:
                newObject = new FlyingBrick(x,y,map_unit,map_unit,this);
                terrains.insert(static_cast<FlyingBrick*>(newObject));
                movethings.insert(static_cast<FlyingBrick*>(newObject));
                break;
            case ClassName::DestructibleBrick:
                newObject = new DestructibleBrick(x,y,map_unit,map_unit,this);
                terrains.insert(static_cast<DestructibleBrick*>(newObject));
                break;
            case ClassName::ActiveTrap:
                newObject = new ActiveTrap(x,y,map_unit,map_unit,this);
                traps.insert(static_cast<ActiveTrap*>(newObject));
                movethings.insert(static_cast<ActiveTrap*>(newObject));
                break;
            case ClassName::PassiveTrap:
                newObject = new PassiveTrap(x,y,map_unit,map_unit,this);
                traps.insert(static_cast<PassiveTrap*>(newObject));
                break;
            case ClassName::ArrowTrap:
                newObject = new ArrowTrap(x,y,map_unit,map_unit,this);
                traps.insert(static_cast<ArrowTrap*>(newObject));
                movethings.insert(static_cast<ArrowTrap*>(newObject));
                break;
            case ClassName::FirstMonster:
                newObject = new FirstMonster(x,y,map_unit,map_unit,this);
                monsters.insert(static_cast<FirstMonster*>(newObject));
                movethings.insert(static_cast<FirstMonster*>(newObject));
                break;
            case ClassName::SecondMonster:
                newObject = new SecondMonster(x,y,map_unit,map_unit,this);
                monsters.insert(static_cast<SecondMonster*>(newObject));
                movethings.insert(static_cast<SecondMonster*>(newObject));
                break;
            case ClassName::ThirdMonster:
                newObject = new ThirdMonster(x,y,map_unit,map_unit,this);
                monsters.insert(static_cast<ThirdMonster*>(newObject));
                movethings.insert(static_cast<ThirdMonster*>(newObject));
                break;
            case ClassName::MushroomBuff:
                newObject = new MushroomBuff(x,y,map_unit,map_unit,this);
                buffs.insert(static_cast<MushroomBuff*>(newObject));
                break;
            case ClassName::FlowerBuff:
                newObject = new FlowerBuff(x,y,map_unit,map_unit,this);
                buffs.insert(static_cast<FlowerBuff*>(newObject));
                break;
            case ClassName::Gold:
                newObject = new Gold(x,y,map_unit,map_unit,this);
                values.insert(static_cast<Gold*>(newObject));
                break;
            case ClassName::Goal:
                goal = new Goal(x,y,map_unit,map_unit,this);
                newObject = goal;
                break;
            default:
                QMessageBox::warning(this,"Warning","场景文件有奇怪的东西！");
            }
            sceneMap[x/map_unit][y/map_unit] = newObject; // 保存到指针数组中
        }
    }
    file.close();
    // 小提示
    if(player==nullptr&&goal==nullptr){
        QMessageBox::information(this,"Info","请放置你的人物和目的地哟~");
    }
    else if(player==nullptr){
        QMessageBox::information(this,"Info","请放置你的人物哟~");
    } else if(goal==nullptr){
        QMessageBox::information(this,"Info","请放置你的目的地哟~");
    }
    gameStart();
}

// 保存场景
void Scene::saveScene(const QString &scenePath)
{
    //    qDebug() << "save";
    QFile file(scenePath);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    // 保存玩家信息，要保存初始位置
    //    if(player){
    //        out<<player->metaObject()->className()<<" "<<player->originX()<<" "<<player->originY()<<endl;
    //        sceneMap[player->x()/map_unit][player->y()/map_unit] = nullptr;
    //    }
    // 保存地图信息
    if(sceneMap){
        for(int i=0;i<map_width;i++){
            for(int j=0;j<map_height;j++){
                if(sceneMap[i][j]) {
                    out << sceneMap[i][j]->metaObject()->className()<<" "<<sceneMap[i][j]->originX()<<" "<<sceneMap[i][j]->originY()<<endl;
                }
            }
        }
    }
    //    for(auto iter = terrains.begin();iter!=terrains.end();++iter){
    //        out << (*iter)->metaObject()->className()<<" "<<(*iter)->originX()<<" "<<(*iter)->originY()<<endl;
    //    }
    file.close();
}

void Scene::gameReload()
{
    // 人物回到原位
    if(player){
        player->initialize();
    }

    // 移动物体回到原位
    for(auto iter=movethings.begin();iter!=movethings.end();++iter){
        (*iter)->initialize();
    }

    // 重新显示
    if(sceneMap){
        for(int i=0;i<map_width;i++){
            for(int j=0;j<map_height;j++){
                if(sceneMap[i][j]) {
                    sceneMap[i][j]->show();
                }
            }
        }
    }
}

void Scene::gameStart()
{
    gameReload();
    gameTime = clock();
}

// SLOT，过关
void Scene::gameSuccess()
{
    QMessageBox::information(this,"Congratulation","恭喜过关！");
    gameStart();
    emit clearKeyPressed();
}

// 构造函数，初始化
Scene::Scene(QWidget *parent) : QWidget(parent),m_width(1902),m_height(1002),map_unit(50),map_width(m_width/map_unit),map_height(m_height/map_unit),
    fps(16),gameTime(0),background(":/images/background/images/background/background.png"), sceneMap(nullptr),player(nullptr),goal(nullptr), temp(nullptr),
    ci(SceneInfo(m_width,m_height,&player,&goal,&terrains,&traps,&monsters,&buffs,&values)), updater(fps,this),
    isEdit(false), isShowChooseWidget(false),isMovingThing(false)
{
    resize(m_width,m_height); // 重构大小
    setMouseTracking(true); // 鼠标追踪
    makeName2Num(); // 初始化映射
    makeConnection(); // 初始化连接
    initialize(); // 初始化变量
}

// 析构函数，释放空间
Scene::~Scene()
{
    if(sceneMap){
        for(int i=0;i<map_width;i++){
            for(int j=0;j<map_height;j++){
                delete sceneMap[i][j];
            }
            delete[] sceneMap[i];
        }
        delete[] sceneMap;
    }
}

int Scene::getFPS() const
{
    return fps;
}

