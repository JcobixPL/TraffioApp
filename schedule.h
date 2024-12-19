#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QPageLayout>
#include <QPageSize>
#include <QPrintDialog>

namespace Ui {
class Schedule;
}

class Schedule : public QMainWindow
{
    Q_OBJECT

public:
    explicit Schedule(int scheduleID, QWidget *parent = nullptr);
    ~Schedule();

private slots:
    void on_exportToPDFButton_clicked();

private:
    Ui::Schedule *ui;
    void setupUI();
    void setupScheduleTable();
    void calculateVacationSum();
    QString formatTime(int totalMinutes);
    void setFullWorkTime();
    int getDriverID();
    int scheduleId;
};

#endif // SCHEDULE_H
