#include "authwindow.h"

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/Resources/Icons/icon.png"));
    a.setApplicationName("Traffio");

    QSqlDatabase database = QSqlDatabase::addDatabase("QPSQL");
    database.setHostName("localhost");
    database.setDatabaseName("PTMSDatabase");
    database.setUserName("postgres");
    database.setPassword("postgres");
    database.setPort(5432);

    if (!database.open()) {
        qDebug() << "Failed to connect to database:" << database.lastError().text();
        QMessageBox::critical(nullptr, "Database Connection Error", "Could not connect to the PostgreSQL database.");
        return false;
    } else {
        qDebug() << "Connected to database successfully!";
    }

    AuthWindow w;
    w.setWindowTitle("Traffio - Logowanie");
    w.show();
    return a.exec();
}
