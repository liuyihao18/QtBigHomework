#include "terrain.h"

Terrain::Terrain(QObject *parent) : BaseObject(parent)
{}

Terrain::Terrain(int            x,
                 int            y,
                 int            width,
                 int            height,
                 const QString& imgPath,
                 QObject       *parent)
    : BaseObject(x, y, width, height, imgPath, parent)
{}
