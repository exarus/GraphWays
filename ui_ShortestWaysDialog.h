/********************************************************************************
** Form generated from reading UI file 'ShortestWaysDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHORTESTWAYSDIALOG_H
#define UI_SHORTESTWAYSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ShortestWaysDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *choiseLabel;
    QLabel *label;
    QPushButton *DijkstraButton;
    QPushButton *BellmanFordButton;
    QLabel *label_2;
    QPushButton *FloydWarshallButton;
    QPushButton *DantzigButton;
    QPushButton *JohnsonButton;
    QLabel *choiseLabel_2;
    QPushButton *planarityButton;

    void setupUi(QDialog *ShortestWaysDialog)
    {
        if (ShortestWaysDialog->objectName().isEmpty())
            ShortestWaysDialog->setObjectName(QStringLiteral("ShortestWaysDialog"));
        ShortestWaysDialog->resize(467, 282);
        ShortestWaysDialog->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(ShortestWaysDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        choiseLabel = new QLabel(ShortestWaysDialog);
        choiseLabel->setObjectName(QStringLiteral("choiseLabel"));
        choiseLabel->setMaximumSize(QSize(450, 40));
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        choiseLabel->setFont(font);

        verticalLayout->addWidget(choiseLabel);

        label = new QLabel(ShortestWaysDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        DijkstraButton = new QPushButton(ShortestWaysDialog);
        DijkstraButton->setObjectName(QStringLiteral("DijkstraButton"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DijkstraButton->sizePolicy().hasHeightForWidth());
        DijkstraButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(DijkstraButton);

        BellmanFordButton = new QPushButton(ShortestWaysDialog);
        BellmanFordButton->setObjectName(QStringLiteral("BellmanFordButton"));
        sizePolicy.setHeightForWidth(BellmanFordButton->sizePolicy().hasHeightForWidth());
        BellmanFordButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(BellmanFordButton);

        label_2 = new QLabel(ShortestWaysDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        FloydWarshallButton = new QPushButton(ShortestWaysDialog);
        FloydWarshallButton->setObjectName(QStringLiteral("FloydWarshallButton"));
        sizePolicy.setHeightForWidth(FloydWarshallButton->sizePolicy().hasHeightForWidth());
        FloydWarshallButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(FloydWarshallButton);

        DantzigButton = new QPushButton(ShortestWaysDialog);
        DantzigButton->setObjectName(QStringLiteral("DantzigButton"));

        verticalLayout->addWidget(DantzigButton);

        JohnsonButton = new QPushButton(ShortestWaysDialog);
        JohnsonButton->setObjectName(QStringLiteral("JohnsonButton"));
        sizePolicy.setHeightForWidth(JohnsonButton->sizePolicy().hasHeightForWidth());
        JohnsonButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(JohnsonButton);

        choiseLabel_2 = new QLabel(ShortestWaysDialog);
        choiseLabel_2->setObjectName(QStringLiteral("choiseLabel_2"));
        choiseLabel_2->setMaximumSize(QSize(450, 40));
        choiseLabel_2->setFont(font);

        verticalLayout->addWidget(choiseLabel_2);

        planarityButton = new QPushButton(ShortestWaysDialog);
        planarityButton->setObjectName(QStringLiteral("planarityButton"));

        verticalLayout->addWidget(planarityButton);


        retranslateUi(ShortestWaysDialog);

        QMetaObject::connectSlotsByName(ShortestWaysDialog);
    } // setupUi

    void retranslateUi(QDialog *ShortestWaysDialog)
    {
        ShortestWaysDialog->setWindowTitle(QApplication::translate("ShortestWaysDialog", "\320\237\320\276\320\270\321\201\320\272 \320\272\321\200\320\260\321\202\321\207\320\260\320\271\321\210\320\270\321\205 \320\277\321\203\321\202\320\265\320\271", 0));
        choiseLabel->setText(QApplication::translate("ShortestWaysDialog", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\260\320\273\320\263\320\276\321\200\320\270\321\202\320\274 \320\264\320\273\321\217 \320\277\320\276\320\270\321\201\320\272\320\260 \320\272\321\200\320\260\321\202\321\207\320\260\320\271\321\210\320\265\320\263\320\276 \320\277\321\203\321\202\320\270:", 0));
        label->setText(QApplication::translate("ShortestWaysDialog", "\320\224\320\273\321\217 \320\276\320\264\320\275\320\276\320\271 \320\262\320\265\321\200\321\210\320\270\320\275\321\213-\320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\260:", 0));
        DijkstraButton->setText(QApplication::translate("ShortestWaysDialog", "\320\224\320\265\320\271\320\272\321\201\321\202\321\200\320\270", 0));
        BellmanFordButton->setText(QApplication::translate("ShortestWaysDialog", "\320\221\320\265\320\273\320\273\320\274\320\260\320\275\320\260-\320\244\320\276\321\200\320\264\320\260", 0));
        label_2->setText(QApplication::translate("ShortestWaysDialog", "\320\224\320\273\321\217 \320\262\321\201\320\265\321\205 \320\262\320\265\321\200\321\210\320\270\320\275:", 0));
        FloydWarshallButton->setText(QApplication::translate("ShortestWaysDialog", "\320\244\320\273\320\276\320\271\320\264\320\260-\320\243\320\276\321\200\321\210\320\265\320\273\320\273\320\260", 0));
        DantzigButton->setText(QApplication::translate("ShortestWaysDialog", "\320\224\320\260\320\275\321\206\320\270\320\263\320\260", 0));
        JohnsonButton->setText(QApplication::translate("ShortestWaysDialog", "\320\224\320\266\320\276\320\275\321\201\320\276\320\275\320\260", 0));
        choiseLabel_2->setText(QApplication::translate("ShortestWaysDialog", "\320\224\321\200\321\203\320\263\320\270\320\265 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\217:", 0));
        planarityButton->setText(QApplication::translate("ShortestWaysDialog", "\320\237\321\200\320\276\320\262\320\265\321\200\320\270\321\202\321\214 \320\275\320\260 \320\277\320\273\320\260\320\275\320\260\321\200\320\275\320\276\321\201\321\202\321\214 \320\270 \320\274\320\270\320\275\320\270\320\274\320\260\320\273\321\214\320\275\320\276\320\265 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\206\320\262\320\265\321\202\320\276\320\262 \320\264\320\273\321\217 \321\200\320\260\321\201\320\272\321\200\320\260\321\201\320\272\320\270", 0));
    } // retranslateUi

};

namespace Ui {
    class ShortestWaysDialog: public Ui_ShortestWaysDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHORTESTWAYSDIALOG_H
