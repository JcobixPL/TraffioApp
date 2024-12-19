/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *menuLayout;
    QPushButton *dashboardButton;
    QPushButton *workOrganizationButton;
    QPushButton *busLinesButton;
    QPushButton *busesFleetButton;
    QPushButton *workshopServicesButton;
    QPushButton *rentsButton;
    QPushButton *dayOffsButton;
    QPushButton *reportsButton;
    QPushButton *notificationsButton;
    QPushButton *settingsButton;
    QPushButton *accountButton;
    QHBoxLayout *mainWindowLayout;
    QStackedWidget *stackedWidget;
    QWidget *dashboardPage;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *leftSideLayout;
    QHBoxLayout *horizontalLayout_2;
    QCalendarWidget *calendarWidget;
    QTableWidget *eventsTable;
    QVBoxLayout *eventsManagementLayout;
    QPushButton *addEventButton;
    QPushButton *editEventButton;
    QPushButton *removeEventButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *tablesLayout;
    QTableWidget *tableWidget_2;
    QTableWidget *driversLinesTable;
    QTableWidget *tableWidget_3;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *righSideLayout;
    QHBoxLayout *eventsLayout;
    QWidget *workOrganizationPage;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *driversTab;
    QGridLayout *gridLayout_3;
    QStackedWidget *driversTabStackedWidget;
    QWidget *shiftPlansPage;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *shiftPlansTable;
    QVBoxLayout *shiftPlanActivitiesLayout;
    QPushButton *addShiftPlanButton;
    QPushButton *editShiftPlanButton;
    QPushButton *removeShiftPlanButton;
    QPushButton *changeShiftPlanStatusButton;
    QSpacerItem *verticalSpacer_3;
    QWidget *schedulesPage;
    QHBoxLayout *horizontalLayout_4;
    QTableWidget *schedulesTable;
    QVBoxLayout *verticalLayout;
    QPushButton *addScheduleButton;
    QPushButton *editScheduleButton;
    QPushButton *removeScheduleButton;
    QPushButton *changeScheduleStatusButton;
    QSpacerItem *verticalSpacer_4;
    QWidget *shortenedSchedulesPage;
    QHBoxLayout *horizontalLayout_5;
    QTableWidget *shortenedSchedulesTable;
    QVBoxLayout *shortenedSchedulesActivitiesLayout;
    QPushButton *addShortenedScheduleButton;
    QPushButton *editShortenedScheduleButton;
    QPushButton *deleteShortenedScheduleButton;
    QPushButton *changeShortenedScheduleStatusButton;
    QSpacerItem *verticalSpacer_5;
    QWidget *workTimeRecordsPage;
    QWidget *workCardsPage;
    QVBoxLayout *workOrganizationModulesLayout;
    QPushButton *shiftPlansModuleButton;
    QPushButton *schedulesModuleButton;
    QPushButton *shortenedSchedulesModuleButton;
    QPushButton *workTimeRecordsModuleButton;
    QPushButton *workCardsModuleButton;
    QSpacerItem *verticalSpacer_2;
    QWidget *operationsStaffTab;
    QWidget *mechanicsTab;
    QWidget *cleaningStaff;
    QWidget *dailySummary;
    QWidget *busLinesPage;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QPushButton *busLinesPageButton;
    QPushButton *timetablesPageButton;
    QSpacerItem *verticalSpacer_6;
    QStackedWidget *stackedWidget_2;
    QWidget *page;
    QHBoxLayout *horizontalLayout_7;
    QTableWidget *busLinesTable;
    QVBoxLayout *verticalLayout_4;
    QPushButton *addBusLineButton;
    QPushButton *editBusLineButton;
    QPushButton *removeBusLineButton;
    QSpacerItem *verticalSpacer_7;
    QWidget *page_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1036, 778);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(1024, 768));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        menuLayout = new QHBoxLayout();
        menuLayout->setObjectName("menuLayout");
        dashboardButton = new QPushButton(centralwidget);
        dashboardButton->setObjectName("dashboardButton");

        menuLayout->addWidget(dashboardButton);

        workOrganizationButton = new QPushButton(centralwidget);
        workOrganizationButton->setObjectName("workOrganizationButton");

        menuLayout->addWidget(workOrganizationButton);

        busLinesButton = new QPushButton(centralwidget);
        busLinesButton->setObjectName("busLinesButton");

        menuLayout->addWidget(busLinesButton);

        busesFleetButton = new QPushButton(centralwidget);
        busesFleetButton->setObjectName("busesFleetButton");

        menuLayout->addWidget(busesFleetButton);

        workshopServicesButton = new QPushButton(centralwidget);
        workshopServicesButton->setObjectName("workshopServicesButton");

        menuLayout->addWidget(workshopServicesButton);

        rentsButton = new QPushButton(centralwidget);
        rentsButton->setObjectName("rentsButton");

        menuLayout->addWidget(rentsButton);

        dayOffsButton = new QPushButton(centralwidget);
        dayOffsButton->setObjectName("dayOffsButton");

        menuLayout->addWidget(dayOffsButton);

        reportsButton = new QPushButton(centralwidget);
        reportsButton->setObjectName("reportsButton");

        menuLayout->addWidget(reportsButton);

        notificationsButton = new QPushButton(centralwidget);
        notificationsButton->setObjectName("notificationsButton");

        menuLayout->addWidget(notificationsButton);

        settingsButton = new QPushButton(centralwidget);
        settingsButton->setObjectName("settingsButton");

        menuLayout->addWidget(settingsButton);

        accountButton = new QPushButton(centralwidget);
        accountButton->setObjectName("accountButton");

        menuLayout->addWidget(accountButton);


        verticalLayout_2->addLayout(menuLayout);

        mainWindowLayout = new QHBoxLayout();
        mainWindowLayout->setObjectName("mainWindowLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        dashboardPage = new QWidget();
        dashboardPage->setObjectName("dashboardPage");
        horizontalLayout = new QHBoxLayout(dashboardPage);
        horizontalLayout->setObjectName("horizontalLayout");
        leftSideLayout = new QVBoxLayout();
        leftSideLayout->setObjectName("leftSideLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        calendarWidget = new QCalendarWidget(dashboardPage);
        calendarWidget->setObjectName("calendarWidget");

        horizontalLayout_2->addWidget(calendarWidget);

        eventsTable = new QTableWidget(dashboardPage);
        eventsTable->setObjectName("eventsTable");

        horizontalLayout_2->addWidget(eventsTable);

        eventsManagementLayout = new QVBoxLayout();
        eventsManagementLayout->setObjectName("eventsManagementLayout");
        addEventButton = new QPushButton(dashboardPage);
        addEventButton->setObjectName("addEventButton");

        eventsManagementLayout->addWidget(addEventButton);

        editEventButton = new QPushButton(dashboardPage);
        editEventButton->setObjectName("editEventButton");

        eventsManagementLayout->addWidget(editEventButton);

        removeEventButton = new QPushButton(dashboardPage);
        removeEventButton->setObjectName("removeEventButton");

        eventsManagementLayout->addWidget(removeEventButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        eventsManagementLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(eventsManagementLayout);


        leftSideLayout->addLayout(horizontalLayout_2);

        tablesLayout = new QHBoxLayout();
        tablesLayout->setObjectName("tablesLayout");
        tableWidget_2 = new QTableWidget(dashboardPage);
        tableWidget_2->setObjectName("tableWidget_2");

        tablesLayout->addWidget(tableWidget_2);

        driversLinesTable = new QTableWidget(dashboardPage);
        driversLinesTable->setObjectName("driversLinesTable");

        tablesLayout->addWidget(driversLinesTable);

        tableWidget_3 = new QTableWidget(dashboardPage);
        tableWidget_3->setObjectName("tableWidget_3");

        tablesLayout->addWidget(tableWidget_3);


        leftSideLayout->addLayout(tablesLayout);


        horizontalLayout->addLayout(leftSideLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        righSideLayout = new QVBoxLayout();
        righSideLayout->setObjectName("righSideLayout");
        eventsLayout = new QHBoxLayout();
        eventsLayout->setObjectName("eventsLayout");

        righSideLayout->addLayout(eventsLayout);


        horizontalLayout->addLayout(righSideLayout);

        stackedWidget->addWidget(dashboardPage);
        workOrganizationPage = new QWidget();
        workOrganizationPage->setObjectName("workOrganizationPage");
        gridLayout_2 = new QGridLayout(workOrganizationPage);
        gridLayout_2->setObjectName("gridLayout_2");
        tabWidget = new QTabWidget(workOrganizationPage);
        tabWidget->setObjectName("tabWidget");
        driversTab = new QWidget();
        driversTab->setObjectName("driversTab");
        gridLayout_3 = new QGridLayout(driversTab);
        gridLayout_3->setObjectName("gridLayout_3");
        driversTabStackedWidget = new QStackedWidget(driversTab);
        driversTabStackedWidget->setObjectName("driversTabStackedWidget");
        shiftPlansPage = new QWidget();
        shiftPlansPage->setObjectName("shiftPlansPage");
        horizontalLayout_3 = new QHBoxLayout(shiftPlansPage);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        shiftPlansTable = new QTableWidget(shiftPlansPage);
        shiftPlansTable->setObjectName("shiftPlansTable");

        horizontalLayout_3->addWidget(shiftPlansTable);

        shiftPlanActivitiesLayout = new QVBoxLayout();
        shiftPlanActivitiesLayout->setObjectName("shiftPlanActivitiesLayout");
        addShiftPlanButton = new QPushButton(shiftPlansPage);
        addShiftPlanButton->setObjectName("addShiftPlanButton");

        shiftPlanActivitiesLayout->addWidget(addShiftPlanButton);

        editShiftPlanButton = new QPushButton(shiftPlansPage);
        editShiftPlanButton->setObjectName("editShiftPlanButton");

        shiftPlanActivitiesLayout->addWidget(editShiftPlanButton);

        removeShiftPlanButton = new QPushButton(shiftPlansPage);
        removeShiftPlanButton->setObjectName("removeShiftPlanButton");

        shiftPlanActivitiesLayout->addWidget(removeShiftPlanButton);

        changeShiftPlanStatusButton = new QPushButton(shiftPlansPage);
        changeShiftPlanStatusButton->setObjectName("changeShiftPlanStatusButton");

        shiftPlanActivitiesLayout->addWidget(changeShiftPlanStatusButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        shiftPlanActivitiesLayout->addItem(verticalSpacer_3);


        horizontalLayout_3->addLayout(shiftPlanActivitiesLayout);

        driversTabStackedWidget->addWidget(shiftPlansPage);
        schedulesPage = new QWidget();
        schedulesPage->setObjectName("schedulesPage");
        horizontalLayout_4 = new QHBoxLayout(schedulesPage);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        schedulesTable = new QTableWidget(schedulesPage);
        schedulesTable->setObjectName("schedulesTable");

        horizontalLayout_4->addWidget(schedulesTable);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        addScheduleButton = new QPushButton(schedulesPage);
        addScheduleButton->setObjectName("addScheduleButton");

        verticalLayout->addWidget(addScheduleButton);

        editScheduleButton = new QPushButton(schedulesPage);
        editScheduleButton->setObjectName("editScheduleButton");

        verticalLayout->addWidget(editScheduleButton);

        removeScheduleButton = new QPushButton(schedulesPage);
        removeScheduleButton->setObjectName("removeScheduleButton");

        verticalLayout->addWidget(removeScheduleButton);

        changeScheduleStatusButton = new QPushButton(schedulesPage);
        changeScheduleStatusButton->setObjectName("changeScheduleStatusButton");

        verticalLayout->addWidget(changeScheduleStatusButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout_4->addLayout(verticalLayout);

        driversTabStackedWidget->addWidget(schedulesPage);
        shortenedSchedulesPage = new QWidget();
        shortenedSchedulesPage->setObjectName("shortenedSchedulesPage");
        horizontalLayout_5 = new QHBoxLayout(shortenedSchedulesPage);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        shortenedSchedulesTable = new QTableWidget(shortenedSchedulesPage);
        shortenedSchedulesTable->setObjectName("shortenedSchedulesTable");

        horizontalLayout_5->addWidget(shortenedSchedulesTable);

        shortenedSchedulesActivitiesLayout = new QVBoxLayout();
        shortenedSchedulesActivitiesLayout->setObjectName("shortenedSchedulesActivitiesLayout");
        addShortenedScheduleButton = new QPushButton(shortenedSchedulesPage);
        addShortenedScheduleButton->setObjectName("addShortenedScheduleButton");

        shortenedSchedulesActivitiesLayout->addWidget(addShortenedScheduleButton);

        editShortenedScheduleButton = new QPushButton(shortenedSchedulesPage);
        editShortenedScheduleButton->setObjectName("editShortenedScheduleButton");

        shortenedSchedulesActivitiesLayout->addWidget(editShortenedScheduleButton);

        deleteShortenedScheduleButton = new QPushButton(shortenedSchedulesPage);
        deleteShortenedScheduleButton->setObjectName("deleteShortenedScheduleButton");

        shortenedSchedulesActivitiesLayout->addWidget(deleteShortenedScheduleButton);

        changeShortenedScheduleStatusButton = new QPushButton(shortenedSchedulesPage);
        changeShortenedScheduleStatusButton->setObjectName("changeShortenedScheduleStatusButton");

        shortenedSchedulesActivitiesLayout->addWidget(changeShortenedScheduleStatusButton);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        shortenedSchedulesActivitiesLayout->addItem(verticalSpacer_5);


        horizontalLayout_5->addLayout(shortenedSchedulesActivitiesLayout);

        driversTabStackedWidget->addWidget(shortenedSchedulesPage);
        workTimeRecordsPage = new QWidget();
        workTimeRecordsPage->setObjectName("workTimeRecordsPage");
        driversTabStackedWidget->addWidget(workTimeRecordsPage);
        workCardsPage = new QWidget();
        workCardsPage->setObjectName("workCardsPage");
        driversTabStackedWidget->addWidget(workCardsPage);

        gridLayout_3->addWidget(driversTabStackedWidget, 0, 1, 1, 1);

        workOrganizationModulesLayout = new QVBoxLayout();
        workOrganizationModulesLayout->setObjectName("workOrganizationModulesLayout");
        shiftPlansModuleButton = new QPushButton(driversTab);
        shiftPlansModuleButton->setObjectName("shiftPlansModuleButton");

        workOrganizationModulesLayout->addWidget(shiftPlansModuleButton);

        schedulesModuleButton = new QPushButton(driversTab);
        schedulesModuleButton->setObjectName("schedulesModuleButton");

        workOrganizationModulesLayout->addWidget(schedulesModuleButton);

        shortenedSchedulesModuleButton = new QPushButton(driversTab);
        shortenedSchedulesModuleButton->setObjectName("shortenedSchedulesModuleButton");

        workOrganizationModulesLayout->addWidget(shortenedSchedulesModuleButton);

        workTimeRecordsModuleButton = new QPushButton(driversTab);
        workTimeRecordsModuleButton->setObjectName("workTimeRecordsModuleButton");

        workOrganizationModulesLayout->addWidget(workTimeRecordsModuleButton);

        workCardsModuleButton = new QPushButton(driversTab);
        workCardsModuleButton->setObjectName("workCardsModuleButton");

        workOrganizationModulesLayout->addWidget(workCardsModuleButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        workOrganizationModulesLayout->addItem(verticalSpacer_2);


        gridLayout_3->addLayout(workOrganizationModulesLayout, 0, 0, 1, 1);

        tabWidget->addTab(driversTab, QString());
        operationsStaffTab = new QWidget();
        operationsStaffTab->setObjectName("operationsStaffTab");
        tabWidget->addTab(operationsStaffTab, QString());
        mechanicsTab = new QWidget();
        mechanicsTab->setObjectName("mechanicsTab");
        tabWidget->addTab(mechanicsTab, QString());
        cleaningStaff = new QWidget();
        cleaningStaff->setObjectName("cleaningStaff");
        tabWidget->addTab(cleaningStaff, QString());
        dailySummary = new QWidget();
        dailySummary->setObjectName("dailySummary");
        tabWidget->addTab(dailySummary, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(workOrganizationPage);
        busLinesPage = new QWidget();
        busLinesPage->setObjectName("busLinesPage");
        horizontalLayout_6 = new QHBoxLayout(busLinesPage);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        busLinesPageButton = new QPushButton(busLinesPage);
        busLinesPageButton->setObjectName("busLinesPageButton");

        verticalLayout_3->addWidget(busLinesPageButton);

        timetablesPageButton = new QPushButton(busLinesPage);
        timetablesPageButton->setObjectName("timetablesPageButton");

        verticalLayout_3->addWidget(timetablesPageButton);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_6);


        horizontalLayout_6->addLayout(verticalLayout_3);

        stackedWidget_2 = new QStackedWidget(busLinesPage);
        stackedWidget_2->setObjectName("stackedWidget_2");
        page = new QWidget();
        page->setObjectName("page");
        horizontalLayout_7 = new QHBoxLayout(page);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        busLinesTable = new QTableWidget(page);
        busLinesTable->setObjectName("busLinesTable");

        horizontalLayout_7->addWidget(busLinesTable);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        addBusLineButton = new QPushButton(page);
        addBusLineButton->setObjectName("addBusLineButton");

        verticalLayout_4->addWidget(addBusLineButton);

        editBusLineButton = new QPushButton(page);
        editBusLineButton->setObjectName("editBusLineButton");

        verticalLayout_4->addWidget(editBusLineButton);

        removeBusLineButton = new QPushButton(page);
        removeBusLineButton->setObjectName("removeBusLineButton");

        verticalLayout_4->addWidget(removeBusLineButton);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_7);


        horizontalLayout_7->addLayout(verticalLayout_4);

        stackedWidget_2->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget_2->addWidget(page_2);

        horizontalLayout_6->addWidget(stackedWidget_2);

        stackedWidget->addWidget(busLinesPage);

        mainWindowLayout->addWidget(stackedWidget);


        verticalLayout_2->addLayout(mainWindowLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        dashboardButton->setText(QCoreApplication::translate("MainWindow", "DASHBOARD", nullptr));
        workOrganizationButton->setText(QCoreApplication::translate("MainWindow", "ORGANIZACJA PRACY", nullptr));
        busLinesButton->setText(QCoreApplication::translate("MainWindow", "LINIE", nullptr));
        busesFleetButton->setText(QCoreApplication::translate("MainWindow", "FLOTA", nullptr));
        workshopServicesButton->setText(QCoreApplication::translate("MainWindow", "WARSZTAT", nullptr));
        rentsButton->setText(QCoreApplication::translate("MainWindow", "WYNAJMY", nullptr));
        dayOffsButton->setText(QCoreApplication::translate("MainWindow", "URLOPY I DNI WOLNE", nullptr));
        reportsButton->setText(QCoreApplication::translate("MainWindow", "RAPORTY", nullptr));
        notificationsButton->setText(QCoreApplication::translate("MainWindow", "POWIADOMIENIA", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "USTAWIENIA", nullptr));
        accountButton->setText(QCoreApplication::translate("MainWindow", "KONTO", nullptr));
        addEventButton->setText(QCoreApplication::translate("MainWindow", "DODAJ", nullptr));
        editEventButton->setText(QCoreApplication::translate("MainWindow", "EDYTUJ", nullptr));
        removeEventButton->setText(QCoreApplication::translate("MainWindow", "USU\305\203", nullptr));
        addShiftPlanButton->setText(QCoreApplication::translate("MainWindow", "DODAJ", nullptr));
        editShiftPlanButton->setText(QCoreApplication::translate("MainWindow", "EDYTUJ", nullptr));
        removeShiftPlanButton->setText(QCoreApplication::translate("MainWindow", "USU\305\203", nullptr));
        changeShiftPlanStatusButton->setText(QCoreApplication::translate("MainWindow", "ZMIE\305\203 STATUS", nullptr));
        addScheduleButton->setText(QCoreApplication::translate("MainWindow", "DODAJ", nullptr));
        editScheduleButton->setText(QCoreApplication::translate("MainWindow", "EDYTUJ", nullptr));
        removeScheduleButton->setText(QCoreApplication::translate("MainWindow", "USU\305\203", nullptr));
        changeScheduleStatusButton->setText(QCoreApplication::translate("MainWindow", "ZMIE\305\203 STATUS", nullptr));
        addShortenedScheduleButton->setText(QCoreApplication::translate("MainWindow", "DODAJ", nullptr));
        editShortenedScheduleButton->setText(QCoreApplication::translate("MainWindow", "EDYTUJ", nullptr));
        deleteShortenedScheduleButton->setText(QCoreApplication::translate("MainWindow", "USU\305\203", nullptr));
        changeShortenedScheduleStatusButton->setText(QCoreApplication::translate("MainWindow", "ZMIE\305\203 STATUS", nullptr));
        shiftPlansModuleButton->setText(QCoreApplication::translate("MainWindow", "GRAFIKI", nullptr));
        schedulesModuleButton->setText(QCoreApplication::translate("MainWindow", "HARMONOGRAMY", nullptr));
        shortenedSchedulesModuleButton->setText(QCoreApplication::translate("MainWindow", "SKR\303\223CONE HARMONOGRAMY", nullptr));
        workTimeRecordsModuleButton->setText(QCoreApplication::translate("MainWindow", "EWIDENCJA CZASU PRACY", nullptr));
        workCardsModuleButton->setText(QCoreApplication::translate("MainWindow", "KARTY PRACY", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(driversTab), QCoreApplication::translate("MainWindow", "Kierowcy", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(operationsStaffTab), QCoreApplication::translate("MainWindow", "S\305\202u\305\274by eksploatacyjne", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(mechanicsTab), QCoreApplication::translate("MainWindow", "Mechanicy", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(cleaningStaff), QCoreApplication::translate("MainWindow", "Personel sprz\304\205taj\304\205cy", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(dailySummary), QCoreApplication::translate("MainWindow", "Podsumowanie dzienne", nullptr));
        busLinesPageButton->setText(QCoreApplication::translate("MainWindow", "LINIE", nullptr));
        timetablesPageButton->setText(QCoreApplication::translate("MainWindow", "ROZK\305\201AD JAZDY", nullptr));
        addBusLineButton->setText(QCoreApplication::translate("MainWindow", "DODAJ", nullptr));
        editBusLineButton->setText(QCoreApplication::translate("MainWindow", "EDYTUJ", nullptr));
        removeBusLineButton->setText(QCoreApplication::translate("MainWindow", "USU\305\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
