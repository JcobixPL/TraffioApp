#include "authwindow.h"
#include "ui_authwindow.h"

AuthWindow::AuthWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    connect(ui->emailLineEdit, &QLineEdit::returnPressed, ui->logInButton, &QPushButton::click);
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, ui->logInButton, &QPushButton::click);
    setWindowTitle("Traffio");
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

void AuthWindow::on_logInButton_clicked()
{
    QString email = ui->emailLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    authenticateUser(email, password);
}

void AuthWindow::authenticateUser(const QString &email, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT userid FROM users WHERE email = :email AND password = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if(query.exec()) {
        if(query.next()) {
            qDebug() << "Logged in successfully! UserID: " << query.value(0).toInt();
            this->close();
            MainWindow *w = new MainWindow(query.value(0).toInt(), nullptr);
            w->showMaximized();
            w->show();
        } else {
            qDebug() << "Login failed: No user found";
            QMessageBox::warning(this, "Login failed", "Invalid email or password");
        }
    } else {
        qDebug() << "Query failed: " << query.lastError().text();
    }
}

void AuthWindow::on_passwordVisibilityCheckBox_checkStateChanged(const Qt::CheckState &arg1) {
    if (arg1 == Qt::Checked) {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    } else {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    }
}

