#-------------------------------------------------
#
# Project created by QtCreator 2014-03-29T19:26:40
#
#-------------------------------------------------

QT       += core\
            gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graph_Ways
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    graphscene.cpp \
    GraphParts/Vertex.cpp \
    GraphicsObjects/VertexCircle.cpp \
    GraphicsObjects/VertexGraphicsItem.cpp \
    GraphicsObjects/VertexText.cpp \
    GraphParts/Graph.cpp \
    GraphParts/Edge.cpp \
    GraphicsObjects/LineGraphicsItem.cpp \
    GlobalSettings.cpp \
    ShortestWaysDialog.cpp \
    algoritmic_windows/AllPathsForm.cpp \
    algoritmic_windows/SingleSourcePathsForm.cpp \
    algoritmic_windows/AlgorithmErrorDialog.cpp \
    algorythms.cpp

HEADERS  += mainwindow.h \
    graphscene.h \
    GraphParts/Vertex.h \
    GraphicsObjects/VertexCircle.h \
    GraphicsObjects/VertexGraphicsItem.h \
    GraphicsObjects/VertexText.h \
    GraphParts/Graph.h \
    GraphParts/Edge.h \
    GraphicsObjects/LineGraphicsItem.h \
    GlobalSettings.h \
    ShortestWaysDialog.h \
    algoritmic_windows/AllPathsForm.h \
    algoritmic_windows/SingleSourcePathsForm.h \
    algoritmic_windows/AlgorithmErrorDialog.h \
    algorythms.h

FORMS    += mainwindow.ui \
    ShortestWaysDialog.ui \
    algoritmic_windows/AllPathsForm.ui \
    algoritmic_windows/SingleSourcePathsForm.ui \
    algoritmic_windows/AlgorithmErrorDialog.ui
