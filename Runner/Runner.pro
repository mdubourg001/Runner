TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += main.cpp \
    Player.cpp \
    Bonus.cpp \
    Coin.cpp \
    Obstacle.cpp \
    Model.cpp \
    View.cpp \
    MovableElement.cpp \
    SlidingBackground.cpp \
    AnimatedSprite.cpp \
    Counter.cpp \
    Item.cpp \
    Preview.cpp \
    Diamond.cpp \
    Cube.cpp \
    Button.cpp \
    Popup.cpp \
    utils.cpp

HEADERS += \
    Player.h \
    Bonus.h \
    Coin.h \
    Obstacle.h \
    Model.h \
    View.h \
    main.h \
    MovableElement.h \
    SlidingBackground.h \
    AnimatedSprite.h \
    Counter.h \
    Item.h \
    Preview.h \
    Diamond.h \
    Cube.h \
    Button.h \
    Popup.h \
    utils.h
