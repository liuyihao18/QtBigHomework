#ifndef FLOWERBUFF_H
#define FLOWERBUFF_H

#include "buff.h"

class FlowerBuff : public Buff {
    Q_OBJECT

public:

    FlowerBuff(QObject *parent = nullptr);
    FlowerBuff(int      x,
               int      y,
               int      width,
               int      height,
               QObject *parent = nullptr);
};

#endif // FLOWERBUFF_H
