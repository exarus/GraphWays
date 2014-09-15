#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "GraphParts/Graph.h"

class GraphScene : public QGraphicsScene
{
    Q_OBJECT

    Graph* graph;
    QGraphicsItem *lastItem;
    bool edgeCreating;
    bool vertexMoving;
    int scalePercent;

public:
    explicit GraphScene(qreal x, qreal y, qreal width,qreal height,
                        QObject *parent = 0);
    ~GraphScene();

    Graph *getGraph() const;
    void   setGraph(Graph *value);
    int    getScalePercent();
    void   setScalePercent(int percent);
    void addItem(QGraphicsItem *item);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    // virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    bool isVertexChild(QGraphicsItem *item);

public slots:
    void setScalePercentFromBox();
};

#endif // GRAPHSCENE_H
