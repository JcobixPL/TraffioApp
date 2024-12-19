#include "buslines.h"
#include "ui_buslines.h"

BusLines::BusLines(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BusLines)
{
    ui->setupUi(this);
}

BusLines::~BusLines()
{
    delete ui;
}


void BusLines::on_addBusLineButton_clicked()
{
    QString lineGroup = ui->textEdit->toPlainText();
    QString lineID = ui->lineIdTextEdit->toPlainText();
    QString startTime = ui->startTimeTimeEdit->time().toString("hh:mm:ss");
    QString endTime = ui->endTimeTimeEdit->time().toString("hh:mm:ss");
    QString drivingTime = ui->drivingTimeTimeEdit->time().toString("hh:mm:ss");
    QString breaksAbove15Min = ui->breaksAbove15MinTimeEdit->time().toString("hh:mm:ss");
    int countBreaksAbove15Min = ui->countBreaksAbove15MinTimeEdit->value();
    QString otherBreaksAndWork = ui->otherBreaksAndWorkTimeEdit->time().toString("hh:mm:ss");
    QString oc = ui->ocTimeEdit->time().toString("hh:mm:ss");
    QString totalWorkTime = ui->totalWorkTimeTimeEdit->time().toString("hh:mm:ss");

    QSqlQuery query;

    // Sprawdź, czy linia już istnieje
    query.prepare("SELECT COUNT(*) FROM buslines WHERE lineid = :id");
    query.bindValue(":id", lineID);
    if (!query.exec()) {
        qDebug() << "SQL Error (SELECT): " << query.lastError().text();
        return;
    }
    query.next(); // Przesunięcie kursora na wynik

    if (query.value(0).toInt() == 0) { // Jeśli linia nie istnieje
        query.prepare("INSERT INTO buslines (lineid, starttime, endtime, drivingtime, breaks15minandlonger, breakscountabove15, otherbreaksandwork, oc, linegroup) "
                      "VALUES (:lineid, :starttime, :endtime, :drivingtime, :breaks15minandlonger, :breakscountabove15, :otherbreaksandwork, :oc, :linegroup)");

        query.bindValue(":lineid", lineID);
        query.bindValue(":starttime", startTime);
        query.bindValue(":endtime", endTime);
        query.bindValue(":drivingtime", drivingTime);
        query.bindValue(":breaks15minandlonger", breaksAbove15Min);
        query.bindValue(":breakscountabove15", countBreaksAbove15Min);
        query.bindValue(":otherbreaksandwork", otherBreaksAndWork);
        query.bindValue(":oc", oc);
        query.bindValue(":linegroup", lineGroup);

        if (!query.exec()) {
            qDebug() << "SQL Error (INSERT): " << query.lastError().text();
            return;
        } else {
            qDebug() << "BusLine added correctly";
        }
    } else {
        qDebug() << "BusLine already exists.";
    }
    this->close();
}
