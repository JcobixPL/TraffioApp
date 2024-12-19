/********************************************************************************
** Form generated from reading UI file 'buslines.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUSLINES_H
#define UI_BUSLINES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BusLines
{
public:
    QGridLayout *gridLayout;
    QLabel *titleLabel;
    QStackedWidget *stackedWidget;
    QWidget *createBusLinePage;
    QVBoxLayout *verticalLayout_2;
    QLabel *linegroupLabel;
    QTextEdit *textEdit;
    QLabel *lineIdLabel;
    QTextEdit *lineIdTextEdit;
    QLabel *startTimeLabel;
    QTimeEdit *startTimeTimeEdit;
    QLabel *endTimeLabel;
    QTimeEdit *endTimeTimeEdit;
    QLabel *drivingTimeLabel;
    QTimeEdit *drivingTimeTimeEdit;
    QLabel *breaksAbove15MinLabel;
    QTimeEdit *breaksAbove15MinTimeEdit;
    QLabel *countBreaksAbove15MinLabel;
    QSpinBox *countBreaksAbove15MinTimeEdit;
    QLabel *otherBreaksAndWorkLabel;
    QTimeEdit *otherBreaksAndWorkTimeEdit;
    QLabel *ocLabel;
    QTimeEdit *ocTimeEdit;
    QLabel *totalWorkTimeLabel;
    QTimeEdit *totalWorkTimeTimeEdit;
    QPushButton *addBusLineButton;
    QWidget *editBusLinePage;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *BusLines)
    {
        if (BusLines->objectName().isEmpty())
            BusLines->setObjectName("BusLines");
        BusLines->resize(444, 660);
        gridLayout = new QGridLayout(BusLines);
        gridLayout->setObjectName("gridLayout");
        titleLabel = new QLabel(BusLines);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(titleLabel, 1, 0, 1, 1);

        stackedWidget = new QStackedWidget(BusLines);
        stackedWidget->setObjectName("stackedWidget");
        createBusLinePage = new QWidget();
        createBusLinePage->setObjectName("createBusLinePage");
        verticalLayout_2 = new QVBoxLayout(createBusLinePage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        linegroupLabel = new QLabel(createBusLinePage);
        linegroupLabel->setObjectName("linegroupLabel");

        verticalLayout_2->addWidget(linegroupLabel);

        textEdit = new QTextEdit(createBusLinePage);
        textEdit->setObjectName("textEdit");

        verticalLayout_2->addWidget(textEdit);

        lineIdLabel = new QLabel(createBusLinePage);
        lineIdLabel->setObjectName("lineIdLabel");

        verticalLayout_2->addWidget(lineIdLabel);

        lineIdTextEdit = new QTextEdit(createBusLinePage);
        lineIdTextEdit->setObjectName("lineIdTextEdit");
        lineIdTextEdit->setMaximumSize(QSize(393, 22));

        verticalLayout_2->addWidget(lineIdTextEdit);

        startTimeLabel = new QLabel(createBusLinePage);
        startTimeLabel->setObjectName("startTimeLabel");

        verticalLayout_2->addWidget(startTimeLabel);

        startTimeTimeEdit = new QTimeEdit(createBusLinePage);
        startTimeTimeEdit->setObjectName("startTimeTimeEdit");
        startTimeTimeEdit->setCorrectionMode(QAbstractSpinBox::CorrectionMode::CorrectToNearestValue);
        startTimeTimeEdit->setKeyboardTracking(true);
        startTimeTimeEdit->setProperty("showGroupSeparator", QVariant(false));
        startTimeTimeEdit->setMaximumDateTime(QDateTime(QDate(2000, 1, 1), QTime(22, 59, 59)));
        startTimeTimeEdit->setCurrentSection(QDateTimeEdit::Section::HourSection);
        startTimeTimeEdit->setCalendarPopup(false);
        startTimeTimeEdit->setTimeSpec(Qt::TimeSpec::UTC);
        startTimeTimeEdit->setTime(QTime(0, 0, 0));

        verticalLayout_2->addWidget(startTimeTimeEdit);

        endTimeLabel = new QLabel(createBusLinePage);
        endTimeLabel->setObjectName("endTimeLabel");

        verticalLayout_2->addWidget(endTimeLabel);

        endTimeTimeEdit = new QTimeEdit(createBusLinePage);
        endTimeTimeEdit->setObjectName("endTimeTimeEdit");

        verticalLayout_2->addWidget(endTimeTimeEdit);

        drivingTimeLabel = new QLabel(createBusLinePage);
        drivingTimeLabel->setObjectName("drivingTimeLabel");

        verticalLayout_2->addWidget(drivingTimeLabel);

        drivingTimeTimeEdit = new QTimeEdit(createBusLinePage);
        drivingTimeTimeEdit->setObjectName("drivingTimeTimeEdit");

        verticalLayout_2->addWidget(drivingTimeTimeEdit);

        breaksAbove15MinLabel = new QLabel(createBusLinePage);
        breaksAbove15MinLabel->setObjectName("breaksAbove15MinLabel");

        verticalLayout_2->addWidget(breaksAbove15MinLabel);

        breaksAbove15MinTimeEdit = new QTimeEdit(createBusLinePage);
        breaksAbove15MinTimeEdit->setObjectName("breaksAbove15MinTimeEdit");

        verticalLayout_2->addWidget(breaksAbove15MinTimeEdit);

        countBreaksAbove15MinLabel = new QLabel(createBusLinePage);
        countBreaksAbove15MinLabel->setObjectName("countBreaksAbove15MinLabel");

        verticalLayout_2->addWidget(countBreaksAbove15MinLabel);

        countBreaksAbove15MinTimeEdit = new QSpinBox(createBusLinePage);
        countBreaksAbove15MinTimeEdit->setObjectName("countBreaksAbove15MinTimeEdit");

        verticalLayout_2->addWidget(countBreaksAbove15MinTimeEdit);

        otherBreaksAndWorkLabel = new QLabel(createBusLinePage);
        otherBreaksAndWorkLabel->setObjectName("otherBreaksAndWorkLabel");

        verticalLayout_2->addWidget(otherBreaksAndWorkLabel);

        otherBreaksAndWorkTimeEdit = new QTimeEdit(createBusLinePage);
        otherBreaksAndWorkTimeEdit->setObjectName("otherBreaksAndWorkTimeEdit");

        verticalLayout_2->addWidget(otherBreaksAndWorkTimeEdit);

        ocLabel = new QLabel(createBusLinePage);
        ocLabel->setObjectName("ocLabel");

        verticalLayout_2->addWidget(ocLabel);

        ocTimeEdit = new QTimeEdit(createBusLinePage);
        ocTimeEdit->setObjectName("ocTimeEdit");

        verticalLayout_2->addWidget(ocTimeEdit);

        totalWorkTimeLabel = new QLabel(createBusLinePage);
        totalWorkTimeLabel->setObjectName("totalWorkTimeLabel");

        verticalLayout_2->addWidget(totalWorkTimeLabel);

        totalWorkTimeTimeEdit = new QTimeEdit(createBusLinePage);
        totalWorkTimeTimeEdit->setObjectName("totalWorkTimeTimeEdit");

        verticalLayout_2->addWidget(totalWorkTimeTimeEdit);

        addBusLineButton = new QPushButton(createBusLinePage);
        addBusLineButton->setObjectName("addBusLineButton");

        verticalLayout_2->addWidget(addBusLineButton);

        stackedWidget->addWidget(createBusLinePage);
        editBusLinePage = new QWidget();
        editBusLinePage->setObjectName("editBusLinePage");
        stackedWidget->addWidget(editBusLinePage);

        gridLayout->addWidget(stackedWidget, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);


        retranslateUi(BusLines);

        QMetaObject::connectSlotsByName(BusLines);
    } // setupUi

    void retranslateUi(QDialog *BusLines)
    {
        BusLines->setWindowTitle(QCoreApplication::translate("BusLines", "Dialog", nullptr));
        titleLabel->setText(QCoreApplication::translate("BusLines", "DODAWANIE NOWEJ LINII", nullptr));
        linegroupLabel->setText(QCoreApplication::translate("BusLines", "NAZWA LINII", nullptr));
        lineIdLabel->setText(QCoreApplication::translate("BusLines", "NAZWA ZMIANY", nullptr));
        startTimeLabel->setText(QCoreApplication::translate("BusLines", "GODZINA ROZPOCZ\304\230CIA", nullptr));
        startTimeTimeEdit->setDisplayFormat(QCoreApplication::translate("BusLines", "HH:mm", nullptr));
        endTimeLabel->setText(QCoreApplication::translate("BusLines", "GODZINA ZAKO\305\203CZENIA", nullptr));
        drivingTimeLabel->setText(QCoreApplication::translate("BusLines", "CZAS JAZDY", nullptr));
        breaksAbove15MinLabel->setText(QCoreApplication::translate("BusLines", "PRZERWY POWY\305\273EJ 15 MINUT", nullptr));
        countBreaksAbove15MinLabel->setText(QCoreApplication::translate("BusLines", "ILO\305\232\304\206 PRZERW POWY\305\273EJ 15 MINUT", nullptr));
        otherBreaksAndWorkLabel->setText(QCoreApplication::translate("BusLines", "INNE PRZERWY I PRACA", nullptr));
        ocLabel->setText(QCoreApplication::translate("BusLines", "OC", nullptr));
        totalWorkTimeLabel->setText(QCoreApplication::translate("BusLines", "\305\201\304\204CZNY CZAS PRACY", nullptr));
        addBusLineButton->setText(QCoreApplication::translate("BusLines", "DODAJ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BusLines: public Ui_BusLines {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUSLINES_H
