/********************************************************************************
** Form generated from reading UI file 'shiftplan.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHIFTPLAN_H
#define UI_SHIFTPLAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShiftPlan
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *exportToPDFButton;
    QPushButton *clearButton;
    QPushButton *saveButton;
    QTableWidget *shiftPlanTable;

    void setupUi(QMainWindow *ShiftPlan)
    {
        if (ShiftPlan->objectName().isEmpty())
            ShiftPlan->setObjectName("ShiftPlan");
        ShiftPlan->resize(1280, 720);
        ShiftPlan->setMinimumSize(QSize(0, 0));
        centralwidget = new QWidget(ShiftPlan);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        exportToPDFButton = new QPushButton(centralwidget);
        exportToPDFButton->setObjectName("exportToPDFButton");

        horizontalLayout->addWidget(exportToPDFButton);

        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName("clearButton");

        horizontalLayout->addWidget(clearButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");

        horizontalLayout->addWidget(saveButton);


        verticalLayout_2->addLayout(horizontalLayout);

        shiftPlanTable = new QTableWidget(centralwidget);
        shiftPlanTable->setObjectName("shiftPlanTable");

        verticalLayout_2->addWidget(shiftPlanTable);

        ShiftPlan->setCentralWidget(centralwidget);

        retranslateUi(ShiftPlan);

        QMetaObject::connectSlotsByName(ShiftPlan);
    } // setupUi

    void retranslateUi(QMainWindow *ShiftPlan)
    {
        ShiftPlan->setWindowTitle(QCoreApplication::translate("ShiftPlan", "MainWindow", nullptr));
        exportToPDFButton->setText(QCoreApplication::translate("ShiftPlan", "PDF", nullptr));
        clearButton->setText(QCoreApplication::translate("ShiftPlan", "WYCZY\305\232\304\206", nullptr));
        saveButton->setText(QCoreApplication::translate("ShiftPlan", "ZAPISZ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShiftPlan: public Ui_ShiftPlan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHIFTPLAN_H
