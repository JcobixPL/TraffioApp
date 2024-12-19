QT       += core gui sql pdf printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buslines.cpp \
    createscheduledialog.cpp \
    createshiftplandialog.cpp \
    createshortenedscheduledialog.cpp \
    main.cpp \
    authwindow.cpp \
    mainwindow.cpp \
    schedule.cpp \
    shiftplan.cpp \
    shortenedschedule.cpp

HEADERS += \
    authwindow.h \
    buslines.h \
    createscheduledialog.h \
    createshiftplandialog.h \
    createshortenedscheduledialog.h \
    mainwindow.h \
    schedule.h \
    shiftplan.h \
    shortenedschedule.h

FORMS += \
    authwindow.ui \
    buslines.ui \
    createscheduledialog.ui \
    createshiftplandialog.ui \
    createshortenedscheduledialog.ui \
    mainwindow.ui \
    schedule.ui \
    shiftplan.ui \
    shortenedschedule.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
