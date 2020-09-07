#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <QObject>
#include <QRect>
#include <QImage>

class BaseObject : public QObject
{
    Q_OBJECT
protected:
    QRect rect;
    QImage image;
    int m_origin_x;
    int m_origin_y;
    bool is_show;

public:
    BaseObject(QObject *parent=nullptr);
    BaseObject(int x, int y, int width,int height, const QString& imgPath, QObject* parent=nullptr);
    int width() const;
    int height() const;
    int x() const;
    int y() const;
    int originX() const;
    int originY() const;
    void setOrigin(int x, int y);
    void show();
    void hide();
    bool isShow() const;
    const QRect& getRect() const;
    const QImage& getImage() const;
    void moveRect(int x, int y);
};

#endif // BASEOBJECT_H
