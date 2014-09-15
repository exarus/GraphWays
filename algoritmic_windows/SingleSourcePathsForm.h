#ifndef SINGLESOURCEPATHSFORM_H
#define SINGLESOURCEPATHSFORM_H

#include "ui_singleSourcePathsForm.h"
class Graph;

class SingleSourcePathsForm : public QWidget, private Ui::SingleSourcePathsForm
{
    Q_OBJECT
public:
    enum Algorithm {
        Dijkstra,
        BellmanFord
    };

    explicit SingleSourcePathsForm(Graph *graph, Algorithm algorithm, QWidget *parent = 0);
    ~SingleSourcePathsForm();
private:
    Graph *graph;
    Algorithm algorithm;
public slots:
    void displayVectorInTable(int *M, QTableWidget *widget);
    void changedVertexCount();
private slots:
    void on_pathSearchButton_clicked();
};

#endif // SINGLESOURCEPATHSFORM_H
