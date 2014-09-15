#include "Edge.h"
#include "Vertex.h"
#include <QPen>
#include <GlobalSettings.h>

Edge::Edge(Vertex *start) :
    LineGraphicsItem(start)
{
    setStart(start);
    veigth = GlobalSettings::getEdgeVeight();
}

Edge::Edge(Vertex *start, Vertex *end) :
    LineGraphicsItem(start, end)
{
    setStart(start);
    setEnd(end);
    veigth = GlobalSettings::getEdgeVeight();
}

Vertex *Edge::getStart() const
{
    return startVertex;
}

void Edge::setStart(Vertex *value)
{
    startVertex = value;
}

Vertex *Edge::getEnd() const
{
    return endVertex;
}

void Edge::setEnd(Vertex *vertex)
{
    if ((startVertex != nullptr) && (vertex != nullptr) &&
            (*vertex != *startVertex)) {
        endVertex = vertex;
        LineGraphicsItem::setEnd(vertex);

    } else {
        endVertex = nullptr;
    }
}

int Edge::getVeigth() const
{
    return veigth;
}

void Edge::setVeigth(int value)
{
    veigth = value;
}

bool Edge::operator ==(const Edge &other) const
{
    return (startVertex == other.startVertex) &&
            (endVertex == other.endVertex) &&
            (veigth == other.veigth);
}

void Edge::remove()
{
    startVertex->getOutgoingEdges()->removeAll(this);
    LineGraphicsItem::remove();
}



