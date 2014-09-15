#include "AlgorithmErrorDialog.h"

AlgorithmErrorDialog::AlgorithmErrorDialog(const QString &text, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    algorithmLabel->setText(text);
    connect(dialogButtonBox, SIGNAL(rejected()),
            parent, SLOT(close()));
}
