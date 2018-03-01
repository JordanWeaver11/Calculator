CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
SOURCES += main.cpp \
    CalDialog.cpp \
    Calculator.cpp


QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -std=c++11
QT += widgets

QMAKE_CXXFLAGS += -Wmissing-include-dirs
QMAKE_CXXFLAGS += -Wfloat-equal
QMAKE_CXXFLAGS += -Wredundant-decls
QMAKE_CXXFLAGS += -Winit-self
QMAKE_CXXFLAGS += -Wshadow
QMAKE_CXXFLAGS += -Wconversion

# QMAKE_CXXFLAGS += -Werror
# QMAKE_CXXFLAGS += -Wno-error=unused-variable

QMAKE_CXXFLAGS += -pedantic
QMAKE_CXXFLAGS += -pedantic-errors

HEADERS += \
    CalDialog.h \
    Calculator.h

