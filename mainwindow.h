#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "createshiftplandialog.h"
#include "shiftplan.h"
#include "createscheduledialog.h"
#include "schedule.h"
#include "shortenedschedule.h"
#include "createshortenedscheduledialog.h"
#include "buslines.h"

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int userid, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dashboardButton_clicked();

    void on_workOrganizationButton_clicked();

    void on_addShiftPlanButton_clicked();

    void on_editShiftPlanButton_clicked();

    void on_addScheduleButton_clicked();

    void on_schedulesModuleButton_clicked();

    void on_shiftPlansModuleButton_clicked();

    void on_changeShiftPlanStatusButton_clicked();

    void on_editScheduleButton_clicked();

    void on_shortenedSchedulesModuleButton_clicked();

    void on_removeScheduleButton_clicked();

    void on_removeShiftPlanButton_clicked();

    void on_changeScheduleStatusButton_clicked();

    void on_addShortenedScheduleButton_clicked();

    void on_editShortenedScheduleButton_clicked();

    void on_busLinesButton_clicked();

    void on_addBusLineButton_clicked();

private:
    Ui::MainWindow *ui;

    int userID;

    void setupUI();
    void refreshDriversLinesTable();
    void refreshShiftPlans();
    void refreshShortenedSchedules();
    void refreshSchedules();
    void refreshBusLines();
};

#endif // MAINWINDOW_H
