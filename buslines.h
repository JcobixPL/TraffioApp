#ifndef BUSLINES_H
#define BUSLINES_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class BusLines;
}

class BusLines : public QDialog
{
    Q_OBJECT

public:
    explicit BusLines(QWidget *parent = nullptr);
    ~BusLines();

private slots:
    void on_addBusLineButton_clicked();

private:
    Ui::BusLines *ui;
};

#endif // BUSLINES_H
