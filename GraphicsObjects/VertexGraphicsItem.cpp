#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include "VertexGraphicsItem.h"

const qreal VertexGraphicsItem::DEFAULT_SIZE = 40;

unsigned int VertexGraphicsItem::nextIndex = 1;

VertexGraphicsItem::VertexGraphicsItem
        (const QPointF &center, const qreal &size,
         const QString &text, QGraphicsItem *parent) :
    QGraphicsItemGroup(parent)
{
    this->size = size > 0? size : DEFAULT_SIZE;
    this->setPos(center);
    this->circle = new VertexCircle(this->size, this);
    this->text   = new VertexText((text != 0)? text
                                             : getNextStr(), this->size, this);
    this->ID = this->nextIndex++;

    this->addToGroup(this->circle);
    this->addToGroup(this->text);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

VertexGraphicsItem::~VertexGraphicsItem()
{
//    for(LineGraphicsItem* line : attachedLines) {
//        if ((line->getStartItem() != this) &&
//                (line->getStartItem() != nullptr)) {
//            line->getStartItem()->detachLine(line);
//        }
//        if ((line->getEndItem() != this) &&
//                (line->getStartItem() != nullptr)) {
//            line->getEndItem()->detachLine(line);
//        }
//        delete line;
//    }
    scene()->removeItem(this);
    delete circle;
    delete text;
}

VertexCircle *VertexGraphicsItem::getCircle() const
{
    return circle;
}

inline unsigned int VertexGraphicsItem::getNextID() const {
    return nextIndex;
}

inline QString VertexGraphicsItem::getNextStr() const {
    return QString::number(nextIndex);
}

void VertexGraphicsItem::attachLine(LineGraphicsItem *newLine)
{    
    attachedLines.append(newLine);
}

bool VertexGraphicsItem::detachLine(LineGraphicsItem *oldLine)
{
    // Обход по линиям
    for (int i = 0; i < attachedLines.count(); ++i) {
        LineGraphicsItem *line = attachedLines.at(i);
        if (*line == *oldLine) {
            if (oldLine->getStartItem() == this) {
                oldLine->setStart(nullptr);
            } else if (line->getEndItem() == this) {
                oldLine->setEnd(nullptr);
            }
            return attachedLines.removeAll(line);
        }
    }

    return false;
}

QList<LineGraphicsItem *> VertexGraphicsItem::getAttachedLines() const
{
    return attachedLines;
}

bool VertexGraphicsItem::operator !=(const VertexGraphicsItem &other) const
{
    return (this->ID != other.ID);
}

bool VertexGraphicsItem::operator ==(const VertexGraphicsItem &other) const
{
    return (this->ID == other.ID);
}
int VertexGraphicsItem::getID() const
{
    return ID;
}

