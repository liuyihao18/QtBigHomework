#ifndef BUFF_H
#define BUFF_H

#include "baseobject.h"

class Buff : public BaseObject
{
    Q_OBJECT
public:
    Buff(QObject* parent = nullptr);
    Buff(int x,int y,int width,int height, const QString& imgPath,QObject* parent=nullptr);
};

#endif // BUFF_H
