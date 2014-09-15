#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QLabel>
#include <GlobalSettings.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new GraphScene(0, 0, ui->graphicsView->height(),
                           ui->graphicsView->height(), ui->graphicsView);

    /* Настройка окна весов ребер */
    edgeVeightBox = new QSpinBox(this);
    edgeVeightBox->setMinimum(INT_MIN + 1);
    edgeVeightBox->setMaximum(INT_MAX - 1);
    edgeVeightBox->setValue(GlobalSettings::getEdgeVeight());
    connect(edgeVeightBox, SIGNAL(valueChanged(int)),
            scene->getGraph(), SLOT(newEdgesVeight(int)));

    /* Настройка кнопки поиска кратчайших путей */
    shortestPathsButton = new QCommandLinkButton(
                tr("Поиск кратчайших путей"), this);
    connect(shortestPathsButton, SIGNAL(clicked()),
            scene->getGraph(), SLOT(shortestWaysWindow()));
    connect(ui->shortestPathsAction, SIGNAL(triggered()),
            scene->getGraph(), SLOT(shortestWaysWindow()));

    /* Настройка окна масштабирования */
    scaleBox = new QSpinBox(this);
    scaleBox->setMinimum(1);
    scaleBox->setMaximum(INT_MAX);
    scaleBox->setValue(100);
    connect(scaleBox, SIGNAL(editingFinished()),
            scene, SLOT(setScalePercentFromBox()));

    /* Настройка отображения графа */

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    /* Настройка главного тулбара */
    ui->mainToolBar->addWidget(new QLabel(tr("Масштаб ")));
    ui->mainToolBar->addWidget(scaleBox);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(new QLabel(tr("Вес новых ребер ")));
    ui->mainToolBar->addWidget(edgeVeightBox);
    ui->mainToolBar->addWidget(shortestPathsButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QSpinBox *MainWindow::getScaleBox() const
{
    return scaleBox;
}

void MainWindow::setScaleBox(QSpinBox *value)
{
    scaleBox = value;
}

