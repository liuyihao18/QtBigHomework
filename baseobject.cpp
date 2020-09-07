#include "baseobject.h"

BaseObject::BaseObject(QObject *parent) : QObject(parent)
{

}

BaseObject::BaseObject(int x, int y, int width, int height,
                       const QString &imgPath, QObject* parent)
    :QObject(parent), rect(x,y,width,height), image(imgPath), m_origin_x(x), m_origin_y(y), is_show(true)
{

}

int BaseObject::width() const
{
    return rect.width();
}

int BaseObject::height() const
{
    return rect.height();
}

int BaseObject::x() const
{
    return rect.x();
}

int BaseObject::y() const
{
    return rect.y();
}

int BaseObject::originX() const
{
    return m_origin_x;
}

int BaseObject::originY() const
{
    return m_origin_y;
}

void BaseObject::setOrigin(int x, int y)
{
    m_origin_x = x;
    m_origin_y = y;
}

void BaseObject::show()
{
    is_show = true;
}

void BaseObject::hide()
{
    is_show = false;
}

bool BaseObject::isShow() const
{
    return is_show;
}

const QRect &BaseObject::getRect() const
{
    return rect;
}

const QImage &BaseObject::getImage() const
{
    return image;
}

void BaseObject::moveRect(int x, int y)
{
    rect.moveTo(x, y);
}
