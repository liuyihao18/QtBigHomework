#ifndef PASSIVETRAP_H
#define PASSIVETRAP_H

#include "trap.h"

// 被动触发式陷阱
class PassiveTrap : public Trap
{
    Q_OBJECT
public:
    PassiveTrap(QObject* parent = nullptr);
    PassiveTrap(int x,int y, int width, int height, QObject* parent=nullptr);
};

#endif // PASSIVETRAP_H
