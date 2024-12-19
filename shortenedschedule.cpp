#include "shortenedschedule.h"
#include "ui_shortenedschedule.h"

ShortenedSchedule::ShortenedSchedule(int shortenedScheduleID, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShortenedSchedule)
    , shortenedScheduleID(shortenedScheduleID)
{
    ui->setupUi(this);
    setupUI();
}

ShortenedSchedule::~ShortenedSchedule()
{
    delete ui;
}

void ShortenedSchedule::setupUI() {
    setWindowTitle("Traffio - Schedule");
    setWindowIcon(QIcon(":/icons/icon.png"));
    ui->shortenedScheduleTable->horizontalHeader()->setVisible(false);
    ui->shortenedScheduleTable->verticalHeader()->setVisible(false);

    // POBIERANIE LISTY KIEROWCÓW Z BAZY DANYCH
    QSqlQuery query;
    query.prepare("SELECT name, surname FROM drivers");
    if (query.exec()) {
        QList<QPair<QString, QString>> drivers; // Lista imion i nazwisk kierowców
        while (query.next()) {
            QString firstName = query.value(0).toString();
            QString lastName = query.value(1).toString();
            drivers.append(qMakePair(firstName, lastName));
        }

        int numberOfDrivers = drivers.size();
        int rowCount = numberOfDrivers * 6 + (2 * numberOfDrivers - 1);

        // OBLICZENIE LICZBY DNI W DANYM MIESIĄCU
        QDate currentDate = QDate::currentDate();
        int daysInMonth = currentDate.daysInMonth();

        // USTAWIENIE LICZBY WIERSZY I KOLUMN W TABELI
        ui->shortenedScheduleTable->setRowCount(rowCount);
        ui->shortenedScheduleTable->setColumnCount(daysInMonth + 2); // +2: 1 dodatkowa kolumna na imię/nazwisko + kolumna dni

        // WYPEŁNIANIE TABELI
        int currentRow = 0;

        for (int driver = 0; driver < numberOfDrivers; ++driver) {
            QString firstName = drivers[driver].first;
            QString lastName = drivers[driver].second;

            // Wypełnianie nagłówka "DATA" w pierwszej kolumnie
            ui->shortenedScheduleTable->setItem(currentRow, 0, new QTableWidgetItem(lastName)); // Nazwisko w 1 kolumnie
            ui->shortenedScheduleTable->setItem(currentRow, 1, new QTableWidgetItem("DATA"));
            for (int col = 2; col <= daysInMonth + 1; ++col) {
                QString date = QString("%1.%2")
                .arg(col - 1, 2, 10, QChar('0')) // Numer dnia
                    .arg(currentDate.month(), 2, 10, QChar('0')); // Miesiąc
                ui->shortenedScheduleTable->setItem(currentRow, col, new QTableWidgetItem(date));
            }
            currentRow++; // Przejście do wiersza DZIEŃ TYG.

            // Wypełnianie nagłówka "DZIEŃ TYG." w pierwszej kolumnie
            ui->shortenedScheduleTable->setItem(currentRow, 0, new QTableWidgetItem(firstName)); // Imię w 1 kolumnie
            ui->shortenedScheduleTable->setItem(currentRow, 1, new QTableWidgetItem("DZIEŃ TYG."));
            for (int col = 2; col <= daysInMonth + 1; ++col) {
                QDate date(currentDate.year(), currentDate.month(), col - 1);
                QString dayOfWeek;
                switch (date.dayOfWeek()) {
                case 1: dayOfWeek = "PON"; break;
                case 2: dayOfWeek = "WT"; break;
                case 3: dayOfWeek = "ŚR"; break;
                case 4: dayOfWeek = "CZW"; break;
                case 5: dayOfWeek = "PT"; break;
                case 6: dayOfWeek = "SOB"; break;
                case 7: dayOfWeek = "ND"; break;
                }
                ui->shortenedScheduleTable->setItem(currentRow, col, new QTableWidgetItem(dayOfWeek));
            }
            currentRow++; // Przejście do wiersza LINIA

            // Wypełnianie wierszy LINIA, ROZP.PRACY, ZAKOŃ.PRACY, CZAS PRACY
            ui->shortenedScheduleTable->setItem(currentRow++, 1, new QTableWidgetItem("LINIA"));
            ui->shortenedScheduleTable->setItem(currentRow++, 1, new QTableWidgetItem("ROZP.PRACY"));
            ui->shortenedScheduleTable->setItem(currentRow++, 1, new QTableWidgetItem("ZAKOŃ.PRACY"));
            ui->shortenedScheduleTable->setItem(currentRow++, 1, new QTableWidgetItem("CZAS PRACY"));

            // Dodanie wierszy pustych
            if (driver == numberOfDrivers - 1) {
                ui->shortenedScheduleTable->setItem(currentRow++, 1, new QTableWidgetItem(""));
            } else {
                ui->shortenedScheduleTable->setItem(currentRow++, 1, new QTableWidgetItem(""));
                ui->shortenedScheduleTable->setItem(currentRow++, 1, new QTableWidgetItem(""));
            }
        }
    }
}
