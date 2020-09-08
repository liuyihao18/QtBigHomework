#ifndef ACTIVETRAP_H
#define ACTIVETRAP_H

#include "trap.h"
#include "movething.h"

// 主动触发式陷阱
class ActiveTrap : public Trap
{
    Q_OBJECT
public:
    ActiveTrap(QObject* parent = nullptr);
    ActiveTrap(int x,int y,int width, int height, QObject* parent=nullptr);
};

#endif // ACTIVETRAP_H
