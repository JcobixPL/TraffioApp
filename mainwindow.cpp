#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int userid, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
    , userID(userid)
{
    ui->setupUi(this);

    setupUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI() {
    ui->stackedWidget->setCurrentIndex(0);
    refreshDriversLinesTable();
    refreshShortenedSchedules();
    refreshShiftPlans();
    refreshSchedules();
    connect(ui->schedulesTable, &QAbstractItemView::doubleClicked, this, &MainWindow::on_editScheduleButton_clicked);
    connect(ui->shiftPlansTable, &QAbstractItemView::doubleClicked, this, &MainWindow::on_editShiftPlanButton_clicked);
    connect(ui->shortenedSchedulesTable, &QAbstractItemView::doubleClicked, this, &MainWindow::on_editShortenedScheduleButton_clicked);
}

void MainWindow::refreshDriversLinesTable() {
    // Pobranie dzisiejszej daty
    QDate currentDate = QDate::currentDate();
    int currentMonth = currentDate.month();
    int currentYear = currentDate.year();

    // Zapytanie SQL, aby sprawdzić, czy istnieje grafik na aktualny miesiąc i rok
    QString queryStr = QString(R"(
        SELECT id
        FROM shiftplans
        WHERE month = %1
        AND year = %2;
    )").arg(currentMonth).arg(currentYear);

    QSqlQuery query(queryStr);

    if (query.next()) {
        // Jeśli istnieje grafik, pobierz jego ID
        int shiftPlanId = query.value(0).toInt();

        // Przygotowanie zapytania do pobrania danych o przypisanych liniach i kierowcach (z nazwiskiem)
        QString assignmentQueryStr = QString(R"(
            SELECT buslines.lineid, UPPER(drivers.surname)
            FROM shiftplansassignments
            JOIN buslines ON buslines.lineid = shiftplansassignments.lineid
            JOIN drivers ON drivers.driverid = shiftplansassignments.driverid
            WHERE shiftplansassignments.shiftplanid = %1
            AND shiftplansassignments.day = %2
            AND buslines.lineid != 'U';
        )").arg(shiftPlanId).arg(currentDate.day());

        // Wykonanie zapytania
        QSqlQuery assignmentQuery(assignmentQueryStr);

        // Sprawdzanie czy zapytanie zwróciło wyniki
        if (assignmentQuery.size() > 0) {
            // Zainicjowanie QTableWidget
            ui->driversLinesTable->setRowCount(0);  // Czyszczenie poprzednich danych
            ui->driversLinesTable->setColumnCount(2); // Ustawienie liczby kolumn: LINIA, KIEROWCA
            ui->driversLinesTable->setHorizontalHeaderLabels(QStringList() << "LINIA" << "KIEROWCA");

            // Wstawianie wierszy do tabeli
            int row = 0;
            while (assignmentQuery.next()) {
                // Tworzenie wierszy w QTableWidget
                ui->driversLinesTable->insertRow(row);
                ui->driversLinesTable->setItem(row, 0, new QTableWidgetItem(assignmentQuery.value(0).toString())); // LINIA
                ui->driversLinesTable->setItem(row, 1, new QTableWidgetItem(assignmentQuery.value(1).toString())); // KIEROWCA
                row++;
            }

            // Ustawienia wyglądu
            ui->driversLinesTable->resizeColumnsToContents();  // Dopasowanie szerokości kolumn
            ui->driversLinesTable->resizeRowsToContents();     // Dopasowanie wysokości wierszy
        } else {
            qDebug() << "Brak przypisanych danych do tabeli.";
        }
    } else {
        // Jeśli grafik nie istnieje, można dodać komunikat lub wykonać inną akcję
        qDebug() << "Brak grafiku na obecny miesiąc.";
    }
}


void MainWindow::on_dashboardButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    setupUI();
}


void MainWindow::on_workOrganizationButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::refreshShiftPlans() {
    ui->shiftPlansTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->shiftPlansTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->shiftPlansTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->shiftPlansTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;
    query.prepare("SELECT year, "
                  "CASE month "
                  "  WHEN 1 THEN 'Styczeń' WHEN 2 THEN 'Luty' WHEN 3 THEN 'Marzec' "
                  "  WHEN 4 THEN 'Kwiecień' WHEN 5 THEN 'Maj' WHEN 6 THEN 'Czerwiec' "
                  "  WHEN 7 THEN 'Lipiec' WHEN 8 THEN 'Sierpień' WHEN 9 THEN 'Wrzesień' "
                  "  WHEN 10 THEN 'Październik' WHEN 11 THEN 'Listopad' WHEN 12 THEN 'Grudzień' "
                  "END AS month, "
                  "status, modified_date, modified_by "
                  "FROM shiftplans WHERE userid = :id ORDER BY year, month");
    query.bindValue(":id", userID);

    if (query.exec()) {
        ui->shiftPlansTable->setRowCount(0);
        QStringList headers = {"ROK", "MIESIĄC", "STATUS", "OSTATNIA MODYFIKACJA", "ZMODYFIKOWANE PRZEZ"};
        ui->shiftPlansTable->setColumnCount(5);
        ui->shiftPlansTable->setHorizontalHeaderLabels(headers);

        int row = 0;
        while(query.next()) {
            ui->shiftPlansTable->insertRow(row);
            ui->shiftPlansTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->shiftPlansTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->shiftPlansTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->shiftPlansTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->shiftPlansTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));

            QString modifiedDate = query.value(3).toString();
            QDateTime dateTime = QDateTime::fromString(modifiedDate, Qt::ISODate);
            if (dateTime.isValid()) {
                // Formatujemy datę na "yyyy-MM-dd HH:mm"
                QString formattedDate = dateTime.toString("yyyy-MM-dd HH:mm");
                ui->shiftPlansTable->setItem(row, 3, new QTableWidgetItem(formattedDate));
            } else {
                // Jeśli data jest nieprawidłowa, zostawiamy oryginalną
                ui->shiftPlansTable->setItem(row, 3, new QTableWidgetItem(modifiedDate));
            }

            ui->shiftPlansTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));

            ++row;
        }
        for (int col = 0; col < ui->shiftPlansTable->columnCount(); ++col) {
            ui->shiftPlansTable->resizeColumnToContents(col);
        }
        for (int row = 0; row < ui->shiftPlansTable->rowCount(); ++row) {
            ui->shiftPlansTable->resizeRowToContents(row);
        }
    } else {
        qDebug() << "Query failed: " << query.lastError().text();
    }
}

void MainWindow::on_addShiftPlanButton_clicked()
{
    createShiftPlanDialog *dialog = new createShiftPlanDialog(userID);
    dialog->show();
    if (dialog->exec() == QDialog::Accepted) {
        refreshShiftPlans();
    }
}


void MainWindow::on_editShiftPlanButton_clicked()
{
    // Pobieramy model selekcji
    QItemSelectionModel *selectionModel = ui->shiftPlansTable->selectionModel();

    // Sprawdzamy, czy jest zaznaczona jakakolwiek komórka
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        // Jeśli nie ma zaznaczonej komórki, wyświetlamy komunikat
        QMessageBox::warning(this, "Błąd", "Proszę zaznaczyć komórkę!");
        return;
    }

    // Pobieramy indeks pierwszej zaznaczonej komórki
    QModelIndex index = selectedIndexes.first();

    // Pobieramy numer wiersza
    int row = index.row();

    // Pobieramy rok z kolumny 0
    int year = ui->shiftPlansTable->model()->data(ui->shiftPlansTable->model()->index(row, 0)).toInt();

    // Pobieramy nazwę miesiąca z kolumny 1
    QString monthName = ui->shiftPlansTable->model()->data(ui->shiftPlansTable->model()->index(row, 1)).toString();

    // Mapa przyporządkowująca nazwę miesiąca do numeru
    QMap<QString, int> monthMap = {
        {"Styczeń", 1}, {"Luty", 2}, {"Marzec", 3}, {"Kwiecień", 4},
        {"Maj", 5}, {"Czerwiec", 6}, {"Lipiec", 7}, {"Sierpień", 8},
        {"Wrzesień", 9}, {"Październik", 10}, {"Listopad", 11}, {"Grudzień", 12}
    };

    // Zamiana nazwy miesiąca na numer
    int month = monthMap.value(monthName, 0); // Domyślnie 0, jeśli miesiąc nie zostanie znaleziony

    if (month == 0) {
        QMessageBox::warning(this, "Błąd", "Niepoprawna nazwa miesiąca!");
        return;
    }

    // Wyszukujemy shiftplanid na podstawie roku i miesiąca
    QSqlQuery query;
    query.prepare("SELECT id FROM shiftplans WHERE year = :year AND month = :month");
    query.bindValue(":year", year);
    query.bindValue(":month", month);

    if (!query.exec()) {
        QMessageBox::critical(this, "Błąd", "Nie udało się pobrać ID planu zmian: " + query.lastError().text());
        return;
    }

    if (!query.next()) {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono planu zmian dla podanego roku i miesiąca.");
        return;
    }

    // Pobieramy shiftplanid
    int shiftPlanID = query.value(0).toInt();

    // Otwieramy okno edycji planu zmian
    ShiftPlan *sp = new ShiftPlan(shiftPlanID);
    sp->setWindowModality(Qt::ApplicationModal);
    sp->show();
}


void MainWindow::on_addScheduleButton_clicked() {
    CreateScheduleDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {

        int shiftPlanID = dialog.getChosenShiftPlan();
        qDebug() << shiftPlanID;
        if(shiftPlanID != -1) {
            QSqlQuery query;
            query.prepare("INSERT INTO schedules (shiftplanid, userid, modified_by) VALUES (:shiftplanid, :id, :id)");
            query.bindValue(":shiftplanid", shiftPlanID);
            query.bindValue(":id", userID);
            if(!query.exec()) {

            } else {
                qDebug() << "Schedule added correctly";
                int scheduleID = query.lastInsertId().toInt();

                query.prepare("DELETE FROM schedulesassignments WHERE scheduleid = :id");
                query.bindValue(":id", scheduleID);
                query.exec();

                query.prepare("INSERT INTO schedulesassignments (scheduleid, driverid, day, lineid) SELECT :scheduleid, driverid, day, lineid FROM shiftplansassignments WHERE shiftplanid = :shiftplanid");
                query.bindValue(":scheduleid", scheduleID);
                query.bindValue(":shiftplanid", shiftPlanID);

                if(!query.exec()) {

                } else {
                    qDebug() << "Data copied correctly";
                }
                refreshSchedules();
            }
        } else {
            qDebug() << "No shift plan chosen";
        }
    }
}

void MainWindow::refreshSchedules() {
    ui->schedulesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->schedulesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->schedulesTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->schedulesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;
    query.prepare(
        "SELECT sp.year, "
        "       CASE sp.month "
        "           WHEN 1 THEN 'Styczeń' "
        "           WHEN 2 THEN 'Luty' "
        "           WHEN 3 THEN 'Marzec' "
        "           WHEN 4 THEN 'Kwiecień' "
        "           WHEN 5 THEN 'Maj' "
        "           WHEN 6 THEN 'Czerwiec' "
        "           WHEN 7 THEN 'Lipiec' "
        "           WHEN 8 THEN 'Sierpień' "
        "           WHEN 9 THEN 'Wrzesień' "
        "           WHEN 10 THEN 'Październik' "
        "           WHEN 11 THEN 'Listopad' "
        "           WHEN 12 THEN 'Grudzień' "
        "       END AS month, "
        "       s.status, "
        "       s.modified_date, "
        "       s.modified_by "
        "FROM schedules s "
        "JOIN shiftplans sp ON s.shiftplanid = sp.id "
        "WHERE sp.userid = :id "
        "ORDER BY sp.year DESC, sp.month DESC"
        );

    query.bindValue(":id", userID);

    if (!query.exec()) {
        qDebug() << "SQL error: " << query.lastError().text();
        return;
    }

    // Wyczyszczenie tabeli przed odświeżeniem
    ui->schedulesTable->clear();
    ui->schedulesTable->setRowCount(0); // Usuwa wszystkie wiersze
    ui->schedulesTable->setColumnCount(5); // Ustawienie liczby kolumn

    // Ustawienie nagłówków
    QStringList headers = {"ROK", "MIESIĄC", "STATUS", "OSTATNIA MODYFIKACJA", "OSOBA MODYFIKUJĄCA"};
    ui->schedulesTable->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        ui->schedulesTable->insertRow(row); // Dodajemy nowy wiersz

        // Wypełnienie danych do wiersza
        ui->schedulesTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // ROK
        ui->schedulesTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // MIESIĄC
        ui->schedulesTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // STATUS
        ui->schedulesTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // OSTATNIA MODYFIKACJA
        ui->schedulesTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // OSOBA MODYFIKUJĄCA

        QString modifiedDate = query.value(3).toString();
        QDateTime dateTime = QDateTime::fromString(modifiedDate, Qt::ISODate);
        if (dateTime.isValid()) {
            // Formatujemy datę na "yyyy-MM-dd HH:mm"
            QString formattedDate = dateTime.toString("yyyy-MM-dd HH:mm");
            ui->schedulesTable->setItem(row, 3, new QTableWidgetItem(formattedDate));
        } else {
            // Jeśli data jest nieprawidłowa, zostawiamy oryginalną
            ui->schedulesTable->setItem(row, 3, new QTableWidgetItem(modifiedDate));
        }

        ui->schedulesTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));

        row++;
    }

    if (row == 0) {
        qDebug() << "No schedules found for userid: " << userID;
    } else {
        qDebug() << "Refresh completed, rows loaded:" << row;
    }
}

void MainWindow::on_schedulesModuleButton_clicked()
{
    ui->driversTabStackedWidget->setCurrentIndex(1);
}


void MainWindow::on_shiftPlansModuleButton_clicked()
{
    ui->driversTabStackedWidget->setCurrentIndex(0);
}


void MainWindow::on_changeShiftPlanStatusButton_clicked()
{
    QModelIndex currentIndex = ui->shiftPlansTable->currentIndex();
    if(!currentIndex.isValid()) {
        qDebug() << "No cell chosen";
        return;
    }

    QMap<QString, int> monthMap = {
        {"Styczeń", 1}, {"Luty", 2}, {"Marzec", 3}, {"Kwiecień", 4},
        {"Maj", 5}, {"Czerwiec", 6}, {"Lipiec", 7}, {"Sierpień", 8},
        {"Wrzesień", 9}, {"Październik", 10}, {"Listopad", 11}, {"Grudzień", 12}
    };

    int year = ui->shiftPlansTable->model()->data(ui->shiftPlansTable->model()->index(currentIndex.row(), 0)).toInt();

    QString monthName = ui->shiftPlansTable->model()->data(ui->shiftPlansTable->model()->index(currentIndex.row(), 1)).toString();

    int month = monthMap.value(monthName, 0);

    QString currentStatus = ui->shiftPlansTable->model()->data(ui->shiftPlansTable->model()->index(currentIndex.row(), 2)).toString();

    QString newStatus = (currentStatus == "W trakcie") ? "Gotowy" : "W trakcie";

    QSqlQuery query;
    query.prepare("UPDATE shiftplans SET status = :status WHERE year = :year AND month = :month");
    query.bindValue(":status", newStatus);
    query.bindValue(":year", year);
    query.bindValue(":month", month);

    if(!query.exec()) {
        qDebug() << "Status update failed: " << query.lastError().text();
        return;
    }

    refreshShiftPlans();
}


void MainWindow::on_editScheduleButton_clicked()
{
    QModelIndex index = ui->schedulesTable->currentIndex();
    if (index.isValid()) {
        QString year = ui->schedulesTable->model()->data(index.sibling(index.row(), 0)).toString();
        QString monthName = ui->schedulesTable->model()->data(index.sibling(index.row(), 1)).toString();

        QMap<QString, int> monthMap;
        monthMap["Styczeń"] = 1;
        monthMap["Luty"] = 2;
        monthMap["Marzec"] = 3;
        monthMap["Kwiecień"] = 4;
        monthMap["Maj"] = 5;
        monthMap["Czerwiec"] = 6;
        monthMap["Lipiec"] = 7;
        monthMap["Sierpień"] = 8;
        monthMap["Wrzesień"] = 9;
        monthMap["Październik"] = 10;
        monthMap["Listopad"] = 11;
        monthMap["Grudzień"] = 12;

        int month = monthMap.value(monthName, -1);
        QSqlQuery query;
        query.prepare("SELECT id FROM shiftplans WHERE year = :year AND month = :month");
        query.bindValue(":year", year);
        query.bindValue(":month", month);
        if (query.exec()) {
            if (query.next()) {
                int shiftPlanId = query.value(0).toInt();
                query.prepare("SELECT id FROM schedules WHERE shiftplanid = :id");
                query.bindValue(":id", shiftPlanId);
                if (query.exec()) {
                    if (query.next()) {
                        int scheduleId = query.value(0).toInt();
                        Schedule *schedule = new Schedule(scheduleId);
                        schedule->setWindowModality(Qt::ApplicationModal);
                        schedule->show();
                    }
                } else {
                    qDebug() << "SQL Error: " << query.lastError().text();
                }
            }
        } else {
            qDebug() << "SQL Error: " << query.lastError().text();
        }
    }
}


void MainWindow::on_shortenedSchedulesModuleButton_clicked()
{
    ui->driversTabStackedWidget->setCurrentIndex(2);
}


void MainWindow::on_removeScheduleButton_clicked()
{
    QModelIndex currentIndex = ui->schedulesTable->currentIndex();

    if(!currentIndex.isValid()) {
        qDebug() << "Nie wybrano żadnej komórki.";
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potwierdzenie usunięcia",
                                  "Czy na pewno chcesz usunąć wybrany harmonogram?",
                                  QMessageBox::Yes | QMessageBox::No);

    // Obsługa odpowiedzi użytkownika
    if (reply == QMessageBox::No) {
        return; // Użytkownik wybrał "Nie", przerwij operację
    }

    if (reply == QMessageBox::Yes) {
        QMap<QString, int> monthMap = {
            {"Styczeń", 1}, {"Luty", 2}, {"Marzec", 3}, {"Kwiecień", 4},
            {"Maj", 5}, {"Czerwiec", 6}, {"Lipiec", 7}, {"Sierpień", 8},
            {"Wrzesień", 9}, {"Październik", 10}, {"Listopad", 11}, {"Grudzień", 12}
        };


        QSqlQuery query;

        int year = ui->schedulesTable->model()->data(ui->schedulesTable->model()->index(currentIndex.row(), 0)).toInt();
        QString monthName = ui->shiftPlansTable->model()->data(ui->shiftPlansTable->model()->index(currentIndex.row(), 1)).toString();
        int month = monthMap.value(monthName, 0);

        int tempID;

        query.prepare("SELECT id FROM shiftplans WHERE year = :year AND month = :month");
        query.bindValue(":year", year);
        query.bindValue(":month", month);
        if(query.exec()) {
            if(query.next()) {
                tempID = query.value(0).toInt();
            }
        }

        int scheduleID;

        query.prepare("SELECT id FROM schedules WHERE shiftplanid = :id");
        query.bindValue(":id", tempID);
        if(query.exec() && query.next()) {
            scheduleID = query.value(0).toInt();
        }

        query.prepare("DELETE FROM schedulesassignments WHERE scheduleid = :id");
        query.bindValue(":id", scheduleID);

        if (!query.exec()) {
            qDebug() << "Błąd aktualizacji statusu: " << query.lastError().text();
            return;
        }

        query.prepare("DELETE FROM schedules WHERE id = :id");
        query.bindValue(":id", scheduleID);

        if (!query.exec()) {
            qDebug() << "Błąd aktualizacji statusu: " << query.lastError().text();
            return;
        }

        // Odświeżenie tabeli po aktualizacji
        refreshSchedules();
    }
}


void MainWindow::on_removeShiftPlanButton_clicked()
{
    QModelIndex currentIndex = ui->shiftPlansTable->currentIndex();

    if (!currentIndex.isValid()) {
        qDebug() << "Nie wybrano żadnej komórki.";
        return;
    }

    // Wyświetlenie okna dialogowego z pytaniem
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potwierdzenie usunięcia",
                                  "Czy na pewno chcesz usunąć wybrany grafik?",
                                  QMessageBox::Yes | QMessageBox::No);

    // Obsługa odpowiedzi użytkownika
    if (reply == QMessageBox::No) {
        return; // Użytkownik wybrał "Nie", przerwij operację
    }

    if (reply == QMessageBox::Yes) {
        QMap<QString, int> monthMap = {
            {"Styczeń", 1}, {"Luty", 2}, {"Marzec", 3}, {"Kwiecień", 4},
            {"Maj", 5}, {"Czerwiec", 6}, {"Lipiec", 7}, {"Sierpień", 8},
            {"Wrzesień", 9}, {"Październik", 10}, {"Listopad", 11}, {"Grudzień", 12}
        };

        // Pobranie roku z kolumny 0
        int year = ui->shiftPlansTable->model()->data(ui->shiftPlansTable->model()->index(currentIndex.row(), 0)).toInt();

        // Pobranie nazwy miesiąca z kolumny 1
        QString monthName = ui->shiftPlansTable->model()->data(ui->shiftPlansTable->model()->index(currentIndex.row(), 1)).toString();

        // Zamiana nazwy miesiąca na numer
        int month = monthMap.value(monthName, 0);

        int tempID;

        QSqlQuery query;

        query.prepare("SELECT id FROM shiftplans WHERE year = :year AND month = :month");
        query.bindValue(":year", year);
        query.bindValue(":month", month);

        if(query.exec()) {
            if(query.next()) {
                tempID = query.value(0).toInt();
            }
        }

        query.prepare("DELETE FROM shiftplansassignments WHERE shiftplanid = :id");
        query.bindValue(":id", tempID);

        if (!query.exec()) {
            qDebug() << "Błąd aktualizacji statusu: " << query.lastError().text();
            return;
        }

        query.prepare("DELETE FROM shiftplans WHERE id = :id");
        query.bindValue(":id", tempID);

        if (!query.exec()) {
            qDebug() << "Błąd aktualizacji statusu: " << query.lastError().text();
            return;
        }

        // Odświeżenie tabeli po aktualizacji
        refreshShiftPlans();
    }

}


void MainWindow::on_changeScheduleStatusButton_clicked()
{
    QModelIndex currentIndex = ui->schedulesTable->currentIndex();
    if(!currentIndex.isValid()) {
        qDebug() << "No cell chosen";
        return;
    }

    QMap<QString, int> monthMap = {
        {"Styczeń", 1}, {"Luty", 2}, {"Marzec", 3}, {"Kwiecień", 4},
        {"Maj", 5}, {"Czerwiec", 6}, {"Lipiec", 7}, {"Sierpień", 8},
        {"Wrzesień", 9}, {"Październik", 10}, {"Listopad", 11}, {"Grudzień", 12}
    };

    int year = ui->schedulesTable->model()->data(ui->schedulesTable->model()->index(currentIndex.row(), 0)).toInt();

    QString monthName = ui->schedulesTable->model()->data(ui->schedulesTable->model()->index(currentIndex.row(), 1)).toString();

    int month = monthMap.value(monthName, 0);

    QString currentStatus = ui->schedulesTable->model()->data(ui->schedulesTable->model()->index(currentIndex.row(), 2)).toString();

    QString newStatus = (currentStatus == "W trakcie") ? "Gotowy" : "W trakcie";

    int shiftPlanID;
    QSqlQuery query;
    query.prepare("SELECT id FROM shiftplans WHERE year = :year AND month = :month");
    query.bindValue(":year", year);
    query.bindValue(":month", month);
    if (query.exec()) {
        if (query.next()) {
            shiftPlanID = query.value(0).toInt();
        }
    }

    query.prepare("UPDATE schedules SET status = :status WHERE shiftplanid = :id");
    query.bindValue(":status", newStatus);
    query.bindValue(":id", shiftPlanID);
    query.exec();

    refreshSchedules();
}


void MainWindow::on_addShortenedScheduleButton_clicked() {
    CreateShortenedScheduleDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        int shiftPlanID = dialog.getChosenShiftPlan();
        if (shiftPlanID != -1) {
            QSqlQuery query;
            query.prepare("INSERT INTO shortenedschedules (shiftplanid, userid, modified_by) VALUES (:shiftplanid, :id, :id)");
            query.bindValue(":shiftplanid", shiftPlanID);
            query.bindValue(":id", userID);
            if (!query.exec()) {

            } else {
                int shortenedScheduleID = query.lastInsertId().toInt();
                query.prepare("DELETE FROM shortenedschedulesassignments WHERE shortenedschedules = :id");
                query.bindValue(":id", shortenedScheduleID);
                query.exec();

                query.prepare("INSERT INTO shortenedschedulesassignments (shortenedscheduleid, driverid, day, lineid) SELECT :shortenedscheduleid, driverid, day, lineid, FROM shiftplansassignments WHERE shiftplanid = :shiftplanid");
                query.bindValue(":shortenedscheduleid", shortenedScheduleID);
                query.bindValue(":shiftplanid", shiftPlanID);

                if(!query.exec()) {

                } else {
                    qDebug() << "Data copied correctly";
                }
                refreshShortenedSchedules();
            }
        } else {
            qDebug() << "No shift plan chosen";
        }
    }
}

void MainWindow::refreshShortenedSchedules() {
    ui->shortenedSchedulesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->shortenedSchedulesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->shortenedSchedulesTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->shortenedSchedulesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;
    query.prepare(
        "SELECT sp.year, "
        "       CASE sp.month "
        "           WHEN 1 THEN 'Styczeń' "
        "           WHEN 2 THEN 'Luty' "
        "           WHEN 3 THEN 'Marzec' "
        "           WHEN 4 THEN 'Kwiecień' "
        "           WHEN 5 THEN 'Maj' "
        "           WHEN 6 THEN 'Czerwiec' "
        "           WHEN 7 THEN 'Lipiec' "
        "           WHEN 8 THEN 'Sierpień' "
        "           WHEN 9 THEN 'Wrzesień' "
        "           WHEN 10 THEN 'Październik' "
        "           WHEN 11 THEN 'Listopad' "
        "           WHEN 12 THEN 'Grudzień' "
        "       END AS month, "
        "       s.status, "
        "       s.modified_date, "
        "       s.modified_by "
        "FROM shortenedschedules s "
        "JOIN shiftplans sp ON s.shiftplanid = sp.id "
        "WHERE sp.userid = :id "
        "ORDER BY sp.year DESC, sp.month DESC"
        );

    query.bindValue(":id", userID);

    if (!query.exec()) {
        qDebug() << "SQL error: " << query.lastError().text();
        return;
    }

    ui->shortenedSchedulesTable->clear();
    ui->shortenedSchedulesTable->setRowCount(0);
    ui->shortenedSchedulesTable->setColumnCount(5);

    QStringList headers = {"ROK", "MIESIĄC", "STATUS", "OSTATNIA MODYFIKACJA", "ZMODYFIKOWANE PRZEZ"};
    ui->shortenedSchedulesTable->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        ui->shortenedSchedulesTable->insertRow(row);

        ui->shortenedSchedulesTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // ROK
        ui->shortenedSchedulesTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // MIESIĄC
        ui->shortenedSchedulesTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // STATUS
        ui->shortenedSchedulesTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // OSTATNIA MODYFIKACJA
        ui->shortenedSchedulesTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // OSOBA MODYFIKUJĄCA

        QString modifiedDate = query.value(3).toString();
        QDateTime dateTime = QDateTime::fromString(modifiedDate, Qt::ISODate);
        if (dateTime.isValid()) {
            QString formattedDate = dateTime.toString("yyyy-MM-dd HH:mm");
            ui->shortenedSchedulesTable->setItem(row, 3, new QTableWidgetItem(formattedDate));
        } else {
            // Jeśli data jest nieprawidłowa, zostawiamy oryginalną
            ui->shortenedSchedulesTable->setItem(row, 3, new QTableWidgetItem(modifiedDate));
        }

        ui->shortenedSchedulesTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));

        row++;
        }

    if (row == 0) {
        qDebug() << "No shortened schedules found for userid: " << userID;
    } else {
        qDebug() << "Refresh completed, rows loaded:" << row;
    }
}

void MainWindow::on_editShortenedScheduleButton_clicked()
{
    QModelIndex index = ui->shortenedSchedulesTable->currentIndex();
    if (index.isValid()) {
        QString year = ui->shortenedSchedulesTable->model()->data(index.sibling(index.row(), 0)).toString();
        QString monthName = ui->shortenedSchedulesTable->model()->data(index.sibling(index.row(), 1)).toString();

        QMap<QString, int> monthMap;
        monthMap["Styczeń"] = 1;
        monthMap["Luty"] = 2;
        monthMap["Marzec"] = 3;
        monthMap["Kwiecień"] = 4;
        monthMap["Maj"] = 5;
        monthMap["Czerwiec"] = 6;
        monthMap["Lipiec"] = 7;
        monthMap["Sierpień"] = 8;
        monthMap["Wrzesień"] = 9;
        monthMap["Październik"] = 10;
        monthMap["Listopad"] = 11;
        monthMap["Grudzień"] = 12;

        int month = monthMap.value(monthName, -1);
        QSqlQuery query;
        query.prepare("SELECT id FROM shiftplans WHERE year = :year AND month = :month");
        query.bindValue(":year", year);
        query.bindValue(":month", month);
        if (query.exec()) {
            if (query.next()) {
                int shiftPlanId = query.value(0).toInt();
                query.prepare("SELECT id FROM shortenedschedules WHERE shiftplanid = :id");
                query.bindValue(":id", shiftPlanId);
                if (query.exec()) {
                    if (query.next()) {
                        int shortenedscheduleId = query.value(0).toInt();
                        ShortenedSchedule *shortenedschedule = new ShortenedSchedule(shortenedscheduleId);
                        shortenedschedule->setWindowModality(Qt::ApplicationModal);
                        shortenedschedule->show();
                    }
                } else {
                    qDebug() << "SQL Error: " << query.lastError().text();
                }
            }
        } else {
            qDebug() << "SQL Error: " << query.lastError().text();
        }
    }
}

void MainWindow::on_busLinesButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    refreshBusLines();
}

void MainWindow::refreshBusLines() {
    QStringList headers = {
        "LINIA",
        "GODZ. ROZPOCZĘCIA",
        "GODZ. ZAKOŃCZENIA",
        "CZAS JAZDY"
        "PRZERWY POWYŻEJ 15 MIN",
        "ILOŚĆ PRZERW POWYŻEJ 15 MIN",
        "INNE PRZERWY I PRACA",
        "OC",
        "CZAS PRACY"
    };

    ui->busLinesTable->clear();
    ui->busLinesTable->setRowCount(0);

    ui->busLinesTable->setColumnCount(headers.size());
    ui->busLinesTable->setHorizontalHeaderLabels(headers);

    ui->busLinesTable->verticalHeader()->setVisible(false);

    ui->busLinesTable->setSelectionMode(QAbstractItemView::SingleSelection);

    QSqlQuery query;
    query.prepare("SELECT * FROM buslines");
    if (!query.exec()) {
        qDebug() << "SQL Error: " << query.lastError().text();
        return;
    }
    int row = 0;
    while (query.next()) {
        ui->busLinesTable->insertRow(row);
        for (int col = 0; col < headers.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->busLinesTable->setItem(row, col, item);
        }
        ++row;
    }

    ui->busLinesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_addBusLineButton_clicked()
{
    BusLines *busLinesWindow = new BusLines();
    connect(busLinesWindow, &BusLines::destroyed, this, &MainWindow::refreshBusLines);
    busLinesWindow->show();
}

