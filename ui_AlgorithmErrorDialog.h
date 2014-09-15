/********************************************************************************
** Form generated from reading UI file 'AlgorithmErrorDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGORITHMERRORDIALOG_H
#define UI_ALGORITHMERRORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AlgorithmErrorDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *negativeLoopLabel;
    QLabel *algorithmLabel;
    QDialogButtonBox *dialogButtonBox;

    void setupUi(QDialog *AlgorithmErrorDialog)
    {
        if (AlgorithmErrorDialog->objectName().isEmpty())
            AlgorithmErrorDialog->setObjectName(QStringLiteral("AlgorithmErrorDialog"));
        AlgorithmErrorDialog->resize(598, 119);
        verticalLayout = new QVBoxLayout(AlgorithmErrorDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        negativeLoopLabel = new QLabel(AlgorithmErrorDialog);
        negativeLoopLabel->setObjectName(QStringLiteral("negativeLoopLabel"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        negativeLoopLabel->setFont(font);

        verticalLayout->addWidget(negativeLoopLabel);

        algorithmLabel = new QLabel(AlgorithmErrorDialog);
        algorithmLabel->setObjectName(QStringLiteral("algorithmLabel"));
        QFont font1;
        font1.setPointSize(13);
        font1.setUnderline(true);
        algorithmLabel->setFont(font1);

        verticalLayout->addWidget(algorithmLabel);

        dialogButtonBox = new QDialogButtonBox(AlgorithmErrorDialog);
        dialogButtonBox->setObjectName(QStringLiteral("dialogButtonBox"));
        dialogButtonBox->setOrientation(Qt::Horizontal);
        dialogButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(dialogButtonBox);


        retranslateUi(AlgorithmErrorDialog);
        QObject::connect(dialogButtonBox, SIGNAL(accepted()), AlgorithmErrorDialog, SLOT(accept()));
        QObject::connect(dialogButtonBox, SIGNAL(rejected()), AlgorithmErrorDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AlgorithmErrorDialog);
    } // setupUi

    void retranslateUi(QDialog *AlgorithmErrorDialog)
    {
        AlgorithmErrorDialog->setWindowTitle(QApplication::translate("AlgorithmErrorDialog", "Dialog", 0));
        negativeLoopLabel->setText(QApplication::translate("AlgorithmErrorDialog", "\320\223\321\200\320\260\321\204 \321\201\320\276\320\264\320\265\321\200\320\266\320\270\321\202 \320\276\321\202\321\200\320\270\321\206\320\260\321\202\320\265\320\273\321\214\320\275\321\213\320\265 \321\206\320\270\320\272\320\273\321\213!", 0));
        algorithmLabel->setText(QApplication::translate("AlgorithmErrorDialog", "\320\237\320\276\320\270\321\201\320\272 \320\272\321\200\320\260\321\202\321\207\320\260\320\271\321\210\320\270\321\205 \320\277\321\203\321\202\320\265\320\271 \320\260\320\273\320\263\320\276\321\200\320\270\321\202\320\274\320\276\320\274 \320\221\320\265\320\273\320\273\320\274\320\260\320\275\320\260-\320\244\320\276\321\200\320\264\320\260 \320\275\320\265\320\262\320\276\320\267\320\274\320\276\320\266\320\265\320\275.", 0));
    } // retranslateUi

};

namespace Ui {
    class AlgorithmErrorDialog: public Ui_AlgorithmErrorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGORITHMERRORDIALOG_H
