#include "createscheduledialog.h"
#include "ui_createscheduledialog.h"

CreateScheduleDialog::CreateScheduleDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateScheduleDialog)
{
    ui->setupUi(this);
    setWindowTitle("PTMS");
    setWindowIcon(QIcon(":/icons/icon.png"));
    initializeComboBox();
}

CreateScheduleDialog::~CreateScheduleDialog()
{
    delete ui;
}

void CreateScheduleDialog::initializeComboBox() {
    QSqlQuery query;
    query.prepare("SELECT month, year FROM shiftplans WHERE status = 'Gotowy' GROUP BY year, month ORDER BY year DESC, month DESC");
    if (!query.exec()) {
        qDebug() << "Query failed: " << query.lastError().text();
        return;
    }

    // Zbieramy wszystkie miesiące i lata, dla których nie ma harmonogramu
    QList<QString> availablePlans;

    while (query.next()) {
        int month = query.value(0).toInt();
        int year = query.value(1).toInt();

        // Sprawdzamy, czy istnieje harmonogram dla tego grafiku
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM schedules WHERE shiftPlanId IN "
                           "(SELECT id FROM shiftplans WHERE month = :month AND year = :year)");
        checkQuery.bindValue(":month", month);
        checkQuery.bindValue(":year", year);
        if (!checkQuery.exec()) {
            qDebug() << "Check query failed: " << checkQuery.lastError().text();
            continue;
        }

        checkQuery.next();
        int count = checkQuery.value(0).toInt();

        // Jeżeli nie ma harmonogramu (count == 0), dodajemy do ComboBox
        if (count == 0) {
            QDate date(year, month, 1);
            QString monthName = date.toString("MMMM yyyy");
            availablePlans.append(monthName);
        }
    }

    // Dodajemy dostępne plany do ComboBox
    ui->shiftPlansComboBox->addItems(availablePlans);

    connect(ui->okButton, &QPushButton::clicked, this, &CreateScheduleDialog::accept);
}


int CreateScheduleDialog::getChosenShiftPlan() const {
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
