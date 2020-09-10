#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QFile>
#include <windows.h>

int main(int argc, char *argv[])
{
    // 主程序
    QApplication a(argc, argv);

    a.setFont(QFont("华文新魏", 9)); // 设置字体为华文新魏9号字

    // 应用QSplashScreen实现启动加载动画
    QImage image(":/splash/splash/splash.png");
    QSplashScreen splash(QPixmap::fromImage(image));

    splash.show();
    a.processEvents();
    Sleep(2000);

    // 显示主窗口
    MainWindow w;

    w.show();
    return a.exec();
}
