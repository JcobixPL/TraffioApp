/********************************************************************************
** Form generated from reading UI file 'schedule.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULE_H
#define UI_SCHEDULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Schedule
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *driversComboBox;
    QPushButton *exportToPDFButton;
    QSpacerItem *horizontalSpacer;
    QTableWidget *scheduleTable;

    void setupUi(QMainWindow *Schedule)
    {
        if (Schedule->objectName().isEmpty())
            Schedule->setObjectName("Schedule");
        Schedule->resize(1024, 768);
        Schedule->setMinimumSize(QSize(0, 0));
        Schedule->setMaximumSize(QSize(16777214, 16777215));
        centralwidget = new QWidget(Schedule);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        driversComboBox = new QComboBox(centralwidget);
        driversComboBox->setObjectName("driversComboBox");

        horizontalLayout->addWidget(driversComboBox);

        exportToPDFButton = new QPushButton(centralwidget);
        exportToPDFButton->setObjectName("exportToPDFButton");

        horizontalLayout->addWidget(exportToPDFButton);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        scheduleTable = new QTableWidget(centralwidget);
        scheduleTable->setObjectName("scheduleTable");

        verticalLayout_2->addWidget(scheduleTable);

        Schedule->setCentralWidget(centralwidget);

        retranslateUi(Schedule);

        QMetaObject::connectSlotsByName(Schedule);
    } // setupUi

    void retranslateUi(QMainWindow *Schedule)
    {
        Schedule->setWindowTitle(QCoreApplication::translate("Schedule", "MainWindow", nullptr));
        exportToPDFButton->setText(QCoreApplication::translate("Schedule", "PDF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Schedule: public Ui_Schedule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULE_H
