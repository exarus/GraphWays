#ifndef ALGORITHMERRORDIALOG_H
#define ALGORITHMERRORDIALOG_H

#include "ui_AlgorithmErrorDialog.h"

class AlgorithmErrorDialog : public QDialog, private Ui::AlgorithmErrorDialog
{
    Q_OBJECT

public:
    explicit AlgorithmErrorDialog(const QString &text, QWidget *parent = 0);
};

#endif // ALGORITHMERRORDIALOG_H
