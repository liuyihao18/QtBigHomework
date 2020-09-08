#ifndef MONSTER_H
#define MONSTER_H

#include "role.h"
#include "hpreducer.h"

class Monster : public Role, public HPReducer
{
    Q_OBJECT
public:
    Monster(QObject* parent = nullptr);
    Monster(int x, int y, int height, int width, const QString& imgPath, int HP, int direction, int HPReduced, QObject* parent=nullptr);

};

#endif // MONSTER_H
