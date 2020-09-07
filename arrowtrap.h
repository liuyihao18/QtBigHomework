#ifndef ARROWTRAP_H
#define ARROWTRAP_H

#include "trap.h"
#include "movething.h"

class ArrowTrap : public Trap, public MoveThing
{
    Q_OBJECT
public:
    ArrowTrap(QObject* parent = nullptr);
    ArrowTrap(int x,int y,int width,int height,QObject* parent = nullptr);
};

#endif // ARROWTRAP_H
