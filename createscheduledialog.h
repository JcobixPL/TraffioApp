#ifndef CREATESCHEDULEDIALOG_H
#define CREATESCHEDULEDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>


namespace Ui {
class CreateScheduleDialog;
}

class CreateScheduleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateScheduleDialog(QWidget *parent = nullptr);
    ~CreateScheduleDialog();
    int getChosenShiftPlan() const;

private:
    Ui::CreateScheduleDialog *ui;
    void initializeComboBox();
};

#endif // CREATESCHEDULEDIALOG_H
