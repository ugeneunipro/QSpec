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
    DEFINES += _DEBUG
    win32:LIBS += ../debug/qspec.lib
    else:LIBS += ../debug/libQSpec.so
    MOC_DIR=_tmp/moc/debug
    OBJECTS_DIR=_tmp/obj/debug
    DESTDIR=debug

    unix:{
        QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/../../debug\'"
    }
}

CONFIG(release, debug|release) {
    DEFINES+=NDEBUG
    win32:LIBS += ../release/qspec.lib
    else:LIBS += ../release/libQSpec.so
    MOC_DIR=_tmp/moc/release
    OBJECTS_DIR=_tmp/obj/release
    DESTDIR=release

    unix:{
        QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/../../release\'"
    }
}
