TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += main.cpp \
    Player.cpp \
    Bonus.cpp \
    Coin.cpp \
    Obstacle.cpp \
    Model.cpp \
    View.cpp \
    Time.cpp \
    Timer.cpp \
    MovableElement.cpp \
    Intro_View.cpp \
    Intro_Model.cpp \
    Menu_View.cpp \
    Menu_Model.cpp \
    SlidingBackground.cpp \
    AnimatedSprite.cpp

HEADERS += \
    Player.h \
    Bonus.h \
    Coin.h \
    Obstacle.h \
    Model.h \
    View.h \
    main.h \
    Time.h \
    Timer.h \
    MovableElement.h \
    Intro_View.h \
    Intro_Model.h \
    Menu_View.h \
    Menu_Model.h \
    SlidingBackground.h \
    AnimatedSprite.h
