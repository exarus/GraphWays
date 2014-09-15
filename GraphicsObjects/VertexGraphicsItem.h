#ifndef VERTEXGRAPHICSITEM_H
#define VERTEXGRAPHICSITEM_H

#include <QGraphicsItemGroup>
#include "QList"
#include "VertexCircle.h"
#include "VertexText.h"
#include "LineGraphicsItem.h"

class VertexGraphicsItem : public QGraphicsItemGroup
{
public:
    explicit VertexGraphicsItem(const QPointF &center, const qreal &size = 0,
                                const QString &text = 0, QGraphicsItem *parent = 0);
    ~VertexGraphicsItem();
    VertexCircle       *getCircle()     const;
    inline unsigned int getNextID()  const;
    inline QString      getNextStr() const;
    void                attachLine(LineGraphicsItem*newLine);
    bool detachLine(LineGraphicsItem *oldLine);

    QList<LineGraphicsItem *> getAttachedLines() const;

    bool operator != (const VertexGraphicsItem &other) const;
    bool operator == (const VertexGraphicsItem &other) const;

    int getID() const;

private:
    QList<LineGraphicsItem *> attachedLines;
    VertexCircle*             circle;
    VertexText*               text;
    static uint               nextIndex;
    static const qreal        DEFAULT_SIZE;
    qreal                     size;
    int                       ID;
};
#endif // VERTEXGRAPHICSITEM_H
