#ifndef TRAP_H
#define TRAP_H

#include "baseobject.h"

class Trap : public BaseObject
{
    Q_OBJECT
public:
    Trap(QObject* parent = nullptr);
    Trap(int x, int y, int width, int height,const QString& imgPath, int HPReduce, QObject* parent=nullptr);
    int getHPReduce() const;

protected:
    int HPReduce;
};

#endif // TRAP_H
