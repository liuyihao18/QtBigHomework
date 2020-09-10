#include "destructiblebrick.h"

DestructibleBrick::DestructibleBrick(QObject *parent) : Terrain(parent)
{}

DestructibleBrick::DestructibleBrick(int      x,
                                     int      y,
                                     int      width,
                                     int      height,
                                     QObject *parent)
    : Terrain(x,
              y,
              width,
              height,
              ":/images/terrain/images/terrain/destuctibleBrick.png",
              parent),
    _points(5), _collisionCount(0)
{}

int DestructibleBrick::getPoints() const
{
    return _points;
}

void DestructibleBrick::collide()
{
    if (_collisionCount == 2) {
        _collisionCount = 0;
        hide();
    } else {
        _collisionCount++;
    }
}
