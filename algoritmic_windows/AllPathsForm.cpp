#include "AllPathsForm.h"
#include "ui_AllPathsForm.h"
#include <GraphParts/Graph.h>
#include <QTime>
#include <QDebug>
#include "algorythms.h"

AllPathsForm::AllPathsForm(Graph *graph, Algorithm algorithm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllPathsForm)
{
    int **D0 = graph->distanceMatrix(); // Матриця відстаней
    int **P = nullptr;                  // Матриця відновлення шляхів
    int **D = nullptr;                  // Матриця найкоротших відстаней
    int n = graph->vertexCount();       // Кількість вершин у графі

    // Вимірювання часу затраченого на виконання алгоритму
    QTime t;                            // Таймер
    int ms = 1;                         // Час виконання алгоритму

    // Выбрать алгоритм
    if (algorithm == FloydWarshall) {
        t.start();
        D = shortestPathsByFloyd(D0, n, P);
        ms += t.elapsed();
    } else if (algorithm == Dantzig) {
        t.start();
        D = shortestPathsByDantzig(D0, n, P);
        ms += t.elapsed();
    } else {
        t.start();
        D = shortestPathsByFloyd(D0, n, P);
        ms += t.elapsed();
    }

    ui->setupUi(this);          // Настроює графічний інтерфейс
    ui->timeLCD_3->display(ms); // Відображує час у матриці
    displayMatrixInTable(D,
                         graph->vertexCount(),
                         ui->shortestDistanceTableWidget);
    displayMatrixInTable(P,
                         graph->vertexCount(),
                         ui->predecessorTableWidget);
}

void AllPathsForm::displayMatrixInTable(int **M, int n, QTableWidget *widget)
{
    if (M == nullptr) {
        return;
    }

    // настройка отображения
    widget->setRowCount(n);
    widget->setColumnCount(n);
    widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int longestStringSize = 0;

    // Инициализация
    QChar *plusInf = new QChar[2];
    QChar *minusInf = new QChar[3];
    minusInf[0]              = QChar('-');
    minusInf[1] = plusInf[0] = QChar(8734);
    minusInf[2] = plusInf[1] = QChar(0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            QString nextNumber = nullptr;
            if (**M == INT_MAX) {
                nextNumber = QString(plusInf);
                if (longestStringSize < 2) {
                    longestStringSize = 2;
                }
            } else if (**M == INT_MIN) {
                nextNumber = QString(minusInf);
                if (longestStringSize < 3) {
                    longestStringSize = 3;
                }
            } else {
                nextNumber = QString::number(**M);
            }
            ++*M;
            if (longestStringSize < nextNumber.size()) {
                longestStringSize = nextNumber.size();
            }
            QTableWidgetItem *newItem = new QTableWidgetItem(nextNumber);
            newItem->setTextAlignment(Qt::AlignHCenter);
            widget->setItem(i, j, newItem);
        }
        ++M;
    }

    /* Настройка размера клеточек */
    for (int i = 0; i < n; ++i) {
        widget->setColumnWidth(i, 8 + 6 * longestStringSize);
        widget->setRowHeight  (i, 8 + 6 * longestStringSize);
    }

    delete[] plusInf;
    delete[] minusInf;
}

AllPathsForm::~AllPathsForm()
{
    delete ui;
}
