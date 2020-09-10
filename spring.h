#ifndef SPRING_H
#define SPRING_H

#include "terrain.h"

// 弹簧
class Spring : public Terrain {
    Q_OBJECT

public:

    Spring(QObject *parent = nullptr);
    Spring(int      x,
           int      y,
           int      width,
           int      height,
           QObject *parent = nullptr);
};

#endif // SPRING_H
