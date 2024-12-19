#include "createshortenedscheduledialog.h"
#include "ui_createshortenedscheduledialog.h"

CreateShortenedScheduleDialog::CreateShortenedScheduleDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateShortenedScheduleDialog)
{
    ui->setupUi(this);
    setWindowTitle("PTMS");
    setWindowIcon(QIcon(":/icons/icon.png"));
    initializeComboBox();
}

CreateShortenedScheduleDialog::~CreateShortenedScheduleDialog()
{
    delete ui;
}

void CreateShortenedScheduleDialog::initializeComboBox() {
    QSqlQuery query;
    query.prepare(R"(
    SELECT shiftplans.month, shiftplans.year
    FROM shiftplans
    JOIN schedules ON schedules.shiftplanid = shiftplans.id
    WHERE shiftplans.status = 'Gotowy'
    AND schedules.status = 'Gotowy'
    GROUP BY shiftplans.year, shiftplans.month
    ORDER BY shiftplans.year DESC, shiftplans.month DESC)");
    if (!query.exec()) {
        qDebug() << "SQL Error: " << query.lastError().text();
        return;
    }

    QList<QString> availablePlans;

    while (query.next()) {
        int month = query.value(0).toInt();
        int year = query.value(1).toInt();

        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM shortenedschedules WHERE shiftplanid IN (SELECT id FROM shiftplans WHERE month = :month AND year = :year)");
        checkQuery.bindValue(":month", month);
        checkQuery.bindValue(":year", year);
        if (!checkQuery.exec()) {
            qDebug() << "SQL Error: " << checkQuery.lastError().text();
            continue;
        }

        checkQuery.next();
        int count = checkQuery.value(0).toInt();

        if (count == 0) {
            QDate date(year, month, 1);
            QString monthName = date.toString("MMMM yyyy");
            availablePlans.append(monthName);
        }
    }

    ui->shiftPlansComboBox->addItems(availablePlans);

    connect(ui->okButton, &QPushButton::clicked, this, &CreateShortenedScheduleDialog::accept);
}

int CreateShortenedScheduleDialog::getChosenShiftPlan() const {
    QString selectedText = ui->shiftPlansComboBox->currentText();
    QDate date = QDate::fromString(selectedText, "MMMM yyyy");
    if (!date.isValid()) {
        return -1;
    }

    int month = date.month();
    int year = date.year();

    QSqlQuery query;
    query.prepare("SELECT id FROM shiftplans WHERE month = :month AND year = :year");
    query.bindValue(":month", month);
    query.bindValue(":year", year);
    if (!query.exec()) {
        return -1;
    }
    if (query.next()) {
        return query.value(0).toInt();
    }

    return -1;
}
