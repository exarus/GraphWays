#include "VertexCircle.h"
#include "GlobalSettings.h"
#include <QPen>
#include <QBrush>
#define RAD this->radius

const qreal VertexCircle::DEFAULT_VERTEX_CIRCLE_RADIUS = 40;

VertexCircle::VertexCircle (const qreal &radius, QGraphicsItem *parent) :
    QGraphicsEllipseItem (parent)
{
    RAD = radius > 0? radius : DEFAULT_VERTEX_CIRCLE_RADIUS;

    setRect(-RAD, -RAD, 2 * RAD, 2 * RAD);
    setPen(GlobalSettings::getVertexPen());
    setBrush(GlobalSettings::getVertexBrush());
}
qreal VertexCircle::getRadius() const
{
    return radius;
}

void VertexCircle::setRadius(const qreal &value)
{
    radius = value;
}

