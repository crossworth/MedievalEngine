TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
INCLUDEPATH += "C:\Program Files (x86)\SFML\include"
INCLUDEPATH += "C:\Program Files (x86)\lua\include"

SOURCES += main.cpp \
    debugger.cpp \
    assetsmanager.cpp \
    cfgparser.cpp \
    profiler.cpp \
    gamestate.cpp \
    renderwindow.cpp \
    gameengine.cpp \
    luafunctions.cpp \
    map.cpp \
    editor.cpp \
    texthandle.cpp \
    gui.cpp \
    TO.cpp \
    luaengine.cpp \
    luastate.cpp \
    effects.cpp \
    fade.cpp

HEADERS += \
    debugger.h \
    assetsmanager.h \
    cfgparser.h \
    profiler.h \
    gamestate.h \
    renderwindow.h \
    gameengine.h \
    luafunctions.h \
    map.h \
    editor.h \
    texthandle.h \
    gui.h \
    TO.h \
    config.h \
    luaengine.h \
    key.h \
    luastate.h \
    effects.h \
    fade.h

QMAKE_CXXFLAGS += -std=gnu++1y
LIBS += -L"C:\Program Files (x86)\SFML\lib" -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
LIBS += -L"C:\Program Files (x86)\lua" -llua53
