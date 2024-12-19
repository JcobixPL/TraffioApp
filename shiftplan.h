#ifndef SHIFTPLAN_H
#define SHIFTPLAN_H

#include "qtablewidget.h"
#include <QMainWindow>
#include <QPrintDialog>

namespace Ui {
class ShiftPlan;
}

class ShiftPlan : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShiftPlan(int id, QWidget *parent = nullptr);
    ~ShiftPlan();

private slots:
    void updateTableDimensions();
    void onCellChanged(int row, int col);
    void calculateRowSum(int row);

    void on_saveButton_clicked();

    void on_clearButton_clicked();

    void on_exportToPDFButton_clicked();

private:
    Ui::ShiftPlan *ui;
    int id;
    int selectedMonth;
    int selectedYear;
    int numDays;
    int numDrivers;
    QTimer *autoSaveTimer;
    void closeEvent(QCloseEvent *event);
    void loadShiftPlanData();
    void fillShiftPlanAssignments();
    QString getDriverNameById(int driverId);
    int getDriverRowIndex(const QString& driverSurname);
    int getShiftPlanID(int year, int month);
    int getDriverID(const QString &driverName);
    void on_hoursVisibilityCheckBox_toggled(bool checked);
};

#endif // SHIFTPLAN_H
