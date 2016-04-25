TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_LIBS += -lboost_unit_test_framework
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

SOURCES += \
    main.cpp \
    ../Runner/Bonus.cpp \
    ../Runner/Coin.cpp \
    ../Runner/Counter.cpp \
    ../Runner/Cube.cpp \
    ../Runner/Diamond.cpp \
    ../Runner/MovableElement.cpp \
    ../Runner/Obstacle.cpp \
    ../Runner/Player.cpp \
    ../Runner/AnimatedSprite.cpp

HEADERS += \
    ../Runner/Bonus.h \
    ../Runner/Coin.h \
    ../Runner/Counter.h \
    ../Runner/Cube.h \
    ../Runner/Diamond.h \
    ../Runner/MovableElement.h \
    ../Runner/Obstacle.h \
    ../Runner/Player.h \
    ../Runner/AnimatedSprite.h

