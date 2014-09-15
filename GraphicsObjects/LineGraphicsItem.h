#ifndef LINEGRAPHICSITEM_H
#define LINEGRAPHICSITEM_H
#include <QGraphicsLineItem>
class VertexGraphicsItem;
class VertexText;

class LineGraphicsItem : public QGraphicsLineItem
{
public:
    explicit LineGraphicsItem
             (VertexGraphicsItem* start, QGraphicsItem *parent = 0);
    explicit LineGraphicsItem
             (VertexGraphicsItem* start, VertexGraphicsItem* end, QGraphicsItem *parent = 0);
    ~LineGraphicsItem();

    static qreal lineCos(QLineF line);
    static qreal lineSin(QLineF line);

    void setLine(const QLineF &line);

    void setEndPoint(const QPointF &end);
    QPointF getEndPoint() const;

    void setStart(VertexGraphicsItem *startItem);
    void setEnd  (VertexGraphicsItem *endItem);

    QPointF getStartPoint() const;
    void setStartPoint(const QPointF &value);

    VertexGraphicsItem *getStartItem() const;
    VertexGraphicsItem *getEndItem() const;

    bool operator==(const LineGraphicsItem &other) const;

    void show();
    void hide();
    void remove();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    VertexText *getWeightText() const;

    QGraphicsLineItem *getRight() const;
    QGraphicsLineItem *getLeft() const;

private:
//    QGraphicsLineItem *left;
//    QGraphicsLineItem *right;
    VertexText *weightText;
    QPointF startPoint;
    QPointF endPoint;
    VertexGraphicsItem *startItem;
    VertexGraphicsItem *endItem;

    const int _arrowSizeX = 15;
    const int _arrowSizeY = 7;
    const QPolygonF _arrow = QPolygonF(QVector<QPointF>( {QPointF(0, 0),
                                                          QPointF(-_arrowSizeX, _arrowSizeY),
                                                          QPointF(-_arrowSizeX, -_arrowSizeY),
                                                          QPointF(0, 0)}));
};

#endif // LINEGRAPHICSITEM_H
