include(../shared/shared.pri)

# QMAKE_CXX = gcc
# QMAKE_CXXFLAGS = -x c

TARGET = client
TEMPLATE = app

CONFIG(debug, debug|release) {
    CONFIG += debug
    QMAKE_CXXFLAGS = -g3 -O0 -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wpedantic
}

CONFIG(release, debug|release) {
    CONFIG += release
    QMAKE_CXXFLAGS = -g0 -O2 -std=c++11 -Wall -Werror -Wextra -Wpedantic
}

DESTDIR         = $${PWD}/build
DISTFILES       = $${PWD}/dist
DESTDIR_TARGET  = $${PWD}/dest
MOC_DIR         = $${OUT_PWD}/moc
OBJECTS_DIR     = $${OUT_PWD}/obj
UI_DIR          = $${OUT_PWD}/ui

CONFIG         += console
CONFIG         -= app_bundle
HEADERS        += $$files(include/*.h)
INCLUDEPATH    += include/
SOURCES        += $$files(src/*.cpp)
QT             -= core
QT             -= gui
