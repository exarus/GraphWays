#ifndef ALLPATHSFORM_H
#define ALLPATHSFORM_H

#include <QTableWidget>
class Graph;

namespace Ui {
class AllPathsForm;
}

class AllPathsForm : public QWidget
{
    Q_OBJECT

public:

    enum Algorithm {
        FloydWarshall,
        Dantzig,
        Johnsohn
    };

    explicit AllPathsForm(Graph *graph, Algorithm algorithm, QWidget *parent = 0);
    ~AllPathsForm();

private:
    Ui::AllPathsForm *ui;

    /**
     * @brief displayMatrixInTable
     * @param M
     * @param widget
     */
    void displayMatrixInTable(int **M, int n, QTableWidget *widget);
};

#endif // ALLPATHSFORM_H
