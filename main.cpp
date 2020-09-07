#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QFile>
#include <windows.h>

int main(int argc, char *argv[])
{
    // 主程序
    QApplication a(argc, argv);
    a.setFont(QFont("华文新魏",9)); // 设置字体为华文新魏9号字
    // 引入QSS样式表
//    QFile qssFile(":/qss/qss/main.qss");
//    qssFile.open(QFile::ReadOnly);
//    if(qssFile.isOpen()){
//        a.setStyleSheet(QLatin1String(qssFile.readAll()));
//        qssFile.close();
//    }

    // 应用QSplashScreen实现启动加载动画
    QImage image(":/splash/splash/splash.png");
    QSplashScreen splash(QPixmap::fromImage(image));
//    splash.showMessage("Copyright <span style=\" font-family:'Arial';\">&copy;</span>2020 刘怡豪&amp;刘怡馨"); // 版权信息
    splash.show();
    a.processEvents();
//    Sleep(2000);

    // 显示主窗口
    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
