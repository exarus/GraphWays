/********************************************************************************
** Form generated from reading UI file 'AllPathsForm.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALLPATHSFORM_H
#define UI_ALLPATHSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AllPathsForm
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QLabel *infDistanceLabel_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *timeLabel_5;
    QLCDNumber *timeLCD_3;
    QLabel *timeLabel_6;
    QTableWidget *predecessorTableWidget;
    QTableWidget *shortestDistanceTableWidget;
    QLabel *predecessorLabel;
    QLabel *shortestDistanceLabel;

    void setupUi(QWidget *AllPathsForm)
    {
        if (AllPathsForm->objectName().isEmpty())
            AllPathsForm->setObjectName(QStringLiteral("AllPathsForm"));
        AllPathsForm->resize(712, 414);
        gridLayout_4 = new QGridLayout(AllPathsForm);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        infDistanceLabel_3 = new QLabel(AllPathsForm);
        infDistanceLabel_3->setObjectName(QStringLiteral("infDistanceLabel_3"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(infDistanceLabel_3->sizePolicy().hasHeightForWidth());
        infDistanceLabel_3->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(infDistanceLabel_3, 6, 0, 1, 3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        timeLabel_5 = new QLabel(AllPathsForm);
        timeLabel_5->setObjectName(QStringLiteral("timeLabel_5"));
        sizePolicy.setHeightForWidth(timeLabel_5->sizePolicy().hasHeightForWidth());
        timeLabel_5->setSizePolicy(sizePolicy);
        timeLabel_5->setMinimumSize(QSize(205, 0));
        timeLabel_5->setMaximumSize(QSize(205, 16777215));

        horizontalLayout_3->addWidget(timeLabel_5);

        timeLCD_3 = new QLCDNumber(AllPathsForm);
        timeLCD_3->setObjectName(QStringLiteral("timeLCD_3"));
        timeLCD_3->setMinimumSize(QSize(80, 0));
        timeLCD_3->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(timeLCD_3);

        timeLabel_6 = new QLabel(AllPathsForm);
        timeLabel_6->setObjectName(QStringLiteral("timeLabel_6"));
        sizePolicy.setHeightForWidth(timeLabel_6->sizePolicy().hasHeightForWidth());
        timeLabel_6->setSizePolicy(sizePolicy);
        timeLabel_6->setMinimumSize(QSize(73, 0));
        timeLabel_6->setMaximumSize(QSize(68, 16777215));

        horizontalLayout_3->addWidget(timeLabel_6);


        gridLayout_3->addLayout(horizontalLayout_3, 4, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 2, 1, 1, 2);

        predecessorTableWidget = new QTableWidget(AllPathsForm);
        predecessorTableWidget->setObjectName(QStringLiteral("predecessorTableWidget"));

        gridLayout_4->addWidget(predecessorTableWidget, 1, 2, 1, 1);

        shortestDistanceTableWidget = new QTableWidget(AllPathsForm);
        shortestDistanceTableWidget->setObjectName(QStringLiteral("shortestDistanceTableWidget"));

        gridLayout_4->addWidget(shortestDistanceTableWidget, 1, 1, 1, 1);

        predecessorLabel = new QLabel(AllPathsForm);
        predecessorLabel->setObjectName(QStringLiteral("predecessorLabel"));

        gridLayout_4->addWidget(predecessorLabel, 0, 2, 1, 1);

        shortestDistanceLabel = new QLabel(AllPathsForm);
        shortestDistanceLabel->setObjectName(QStringLiteral("shortestDistanceLabel"));

        gridLayout_4->addWidget(shortestDistanceLabel, 0, 1, 1, 1);


        retranslateUi(AllPathsForm);

        QMetaObject::connectSlotsByName(AllPathsForm);
    } // setupUi

    void retranslateUi(QWidget *AllPathsForm)
    {
        AllPathsForm->setWindowTitle(QApplication::translate("AllPathsForm", "\320\232\321\200\320\260\321\202\321\207\320\260\320\271\321\210\320\270\320\265 \321\200\320\260\321\201\321\202\320\276\321\217\320\275\320\270\321\217 \320\262 \320\263\321\200\320\260\321\204\320\265", 0));
        infDistanceLabel_3->setText(QApplication::translate("AllPathsForm", "\320\240\320\260\321\201\321\202\320\276\321\217\320\275\320\270\321\217 \320\261\320\276\320\273\320\265\320\265 2 147 483 647 \320\276\321\202\320\274\320\265\321\207\320\265\320\275\321\213 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\274 \342\210\236.", 0));
        timeLabel_5->setText(QApplication::translate("AllPathsForm", "\320\222\321\200\320\265\320\274\321\217 \321\200\320\276\320\261\320\276\321\202\321\213 \320\260\320\273\320\263\320\276\321\200\320\270\321\202\320\274\320\260 \320\267\320\260\320\275\321\217\320\273\320\276 \320\274\320\265\320\275\320\265\320\265 ", 0));
        timeLabel_6->setText(QApplication::translate("AllPathsForm", " \320\274\320\270\320\273\320\270\321\201\320\265\320\272\321\203\320\275\320\264.", 0));
        predecessorLabel->setText(QApplication::translate("AllPathsForm", "\320\234\320\260\321\202\321\200\320\270\321\206\320\260 \320\277\321\200\320\265\320\264\321\213\320\264\321\203\321\211\320\270\321\205 \320\262\320\265\321\200\321\210\320\270\320\275 \320\262 \320\263\321\200\320\260\321\204\320\265:", 0));
        shortestDistanceLabel->setText(QApplication::translate("AllPathsForm", "\320\234\320\260\321\202\321\200\320\270\321\206\320\260 \320\272\321\200\320\260\321\202\321\207\320\260\320\271\321\210\320\270\321\205 \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\320\271 \320\262 \320\263\321\200\320\260\321\204\320\265:", 0));
    } // retranslateUi

};

namespace Ui {
    class AllPathsForm: public Ui_AllPathsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALLPATHSFORM_H
