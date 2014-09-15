#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QColor>
#include <QPen>

class GlobalSettings
{
    static qreal  edgeWidth;
    static QPen   edgePen;
    static QColor edgeColor;
    static int    edgeVeight;

    static QColor vertexPenColor;
    static QColor vertexBrushColor;
    static qreal  vertexWidth;
    static QPen   vertexPen;
    static QBrush vertexBrush;

    static QTransform sceneTransform;

public:

    static QColor getEdgeColor();
    static void   setEdgeColor(const QColor &value);
    static qreal  getEdgeWidth();
    static void   setEdgeWidth(int value);
    static QPen getEdgePen();
    static void setEdgePen(const QPen &value);
    static int getEdgeVeight();
    static void setEdgeVeight(int value);

    static QPen getVertexPen();
    static void setVertexPen(const QPen &value);
    static QColor getVertexPenColor();
    static void   setVertexPenColor(const QColor &value);
    static qreal getVertexWidth();
    static void setVertexWidth(const qreal &value);
    static QBrush getVertexBrush();
    static void setVertexBrush(const QBrush &value);
    static QColor getVertexBrushColor();
    static void setVertexBrushColor(const QColor &value);

    static QTransform getSceneTransform();
    static void       setSceneTransform(const QTransform &value);

private:
    GlobalSettings();
};

#endif // GLOBALSETTINGS_H
