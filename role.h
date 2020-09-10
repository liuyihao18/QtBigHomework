#ifndef ROLE_H
#define ROLE_H

#include "baseobject.h"
#include "movething.h"
#include <QTimer>

class Role : public BaseObject, public MoveThing {
    Q_OBJECT

public:

    Role(QObject *parent = nullptr);
    Role(int            x,
         int            y,
         int            width,
         int            height,
         const QString& imgPath,
         int            speed,
         int            _HP,
         int            directio_n,
         QObject       *parent = nullptr);
    void initialize() override;
    void returnOriginPos() override;
    void confirmPos() override;
    void cancelPos() override;
    int  getHP() const;
    void addHP(int x);
    void reduceHP(int x);

protected:

    int _HP;
    int _originHP;
    bool _invincible;
    QTimer _invincibleTimer;

protected slots:

    void invincibleOver();
};

#endif // ROLE_H
