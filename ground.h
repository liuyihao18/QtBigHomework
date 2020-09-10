#ifndef GROUND_H
#define GROUND_H

#include "terrain.h"

class Ground : public Terrain {
    Q_OBJECT

public:

    Ground(QObject *parent = nullptr);
    Ground(int            x,
           int            y,
           int            width,
           int            height,
           const QString& imgPath,
           QObject       *parent = nullptr);
};

#endif // GROUND_H
