#ifndef SHORTENEDSCHEDULE_H
#define SHORTENEDSCHEDULE_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

namespace Ui {
class ShortenedSchedule;
}

class ShortenedSchedule : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShortenedSchedule(int shortenedScheduleID, QWidget *parent = nullptr);
    ~ShortenedSchedule();

private:
    Ui::ShortenedSchedule *ui;
    int shortenedScheduleID;
    void setupUI();
};

#endif // SHORTENEDSCHEDULE_H
