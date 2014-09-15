#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCommandLinkButton>
#include <QSpinBox>
#include "graphscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSpinBox *getScaleBox() const;
    void setScaleBox(QSpinBox *value);

private:
    Ui::MainWindow *ui;
    GraphScene *scene;
    QSpinBox *edgeVeightBox;
    QCommandLinkButton *shortestPathsButton;
    QSpinBox *scaleBox;
};

#endif // MAINWINDOW_H
