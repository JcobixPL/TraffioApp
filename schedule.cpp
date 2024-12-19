#include "schedule.h"
#include "ui_schedule.h"

Schedule::Schedule(int scheduleID, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Schedule)
    , scheduleId(scheduleID)
{
    ui->setupUi(this);
    setupUI();
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    // Ustawienie okna na tryb pełnoekranowy
    showMaximized();

    // Zablokowanie zmiany rozmiaru okna (można tylko przełączyć do pełnoekranowego)
    setFixedSize(this->size());
}

Schedule::~Schedule()
{
    delete ui;
}

void Schedule::setupUI() {
    setWindowTitle("Traffio - Schedule");
    setWindowIcon(QIcon(":/icons/icon.png"));
    ui->scheduleTable->horizontalHeader()->setVisible(false);
    ui->scheduleTable->verticalHeader()->setVisible(false);

    QSqlQuery query;
    query.prepare("SELECT driverid, name, surname FROM drivers");
    if (query.exec()) {
        ui->driversComboBox->clear();
        while (query.next()) {
            QString id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString surname = query.value(2).toString();

            QString driver = id + ": " + surname + " " + name;

            ui->driversComboBox->addItem(driver);
        }
    } else {
        qDebug() << "SQL Error: " << query.lastError().text();
    }


    setupScheduleTable();
    ui->scheduleTable->setRowHeight(5, 40);
    ui->scheduleTable->setRowHeight(7, 80);

    connect(ui->driversComboBox, &QComboBox::currentIndexChanged, this, &Schedule::setupScheduleTable);
}

void Schedule::setupScheduleTable() {
    getDriverID();
    // Włącz zawijanie tekstu w całej tabeli
    ui->scheduleTable->setWordWrap(true);

    // Ustawienia dla poszczególnych elementów
    auto setWrappingForCell = [](QTableWidgetItem *item) {
        item->setTextAlignment(Qt::AlignCenter); // Wyrównanie tekstu na środku
        item->setFlags(item->flags() | Qt::ItemIsSelectable); // Pozwala na wybór komórki
        item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter); // Wyśrodkowanie tekstu
    };

    // Ustawiamy liczbę kolumn i wierszy
    ui->scheduleTable->setRowCount(8);  // 8 wierszy
    ui->scheduleTable->setColumnCount(12);  // 12 kolumn


    // Skalowanie komórek do zawartości
    ui->scheduleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Wiersz 1: Tytuł, komórki scalone
    QSqlQuery getDataQuery;
    getDataQuery.prepare("SELECT shiftplanid FROM schedules WHERE id = :id");
    getDataQuery.bindValue(":id", scheduleId);
    if(getDataQuery.exec()) {
        if(getDataQuery.next()) {
            int shiftPlanId = getDataQuery.value(0).toInt();

            // Pobierz year i month
            QSqlQuery getMonthYearQuery;
            getMonthYearQuery.prepare("SELECT year, month FROM shiftplans WHERE id = :id");
            getMonthYearQuery.bindValue(":id", shiftPlanId);
            if(getMonthYearQuery.exec()) {
                if(getMonthYearQuery.next()) {
                    // Pobierz year jako QString
                    QString year = QString::number(getMonthYearQuery.value(0).toInt());

                    // Pobierz month jako nazwę miesiąca
                    int monthNumber = getMonthYearQuery.value(1).toInt();
                    QMap<int, QString> monthMap;
                    monthMap[1] = "Styczeń";
                    monthMap[2] = "Luty";
                    monthMap[3] = "Marzec";
                    monthMap[4] = "Kwiecień";
                    monthMap[5] = "Maj";
                    monthMap[6] = "Czerwiec";
                    monthMap[7] = "Lipiec";
                    monthMap[8] = "Sierpień";
                    monthMap[9] = "Wrzesień";
                    monthMap[10] = "Październik";
                    monthMap[11] = "Listopad";
                    monthMap[12] = "Grudzień";

                    QString month = monthMap.value(monthNumber, "Nieznany miesiąc");

                    // Ustawienie tytułu w tabeli
                    QTableWidgetItem *titleItem = new QTableWidgetItem("Harmonogram pracy kierowcy na miesiąc " + month + " " + year);
                    titleItem->setTextAlignment(Qt::AlignCenter);
                    titleItem->setFont(QFont("Arial", 10, QFont::Bold));
                    ui->scheduleTable->setItem(0, 0, titleItem);
                    ui->scheduleTable->setSpan(0, 0, 1, 12); // Scal wszystkie komórki w pierwszym wierszu
                }
            } else {
                qDebug() << "Błąd zapytania SQL" << getMonthYearQuery.lastError();
            }
        }
    } else {
        qDebug() << "Błąd zapytania SQL" << getDataQuery.lastError();
    }


    // Wiersz 2: Informacja o firmie, komórki scalone
    QTableWidgetItem *companyItem = new QTableWidgetItem("Przedsiębiorstwo Wodociągów i Kanalizacji w Jarosławiu Spółka z o.o. - Dział Komunikacji Miejskiej");
    companyItem->setTextAlignment(Qt::AlignCenter);
    companyItem->setFont(QFont("Arial", 10, QFont::Bold));
    ui->scheduleTable->setItem(1, 0, companyItem);
    ui->scheduleTable->setSpan(1, 0, 1, 12); // Scal wszystkie komórki w drugim wierszu

    // Wiersz 3: Pusty wiersz, komórki scalone
    QTableWidgetItem *emptyItem = new QTableWidgetItem("");
    ui->scheduleTable->setItem(2, 0, emptyItem);
    ui->scheduleTable->setSpan(2, 0, 1, 12); // Scal wszystkie kolumny w wierszu 3

    // Wiersz 4: Nazwisko, imię, nr służbowy, komórki scalone
    QSqlQuery getQuery;
    getQuery.prepare("SELECT name, surname FROM drivers WHERE driverid = :id");
    getQuery.bindValue(":id", getDriverID());
    if(getQuery.exec()) {
        if(getQuery.next()) {
            QString name = getQuery.value(0).toString().toUpper();
            QString surname = getQuery.value(1).toString().toUpper();
            QString id = QString::number(getDriverID());
            QTableWidgetItem *nameItem = new QTableWidgetItem(surname + " " + name + " NR. SŁUŻBOWY " + id);
            nameItem->setTextAlignment(Qt::AlignCenter);
            nameItem->setFont(QFont("Arial", 10, QFont::Bold));
            ui->scheduleTable->setItem(3, 0, nameItem);
            ui->scheduleTable->setSpan(3, 0, 1, 12); // Scal wszystkie komórki w czwartym wierszu
        }
    } else {
        qDebug() << "Błąd zapytania SQL: " << getQuery.lastError();
    }

    // Wiersz 5: Nagłówki tabeli (Okres, Norma, itd.)
    QStringList headers = {"OKRES", "NORMA", "PRACA", "URLOP", "CZAS ŁĄCZNY", "", "MIEJSCE POSTOJU POJAZDU", "", "", "", "", ""};
    for (int i = 0; i < 12; ++i) {
        QTableWidgetItem *headerItem = new QTableWidgetItem(headers[i]);
        headerItem->setTextAlignment(Qt::AlignCenter);
        headerItem->setFont(QFont("Arial", 10, QFont::Bold));
        ui->scheduleTable->setItem(4, i, headerItem);
    }

    // Scalanie kolumn w wierszu 5
    ui->scheduleTable->setSpan(4, 4, 1, 2); // Scal kolumny 5 i 6 ("CZAS ŁĄCZNY")
    ui->scheduleTable->setSpan(4, 6, 1, 6); // Scal kolumny 7-12 ("MIEJSCE POSTOJU POJAZDU")

    int year;
    int month;
    int shiftPlanID;

    QSqlQuery query;
    query.prepare("SELECT shiftplanid FROM schedules WHERE id = :id");
    query.bindValue(":id", scheduleId);
    if(query.exec()){
        if(query.next()) {
            shiftPlanID = query.value(0).toInt();
        }
    }

    query.prepare("SELECT year, month FROM shiftplans WHERE id = :id");
    query.bindValue(":id", shiftPlanID);
    if(query.exec()){
        if(query.next()) {
            year = query.value(0).toInt();
            month = query.value(1).toInt();
        }
    }




    QDate firstDayOfMonth(year, month, 1);
    QDate lastDayOfMonth(year, month, firstDayOfMonth.daysInMonth());

    QString dateRange = firstDayOfMonth.toString("dd.MM.yyyy") + " - " + lastDayOfMonth.toString("dd.MM.yyyy");

    // Wiersz 6: Przykładowe dane z zakresem dni
    QStringList exampleData = {dateRange, "00:00", "0:00", "00:00", "0:00", "", "BAZA PWiK-DKM JAROSŁAW UL.ZAMKOWA 1", "", "", "", "", ""};
    for (int i = 0; i < 12; ++i) {
        QTableWidgetItem *exampleItem = new QTableWidgetItem(exampleData[i]);
        exampleItem->setFont(QFont("Arial", 10, QFont::Bold));
        ui->scheduleTable->setItem(5, i, exampleItem);
    }

    query.prepare("SELECT hours FROM worktime WHERE year = :year AND month = :month");
    query.bindValue(":year", year);
    query.bindValue(":month", month);

    // Wykonaj zapytanie
    if (query.exec() && query.next()) {
        QString hours = query.value(0).toString(); // Pobierz wartość 'hours' z bazy
        qDebug() << hours;

        // Sprawdź, czy udało się pobrać godzinę
        if (!hours.isEmpty()) {
            // Podzielamy godzinę na części (godziny, minuty, sekundy)
            QStringList timeParts = hours.split(":");
            if (timeParts.size() >= 2) {
                // Tworzymy nowy ciąg w formacie hh:mm (pomijamy sekundy)
                QString formattedTime = timeParts[0] + ":" + timeParts[1];

                // Zamień wartość w komórce wiersza 6, kolumna 1 (NORMA) na sformatowany czas
                QTableWidgetItem *normaItem = new QTableWidgetItem(formattedTime);
                normaItem->setFont(QFont("Arial", 10, QFont::Bold));
                normaItem->setTextAlignment(Qt::AlignCenter);
                ui->scheduleTable->setItem(5, 1, normaItem); // Ustawienie w odpowiedniej komórce
            }
        }
    } else {
        qDebug() << "Błąd zapytania: " << query.lastError().text();
    }



    // Scalanie kolumn w wierszu 6
    ui->scheduleTable->setSpan(5, 4, 1, 2); // Scal kolumny 5 i 6 ("CZAS ŁĄCZNY")
    ui->scheduleTable->setSpan(5, 6, 1, 6); // Scal kolumny 7-12 ("MIEJSCE POSTOJU POJAZDU")

    QTableWidgetItem *baseLocationItem = ui->scheduleTable->item(5, 6); // Komórka z tekstem "BAZA PWiK-DKM JAROSŁAW UL.ZAMKOWA 1"
    baseLocationItem->setTextAlignment(Qt::AlignCenter); // Wyśrodkowanie tekstu w komórce
    baseLocationItem->setFont(QFont("Arial", 10, QFont::Bold));
    // Wiersz 7: Składowe czasu pracy, podzielone na 2 grupy po 6 scalonych kolumn, puste
    QTableWidgetItem *emptyGroup1 = new QTableWidgetItem("");
    emptyGroup1->setTextAlignment(Qt::AlignCenter);
    emptyGroup1->setFont(QFont("Arial", 10, QFont::Bold));
    ui->scheduleTable->setItem(6, 0, emptyGroup1);
    ui->scheduleTable->setSpan(6, 0, 1, 6); // Scal kolumny 0-5

    QTableWidgetItem *emptyGroup2 = new QTableWidgetItem("SKŁADOWE CZASU PRACY : CZAS PROWADZENIA,PRZERWY,INNA PRACA,OC");
    emptyGroup2->setTextAlignment(Qt::AlignCenter);
    ui->scheduleTable->setItem(6, 6, emptyGroup2);
    ui->scheduleTable->setSpan(6, 6, 1, 6); // Scal kolumny 6-11


    // Wiersz 8: Nagłówki dla dni pracy
    QStringList workHeaders = {"DATA", "DZIEŃ", "LINIA", "WOLNE LUB URLOP", "GODZ. ROZP. PRACY",
                               "GODZ. ZAKOŃ. PRACY", "CZAS PROWADZENIA POJAZDU",
                               "PRZERWY W PROWADZENIU 15 MINUT I DŁUŻSZE", "ILOŚĆ PRZERW POWYŻEJ 15 MIN",
                               "POZOSTAŁE PRZERWY I INNA PRACA", "OC", "RAZEM CZAS PRACY"};
    for (int i = 0; i < 12; ++i) {
        QTableWidgetItem *headerItem = new QTableWidgetItem(workHeaders[i]);
        headerItem->setTextAlignment(Qt::AlignCenter);
        headerItem->setFont(QFont("Arial", 10, QFont::Bold));
        ui->scheduleTable->setItem(7, i, headerItem);
    }

    // Oblicz liczbę dni w miesiącu
    int daysInMonth = firstDayOfMonth.daysInMonth();

    // Tablica skrótów dni tygodnia
    QStringList dayNames = {"pon", "wt", "śr", "czw", "pt", "sob", "nd"};

    query.prepare("SELECT day, lineid FROM schedulesassignments WHERE driverid = :driverid AND scheduleid = :scheduleid");
    query.bindValue(":driverid", getDriverID()); // m_driverId to ID wybranego kierowcy
    query.bindValue(":scheduleid", scheduleId); // m_scheduleId to ID harmonogramu
    query.exec();

    // Przechowujemy przypisane linie dla każdego dnia
    QMap<int, QString> dayToLine;

    while (query.next()) {
        int day = query.value("day").toInt();
        QString lineId = query.value("lineid").toString();
        dayToLine.insert(day, lineId);
    }

    // Wczytaj dane linii z bazy danych
    QMap<QString, QVariantMap> busLineData;
    QSqlQuery busLineQuery("SELECT lineid, starttime, endtime, drivingtime, breaks15minandlonger, "
                           "breakscountabove15, otherbreaksandwork, oc, totalworktime FROM buslines");

    while (busLineQuery.next()) {
        QString lineId = busLineQuery.value("lineid").toString();
        QVariantMap lineDetails = {
            {"starttime", busLineQuery.value("starttime")},
            {"endtime", busLineQuery.value("endtime")},
            {"drivingtime", busLineQuery.value("drivingtime")},
            {"breaks15minandlonger", busLineQuery.value("breaks15minandlonger")},
            {"breakscountabove15", busLineQuery.value("breakscountabove15")},
            {"otherbreaksandwork", busLineQuery.value("otherbreaksandwork")},
            {"oc", busLineQuery.value("oc")},
            {"totalworktime", busLineQuery.value("totalworktime")}
        };
        busLineData.insert(lineId, lineDetails);
    }
    // Zmienna do przechowywania sumy godzin w tygodniu
    // Zmienna do przechowywania sumy minut w tygodniu
    int weeklyTotalMinutes = 0;
    int totalAllWeeklyMinutes = 0;


    for (int day = 1; day <= daysInMonth; ++day) {
        QDate currentDate(year, month, day);
        QString dateString = currentDate.toString("dd.MM.yyyy");
        QString dayOfWeek = dayNames[currentDate.dayOfWeek() - 1];

        int row = ui->scheduleTable->rowCount();
        ui->scheduleTable->insertRow(row);

        ui->scheduleTable->setItem(row, 0, new QTableWidgetItem(dateString));
        ui->scheduleTable->setItem(row, 1, new QTableWidgetItem(dayOfWeek));

        if (dayToLine.contains(day)) {
            QString lineId = dayToLine[day];
            ui->scheduleTable->setItem(row, 2, new QTableWidgetItem(lineId));

            if (lineId == "U") {
                // Wypełnij kolumnę "WOLNE LUB URLOP" czasem 08:00
                ui->scheduleTable->setItem(row, 3, new QTableWidgetItem("08:00"));
            } else if (busLineData.contains(lineId)) {
                QVariantMap lineDetails = busLineData[lineId];

                // Formatowanie czasu
                QString startTime = lineDetails["starttime"].toTime().toString("hh:mm");
                QString endTime = lineDetails["endtime"].toTime().toString("hh:mm");
                QString drivingTime = lineDetails["drivingtime"].toTime().toString("hh:mm");
                QString breaks15Min = lineDetails["breaks15minandlonger"].toTime().toString("hh:mm");
                QString totalWorkTime = lineDetails["totalworktime"].toTime().toString("hh:mm");

                // Wypełnij kolumny danymi z bazy danych
                ui->scheduleTable->setItem(row, 4, new QTableWidgetItem(startTime));
                ui->scheduleTable->setItem(row, 5, new QTableWidgetItem(endTime));
                ui->scheduleTable->setItem(row, 6, new QTableWidgetItem(drivingTime));
                ui->scheduleTable->setItem(row, 7, new QTableWidgetItem(breaks15Min));
                ui->scheduleTable->setItem(row, 8, new QTableWidgetItem(lineDetails["breakscountabove15"].toString()));
                ui->scheduleTable->setItem(row, 9, new QTableWidgetItem(lineDetails["otherbreaksandwork"].toString()));
                ui->scheduleTable->setItem(row, 10, new QTableWidgetItem(lineDetails["oc"].toString()));
                ui->scheduleTable->setItem(row, 11, new QTableWidgetItem(totalWorkTime));

                // Obliczanie całkowitego czasu pracy (sumowanie minut)
                QStringList timeParts = totalWorkTime.split(":");
                if (timeParts.size() == 2) {
                    int hours = timeParts[0].toInt();
                    int minutes = timeParts[1].toInt();
                    // Sumuj czas w minutach
                    weeklyTotalMinutes += (hours * 60) + minutes;
                    totalAllWeeklyMinutes += (hours * 60) + minutes;
                }
            }
        } else {
            ui->scheduleTable->setItem(row, 2, new QTableWidgetItem("")); // Pusta komórka, jeśli brak linii
            for (int col = 3; col < 12; ++col) {
                ui->scheduleTable->setItem(row, col, new QTableWidgetItem(""));
            }
        }

        // Sprawdzenie, czy to jest niedziela lub ostatni dzień miesiąca
        if (dayOfWeek == "nd" || day == daysInMonth) {
            int summaryRow = ui->scheduleTable->rowCount();
            ui->scheduleTable->insertRow(summaryRow);

            QTableWidgetItem *summaryItem = new QTableWidgetItem("SUMA TYGODNIA :");
            summaryItem->setTextAlignment(Qt::AlignCenter);
            ui->scheduleTable->setItem(summaryRow, 0, summaryItem);
            ui->scheduleTable->setSpan(summaryRow, 0, 1, 6);

            // Obliczanie godzin i minut z całkowitej liczby minut
            int totalHours = weeklyTotalMinutes / 60;
            int totalMinutes = weeklyTotalMinutes % 60;

            // Wyświetl sumę tygodnia w ostatniej kolumnie (przekraczającą 24h)
            QString totalTimeString = QString::asprintf("%02d:%02d", totalHours, totalMinutes);
            QTableWidgetItem *timeItem1 = new QTableWidgetItem(totalTimeString);
            timeItem1->setTextAlignment(Qt::AlignCenter);
            ui->scheduleTable->setItem(summaryRow, 11, timeItem1);

            QTableWidgetItem *emptyItem = new QTableWidgetItem("");
            emptyItem->setTextAlignment(Qt::AlignCenter);
            ui->scheduleTable->setItem(summaryRow, 7, emptyItem);
            ui->scheduleTable->setSpan(summaryRow, 7, 1, 4);

            QBrush brush(Qt::lightGray);  // Jasnoszary kolor

            // Sprawdzenie, czy każda komórka istnieje przed ustawieniem tła
            for (int col = 0; col < ui->scheduleTable->columnCount(); ++col) {
                QTableWidgetItem *item = ui->scheduleTable->item(summaryRow, col);
                if (item == nullptr) {
                    // Tworzymy pustą komórkę, jeśli nie istnieje
                    item = new QTableWidgetItem();
                    ui->scheduleTable->setItem(summaryRow, col, item);
                }
                item->setBackground(brush);  // Kolor tła dla każdej komórki
            }

            // Zresetuj sumę minut na początek następnego tygodnia
            weeklyTotalMinutes = 0;
        }
    }

    int rowCount = ui->scheduleTable->rowCount();

    ui->scheduleTable->insertRow(rowCount); // Wiersz 9
    ui->scheduleTable->insertRow(rowCount + 1); // Wiersz 10
    ui->scheduleTable->insertRow(rowCount + 2); // Wiersz 11
    ui->scheduleTable->insertRow(rowCount + 3); // Wiersz 12
    ui->scheduleTable->insertRow(rowCount + 4); // Wiersz 13
    ui->scheduleTable->insertRow(rowCount + 5); // Wiersz 14
    ui->scheduleTable->insertRow(rowCount + 6); // Wiersz 15
    ui->scheduleTable->insertRow(rowCount + 7); // Wiersz 16

    // Tekst w scalonych komórkach 0-5 dla nowych wierszy
    QStringList freeTexts = {
        "W - wolne",
        "W5 - wolne z tytułu 5-dniowego tyg. pracy",
        "WN - wolne za niedzielę lub święto",
        "WD - wolne dodatkowe za godz. nadliczbowe",
        "CH - chorobowe",
        "O2 - opieka",
        "U - urlop",
        "Plan miesięczny może ulec zmianie"
    };

    for (int i = 0; i < 8; ++i) {
        // Dodanie tekstu do pierwszej komórki w wierszach 9-16 (kolumna 0)
        QTableWidgetItem *freeItem = new QTableWidgetItem(freeTexts[i]);
        freeItem->setFont(QFont("Arial", 10, QFont::Bold));
        freeItem->setTextAlignment(Qt::AlignLeft);
        ui->scheduleTable->setItem(rowCount + i, 0, freeItem);
        ui->scheduleTable->setSpan(rowCount + i, 0, 1, 6); // Scal kolumny 0-5
    }

    // Dodanie tekstu do scalonych komórek w kolumnach 7-11 (na dole)
    QStringList additionalTexts = {
        "PRZEKAZANO DNIA:",
        "HARMONOGRAM SPORZĄDZIŁ:"
    };

    // Wstawienie tekstu w wierszach 9-12 w scalonych komórkach 7-11
    for (int i = 0; i < 2; ++i) {
        // Dodanie tekstu do komórki (kolumna 7) w wierszach 9-12
        QTableWidgetItem *additionalItem = new QTableWidgetItem(additionalTexts[i % 2]);
        additionalItem->setTextAlignment(Qt::AlignLeft);
        additionalItem->setFont(QFont("Arial", 10, QFont::Bold));
        ui->scheduleTable->setItem(rowCount + i, 7, additionalItem);
        ui->scheduleTable->setSpan(rowCount + i, 7, 1, 5); // Scal kolumny 7-11
    }

    int totalHours = totalAllWeeklyMinutes / 60;
    int totalMinutes = totalAllWeeklyMinutes % 60;
    QString totalWorkTimeString = QString::asprintf("%02d:%02d", totalHours, totalMinutes);
    QTableWidgetItem *totalWorkTimeItem = new QTableWidgetItem(totalWorkTimeString);
    totalWorkTimeItem->setTextAlignment(Qt::AlignCenter);

    // Wstawienie sumy do komórki w wierszu 6, pod "PRACA"
    ui->scheduleTable->setItem(5, 2, totalWorkTimeItem); // Komórka pod "PRACA" w wierszu 6
    calculateVacationSum();
    setFullWorkTime();
}

void Schedule::setFullWorkTime() {
    // Pobieramy tekst z komórek
    QString summaryLeaveTime = ui->scheduleTable->item(5, 3)->text();
    QString totalWorkTime = ui->scheduleTable->item(5, 2)->text();

    qDebug() << "Summary Leave Time: " << summaryLeaveTime;
    qDebug() << "Total Work Time: " << totalWorkTime;

    // Funkcja do przekształcania czasu w formacie "hh:mm" na minuty
    auto timeToMinutes = [](const QString &timeStr) -> int {
        QStringList timeParts = timeStr.split(":");
        if (timeParts.size() == 2) {
            bool okHour, okMinute;
            int hours = timeParts[0].toInt(&okHour);
            int minutes = timeParts[1].toInt(&okMinute);

            // Sprawdzamy, czy obie wartości są poprawne
            if (okHour && okMinute) {
                return hours * 60 + minutes; // Zwróć czas w minutach
            }
        }
        return -1; // Zwracamy -1 w przypadku niepoprawnego formatu
    };

    // Konwertujemy czasy na minuty
    int leaveTimeInMinutes = timeToMinutes(summaryLeaveTime);
    int workTimeInMinutes = timeToMinutes(totalWorkTime);

    // Sprawdzamy, czy konwersja się powiodła
    if (leaveTimeInMinutes == -1) {
        qDebug() << "Nieprawidłowy czas urlopu!";
    } else {
        qDebug() << "Czas urlopu (w minutach): " << leaveTimeInMinutes;
    }

    if (workTimeInMinutes == -1) {
        qDebug() << "Nieprawidłowy czas pracy!";
    } else {
        qDebug() << "Czas pracy (w minutach): " << workTimeInMinutes;
    }

    // Dodatkowe obliczenia lub konwersja minut z powrotem na godziny i minuty:
    int leaveHours = leaveTimeInMinutes / 60;
    int leaveMinutes = leaveTimeInMinutes % 60;

    int workHours = workTimeInMinutes / 60;
    int workMinutes = workTimeInMinutes % 60;

    int totalTime = leaveTimeInMinutes + workTimeInMinutes;

    int totalTimeHours = totalTime / 60;
    int totalTimeMinutes = totalTime % 60;

    QString totalTimeStr = QString::asprintf("%02d:%02d", totalTimeHours, totalTimeMinutes);
    ui->scheduleTable->item(5, 4)->setText(totalTimeStr);
}

void Schedule::calculateVacationSum() {
    int totalLeaveMinutes = 0;

    for (int row = 8; row < ui->scheduleTable->rowCount(); ++row) {
        QTableWidgetItem *firstCell = ui->scheduleTable->item(row, 0);
        QTableWidgetItem *leaveCell = ui->scheduleTable->item(row, 3);

        if (firstCell && leaveCell) {
            QString firstCellText = firstCell->text();
            QString leaveText = leaveCell->text();

            // Pomijamy wiersze zawierające "SUMA TYGODNIA" w pierwszej kolumnie
            if (!firstCellText.contains("SUMA TYGODNIA", Qt::CaseInsensitive) && !leaveText.isEmpty()) {
                // Zamień tekst "hh:mm" na godziny i minuty
                QStringList timeParts = leaveText.split(":");
                if (timeParts.size() == 2) {
                    int hours = timeParts[0].toInt();
                    int minutes = timeParts[1].toInt();
                    qDebug() << hours << " " << minutes;

                    // Dodaj czas do sumy w minutach
                    totalLeaveMinutes += (hours * 60) + minutes;
                    qDebug() << "Total leave minutes: " << totalLeaveMinutes;
                }
            }
        }
    }

    // Oblicz godziny i minuty z całkowitej liczby minut
    int totalHours = totalLeaveMinutes / 60;
    int remainingMinutes = totalLeaveMinutes % 60;

    // Umieść sumę w odpowiedniej komórce w formacie hh:mm
    int summaryRow = 5; // Wiersz 6 (indeks 5)
    int summaryColumn = 3; // Kolumna "URLOP"

    QTableWidgetItem *summaryLeaveItem = new QTableWidgetItem();
    summaryLeaveItem->setTextAlignment(Qt::AlignCenter);

    // Wyświetlanie w formacie hh:mm
    summaryLeaveItem->setText(QString("%1:%2")
                                  .arg(totalHours, 2, 10, QChar('0'))
                                  .arg(remainingMinutes, 2, 10, QChar('0')));

    ui->scheduleTable->setItem(summaryRow, summaryColumn, summaryLeaveItem);
}

int Schedule::getDriverID() {
    QString selectedDriver = ui->driversComboBox->currentText();

    // Dzielimy tekst na dwie części: 'driverid: nazwisko imię'
    QStringList parts = selectedDriver.split(": ");
    if (parts.size() == 2) {
        QString driverIdString = parts[0];  // Pierwsza część to driverid

        // Konwertujemy driverid na int
        int driverId = driverIdString.toInt();
        qDebug() << "Wybrany driverid: " << driverId;

        return driverId;
    }
    return -1;
}

void Schedule::on_exportToPDFButton_clicked()
{
    QPrinter printer;
    printer.setPrinterName("Printer");
    printer.setPageSize(QPageSize(QPageSize::A4)); // Ustawienie rozmiaru A4
    printer.setResolution(300); // Ustawienie wysokiej rozdzielczości (300 DPI)

    // Dialog drukowania
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() != QDialog::Accepted) {
        return; // Anulowanie
    }

    // Tworzymy QPainter dla drukarki
    QPainter painter;
    if (!painter.begin(&printer)) {
        qWarning("Nie udało się rozpocząć malowania na drukarce.");
        return;
    }

    // Przygotowanie rozmiaru strony
    QRect pageRect = printer.pageRect(QPrinter::DevicePixel).toRect();
    QSize pageSize = pageRect.size(); // Rozmiar strony w pikselach

    // Uzyskanie pełnego rozmiaru tabeli (uwzględniając wszystkie wiersze i kolumny)
    int totalWidth = 0;
    int totalHeight = 0;

    qDebug() << ui->scheduleTable->columnCount() << ui->scheduleTable->rowCount();

    // Obliczanie pełnego rozmiaru tabeli (wszystkich kolumn i wierszy)
    for (int col = 0; col < ui->scheduleTable->columnCount(); ++col) {
        totalWidth += ui->scheduleTable->columnWidth(col);
    }

    for (int row = 0; row < ui->scheduleTable->rowCount(); ++row) {
        totalHeight += ui->scheduleTable->rowHeight(row);
    }

    QSize tableSize(totalWidth, totalHeight); // Całkowity rozmiar tabeli

    // Tworzymy QPixmap, który pomieści całą tabelę
    QPixmap tablePixmap(tableSize);
    tablePixmap.fill(Qt::white); // Tło białe

    // Tworzymy QPainter, aby rysować na QPixmap
    QPainter tablePainter(&tablePixmap);
    tablePainter.setRenderHint(QPainter::Antialiasing); // Lepsza jakość
    tablePainter.setRenderHint(QPainter::TextAntialiasing);

    // Renderowanie całej tabeli na QPixmap
    ui->scheduleTable->render(&tablePainter, QPoint(0, 0), QRegion(0, 0, tableSize.width(), tableSize.height()));
    tablePainter.end();

    // Obliczanie skali, aby tabela zmieściła się na stronie
    double scaleX = static_cast<double>(pageSize.width()) / tableSize.width();
    double scaleY = static_cast<double>(pageSize.height()) / tableSize.height();
    double scale = qMin(scaleX, scaleY); // Skalowanie proporcjonalne

    // Zastosowanie skali i rysowanie tabeli na stronie
    painter.scale(scale, scale);

    // Rysowanie całej tabeli na stronie
    painter.drawPixmap(0, 0, tablePixmap);

    // Zakończenie malowania
    painter.end();
}
