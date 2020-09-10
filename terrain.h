#ifndef TERRAIN_H
#define TERRAIN_H

#include "baseobject.h"

class Terrain : public BaseObject {
    Q_OBJECT

public:

    Terrain(QObject *parent = nullptr);
    Terrain(int            x,
            int            y,
            int            width,
            int            height,
            const QString& imgPath,
            QObject       *parent = nullptr);
};

#endif // TERRAIN_H
