#include "ShortestWaysDialog.h"
#include <algoritmic_windows/AllPathsForm.h>
#include <algoritmic_windows/SingleSourcePathsForm.h>

ShortestWaysDialog::ShortestWaysDialog
            (Graph *graph, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);  // Настраиваем интерфейс
    this->graph = graph;

    /* Настройки размеров */
    resize(100,100);
}

ShortestWaysDialog::~ShortestWaysDialog()
{
}

void ShortestWaysDialog::on_DijkstraButton_clicked()
{
    close();
    SingleSourcePathsForm *f = new SingleSourcePathsForm
            (graph, SingleSourcePathsForm::Dijkstra);
    f->show();
}

void ShortestWaysDialog::on_FloydWarshallButton_clicked()
{
    close();
    AllPathsForm *f = new AllPathsForm
            (graph, AllPathsForm::FloydWarshall);
    f->show();
}

void ShortestWaysDialog::on_BellmanFordButton_clicked()
{
    close();
    SingleSourcePathsForm *f = new SingleSourcePathsForm
            (graph, SingleSourcePathsForm::BellmanFord);
    f->show();
}

void ShortestWaysDialog::on_JohnsonButton_clicked()
{
    close();
    AllPathsForm *f = new AllPathsForm
            (graph, AllPathsForm::Johnsohn);
    f->show();
}

void ShortestWaysDialog::on_planarityButton_clicked()
{
    QLabel *label = new QLabel();
    layout()->addWidget(label);

    if (graph->isPlanar()) {
        label->setText("Граф планарний.");
    } else {
        label->setText("Граф непланарний.");
    }

    QString str = "Кольори для розфарбування: ";

    for (int i = 0; i < graph->vertexCount(); i++) {
        str += QString("\n") + QString::number(i + 1) + QString(": ") +
                QString::number(graph->colors().value(i) + 1);
    }

    QLabel *colors = new QLabel(str);
    layout()->addWidget(colors);
}

void ShortestWaysDialog::on_DantzigButton_clicked()
{
    close();
    AllPathsForm *f = new AllPathsForm
            (graph, AllPathsForm::Dantzig);
    f->show();
}
