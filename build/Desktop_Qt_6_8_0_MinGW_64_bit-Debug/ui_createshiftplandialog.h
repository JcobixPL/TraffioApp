/********************************************************************************
** Form generated from reading UI file 'createshiftplandialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATESHIFTPLANDIALOG_H
#define UI_CREATESHIFTPLANDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_createShiftPlanDialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *yearComboBox;
    QComboBox *monthComboBox;

    void setupUi(QDialog *createShiftPlanDialog)
    {
        if (createShiftPlanDialog->objectName().isEmpty())
            createShiftPlanDialog->setObjectName("createShiftPlanDialog");
        createShiftPlanDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(createShiftPlanDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        yearComboBox = new QComboBox(createShiftPlanDialog);
        yearComboBox->setObjectName("yearComboBox");
        yearComboBox->setGeometry(QRect(170, 110, 69, 22));
        monthComboBox = new QComboBox(createShiftPlanDialog);
        monthComboBox->setObjectName("monthComboBox");
        monthComboBox->setGeometry(QRect(150, 150, 111, 22));

        retranslateUi(createShiftPlanDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, createShiftPlanDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, createShiftPlanDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(createShiftPlanDialog);
    } // setupUi

    void retranslateUi(QDialog *createShiftPlanDialog)
    {
        createShiftPlanDialog->setWindowTitle(QCoreApplication::translate("createShiftPlanDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class createShiftPlanDialog: public Ui_createShiftPlanDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATESHIFTPLANDIALOG_H
