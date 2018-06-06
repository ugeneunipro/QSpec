# include (qspec.pri)

TARGET = QSpec
TEMPLATE = lib
CONFIG += debug_and_release
CONFIG += warn_on
QT += testlib webkitwidgets

DEFINES += BUILDING_QSPEC_DLL
DEFINES += QT_DLL

CONFIG(debug, debug|release) {
    TARGET = $${TARGET}d
    DEFINES += _DEBUG
    CONFIG +=console
    FLAVOR = debug
}

CONFIG(release, debug|release) {
    TARGET = $${TARGET}
    DEFINES+=NDEBUG
    FLAVOR = release
}

# Qt Build directories
PROJECT_ROOT =                      $${PWD}
BUILD_ROOT =                        $${PROJECT_ROOT}/_build/$${FLAVOR}
OBJECTS_DIR =                       $${BUILD_ROOT}/obj
MOC_DIR =                           $${BUILD_ROOT}/moc
UI_DIR =                            $${BUILD_ROOT}/ui
UI_HEADERS_DIR =                    $${BUILD_ROOT}/ui/include
UI_SOURCES_DIR =                    $${BUILD_ROOT}/ui/source
RCC_DIR =                           $${BUILD_ROOT}/rc
DESTDIR =                           $${BUILD_ROOT}

INCLUDEPATH += $${PROJECT_ROOT}/src


unix {
    !macx {
        LIBS += -lXtst
    }
    macx {
        QMAKE_LFLAGS += -framework ApplicationServices
        LIBS += -framework AppKit
    }
    target.path = $$UGENE_INSTALL_DIR/$$UGENE_RELATIVE_DESTDIR
    INSTALLS += target
}

win32 {
    QMAKE_TARGET_OS = xp
    QMAKE_MSVC_PROJECT_NAME=lib_3rd_qscore
    LIBS += User32.lib Gdi32.lib
    LIBS += psapi.lib Advapi32.lib
    DEFINES += "PSAPI_VERSION=1"
}

#Check minimal Qt version
# Taken from Qt Creator project files
defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
}