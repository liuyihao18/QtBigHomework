#ifndef FLYINGBRICKS_H
#define FLYINGBRICKS_H

#include "terrain.h"
#include "movething.h"
#include "direction.h"

// 飞行砖块
class FlyingBrick : public Terrain, public MoveThing {
    Q_OBJECT

public:

    FlyingBrick(QObject *parent = nullptr);
    FlyingBrick(int      x,
                int      y,
                int      width,
                int      height,
                QObject *parent = nullptr);
    bool isReverse() const;
    void updatePos(int judgeUnit) override;
    void confirmPos() override;
    void cancelPos() override;
    void returnOriginPos() override;
    void needToChangeMove() override;
    void initialize() override;

protected:

    bool _reverse;
};

#endif // FLYINGBRICKS_H
