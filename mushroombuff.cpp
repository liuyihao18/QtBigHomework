#include "mushroombuff.h"

MushroomBuff::MushroomBuff(QObject *parent) : Buff(parent)
{}

MushroomBuff::MushroomBuff(int x, int y, int width, int height, QObject *parent)
    : Buff(x,
           y,
           width,
           height,
           ":/images/buff/images/buff/mushroomBuff.png",
           parent)
{}
