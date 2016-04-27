TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_LIBS += -lboost_unit_test_framework
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

SOURCES += \
    main.cpp \
    AnimatedSprite.cpp \
    Bonus.cpp \
    Coin.cpp \
    Counter.cpp \
    Cube.cpp \
    Diamond.cpp \
    Model.cpp \
    Obstacle.cpp \
    Player.cpp \
    MovableElement.cpp

HEADERS += \
    AnimatedSprite.h \
    Bonus.h \
    Coin.h \
    Counter.h \
    Cube.h \
    Diamond.h \
    Model.h \
    Obstacle.h \
    Player.h \
    main.h \
    MovableElement.h

DISTFILES +=

