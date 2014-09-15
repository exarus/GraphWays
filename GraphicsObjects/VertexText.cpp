#include "VertexText.h"

const qreal VertexText::DEFAULT_SIZE = 40;

VertexText::VertexText(const QString &text, const qreal size, QGraphicsItem *parent) :
    QGraphicsTextItem(text, parent)
{
    // changing the size
    this->size = size > 0? size: DEFAULT_SIZE;
    setPos(QPointF(0, 0));
    setScale(size/10);

    // font settings
    QFont font;
    font.setStyleHint(QFont::Serif);
    this->setFont(font);
}

