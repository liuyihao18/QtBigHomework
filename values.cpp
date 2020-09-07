#include "values.h"

Values::Values(QObject* parent) :BaseObject(parent)
{

}

Values::Values(int x, int y, int width, int height, const QString& imgPath, int value, QObject *parent)
    :BaseObject(x,y,width,height,imgPath,parent),value(value)
{

}

int Values::getValue() const
{
    return value;
}

