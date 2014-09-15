#include "singleSourcePathsForm.h"
#include <GraphParts/Graph.h>
#include <algoritmic_windows/AlgorithmErrorDialog.h>

SingleSourcePathsForm::SingleSourcePathsForm
(Graph *graph, Algorithm algorithm, QWidget *parent) :
    QWidget(parent)
{
    // Настройка интерфейса
    setupUi(this);
    vertexChoiseBox->setMaximum(graph->vertexCount());
    this->graph = graph;
    this->algorithm = algorithm;
    if (algorithm == Dijkstra) {
        algorythmNoteLabel->setText
                (tr("Результат работы алгоритма Дейкстры не будет правильным, "
                    "в случае наличия отрицательных ребер в графе."));
    } else if (algorithm == BellmanFord) {
        algorythmNoteLabel->setText
                (tr("Алгоритм Беллмана-Форда работает для ребер с отрицательными "
                    "весами,\nно выдаст сообщение об ошибке, "
                    "в случае наличия отрицательных циклов в графе."));
    }
}

SingleSourcePathsForm::~SingleSourcePathsForm()
{

}

void SingleSourcePathsForm::displayVectorInTable(int *M, QTableWidget *widget)
{
    if (graph->vertexCount() == 0) {
        return;
    }

    if (M == nullptr && algorithm == BellmanFord) {
        AlgorithmErrorDialog *error = new AlgorithmErrorDialog
                (tr("Поиск кратчайших путей алгоритмом Беллмана-Форда невозможен."), this);
        error->show();
        return;
    }
    if (M == nullptr) {
        return;
    }

    if (!graph->hasEdges()) {
        return;
    }

    int n = graph->vertexCount(); // рамер вектора

    // настройка отображения
    widget->setRowCount(1);
    widget->setColumnCount(n);
    widget->setVerticalHeaderItem(0, new QTableWidgetItem
                                  (QString::number(vertexChoiseBox->value())));
    widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int longestStringSize = 0;

    // Инициализация
    QChar *plusInf = new QChar[2];
    QChar *minusInf = new QChar[3];
    minusInf[0]              = QChar('-');
    minusInf[1] = plusInf[0] = QChar(8734);
    minusInf[2] = plusInf[1] = QChar(0);

    for (int i = 0; i < n; ++i) {
        QString nextNumber = nullptr;
        if (*M == INT_MAX) {
            nextNumber = QString(plusInf);
        } else if (*M == INT_MIN) {
            nextNumber = QString(minusInf);
            if (longestStringSize < 3) {
                longestStringSize = 3;
            }
        } else {
            nextNumber = QString::number(*M);
        }
        ++M;
        if (longestStringSize < nextNumber.size()) {
            longestStringSize = nextNumber.size();
        }
        QTableWidgetItem *newItem = new QTableWidgetItem(nextNumber);
        newItem->setTextAlignment(Qt::AlignHCenter);
        widget->setItem(0, i, newItem);
    }

    /* Настройка размера клеточек */
    for (int i = 0; i < n; ++i) {
        widget->setColumnWidth(i, 7 + 6 * longestStringSize);
    }
    widget->setRowHeight  (0, 20);

    delete[] plusInf;
    delete[] minusInf;
}

void SingleSourcePathsForm::changedVertexCount()
{
    vertexChoiseBox->setMaximum(graph->vertexCount());
}

void SingleSourcePathsForm::on_pathSearchButton_clicked()
{
    int vertexIndex = vertexChoiseBox->value(); // Индекс стартовой вершины
    int *vector;                                // Вектор кратчайших путей

    if (algorithm == BellmanFord) {
        vector = graph->shortestPathsByBellmanFord(vertexIndex);
        displayVectorInTable(vector, shortestDistanceVector);
    } else if (algorithm == Dijkstra) {
        vector = graph->shortestPathsByDijkstra(vertexIndex);
        displayVectorInTable(vector, shortestDistanceVector);
    }

    displayVectorInTable(graph->predecessorVector(vertexIndex),
                         pathRenewVector);
}

