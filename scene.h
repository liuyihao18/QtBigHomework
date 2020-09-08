#ifndef MAP_H
#define MAP_H

#include "sceneinfo.h"
#include "classname.h"
#include "collisioninspector.h"
#include "updater.h"
#include <QWidget>
#include <QSet>
#include <QPainter>
#include <QSet>
#include <QMap>


class Scene : public QWidget
{
    Q_OBJECT
private:
    int m_width, m_height, map_unit, placeAcc; // 场景的长宽，地图单位，放置精度
    int fps; // 游戏帧率
    clock_t gameTime; // 游戏时间
    QMap<QString,int> name2num; // className与数字的映射，方便switch
    QImage background; // 背景图片
    Player* player; // 玩家
    Goal* goal; // 终点
    QSet<BaseObject*> allWidgets; // 保存所有的指针
    QSet<Terrain*> terrains; // 保存地形指针的基类数组
    QSet<Trap*> traps; // 保存陷阱指针的基类数组
    QSet<Monster*> monsters; // 保存怪物指针的基类数组
    QSet<Buff*> buffs; // 保存Buff指针的基类数组
    QSet<Values*> values; // 保存有分数物体的基类数组
    QSet<FlyingProp*> flyingProps; // 保存飞行物的指针
    QSet<MoveThing*> moveThings; // 保存会动的物体的指针
    QSet<Launcher*> launchers; // 保存会发射物体的物体的指针
    BaseObject* temp; // 保存临时指针，在放置物体的时候显示
    CollisionInspector ci; // 碰撞检测类
    Updater updater; // 更新场景的类
    bool isEdit,isShowChooseWidget,isMovingThing; // 与编辑模式时的显示有关
    void makeName2Num(); // 构造映射
    void makeConnection(); // 构造连接
    void initialize(); // 初始化

protected:
    void paintEvent(QPaintEvent *) override; // 绘图事件
    void enterEvent(QEvent *) override;; // 进入事件
    void leaveEvent(QEvent *) override;; // 离开事件
    void mouseMoveEvent(QMouseEvent *) override;; // 鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *) override;; // 鼠标松开事件
    void resizeEvent(QResizeEvent *) override;; // 窗口变化事件
    void addSceneWidget(int x, int y); // 增加组件
    void eraseSceneWidget(BaseObject* object); // 擦除组件
    void deleteSceneWidget(int x, int y); // 删除组件
    void moveSceneWidget(int x, int y); // 移动组件

protected slots:
    void updateScene(const QSet<int>&); // 更新场景
    void edit(bool); // 编辑模式
    void chooseSceneWidget(bool, const QString&); // 选择的组件
    void newScene(); // 新建场景
    void loadScene(const QString& scenePath); // 加载场景
    void saveScene(const QString& scenePath); // 保存场景
    void gameReload(); // 游戏恢复
    void gameStart(); // 游戏开始
    void gameSuccess(); // 游戏通关


public:
    explicit Scene(QWidget *parent = nullptr);
    ~Scene();
    int getFPS() const; // 返回帧率

signals:
    void clearChooseSceneWidget(); // 右击清除已选择，返回信号给主窗口
    void clearKeyPressed(); // 清楚键盘状态
};

#endif // MAP_H
