TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_LIBS += -lboost_unit_test_framework

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

SOURCES += \
    main.cpp

