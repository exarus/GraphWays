/********************************************************************************
** Form generated from reading UI file 'SingleSourcePathsForm.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLESOURCEPATHSFORM_H
#define UI_SINGLESOURCEPATHSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleSourcePathsForm
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *vertexChoiseLabel;
    QSpinBox *vertexChoiseBox;
    QPushButton *pathSearchButton;
    QLabel *algorythmNoteLabel;
    QLabel *distanceLabel_2;
    QTableWidget *shortestDistanceVector;
    QLabel *shortestPathsLabel;
    QTableWidget *pathRenewVector;

    void setupUi(QWidget *SingleSourcePathsForm)
    {
        if (SingleSourcePathsForm->objectName().isEmpty())
            SingleSourcePathsForm->setObjectName(QStringLiteral("SingleSourcePathsForm"));
        SingleSourcePathsForm->resize(640, 226);
        verticalLayout = new QVBoxLayout(SingleSourcePathsForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        vertexChoiseLabel = new QLabel(SingleSourcePathsForm);
        vertexChoiseLabel->setObjectName(QStringLiteral("vertexChoiseLabel"));

        horizontalLayout->addWidget(vertexChoiseLabel);

        vertexChoiseBox = new QSpinBox(SingleSourcePathsForm);
        vertexChoiseBox->setObjectName(QStringLiteral("vertexChoiseBox"));
        vertexChoiseBox->setMinimum(1);

        horizontalLayout->addWidget(vertexChoiseBox);


        formLayout_2->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        pathSearchButton = new QPushButton(SingleSourcePathsForm);
        pathSearchButton->setObjectName(QStringLiteral("pathSearchButton"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, pathSearchButton);


        verticalLayout->addLayout(formLayout_2);

        algorythmNoteLabel = new QLabel(SingleSourcePathsForm);
        algorythmNoteLabel->setObjectName(QStringLiteral("algorythmNoteLabel"));

        verticalLayout->addWidget(algorythmNoteLabel);

        distanceLabel_2 = new QLabel(SingleSourcePathsForm);
        distanceLabel_2->setObjectName(QStringLiteral("distanceLabel_2"));

        verticalLayout->addWidget(distanceLabel_2);

        shortestDistanceVector = new QTableWidget(SingleSourcePathsForm);
        shortestDistanceVector->setObjectName(QStringLiteral("shortestDistanceVector"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(shortestDistanceVector->sizePolicy().hasHeightForWidth());
        shortestDistanceVector->setSizePolicy(sizePolicy);
        shortestDistanceVector->setMaximumSize(QSize(16777215, 40));
        shortestDistanceVector->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(shortestDistanceVector);

        shortestPathsLabel = new QLabel(SingleSourcePathsForm);
        shortestPathsLabel->setObjectName(QStringLiteral("shortestPathsLabel"));

        verticalLayout->addWidget(shortestPathsLabel);

        pathRenewVector = new QTableWidget(SingleSourcePathsForm);
        pathRenewVector->setObjectName(QStringLiteral("pathRenewVector"));
        pathRenewVector->setMaximumSize(QSize(16777215, 40));

        verticalLayout->addWidget(pathRenewVector);

#ifndef QT_NO_SHORTCUT
        vertexChoiseLabel->setBuddy(vertexChoiseBox);
#endif // QT_NO_SHORTCUT

        retranslateUi(SingleSourcePathsForm);

        QMetaObject::connectSlotsByName(SingleSourcePathsForm);
    } // setupUi

    void retranslateUi(QWidget *SingleSourcePathsForm)
    {
        SingleSourcePathsForm->setWindowTitle(QApplication::translate("SingleSourcePathsForm", "\320\232\321\200\320\260\321\202\321\207\320\260\320\271\321\210\320\270\320\265 \320\277\321\203\321\202\320\270 \320\264\320\276 \320\262\320\265\321\200\321\210\320\270\320\275\321\213", 0));
        vertexChoiseLabel->setText(QApplication::translate("SingleSourcePathsForm", "\320\222\321\213\320\261\320\276\321\200 \320\275\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\271 \320\262\320\265\321\200\321\210\320\270\320\275\321\213:", 0));
        pathSearchButton->setText(QApplication::translate("SingleSourcePathsForm", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\277\320\276\320\270\321\201\320\272", 0));
        algorythmNoteLabel->setText(QApplication::translate("SingleSourcePathsForm", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202 \321\200\320\260\320\261\320\276\321\202\321\213 \320\260\320\273\320\263\320\276\321\200\320\270\321\202\320\274\320\260 \320\224\320\265\320\271\320\272\321\201\321\202\321\200\321\213 \320\275\320\265 \320\261\321\203\320\264\320\265\321\202 \320\277\321\200\320\260\320\262\320\270\320\273\321\214\320\275\321\213\320\274, \320\262 \321\201\320\273\321\203\321\207\320\260\320\265 \320\275\320\260\320\273\320\270\321\207\320\270\321\217 \320\276\321\202\321\200\320\270\321\206\320\260\321\202\320\265\320\273\321\214\320\275\321\213\321\205 \321\200\320\265\320\261\320\265\321\200 \320\262 \320\263\321\200\320\260\321\204\320\265.", 0));
        distanceLabel_2->setText(QApplication::translate("SingleSourcePathsForm", "\320\222\320\265\320\272\321\202\320\276\321\200 \321\200\320\260\321\201\321\202\320\276\321\217\320\275\320\270\320\271:", 0));
        shortestPathsLabel->setText(QApplication::translate("SingleSourcePathsForm", "\320\222\320\265\320\272\321\202\320\276\321\200 \320\262\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\273\320\265\320\275\320\270\321\217 \320\277\321\203\321\202\320\265\320\271:", 0));
    } // retranslateUi

};

namespace Ui {
    class SingleSourcePathsForm: public Ui_SingleSourcePathsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLESOURCEPATHSFORM_H
