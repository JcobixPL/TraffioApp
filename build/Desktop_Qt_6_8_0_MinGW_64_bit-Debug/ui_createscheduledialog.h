/********************************************************************************
** Form generated from reading UI file 'createscheduledialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATESCHEDULEDIALOG_H
#define UI_CREATESCHEDULEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateScheduleDialog
{
public:
    QComboBox *shiftPlansComboBox;
    QPushButton *okButton;

    void setupUi(QDialog *CreateScheduleDialog)
    {
        if (CreateScheduleDialog->objectName().isEmpty())
            CreateScheduleDialog->setObjectName("CreateScheduleDialog");
        CreateScheduleDialog->resize(400, 300);
        shiftPlansComboBox = new QComboBox(CreateScheduleDialog);
        shiftPlansComboBox->setObjectName("shiftPlansComboBox");
        shiftPlansComboBox->setGeometry(QRect(160, 140, 161, 22));
        okButton = new QPushButton(CreateScheduleDialog);
        okButton->setObjectName("okButton");
        okButton->setGeometry(QRect(230, 250, 75, 24));

        retranslateUi(CreateScheduleDialog);

        QMetaObject::connectSlotsByName(CreateScheduleDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateScheduleDialog)
    {
        CreateScheduleDialog->setWindowTitle(QCoreApplication::translate("CreateScheduleDialog", "Dialog", nullptr));
        okButton->setText(QCoreApplication::translate("CreateScheduleDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateScheduleDialog: public Ui_CreateScheduleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATESCHEDULEDIALOG_H
