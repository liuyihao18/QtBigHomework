#ifndef ARROWTRAP_H
#define ARROWTRAP_H

#include "terrain.h"
#include "launcher.h"
#include "arrow.h"
#include <QTimer>

class ArrowTerrain : public Terrain, public Launcher {
    Q_OBJECT

public:

    ArrowTerrain(QObject *parent = nullptr);
    ArrowTerrain(int      x,
                 int      y,
                 int      width,
                 int      height,
                 QObject *parent = nullptr);
    FlyingProp* launchFlyingProp() override;

protected:

    QTimer _launchTimer;

protected slots:

    void launchOver();
};

#endif // ARROWTRAP_H
