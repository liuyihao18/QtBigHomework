#ifndef DESTRUCTIBLEBRICK_H
#define DESTRUCTIBLEBRICK_H

#include "terrain.h"

// 可被破坏的岩石
class DestructibleBrick : public Terrain
{
    Q_OBJECT
public:
    DestructibleBrick(QObject* parent = nullptr);
    DestructibleBrick(int x,int y, int width, int height,QObject* parent = nullptr);
    int getPoints() const;
    void collide();

protected:
    int points;
    int collisionCount;
};

#endif // DESTRUCTIBLEBRICK_H
