TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    debugger.cpp \
    engine_config.cpp \
    assetsmanager.cpp \
    cfgparser.cpp \
    profiler.cpp \
    lua.cpp \
    gamestate.cpp \
    mainstate.cpp \
    renderwindow.cpp \
    gameengine.cpp \
    luafunctions.cpp \
    converter.cpp \
    map.cpp \
    editor.cpp

HEADERS += \
    debugger.h \
    engine_config.h \
    assetsmanager.h \
    cfgparser.h \
    profiler.h \
    lua.h \
    gamestate.h \
    mainstate.h \
    renderwindow.h \
    gameengine.h \
    luafunctions.h \
    converter.h \
    map.h \
    editor.h

LIBS += -L "/usr/local/lib" -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -llua

