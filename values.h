#ifndef VALUES_H
#define VALUES_H

#include "baseobject.h"

class Values : public BaseObject
{
    Q_OBJECT
public:
    Values(QObject* parent = nullptr);
    Values(int x,int y,int width,int height,const QString& imgPath, int value, QObject* parent=nullptr);

protected:
    int value;
};

#endif // VALUES_H
