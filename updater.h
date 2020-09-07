#ifndef UPDATER_H
#define UPDATER_H

#include "scenewidgets.h"
#include "collisioninspector.h"
#include <QObject>
#include <QTimer>

class Updater : public QObject
{
    Q_OBJECT
public:
    explicit Updater(QObject *parent = nullptr);
    Updater(int fps, QObject *parent = nullptr);
    bool updatePlayer(Player* player, CollisionInspector& ci, const QSet<int>& pressedKeys); // 更新玩家的位置

protected:
    int fps; // 帧率
    int judge_unit; // 判断精度
    bool jumping; // 玩家是否跳跃
    QTimer jumpTimer; // 跳跃计时器

protected slots:
    void jumpOver(); // 跳跃结束

signals:

};

#endif // UPDATER_H
