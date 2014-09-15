#ifndef SHORTESTWAYSDIALOG_H
#define SHORTESTWAYSDIALOG_H

#include "ui_ShortestWaysDialog.h"
#include <GraphParts/Graph.h>

class ShortestWaysDialog : public QDialog, private Ui::ShortestWaysDialog
{
    Q_OBJECT
    Graph *graph;
public:
    explicit ShortestWaysDialog(Graph *graph, QWidget *parent = 0);
    ~ShortestWaysDialog();    
private slots:
    void on_DijkstraButton_clicked();
    void on_FloydWarshallButton_clicked();
    void on_BellmanFordButton_clicked();
    void on_JohnsonButton_clicked();
    void on_DantzigButton_clicked();
    void on_planarityButton_clicked();
};

#endif // SHORTESTWAYSDIALOG_H
