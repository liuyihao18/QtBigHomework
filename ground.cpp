#include "ground.h"

Ground::Ground(QObject *parent) : Terrain(parent)
{}

Ground::Ground(int            x,
               int            y,
               int            width,
               int            height,
               const QString& imgPath,
               QObject       *parent)
    : Terrain(x, y, width, height, imgPath, parent)
{}
