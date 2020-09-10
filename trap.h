#ifndef TRAP_H
#define TRAP_H

#include "baseobject.h"
#include "hpreducer.h"

class Trap : public BaseObject, public HPReducer {
    Q_OBJECT

public:

    Trap(QObject *parent = nullptr);
    Trap(int            x,
         int            y,
         int            width,
         int            height,
         const QString& imgPath,
         int            _HPReduce,
         QObject       *parent = nullptr);
};

#endif // TRAP_H
