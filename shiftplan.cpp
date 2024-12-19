#include "shiftplan.h"
#include "qlabel.h"
#include "qsqlquerymodel.h"
#include "ui_shiftplan.h"

#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

#include <QPdfWriter>
#include <QPointer>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include <QFileDialog>
#include <QHeaderView>
#include <QTimer>

#include <QFileDialog>
#include <QPageSize>
#include <QPrinter>
#include <QPainter>
#include <QTableWidget>
#include <QFileDialog>
#include <QPdfWriter>
#include <QStandardPaths>

#include <QTableWidget>

ShiftPlan::ShiftPlan(int id, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ShiftPlan),
    id(id)
{
    ui->setupUi(this);
    setWindowTitle("PTMS");
    setWindowIcon(QIcon(":/icons/icon.png"));

    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    // Ustawienie okna na tryb pełnoekranowy
    showMaximized();

    // Zablokowanie zmiany rozmiaru okna (można tylko przełączyć do pełnoekranowego)
    setFixedSize(this->size());
    loadShiftPlanData();
    updateTableDimensions();
    connect(ui->shiftPlanTable, SIGNAL(cellChanged(int, int)), this, SLOT(onCellChanged(int, int)));

    // Połączenie sygnału cellChanged z metodą calculateRowSum (lub bezpośrednio z nią)
    connect(ui->shiftPlanTable, &QTableWidget::cellChanged, [this](int row, int col) {
        // Wywołanie calculateRowSum po każdej zmianie komórki
        calculateRowSum(row);
    });

    QLabel *autosaveLabel = new QLabel(this);
    autosaveLabel->setText("Autosave completed!");
    autosaveLabel->setStyleSheet("color: green; font-weight: bold;");
    autosaveLabel->setAlignment(Qt::AlignCenter);
    autosaveLabel->setGeometry(10, 10, 200, 30); // Dostosuj pozycję i rozmiar
    autosaveLabel->hide(); // Ukryj na początku

    // Timer do ukrywania komunikatu
    QTimer *hideMessageTimer = new QTimer(this);
    hideMessageTimer->setSingleShot(true); // Timer uruchamia się raz

    connect(hideMessageTimer, &QTimer::timeout, autosaveLabel, &QLabel::hide);

    // Inicjalizacja timera autosave
    autoSaveTimer = new QTimer(this);
    autoSaveTimer->setInterval(120000); // 2 minuty
    connect(autoSaveTimer, &QTimer::timeout, this, [this, autosaveLabel, hideMessageTimer]() {
        on_saveButton_clicked();  // Autosave
        autosaveLabel->show();    // Pokaż komunikat
        hideMessageTimer->start(3000); // Ukryj po 3 sekundach
    });
    autoSaveTimer->start();

    int drivers;
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM drivers");
    query.exec();
    if(query.next()) drivers = query.value(0).toInt();

    for(int row = 0; row < drivers*2; row+=2)    calculateRowSum(row);
}

ShiftPlan::~ShiftPlan()
{
    delete ui;
}

void ShiftPlan::updateTableDimensions() {
    QSqlQuery query;
    query.prepare("SELECT year, month FROM shiftPlans WHERE id = :id");
    query.bindValue(":id", id);

    if(query.exec()) {
        if(query.next()) {
            selectedYear = query.value(0).toInt();
            selectedMonth = query.value(1).toInt();
        }
    }

    int numDays = QDate(selectedYear, selectedMonth, 1).daysInMonth();
    qDebug() << numDays;

    QSqlQuery query1("SELECT surname FROM drivers");
    QStringList driverNames;
    while (query1.next()) {
        driverNames.append(query1.value(0).toString().toUpper());  // Konwersja na wielkie litery
    }

    int numDrivers = driverNames.size();

    // Pobranie dat świąt z bazy danych
    QSqlQuery holidayQuery;
    holidayQuery.prepare("SELECT date FROM freedays  WHERE EXTRACT(YEAR FROM date) = :year AND EXTRACT(MONTH FROM date) = :month");
    holidayQuery.bindValue(":year", selectedYear);
    holidayQuery.bindValue(":month", selectedMonth);
    QSet<QDate> holidays;
    if (holidayQuery.exec()) {
        while (holidayQuery.next()) {
            QDate holiday = holidayQuery.value(0).toDate();
            holidays.insert(holiday); // Zapisujemy daty świąt do zbioru
        }
    }

    // Ustawienie liczby wierszy i kolumn
    int rowCount = numDrivers * 2; // Jeden wiersz dla każdego kierowcy + pusty wiersz pod każdym
    int colCount = numDays + 1;    // Dni w miesiącu + 1 dodatkowa kolumna na "Suma"

    ui->shiftPlanTable->setRowCount(rowCount);
    ui->shiftPlanTable->setColumnCount(colCount);

    // Ustawienie nagłówków kolumn
    for (int col = 0; col < numDays; ++col) {
        ui->shiftPlanTable->setHorizontalHeaderItem(col, new QTableWidgetItem(QString::number(col + 1)));

        // Ustawienie tła dla sobót i niedziel
        QTableWidgetItem *headerItem = ui->shiftPlanTable->horizontalHeaderItem(col);
        QDate date(selectedYear, selectedMonth, col + 1);

        if (holidays.contains(date)) {
            // Jeśli jest to święto, ustawiamy tło na czerwono
            headerItem->setBackground(QColor(255, 0, 0));
        } else if (date.dayOfWeek() == 6) {
            // Sobota (zielony)
            headerItem->setBackground(QColor(0, 255, 0));
        } else if (date.dayOfWeek() == 7) {
            // Niedziela (czerwony)
            headerItem->setBackground(QColor(255, 0, 0));
        } else {
            // Dni robocze (brak tła lub domyślny kolor)
            headerItem->setBackground(QColor(255, 255, 255));  // Można usunąć, jeśli nie chcesz ustawiać tła
        }

        // Ustawienie tła dla całej kolumny
        for (int row = 0; row < rowCount; ++row) {
            QTableWidgetItem *item = ui->shiftPlanTable->item(row, col);
            if (!item) {
                item = new QTableWidgetItem();  // Tworzymy nowy element, jeśli jeszcze nie istnieje
                ui->shiftPlanTable->setItem(row, col, item);
            }

            if (holidays.contains(date)) {
                // Jeśli jest to święto, ustawiamy tło na czerwono
                item->setBackground(QColor(255, 0, 0));
            } else if (date.dayOfWeek() == 6) {
                // Sobota (zielony)
                item->setBackground(QColor(0, 255, 0));
            } else if (date.dayOfWeek() == 7) {
                // Niedziela (czerwony)
                item->setBackground(QColor(255, 0, 0));
            } else {
                // Dni robocze (brak tła lub domyślny kolor)
                item->setBackground(QColor(255, 255, 255));  // Można usunąć, jeśli nie chcesz ustawiać tła
            }
        }
    }

    ui->shiftPlanTable->setHorizontalHeaderItem(numDays, new QTableWidgetItem("Suma"));


    // Zablokowanie możliwości zmiany rozmiarów kolumn i wierszy
    ui->shiftPlanTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->shiftPlanTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->shiftPlanTable->setSelectionMode(QAbstractItemView::SingleSelection);

    QFont columnHeaderFont = ui->shiftPlanTable->horizontalHeader()->font();
    columnHeaderFont.setBold(true);
    ui->shiftPlanTable->horizontalHeader()->setFont(columnHeaderFont);

    // Pogrubienie czcionki w nagłówkach wierszy
    QFont rowHeaderFont = ui->shiftPlanTable->verticalHeader()->font();
    rowHeaderFont.setBold(true);
    ui->shiftPlanTable->verticalHeader()->setFont(rowHeaderFont);

    for (int col = 0; col < numDays; ++col) {
        ui->shiftPlanTable->setColumnWidth(col, 45); // Ustaw szerokość na 45px
    }
    ui->shiftPlanTable->setColumnWidth(numDays, 60); // Kolumna "Suma" będzie miała większą szerokość



    // Ustawienie nagłówków wierszy
    for (int i = 0; i < numDrivers; ++i) {
        int driverRowIndex = i * 2;

        // Nazwisko kierowcy w wielkich literach
        ui->shiftPlanTable->setVerticalHeaderItem(driverRowIndex, new QTableWidgetItem(driverNames[i]));

        // Pusty wiersz pod każdym kierowcą
        ui->shiftPlanTable->setVerticalHeaderItem(driverRowIndex + 1, new QTableWidgetItem(""));
    }
}


void ShiftPlan::onCellChanged(int row, int col) {
    if (col < ui->shiftPlanTable->columnCount() - 1 && (row % 2 == 0)) {  // Kolumny od 0 do numDays-1 i wiersze parzyste
        QString lineNumber = ui->shiftPlanTable->item(row, col)->text();

        if (!lineNumber.isEmpty()) {
            // Konwertujemy numer linii na wielkie litery
            lineNumber = lineNumber.toUpper();

            // Sprawdzamy, czy ta linia już została wprowadzona w tym dniu
            for (int r = 0; r < ui->shiftPlanTable->rowCount(); r += 2) {
                if (r != row) {
                    QString existingLine = ui->shiftPlanTable->item(r, col)->text();
                    if ((existingLine == lineNumber) && existingLine != 'U') {
                        ui->shiftPlanTable->item(row, col)->setText("");
                        QMessageBox::warning(this, "Błąd", "Ta linia jest już przypisana w tym dniu.");
                        return;
                    }
                }
            }

            // Zaktualizowanie komórki z numerem linii
            ui->shiftPlanTable->item(row, col)->setText(lineNumber);
            QSqlQuery query;
            query.prepare("SELECT totalWorkTime FROM buslines WHERE lineid = :lineNumber");
            query.bindValue(":lineNumber", lineNumber);
            if (query.exec() && query.next()) {
                QString totalWorkTime = query.value(0).toString();
                if (!totalWorkTime.isEmpty()) {
                    QStringList timeParts = totalWorkTime.split(":");
                    if (timeParts.size() == 3) {
                        QString formattedTime = timeParts[0] + ":" + timeParts[1];
                        ui->shiftPlanTable->setItem(row + 1, col, new QTableWidgetItem(formattedTime));
                        updateTableDimensions();
                        // Przeliczenie sumy dla tego wiersza
                        calculateRowSum(row); // Zapewniamy natychmiastową aktualizację sumy po wpisaniu wartości
                    } else {
                        qDebug() << "Niepoprawny format czasu w bazie danych: " << totalWorkTime;
                    }
                }
            } else {
                qDebug() << "Błąd zapytania: " << query.lastError().text();
            }
        } else {
            // Jeżeli komórka jest pusta, to usuwamy czas z poniższej komórki
            ui->shiftPlanTable->setItem(row + 1, col, new QTableWidgetItem(""));
            updateTableDimensions();
            calculateRowSum(row);  // Aktualizacja sumy po usunięciu wartości
        }
    }
    else if (col < ui->shiftPlanTable->columnCount() - 1 && (row % 2 != 0)) {
        QString lineNumber = ui->shiftPlanTable->item(row-1, col)->text();
        if (!lineNumber.isEmpty()) {
            calculateRowSum(row-1);
        }
        else {
            // Jeżeli komórka jest pusta, to usuwamy czas z poniższej komórki
            ui->shiftPlanTable->setItem(row + 1, col, new QTableWidgetItem(""));
            calculateRowSum(row-1);  // Aktualizacja sumy po usunięciu wartości
        }
    }
}


void ShiftPlan::calculateRowSum(int row) {
    int numDays = ui->shiftPlanTable->columnCount() - 1; // liczba dni (kolumn) w tabeli

    int totalMinutes = 0;
    bool allEmpty = true;

    // Iteracja po wszystkich dniach w danym wierszu
    for (int col = 0; col < numDays; ++col) {
        QTableWidgetItem *item = ui->shiftPlanTable->item(row + 1, col); // Pobieramy komórkę poniżej

        if (item && !item->text().isEmpty()) {
            QString timeStr = item->text();
            QStringList timeParts = timeStr.split(":");

            if (timeParts.size() == 2) {
                bool ok;
                int hours = timeParts[0].toInt(&ok);
                int minutes = timeParts[1].toInt(&ok);

                if (ok) {
                    totalMinutes += (hours * 60 + minutes); // Przeliczamy na minuty
                    allEmpty = false;
                }
            }
        }
    }

    // Jeśli nie ma żadnych wartości, ustawiamy sumę na pustą
    if (allEmpty) {
        ui->shiftPlanTable->setItem(row + 1, numDays, new QTableWidgetItem(""));
    } else {
        // Przeliczamy na godziny i minuty
        int hours = totalMinutes / 60;
        int minutes = totalMinutes % 60;

        QString sumTime = QString::number(hours).rightJustified(2, '0') + ":" + QString::number(minutes).rightJustified(2, '0');
        ui->shiftPlanTable->setItem(row + 1, numDays, new QTableWidgetItem(sumTime));
    }
}

void ShiftPlan::on_saveButton_clicked()
{
    // Pobieranie ID grafiku z bazy danych (możesz to dostosować w zależności od swojej logiki)
    int shiftPlanID = getShiftPlanID(selectedYear, selectedMonth);

    // Sprawdzanie, czy ID grafiku jest prawidłowe
    if (shiftPlanID == -1) {
        qDebug() << "Błąd: Nie znaleziono grafiku o podanym roku i miesiącu.";
        return; // Zatrzymaj funkcję, jeśli ID grafiku jest niewłaściwe
    }

    // Sprawdzanie, czy istnieje już grafik o podanym shiftPlanID
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM ShiftPlansAssignments WHERE shiftPlanID = :shiftPlanID");
    checkQuery.bindValue(":shiftPlanID", shiftPlanID);

    if (!checkQuery.exec()) {
        qDebug() << "Błąd zapytania sprawdzającego istnienie grafiku: " << checkQuery.lastError().text();
        return;
    }

    checkQuery.next();
    int count = checkQuery.value(0).toInt();

    // Jeśli istnieją dane dla tego shiftPlanID, to je usuń
    if (count > 0) {
        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM ShiftPlansAssignments WHERE shiftPlanID = :shiftPlanID");
        deleteQuery.bindValue(":shiftPlanID", shiftPlanID);

        if (!deleteQuery.exec()) {
            qDebug() << "Błąd usuwania rekordów z tabeli ShiftPlansAssignments: " << deleteQuery.lastError().text();
            return; // Zatrzymaj, jeśli usunięcie nie powiodło się
        }
    }

    // Iteracja po wszystkich wierszach i kolumnach tabeli
    int numRows = ui->shiftPlanTable->rowCount();
    int numCols = ui->shiftPlanTable->columnCount() - 1; // Ostatnia kolumna to suma

    QSqlQuery query;
    query.prepare("INSERT INTO ShiftPlansAssignments (shiftPlanID, driverID, day, lineID, lineWorkTime, \"row\", col) "
                  "VALUES (:shiftPlanID, :driverID, :day, :lineID, :lineWorkTime, :row, :column)");

    for (int row = 0; row < numRows; row += 2) {  // Wiersze parzyste to kierowcy
        QString driverName = ui->shiftPlanTable->verticalHeaderItem(row)->text();
        int driverID = getDriverID(driverName);  // Funkcja pomocnicza do pobrania ID kierowcy

        for (int col = 0; col < numCols; ++col) {
            QString lineID = ui->shiftPlanTable->item(row, col)->text();  // Numer linii w danym dniu
            QString lineWorkTime = ui->shiftPlanTable->item(row + 1, col)->text();  // Czas pracy w danym dniu

            // Jeśli komórka zawiera dane (np. numer linii)
            if (!lineID.isEmpty() && !lineWorkTime.isEmpty()) {
                query.bindValue(":shiftPlanID", shiftPlanID);
                query.bindValue(":driverID", driverID);
                query.bindValue(":day", col + 1);  // Dzień w miesiącu (kolumna 0 to 1, kolumna 1 to 2, itd.)
                query.bindValue(":lineID", lineID);
                query.bindValue(":lineWorkTime", lineWorkTime);
                query.bindValue(":column", col);  // Zapisanie kolumny
                query.bindValue(":row", row);  // Zapisanie wiersza

                if (!query.exec()) {
                    qDebug() << "Błąd zapisu do bazy danych: " << query.lastError().text();
                }
            }
        }
    }

    query.prepare("SELECT id FROM schedules WHERE shiftplanid = :id");
    query.bindValue(":id", id);
    if(query.exec()){
        if(query.next()) {
            int scheduleID = query.value(0).toInt();

            // Kopiowanie danych z tabeli shiftplansassignments do schedulesassignments
            QSqlQuery copyQuery;
            copyQuery.prepare("DELETE FROM schedulesassignments WHERE scheduleid = :id");
            copyQuery.bindValue(":id", scheduleID);
            copyQuery.exec();
            copyQuery.prepare("INSERT INTO schedulesassignments (scheduleid, driverid, day, lineid) "
                              "SELECT :scheduleid, driverid, day, lineid "
                              "FROM shiftplansassignments "
                              "WHERE shiftplanid = :shiftplanid");

            // Ustawienie parametrów zapytania
            copyQuery.bindValue(":scheduleid", scheduleID);
            copyQuery.bindValue(":shiftplanid", id);

            if (!copyQuery.exec()) {
                qDebug() << "Błąd przy kopiowaniu danych do schedulesassignments: " << copyQuery.lastError().text();
            } else {
                qDebug() << "Dane skopiowane do schedulesassignments pomyślnie!";
            }


        }
    } else {
        qDebug() << "Błąd zapytania SQL: " << query.lastError();
    }

    query.prepare("UPDATE shitplans SET modified_by = :id");
    query.bindValue(":id", id);
    query.exec();


    // Potwierdzenie zapisu
    qDebug() << "Grafik zapisany do bazy danych.";
}



int ShiftPlan::getShiftPlanID(int year, int month)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM ShiftPlans WHERE year = :year AND month = :month");
    query.bindValue(":year", year);
    query.bindValue(":month", month);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        qDebug() << "Błąd pobierania ID grafiku: " << query.lastError().text();
        return -1;  // Zwróć -1, jeśli nie znaleziono grafiku
    }
}

int ShiftPlan::getDriverID(const QString &driverName)
{
    QString capitalizedDriverName = driverName;
    if (!capitalizedDriverName.isEmpty()) {
        capitalizedDriverName[0] = capitalizedDriverName[0].toUpper();  // Pierwsza litera na dużą
        capitalizedDriverName = capitalizedDriverName.toLower();  // Cały tekst na małe litery
        capitalizedDriverName[0] = capitalizedDriverName[0].toUpper();  // Ponownie pierwsza litera na dużą
    }

    QSqlQuery query;
    query.prepare("SELECT driverID FROM drivers WHERE surname = :surname");
    query.bindValue(":surname", capitalizedDriverName);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        qDebug() << "Błąd pobierania ID kierowcy: " << query.lastError().text();
        return -1;  // Zwróć -1, jeśli nie znaleziono kierowcy
    }
}

void ShiftPlan::loadShiftPlanData() {
    updateTableDimensions();
    int numRows = ui->shiftPlanTable->rowCount() + 1;
    int numCols = ui->shiftPlanTable->columnCount() - 1; // Ostatnia kolumna to suma

    // Zaczynamy od pobrania danych z bazy
    QSqlQuery query;
    query.prepare("SELECT driverID, day, lineID, lineWorkTime, \"row\", \"col\" FROM ShiftPlansAssignments WHERE shiftPlanID = :shiftPlanID ORDER BY \"row\", \"col\"");
    query.bindValue(":shiftPlanID", id);

    if (!query.exec()) {
        qDebug() << "Błąd pobierania danych z bazy: " << query.lastError().text();
        return;
    }

    // Inicjalizacja zmiennych do przechowywania sumy czasu pracy dla każdego dnia
    QVector<QTime> totalWorkTimes(numCols, QTime(0, 0)); // Total work time dla każdego dnia w miesiącu

    // Iteracja po wynikach zapytania i wstawianie do tabeli
    while (query.next()) {
        int driverID = query.value("driverID").toInt();
        int day = query.value("day").toInt();
        QString lineID = query.value("lineID").toString();
        QString lineWorkTime = query.value("lineWorkTime").toString();
        int row = query.value("row").toInt();
        int col = query.value("col").toInt();

        // Wstawianie numeru linii do odpowiedniej komórki
        QTableWidgetItem *lineItem = new QTableWidgetItem(lineID);
        ui->shiftPlanTable->setItem(row, col, lineItem);

        // Wstawianie czasu pracy do odpowiedniej komórki poniżej
        QTableWidgetItem *workTimeItem = new QTableWidgetItem(lineWorkTime);
        ui->shiftPlanTable->setItem(row + 1, col, workTimeItem);

        // Zliczanie całkowitego czasu pracy dla danego dnia
        QTime currentWorkTime = QTime::fromString(lineWorkTime, "hh:mm");
        if (currentWorkTime.isValid()) {
            totalWorkTimes[col] = totalWorkTimes[col].addSecs(currentWorkTime.hour() * 3600 + currentWorkTime.minute() * 60);
        }
    }

    // Wstawianie sumy czasu pracy dla każdego dnia poniżej tabeli (w wierszu totalWorkTime)
    for (int col = 0; col < numCols; ++col) {
        QTableWidgetItem *totalWorkTimeItem = new QTableWidgetItem(totalWorkTimes[col].toString("hh:mm"));
        ui->shiftPlanTable->setItem(numRows - 1, col, totalWorkTimeItem); // Wiersz poniżej grafiku
    }

    // Potwierdzenie załadowania danych
    qDebug() << "Dane grafiku załadowane do tabeli.";
}

void ShiftPlan::on_clearButton_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM ShiftPlansAssignments WHERE shiftplanid = :shiftPlanID");
    query.bindValue(":shiftPlanID", id);

    if (!query.exec()) {
        qDebug() << "Błąd podczas usuwania danych: " << query.lastError().text();
        return;
    }

    // Po usunięciu danych, zaktualizuj wygląd tabeli
    ui->shiftPlanTable->clearContents();
    loadShiftPlanData();  // Ponownie ładujemy dane do tabeli

    qDebug() << "Rekordy zostały usunięte i tabela została zaktualizowana.";
}

void ShiftPlan::closeEvent(QCloseEvent *event)
{
    // Zatrzymanie timera autosave przed zamknięciem okna
    autoSaveTimer->stop();

    // Kontynuowanie normalnego zamykania okna
    event->accept();
}

void ShiftPlan::on_exportToPDFButton_clicked()
{
    QPrinter printer;
    printer.setPrinterName("Printer");
    printer.setPageSize(QPageSize(QPageSize::A4)); // Ustawienie rozmiaru A4
    printer.setResolution(300); // Ustawienie wysokiej rozdzielczości (300 DPI)
    printer.setPageOrientation(QPageLayout::Landscape); // Ustawienie orientacji poziomej (landscape)

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

    // Przygotowanie rozmiaru tabeli
    QSize tableSize = ui->shiftPlanTable->size();

    // Obliczenie skali, aby tabela wypełniała całą stronę
    double scaleX = static_cast<double>(pageSize.width()) / tableSize.width();
    double scaleY = static_cast<double>(pageSize.height()) / tableSize.height();
    double scale = qMin(scaleX, scaleY); // Skalowanie proporcjonalne, aby tabela zmieściła się na stronie

    // Tworzenie obrazu o wyższej rozdzielczości (zgodnej z rozdzielczością drukarki)
    int dpi = printer.resolution();  // 300 DPI
    QSize imageSize = tableSize * dpi / 72;  // Ustal rozmiar obrazu w pikselach przy 300 DPI
    QImage image(imageSize, QImage::Format_ARGB32_Premultiplied);
    image.setDevicePixelRatio(dpi / 72.0);  // Współczynnik rozdzielczości

    // Przygotowanie QPainter dla obrazu
    QPainter imagePainter(&image);
    imagePainter.setRenderHint(QPainter::Antialiasing); // Lepsza jakość
    imagePainter.setRenderHint(QPainter::TextAntialiasing);

    // Renderowanie tabeli na QImage
    ui->shiftPlanTable->render(&imagePainter);
    imagePainter.end();

    // Zastosowanie skali, aby tabela wypełniała jak największy obszar strony
    painter.scale(scale, scale);

    // Rysowanie obrazu na stronie
    painter.drawImage(QPoint(0, 0), image);

    // Zakończenie malowania
    painter.end();
}
