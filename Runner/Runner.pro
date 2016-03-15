TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += main.cpp \
    Window.cpp \
    Game.cpp \
    Player.cpp \
    Bonus.cpp \
    Coin.cpp \
    Obstacle.cpp \
    Background.cpp \
    Model.cpp \
    View.cpp \
    Time.cpp \
    Timer.cpp

HEADERS += \
    Window.h \
    Game.h \
    Player.h \
    Bonus.h \
    Coin.h \
    Obstacle.h \
    Background.h \
    Model.h \
    View.h \
    main.h \
    Time.h \
    Timer.h
