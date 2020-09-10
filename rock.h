#ifndef INNERBRICK_H
#define INNERBRICK_H

#include "ground.h"

class Rock : public Ground {
    Q_OBJECT

public:

    Rock(QObject *parent = nullptr);
    Rock(int      x,
         int      y,
         int      width,
         int      height,
         QObject *parent = nullptr);
};

#endif // INNERBRICK_H
