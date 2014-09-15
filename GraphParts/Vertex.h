#ifndef VERTEX_H
#define VERTEX_H
#include <GraphicsObjects/VertexGraphicsItem.h>
#include <QList>
class Edge;

class Vertex : public VertexGraphicsItem
{
public:
    explicit Vertex(const QPointF &center, const qreal &size = 0,
                   const QString &text = 0, QGraphicsItem *parent = 0);
    //~Vertex();

    Edge *connectTo(Vertex *other);
    bool isConnectedTo(const Vertex *other) const;
    bool detachEdge(Edge *oldEdge);
    bool connectToEndOf(Edge *&edge);

    bool addLoop();
    bool hasLoop() const;
    bool removeLoop();

    QList<Edge*> *getOutgoingEdges() const;
    void setOutgoingEdges(QList<Edge *> *value);

    void isolate();
    bool isAdjacentTo(Vertex *v2) const;
private:
    QList <Edge*> *outgoingEdges;
    bool           loop;
};
#endif // VERTEX_H
