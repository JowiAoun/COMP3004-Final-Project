QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += /usr/include/boost/

LIBS += -lboost_serialization

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    control.cpp \
    hardware.cpp \
    healthData.cpp \
    qcustomplot.cpp \
    rawHealthData.cpp \
    user.cpp

HEADERS += \
    MainWindow.h \
    control.h \
    hardware.h \
    healthData.h \
    qcustomplot.h \
    rawHealthData.h \
    user.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/resources.qrc
