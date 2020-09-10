#ifndef FLOORGRASS_H
#define FLOORGRASS_H

#include "ground.h"

// 草坪
class FloorGrass : public Ground {
    Q_OBJECT

public:

    FloorGrass(QObject *parent = nullptr);
    FloorGrass(int      x,
               int      y,
               int      width,
               int      height,
               QObject *parent = nullptr);
};

#endif // FLOORGRASS_H
