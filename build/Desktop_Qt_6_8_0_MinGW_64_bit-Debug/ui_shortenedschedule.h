/********************************************************************************
** Form generated from reading UI file 'shortenedschedule.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHORTENEDSCHEDULE_H
#define UI_SHORTENEDSCHEDULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShortenedSchedule
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *shortenedScheduleTable;

    void setupUi(QMainWindow *ShortenedSchedule)
    {
        if (ShortenedSchedule->objectName().isEmpty())
            ShortenedSchedule->setObjectName("ShortenedSchedule");
        ShortenedSchedule->resize(800, 600);
        centralwidget = new QWidget(ShortenedSchedule);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        shortenedScheduleTable = new QTableWidget(centralwidget);
        shortenedScheduleTable->setObjectName("shortenedScheduleTable");

        verticalLayout_2->addWidget(shortenedScheduleTable);

        ShortenedSchedule->setCentralWidget(centralwidget);

        retranslateUi(ShortenedSchedule);

        QMetaObject::connectSlotsByName(ShortenedSchedule);
    } // setupUi

    void retranslateUi(QMainWindow *ShortenedSchedule)
    {
        ShortenedSchedule->setWindowTitle(QCoreApplication::translate("ShortenedSchedule", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShortenedSchedule: public Ui_ShortenedSchedule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHORTENEDSCHEDULE_H
