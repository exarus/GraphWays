#include <QPen>
#include "LineGraphicsItem.h"
#include "GlobalSettings.h"
#include <QGraphicsScene>
#include <QtMath>
#include "VertexGraphicsItem.h"
#include <QLineF>
#include <QPainter>

LineGraphicsItem::LineGraphicsItem(VertexGraphicsItem *start,
                                   QGraphicsItem *parent)
    : QGraphicsLineItem(parent)
{
    startItem = start;
    endItem = nullptr;
    startItem->attachLine(this);
    startPoint = start->scenePos();
    setPen(GlobalSettings::getEdgePen());
    weightText = new VertexText
            (QString::number(GlobalSettings::getEdgeVeight()), 12, this);
    hide();
}

LineGraphicsItem::LineGraphicsItem(VertexGraphicsItem *start,
                                   VertexGraphicsItem *end,
                                   QGraphicsItem *parent)
    : LineGraphicsItem(start, parent)
{
    if (end !=nullptr) {
        endItem = end;
    } else {
        startItem = nullptr;
        endItem = nullptr;
    }
}

/**
 *  may cause errors with nullptrs
 * @brief LineGraphicsItem::~LineGraphicsItem
 */
LineGraphicsItem::~LineGraphicsItem()
{
    if (scene())
        scene()->removeItem(this);
}

void LineGraphicsItem::setEnd(VertexGraphicsItem* endItem) {
    if (endItem != nullptr && startItem != nullptr) {
        if (this->endItem == nullptr ||
                *this->endItem != *endItem) {
            this->endItem = endItem;
            endItem->attachLine(this);
        }

        endPoint = endItem->scenePos();
        setLine(QLineF(getStartPoint(), getEndPoint()));
    }
}

void LineGraphicsItem::setLine(const QLineF &line) {

    const QPointF dP = line.p2() - startItem->scenePos();
    qreal distance = qSqrt((dP.x() * dP.x()) +
                           (dP.y() * dP.y()));
    qreal radius = startItem->getCircle()->getRadius() +
                   startItem->getCircle()->pen().widthF();

    // Базові точки та вектори
//   qreal alpha = 0.9;  // пропорція
    qreal d = 10.0;     // відстань цифри від прямої

    QPointF vector   = line.p2() - line.p1();
    QPointF middle   = (line.p2() + line.p1()) * 0.5;
    //    QPointF arrowEnd = (line.p1() + alpha * line.p2()) / (1 + alpha);
//    QPointF arrowEnd = line.pointAt(alpha);

//     Результуючі координати цифри
    qreal labelX = middle.x();
    qreal labelY = middle.y();

//    qreal leftX = arrowEnd.x() - 10;
//    qreal leftY = arrowEnd.y() - 10;

//    qreal rightX = arrowEnd.x() + 10;
//    qreal rightY = arrowEnd.y() + 10;

    // Якщо вектор не вертикальний, то


    if (vector.x() != 0) {
        qreal yDivX = vector.y() / vector.x();
        int sign = vector.x() > 0? 1 : -1;
        qreal labelVectorY = d /  qSqrt(1 + yDivX * yDivX);
        labelY += sign * labelVectorY;
        labelX += -sign * yDivX * labelVectorY;

        //leftX  += labelVectorY;
        //leftY  -= yDivX * labelVectorY;
        //rightX -= labelVectorY;
        //rightY += yDivX * labelVectorY;
    } else {
        if (vector.y() > 0) {
            labelX -= d;
        } else {
            labelX += d;
        }
    }


    weightText->setPos(QPointF(labelX, labelY));
//    right->setLine(rightX, rightY, line.p2().x(), line.p2().y());
//    left->setLine(leftX, leftY, line.p2().x(), line.p2().y());
//    weightText->setPos(middle);

    if (distance > radius) {
        show();
    } else {
        hide();
    }
    QGraphicsLineItem::setLine(line);
}



/**
 *  Bugs if endItem == nullptr
 * @brief LineGraphicsItem::getStartPoint
 * @return the best start point for the line.
 */
QPointF LineGraphicsItem::getStartPoint() const
{
    if ((endPoint.isNull()) || (startItem == nullptr)) {
        return startPoint;
    }

    qreal rad = startItem->getCircle()->getRadius() +
                startItem->getCircle()->pen().widthF();
    QLineF line (startItem->scenePos(), endPoint);

    QPointF offset = QPointF (+rad * lineCos(line),
                              -rad * lineSin(line));
    return startItem->scenePos() + offset;
}

/**
 * @brief LineGraphicsItem::getEndPoint
 * @return the best end point for the line.
 */
QPointF LineGraphicsItem::getEndPoint() const
{
    if ((startPoint.isNull()) || (endItem == nullptr)) {
        return endPoint;
    }

    qreal rad = endItem->getCircle()->getRadius() +
                endItem->getCircle()->pen().widthF();
    QLineF line ((startItem == nullptr)? startPoint
                                       : startItem->scenePos(),
                 endItem->scenePos());

    QPointF offset = QPointF (-rad * lineCos(line),
                              +rad * lineSin(line));
    return endItem->scenePos() + offset;
}

void LineGraphicsItem::setStart(VertexGraphicsItem *startItem)
{
    if (*this->startItem != *startItem) {
        this->startItem = startItem;
        if (endItem != nullptr)
            startItem->attachLine(this);
    }
    startPoint = startItem->scenePos();
    setLine(QLineF(getStartPoint(), getEndPoint()));
}

void LineGraphicsItem::setStartPoint(const QPointF &value)
{
    startPoint = value;
}

VertexGraphicsItem *LineGraphicsItem::getStartItem() const
{
    return startItem;
}

VertexGraphicsItem *LineGraphicsItem::getEndItem() const
{
    return endItem;
}

bool LineGraphicsItem::operator==(const LineGraphicsItem &other) const
{
    return (startItem == other.startItem) &&
            (endItem == other.endItem);
}

void LineGraphicsItem::show()
{
    weightText->show();
    QGraphicsLineItem::show();
}

void LineGraphicsItem::hide()
{
    weightText->hide();
    QGraphicsLineItem::hide();
}

void LineGraphicsItem::remove()
{
    getStartItem()->getAttachedLines().takeLast();
    scene()->removeItem(weightText);
    scene()->removeItem(this);
    //delete this->weightText;
}

void LineGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    qreal angle = acos(line().dx() / line().length()) * (180.0 / 3.1415);

    if(line().dy() < 0) {
        angle = -angle;
    }

    qreal multiplier = 1;
    if(line().length() < 80) {
        multiplier = line().length() / 90.0;
    }
    QMatrix matrix;
    matrix.translate(line().x2(), line().y2());
    matrix.scale(multiplier, multiplier);
    matrix.rotate(angle);

    painter->setBrush(QBrush(GlobalSettings::getEdgeColor()));
    painter->setPen(GlobalSettings::getEdgePen());
    painter->drawPolygon(matrix.map(_arrow));

    QGraphicsLineItem::paint(painter, option, widget);
}

QRectF LineGraphicsItem::boundingRect() const
{
    return QGraphicsLineItem::boundingRect().adjusted(-30, -30, 30, 30);
}

VertexText *LineGraphicsItem::getWeightText() const
{
    return weightText;
}

qreal LineGraphicsItem::lineCos(QLineF line)
{
    return line.dx() / line.length();
}

qreal LineGraphicsItem::lineSin(QLineF line)
{
    return -line.dy() / line.length();
}

void LineGraphicsItem::setEndPoint(const QPointF &end)
{
    endPoint = end;
    QLineF line (getStartPoint(), endPoint);
    setLine(line);
}
