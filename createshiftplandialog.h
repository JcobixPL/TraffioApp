    #ifndef CREATESHIFTPLANDIALOG_H
#define CREATESHIFTPLANDIALOG_H

#include <QDateTime>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class createShiftPlanDialog;
}

class createShiftPlanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit createShiftPlanDialog(int userid, QWidget *parent = nullptr);
    ~createShiftPlanDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::createShiftPlanDialog *ui;

    void initializeComboBoxes();
    int userID;
    QStringList months;
};

#endif // CREATESHIFTPLANDIALOG_H
