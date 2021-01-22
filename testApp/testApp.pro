QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    driversGuiTests.cpp \
    systemTests.cpp \
    EventRecorderWidget.cpp \
    EventFilter.cpp

HEADERS  += mainwindow.h \
    driversGuiTests.h \
    systemTests.h \
    EventRecorderWidget.h \
    EventFilter.h

INCLUDEPATH +=../src/

CONFIG(debug, debug|release) {
    LIBS += -L../debug -lqspec
}

CONFIG(release, debug|release) {
    LIBS += -L../release -lqspec
}
