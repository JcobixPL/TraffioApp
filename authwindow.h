#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include "mainwindow.h"

#include <QMainWindow>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class AuthWindow;
}
QT_END_NAMESPACE

class AuthWindow : public QMainWindow
{
    Q_OBJECT

public:
    AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

private slots:
    void on_logInButton_clicked();

    void on_passwordVisibilityCheckBox_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::AuthWindow *ui;

    void authenticateUser(const QString &email, const QString &password);
};
#endif // AUTHWINDOW_H
