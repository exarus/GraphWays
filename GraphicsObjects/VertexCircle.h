#ifndef VERTEXCIRCLE_H
#define VERTEXCIRCLE_H
#include <QGraphicsEllipseItem>

class VertexCircle : public QGraphicsEllipseItem
{
public:
    explicit VertexCircle(const qreal &radius, QGraphicsItem *parent = 0);

    qreal getRadius() const;
    void setRadius(const qreal &value);

private:
    static const qreal DEFAULT_VERTEX_CIRCLE_RADIUS;
    qreal radius;
};

#endif // VERTEXCIRCLE_H
