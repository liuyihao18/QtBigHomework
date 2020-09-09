#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), timer(this), stateTimer(this), loaderTimer(this), fps(0), mm(this)
{
    ui->setupUi(this);
    fps = ui->scene->getFPS();
    timer.setInterval(fps); // 设定帧率为16ms
    timer.start(); // 开始定时器
    stateTimer.setInterval(1000); // 提示时间1s
//    loaderTimer.setInterval(3750); // 加载时间5s
    loaderTimer.setInterval(100);
    makeConnection(); // 建立连接
    showFullScreen(); // 全屏显示
    loaderTimer.start(); // 开始加载计时
    mm.playBGMusic(); // 播放背景音乐
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 保存按下的键
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    pressedKeys.insert(event->key());
    // 全屏显示
    if(event->key()==Qt::Key_F11){
        if(isFullScreen()){
            showMaximized();
        }
        if(isMaximized()){
            showFullScreen();
        }
    }
    if(event->key()==Qt::Key_Escape){
        if(ui->actEdit->isChecked()){
            emit chooseSceneWidget(false,"");
        }
    }
    QMainWindow::keyPressEvent(event);
}

// 删除按下的键
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    pressedKeys.remove(event->key());
    QMainWindow::keyReleaseEvent(event);
}

// 当定时器timeout()之后，发射带有键盘信息的信号，更新地图画面
void MainWindow::timeout()
{
    emit updateScene(pressedKeys);
}

// 工具栏触发事件，确定选择组件的类型，发出信号
void MainWindow::triggerSceneWidgets(QAction* action)
{
    bool isChecked = action->isChecked();
    clearChooseSceneWidget(); // 清楚之前选择的
    action->setChecked(isChecked); // 设置当前选择的有效
    emit chooseSceneWidget(action->isChecked(), action->text());
    ui->stateLabel->setText(action->text());
}

// 清楚其他所有按下的SceneWidget，保证互斥
void MainWindow::clearChooseSceneWidget()
{
    QVector<QAction*> actions = {ui->srcPlayer, ui->srcRock,ui->srcFloorGrass, ui->srcSpring,
                                ui->srcFlyingBrick, ui->srcDestructibleBrick,ui->srcActiveTrap,
                                ui->srcPassiveTrap,ui->srcArrowTerrain, ui->srcFirstMonster,
                                 ui->srcSecondMonster, ui->srcThirdMonster,ui->srcMushroomBuff,
                                 ui->srcFlowerBuff,ui->srcGold, ui->srcGoal};
    for(auto iter=actions.begin();iter!=actions.end();++iter){
        (*iter)->setChecked(false);
    }
}

// 清楚提示文字
void MainWindow::clearStateLabel()
{
    ui->stateLabel->clear();
    stateTimer.stop();
}

// 清楚键盘状态
void MainWindow::clearKeyPressed()
{
    pressedKeys.clear();
}


// 加载结束
void MainWindow::loadOver()
{
    ui->action->setEnabled(true);
    loaderTimer.stop();
}

// 返回主页
void MainWindow::on_actHome_triggered()
{
    sceneFileName = "";
    ui->scene->setGameState(Loading);
    ui->actEdit->setChecked(false);
    ui->sceneWidgets->setEnabled(false);
}

// 新建按钮
void MainWindow::on_actNew_triggered()
{
    sceneFileName = "";
    emit newScene();
    ui->actEdit->setChecked(true);
    emit ui->actEdit->triggered(true);
    ui->stateLabel->setText("新建成功"); // 提示文字
    stateTimer.start();
}

// 编辑按钮
void MainWindow::on_actEdit_triggered(bool checked)
{
    // 进入编辑模式，向场景类发送进入编辑模式的信号
    clearChooseSceneWidget();
    ui->sceneWidgets->setEnabled(checked); // 场景组件是否可用
    if(checked){
        ui->scene->setGameState(Editing);
    }else{
        ui->scene->setGameState(Gaming);
    }
}

// 打开按钮
void MainWindow::on_actOpen_triggered()
{
    // 打开场景，向场景发出打开的信号
    QString openFile = QFileDialog::getOpenFileName(this,tr("Open Scene"),"./scene/",tr("Scene Files(*.scene)"));
    if(!openFile.isEmpty()){
        sceneFileName = openFile; // 保存打开的文件名
        emit loadScene(sceneFileName); // 加载
        if(ui->actEdit->isChecked()){
            ui->scene->setGameState(Editing);
        }else{
            ui->scene->setGameState(Gaming);
        }
        ui->stateLabel->setText("打开成功"); // 提示文字
    }else{
        ui->stateLabel->setText("打开失败"); // 提示文字
    }
    stateTimer.start();
}

// 保存按钮
void MainWindow::on_actSave_triggered()
{
    // 保存，向场景发出保存的信号
    if(!sceneFileName.isEmpty()){
        emit saveScene(sceneFileName); // 如果已经打开文件，则保存
        ui->stateLabel->setText("保存成功");
        stateTimer.start();
    }else{
        on_actSaveAs_triggered(); // 否则另存为
    }
}

// 另存为按钮
void MainWindow::on_actSaveAs_triggered()
{
    // 另存为按钮，向场景发出保存的信号
    QString saveFile = QFileDialog::getSaveFileName(this,tr("Save Scene"),"./scene/",tr("Scene Files(*.scene)"));
    if(!saveFile.isEmpty()){
        if(sceneFileName.isEmpty()){
            on_actNew_triggered();
        }
        sceneFileName = saveFile; // 另存为会改变打开的文件名
        emit saveScene(sceneFileName);
        ui->stateLabel->setText("保存成功");
    }else{
        ui->stateLabel->setText("保存失败");
    }
    stateTimer.start();
}

// 重启游戏
void MainWindow::on_actRestart_triggered()
{
    emit gameRestart();
}

// 建立连接
void MainWindow::makeConnection()
{
    // 加载计时
    connect(&loaderTimer,SIGNAL(timeout()),this,SLOT(loadOver()));
    connect(&loaderTimer,SIGNAL(timeout()),ui->scene,SLOT(loadOver()));
    // 主定时器的timeout()与主窗口的timeout()连接
    connect(&timer,SIGNAL(timeout()),this,SLOT(timeout()));
    // 主窗口发出携带键盘信息的信号给地图，使地图更新画面
    connect(this,SIGNAL(updateScene(const QSet<int>&)),ui->scene,SLOT(updateScene(const QSet<int>&)));
    // sceneWidgets与槽函数连接
    connect(ui->sceneWidgets,SIGNAL(actionTriggered(QAction*)),this,SLOT(triggerSceneWidgets(QAction*)));
    connect(this,SIGNAL(chooseSceneWidget(bool, const QString&)),ui->scene,SLOT(chooseSceneWidget(bool, const QString&)));
    // 清空选择的组件
    connect(ui->scene,SIGNAL(clearChooseSceneWidget()),this,SLOT(clearChooseSceneWidget()));
    // 新建场景
    connect(ui->scene,SIGNAL(newSceneFile()),this,SLOT(on_actNew_triggered()));
    connect(this,SIGNAL(newScene()),ui->scene,SLOT(newScene()));
    // 打开场景
    connect(ui->scene,SIGNAL(chooseSceneFile()),this,SLOT(on_actOpen_triggered()));
    connect(this,SIGNAL(loadScene(const QString&)),ui->scene,SLOT(loadScene(const QString&)));
    // 保存场景
    connect(this,SIGNAL(saveScene(const QString&)),ui->scene,SLOT(saveScene(const QString&)));
    // 状态栏与编辑模式清空状态栏显示
    connect(&stateTimer,SIGNAL(timeout()),this,SLOT(clearStateLabel()));
    // 游戏过关或者结束清楚键盘状态
    connect(ui->scene,SIGNAL(clearKeyPressed()),this,SLOT(clearKeyPressed()));
    // 游戏重新开始
    connect(this,SIGNAL(gameRestart()),ui->scene,SLOT(gameRestart()));
}



