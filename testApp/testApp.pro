QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    driversGuiTests.cpp

HEADERS  += mainwindow.h \
    driversGuiTests.h

INCLUDEPATH +=../src/

CONFIG(debug, debug|release) {
    LIBS += -L../_build/debug -lqspecd
}

CONFIG(release, debug|release) {
    LIBS += -L../_build/release -lqspec
}
