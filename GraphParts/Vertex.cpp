#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(const QPointF &center, const qreal &size,
               const QString &text, QGraphicsItem *parent)
    : VertexGraphicsItem(center, size, text, parent)
{
    outgoingEdges = new QList<Edge*>();
    loop = false;
}

Edge *Vertex::connectTo(Vertex *other)
{
    Edge* edge = nullptr;

    if (!this->isConnectedTo(other)) {
        edge = new Edge(this, other);
        outgoingEdges->append(edge);
    }

    return edge;
}

bool Vertex::isConnectedTo(const Vertex *other) const
{
    for (Edge* edge : *outgoingEdges) {
        if (edge->getEnd() == other) {
            return true;
        }
    }
    return false;
}

bool Vertex::detachEdge(Edge *oldEdge)
{
    for (Edge *edge : *outgoingEdges) {
        if (*edge == *oldEdge) {
            return outgoingEdges->removeAll(edge);
        }
    }
    return false;
}

void Vertex::isolate() {
    while (!outgoingEdges->empty()) {
        Edge *edge = outgoingEdges->takeFirst();
        getAttachedLines().removeAll(edge);
        delete edge;
    }
    while (!getAttachedLines().isEmpty()) {
        LineGraphicsItem *line = getAttachedLines().takeFirst();
        line->getEndItem()->detachLine(line);
        delete line;
    }
}

/**
 *  Function is very dangerous and is not
 * recomended to use.
 *  It makes the edge started from this Vertex
 * and this Vertex connected to the end of the
 * edge.
 *
 * @brief Vertex::connectToEndOf
 * @param edge
 * @return false if edge's end is illegal and nothing
 *         happened, true in other case.
 */
bool Vertex::connectToEndOf(Edge *&edge)
{
    Vertex *other = edge->getEnd(); // вершина для прокладки ребра

    if ((other != NULL) && (other != this) &&
            !this->isConnectedTo(other)) {

        // Переназначаем начало
        edge->setStart(this);
        outgoingEdges->append(edge);
        attachLine(edge);
        return true;
    }

    return false;
}

bool Vertex::addLoop()
{
    if (loop) {
        return false;
    }

    return loop = true;
}

bool Vertex::hasLoop() const
{
    return loop;
}

bool Vertex::removeLoop()
{
    if (loop) {
        return !(loop = false);
    }

    return false;
}
QList<Edge *> *Vertex::getOutgoingEdges() const
{
    return outgoingEdges;
}

void Vertex::setOutgoingEdges(QList<Edge *> *value)
{
    outgoingEdges = value;
}

bool Vertex::isAdjacentTo(Vertex *v2) const {
    for(Edge *edge : *outgoingEdges) {
        if (edge->getEnd() == v2) {
            return true;
        }
    }

    for(Edge *edge : *v2->outgoingEdges) {
        if (edge->getEnd() == this) {
            return true;
        }
    }

    return false;
}

