#include "graphscene.h"
#include "GlobalSettings.h"
#include "qmath.h"
#include <QKeyEvent>
#include <QGraphicsView>
#include <QSpinBox>

#define  TRANSFORM      GlobalSettings::getSceneTransform()
#define  POS            event->scenePos()
#define  LAST_EDGE      qgraphicsitem_cast<Edge*> (lastItem)

/* Конструктор сцены */
GraphScene::GraphScene(qreal x, qreal y, qreal width,
                       qreal height, QObject *parent) :
    QGraphicsScene(x, y, width, height, parent)
{
    graph = new Graph(this);
    edgeCreating = false;
    vertexMoving = false;
    scalePercent = 100;
}

GraphScene::~GraphScene()
{
    delete graph;
}

void GraphScene::keyReleaseEvent(QKeyEvent *event) {
    QList<QGraphicsItem*>  list;

    switch (event->key()) {
    case Qt::Key_Delete:
        list = selectedItems();
        for (QGraphicsItem* item : list) {
            graph->removeVertex(qgraphicsitem_cast<Vertex*>(item));
        }
        break;
    default:
        break;
    }
}


/* Отпускаем кнопку мыши */
void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* предмет на який було натиснуто */
    QGraphicsItem *current = itemAt(POS, TRANSFORM);

    // Обробка різних типів подій
    switch (event->button()) {

    //Правий клік
    case Qt::RightButton:

        /* Якщо було натиснуто на існуючу вершину - додаємо ребро */
        if (isVertexChild(current)) {
            lastItem = new Edge
                    (qgraphicsitem_cast<Vertex*>(current->parentItem()));
            edgeCreating = true;
        } else {
            lastItem = graph->addVertex(POS); // інакше додаємо вершину
        }

        addItem(lastItem); // додаємо елемент
        break;

    // Центральний клік
    case Qt::MiddleButton:
        if (isVertexChild(current)) {
            delete current->parentItem();
        }
        break;

    // Левый клик
    case Qt::LeftButton:
        vertexMoving = true;
        break;
    default:
        break;
    }

    QGraphicsScene::mousePressEvent(event);
}


/* Держим кнопку мыши */
void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Если создаётся ребро
    if (edgeCreating) {

        // Текущее ребро
        Edge* lastEdge =
                qgraphicsitem_cast<Edge*> (lastItem);

        // Переназначаем финальную точку
        lastEdge->setEndPoint(event->scenePos());

    }

    // Если идет передвижение вершины - передвигаем ребра за ней
    else if (vertexMoving) {
        for (QGraphicsItem *item : selectedItems()) {
            VertexGraphicsItem *vertex =
                    qgraphicsitem_cast<VertexGraphicsItem*>(item);
            for (LineGraphicsItem *line : vertex->getAttachedLines()) {
                if (line->getStartItem() == vertex) {
                    line->setStart(vertex);
                } else if (line->getEndItem() == vertex){
                    line->setEnd(vertex);
                }
            }
        }
    }

    QGraphicsScene::mouseMoveEvent(event);
}


/* Отпускаем кнопку мыши */
void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *current; // елемент під курсором

    // Обробка різних типів подій
    switch (event->button()) {

    //Правий клік
    case Qt::RightButton:
        if (edgeCreating && LAST_EDGE) {
            edgeCreating = false;   // Закінчення створення ребра за кліком

            /* Ребро, котре створюється */
            Edge  *edge  = LAST_EDGE;
            qreal  width = edge->pen().widthF();
            /* Потрібно для того щоб дізнатися, що під ребром */
            QPointF delta (+width * Edge::lineCos(edge->line()),
                           -width * Edge::lineSin(edge->line()));
            /* предмет на який було скинуто ребро */
            current = itemAt(POS + delta, TRANSFORM);
            Vertex* vertex = nullptr;

            /* Ініціалізуємо вершину для розгляду */
            if (isVertexChild(current)) {
                vertex = qgraphicsitem_cast<Vertex*>(current->parentItem());

            /* Спроба додання сторони */
                edge->setEnd(vertex);          // устанавливаем конец ребра
                if (!graph->addEdge(edge)) {   // если добавление не удалось,
                    edge->remove();           // то удаляем ребро
                }
            } else {
                edge->remove();
            }
        }

    case Qt::LeftButton:
        vertexMoving = false;
        break;

    // Иначе ничего
    default:
        break;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
/*
void GraphScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *current = itemAt(event->scenePos(), TRANSFORM);

    switch (event->button()) {
    case Qt::RightButton:
        if (isVertexChild(current)) {
            Vertex *vertex = qgraphicsitem_cast<Vertex*>
                             (current->parentItem());
            if (vertex->hasLoop()) {
                vertex->addLoop();
            } else {
                vertex->removeLoop();
            }
        }
    default:
        break;
    }

    QGraphicsScene::mouseDoubleClickEvent(event);
}
*/
bool GraphScene::isVertexChild(QGraphicsItem *item)
{
    return item != nullptr &&
            (qgraphicsitem_cast<VertexText*> (item) ||
             qgraphicsitem_cast<VertexCircle*> (item));
}

void GraphScene::setScalePercentFromBox()
{
    QSpinBox *box = qobject_cast<QSpinBox*>(sender());
    if (box != nullptr) {
        setScalePercent(box->value());
    }
}

Graph *GraphScene::getGraph() const
{
    return graph;
}

void GraphScene::setGraph(Graph *value)
{
    graph = value;
}

int GraphScene::getScalePercent()
{
    return scalePercent;
}

void GraphScene::setScalePercent(int percent)
{
    if (!views().isEmpty()) {
        QGraphicsView *view = views().first();
        qreal mod = ((qreal) percent) / scalePercent;
        view->scale(mod, mod);
        scalePercent = percent;
    }
}

void GraphScene::addItem(QGraphicsItem *item)
{
    LineGraphicsItem *line = qgraphicsitem_cast<LineGraphicsItem*>(item);
    if (line) {
        addItem(line->getWeightText());
        line->getWeightText()->setParent(this);
    }
    QGraphicsScene::addItem(item);
}
