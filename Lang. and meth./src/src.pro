TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    scanner.cpp \
    diagram.cpp \
    semant.cpp \
    ll1.cpp

HEADERS += \
    scanner.h \
    defin.h \
    diagram.h \
    semant.h \
    ll1.h
