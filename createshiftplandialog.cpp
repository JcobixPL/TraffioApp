#include "createshiftplandialog.h"
#include "ui_createshiftplandialog.h"

#include <QDate>

createShiftPlanDialog::createShiftPlanDialog(int userid, QWidget *parent)
    : QDialog(parent), ui(new Ui::createShiftPlanDialog),
    userID(userid)
{
    ui->setupUi(this);
    initializeComboBoxes();
}

createShiftPlanDialog::~createShiftPlanDialog()
{
    delete ui;
}

void createShiftPlanDialog::initializeComboBoxes() {
    months = {
        "Styczeń", "Luty", "Marzec", "Kwiecień", "Maj", "Czerwiec",
        "Lipiec", "Sierpień", "Wrzesień", "Październik", "Listopad", "Grudzień"
    };

    for (int i = 0; i < months.size(); ++i) {
        ui->monthComboBox->addItem(months[i], i + 1);
    }

    int currentYear = QDate::currentDate().year();
    ui->yearComboBox->addItem(QString::number(currentYear));
    ui->yearComboBox->addItem(QString::number(currentYear + 1));

    ui->monthComboBox->setCurrentIndex(QDate::currentDate().month() - 1);
    ui->yearComboBox->setCurrentText(QString::number(currentYear));
}

void createShiftPlanDialog::on_buttonBox_accepted() {
    int year = ui->yearComboBox->currentText().toInt();
    int month = ui->monthComboBox->currentData().toInt(); // Pobranie indeksu (1-12)
    QDateTime currentDate = QDateTime::currentDateTime();

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM shiftplans WHERE year = :year AND month = :month AND userid = :id");
    checkQuery.bindValue(":year", year);
    checkQuery.bindValue(":month", month);
    checkQuery.bindValue(":id", userID);

    if (checkQuery.exec() && checkQuery.next()) {
        int count = checkQuery.value(0).toInt();
        if (count > 0) {
            return;
        }
    } else {
        qDebug() << "Error during checking existing shift plan: " << checkQuery.lastError().text();
        return;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO shiftplans (year, month, modified_date, modified_by, userid) VALUES (:year, :month, :date, :id, :id)");
    insertQuery.bindValue(":year", year);
    insertQuery.bindValue(":month", month);
    insertQuery.bindValue(":date", currentDate);
    insertQuery.bindValue(":id", userID);

    if (insertQuery.exec()) {
        qDebug() << "Shift plan has been saved to database";
    } else {
        qDebug() << "Error during saving new shift plan: " << insertQuery.lastError().text();
    }
}
