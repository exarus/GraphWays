#include "GlobalSettings.h"
#include <QTransform>

qreal  GlobalSettings::edgeWidth   = 2.5;
qreal  GlobalSettings::vertexWidth = 2;

int GlobalSettings::edgeVeight = 40;

QColor GlobalSettings::edgeColor        = Qt::darkBlue;
QColor GlobalSettings::vertexPenColor   = QColor(134, 22, 186);
QColor GlobalSettings::vertexBrushColor = QColor(255, 255, 0, 30);

QPen   GlobalSettings::edgePen
            (QPen(GlobalSettings::edgeColor, GlobalSettings::edgeWidth));
QPen   GlobalSettings::vertexPen
            (QPen(GlobalSettings::vertexPenColor));

QBrush GlobalSettings::vertexBrush (QBrush(GlobalSettings::vertexBrushColor));

QTransform GlobalSettings::sceneTransform = QTransform ();

GlobalSettings::GlobalSettings()
{
}
int GlobalSettings::getEdgeVeight()
{
    return edgeVeight;
}

void GlobalSettings::setEdgeVeight(int value)
{
    edgeVeight = value;
}

QTransform GlobalSettings::getSceneTransform()
{
    return sceneTransform;
}

void GlobalSettings::setSceneTransform(const QTransform &value)
{
    sceneTransform = value;
}

QColor GlobalSettings::getVertexBrushColor()
{
    return vertexBrushColor;
}

void GlobalSettings::setVertexBrushColor(const QColor &value)
{
    vertexBrushColor = value;
}

QBrush GlobalSettings::getVertexBrush()
{
    return vertexBrush;
}

void GlobalSettings::setVertexBrush(const QBrush &value)
{
    vertexBrush = value;
}

qreal GlobalSettings::getVertexWidth()
{
    return vertexWidth;
}

void GlobalSettings::setVertexWidth(const qreal &value)
{
    vertexWidth = value;
}

QPen GlobalSettings::getVertexPen()
{
    return vertexPen;
}

void GlobalSettings::setVertexPen(const QPen &value)
{
    vertexPen = value;
}

QPen GlobalSettings::getEdgePen()
{
    return edgePen;
}

void GlobalSettings::setEdgePen(const QPen &value)
{
    edgePen = value;
}


qreal GlobalSettings::getEdgeWidth()
{
    return edgeWidth;
}

void GlobalSettings::setEdgeWidth(int value)
{
    edgeWidth = value;
}

QColor GlobalSettings::getEdgeColor()
{
    return edgeColor;
}

void GlobalSettings::setEdgeColor(const QColor &value)
{
    edgeColor = value;
}

QColor GlobalSettings::getVertexPenColor()
{
    return vertexPenColor;
}

void GlobalSettings::setVertexPenColor(const QColor &value)
{
    vertexPenColor = value;
}
