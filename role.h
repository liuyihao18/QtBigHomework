#ifndef ROLE_H
#define ROLE_H

#include "baseobject.h"
#include "movething.h"

class Role : public BaseObject, public MoveThing
{
    Q_OBJECT
public:
    Role(QObject* parent = nullptr);
    Role(int x,int y, int width, int height, const QString& imgPath, int speed, int HP, QObject* parent=nullptr);
    void returnOrigin() override;

protected:
    int HP;
};

#endif // ROLE_H
