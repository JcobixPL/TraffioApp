#ifndef CREATESHORTENEDSCHEDULEDIALOG_H
#define CREATESHORTENEDSCHEDULEDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

namespace Ui {
class CreateShortenedScheduleDialog;
}

class CreateShortenedScheduleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateShortenedScheduleDialog(QWidget *parent = nullptr);
    ~CreateShortenedScheduleDialog();
    int getChosenShiftPlan() const;

private:
    Ui::CreateShortenedScheduleDialog *ui;
    void initializeComboBox();
};

#endif // CREATESHORTENEDSCHEDULEDIALOG_H
