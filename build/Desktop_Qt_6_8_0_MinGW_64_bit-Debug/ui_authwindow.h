/********************************************************************************
** Form generated from reading UI file 'authwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHWINDOW_H
#define UI_AUTHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *logInButton;
    QCheckBox *passwordVisibilityCheckBox;

    void setupUi(QMainWindow *AuthWindow)
    {
        if (AuthWindow->objectName().isEmpty())
            AuthWindow->setObjectName("AuthWindow");
        AuthWindow->resize(600, 400);
        centralwidget = new QWidget(AuthWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(600, 400));
        centralwidget->setMaximumSize(QSize(600, 400));
        emailLineEdit = new QLineEdit(centralwidget);
        emailLineEdit->setObjectName("emailLineEdit");
        emailLineEdit->setGeometry(QRect(240, 140, 171, 22));
        passwordLineEdit = new QLineEdit(centralwidget);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(240, 190, 171, 22));
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        logInButton = new QPushButton(centralwidget);
        logInButton->setObjectName("logInButton");
        logInButton->setGeometry(QRect(260, 240, 75, 24));
        passwordVisibilityCheckBox = new QCheckBox(centralwidget);
        passwordVisibilityCheckBox->setObjectName("passwordVisibilityCheckBox");
        passwordVisibilityCheckBox->setGeometry(QRect(430, 190, 91, 20));
        AuthWindow->setCentralWidget(centralwidget);

        retranslateUi(AuthWindow);

        QMetaObject::connectSlotsByName(AuthWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AuthWindow)
    {
        AuthWindow->setWindowTitle(QCoreApplication::translate("AuthWindow", "AuthWindow", nullptr));
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("AuthWindow", "Email", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("AuthWindow", "Has\305\202o", nullptr));
        logInButton->setText(QCoreApplication::translate("AuthWindow", "ZALOGUJ", nullptr));
        passwordVisibilityCheckBox->setText(QCoreApplication::translate("AuthWindow", "Poka\305\274 has\305\202o", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthWindow: public Ui_AuthWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHWINDOW_H
