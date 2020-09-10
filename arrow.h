#ifndef ARROW_H
#define ARROW_H

#include "flyingprop.h"

class Arrow : public FlyingProp {
    Q_OBJECT

public:

    Arrow(QObject *parent = nullptr);
    Arrow(int      x,
          int      y,
          int      width,
          int      height,
          int      directio_n,
          QObject *parent = nullptr);
};

#endif // ARROW_H
