#ifndef GOLD_H
#define GOLD_H

#include "values.h"

class Gold : public Values {
    Q_OBJECT

public:

    Gold(QObject *parent = nullptr);
    Gold(int      x,
         int      y,
         int      width,
         int      height,
         QObject *parent);
};

#endif // GOLD_H
