/********************************************************************************
** Form generated from reading UI file 'createshortenedscheduledialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATESHORTENEDSCHEDULEDIALOG_H
#define UI_CREATESHORTENEDSCHEDULEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateShortenedScheduleDialog
{
public:
    QComboBox *shiftPlansComboBox;
    QPushButton *okButton;

    void setupUi(QDialog *CreateShortenedScheduleDialog)
    {
        if (CreateShortenedScheduleDialog->objectName().isEmpty())
            CreateShortenedScheduleDialog->setObjectName("CreateShortenedScheduleDialog");
        CreateShortenedScheduleDialog->resize(400, 300);
        shiftPlansComboBox = new QComboBox(CreateShortenedScheduleDialog);
        shiftPlansComboBox->setObjectName("shiftPlansComboBox");
        shiftPlansComboBox->setGeometry(QRect(150, 90, 221, 22));
        okButton = new QPushButton(CreateShortenedScheduleDialog);
        okButton->setObjectName("okButton");
        okButton->setGeometry(QRect(190, 190, 75, 24));

        retranslateUi(CreateShortenedScheduleDialog);

        QMetaObject::connectSlotsByName(CreateShortenedScheduleDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateShortenedScheduleDialog)
    {
        CreateShortenedScheduleDialog->setWindowTitle(QCoreApplication::translate("CreateShortenedScheduleDialog", "Dialog", nullptr));
        okButton->setText(QCoreApplication::translate("CreateShortenedScheduleDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateShortenedScheduleDialog: public Ui_CreateShortenedScheduleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATESHORTENEDSCHEDULEDIALOG_H
