cmake_minimum_required(VERSION 3.4)
project(qspec)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOMOC_MOC_OPTIONS -nn) # do not display notes.

find_package(Qt5 REQUIRED Core Gui Widgets Test WebKit WebKitWidgets)

include_directories(src)

file(GLOB_RECURSE SRCS src/*.cpp)
file(GLOB_RECURSE HDRS src/*.h)

add_library(qspec ${HDRS} ${SRCS})
set(APP_QT_LIBS Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Test Qt5::WebKit Qt5::WebKitWidgets)

target_link_libraries(qspec ${APP_QT_LIBS})
