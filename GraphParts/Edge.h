#ifndef EDGE_H
#define EDGE_H

#include "GraphicsObjects/LineGraphicsItem.h"
class Vertex;

class Edge : public LineGraphicsItem
{
public:
    Edge(Vertex *start);
    Edge(Vertex *start, Vertex *end);

    Vertex *getStart() const;
    void setStart(Vertex *value);

    Vertex *getEnd() const;
    void setEnd(Vertex *vertex);

    int getVeigth() const;
    void setVeigth(int value);

    bool operator ==(const Edge &other) const;
    void remove();

private:
    Vertex *startVertex;
    Vertex *endVertex;
    int veigth;    
};

#endif // EDGE_H
