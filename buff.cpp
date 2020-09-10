#include "buff.h"

Buff::Buff(QObject *parent) : BaseObject(parent)
{}

Buff::Buff(int            x,
           int            y,
           int            width,
           int            height,
           const QString& imgPath,
           QObject       *parent)
    : BaseObject(x, y, width, height, imgPath, parent)
{}
