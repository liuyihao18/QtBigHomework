#ifndef MONSTER_H
#define MONSTER_H

#include "role.h"

class Monster : public Role
{
    Q_OBJECT
public:
    Monster(QObject* parent = nullptr);
    Monster(int x, int y, int height, int width, const QString& imgPath, QObject* parent=nullptr);
};

#endif // MONSTER_H
