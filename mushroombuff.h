#ifndef MUSHROOMBUFF_H
#define MUSHROOMBUFF_H

#include "buff.h"

class MushroomBuff : public Buff
{
    Q_OBJECT
public:
    MushroomBuff(QObject* parent=nullptr);
    MushroomBuff(int x,int y,int width,int height,QObject* parent=nullptr);
};

#endif // MUSHROOMBUFF_H
