#include "baseobject.h"

BaseObject::BaseObject(QObject *parent) : QObject(parent)
{}

BaseObject::BaseObject(int x, int y, int width, int height,
                       const QString& imgPath, QObject *parent)
    : QObject(parent), _rect(x, y, width, height), _image(imgPath), _originX(x),
    _originY(y), _show(true)
{}

int BaseObject::width() const
{
    return _rect.width();
}

int BaseObject::height() const
{
    return _rect.height();
}

int BaseObject::x() const
{
    return _rect.x();
}

int BaseObject::y() const
{
    return _rect.y();
}

int BaseObject::originX() const
{
    return _originX;
}

int BaseObject::originY() const
{
    return _originY;
}

void BaseObject::setOrigin(int x, int y)
{
    _originX = x;
    _originY = y;
}

void BaseObject::show()
{
    _show = true;
}

void BaseObject::hide()
{
    _show = false;
}

bool BaseObject::isShow() const
{
    return _show;
}

const QRect& BaseObject::getRect() const
{
    return _rect;
}

const QImage& BaseObject::getImage() const
{
    return _image;
}

void BaseObject::moveRect(int x, int y)
{
    _rect.moveTo(x, y);
}
