#ifndef VERTEXTEXT_H
#define VERTEXTEXT_H

#include <QGraphicsTextItem>
#include <QFont>

class VertexText : public QGraphicsTextItem
{
public:
    explicit VertexText(const QString &text, const qreal size = 0,
                        QGraphicsItem *parent = 0);

    /**
     * @brief setPos
     * @param pos
     */
    inline void setPos(const QPointF &pos) {
        QGraphicsTextItem::setPos
                (pos.x() - size * (0.3 * toPlainText().size() + 0.4),
                pos.y() - 1.1 * size);
    }

private:
    static const qreal DEFAULT_SIZE;
    qreal              size;
};

#endif // VERTEXTEXT_H
