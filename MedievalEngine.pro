TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += warn_off

OBJECTS_DIR = tmp

win32 {
    QMAKE_CXXFLAGS += -std=gnu++1y

    INCLUDEPATH += "C:\Program Files (x86)\SFML\include"
    INCLUDEPATH += "C:\Program Files (x86)\lua\include"

    LIBS += -L"C:\Program Files (x86)\SFML\lib" -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
    LIBS += -L"C:\Program Files (x86)\lua" -llua53
}

macx {
    QMAKE_LFLAGS   += -F/Library/Frameworks/

    INCLUDEPATH += /usr/include

    LIBS += -L "/usr/local/lib" -lsfml-graphics-s -lsfml-audio-s -lsfml-window-s -lsfml-system-s -llua -ljpeg -framework freetype -framework ogg -framework FLAC -framework vorbis -framework vorbisenc -framework vorbisfile -framework OpenAL -framework CoreFoundation -framework CoreServices -framework Carbon -framework Cocoa -framework ApplicationServices -framework OpenGL -framework IOKit
}

SOURCES += main.cpp \
    luafunctions.cpp \
    TO.cpp \
    AssetsManager.cpp \
    GameEngine.cpp \
    CallBack.cpp \
    CFGParser.cpp \
    Debugger.cpp \
    Effects.cpp \
    Fade.cpp \
    GameState.cpp \
    LuaEngine.cpp \
    Profiler.cpp \
    RenderWindow.cpp \
    LuaState.cpp \
    GUI.cpp \
    GUIObject.cpp \
    TextObject.cpp \
    Drawable.cpp \
    ID.cpp \
    Asset.cpp

HEADERS += \
    luafunctions.h \
    TO.h \
    key.h \
    AssetsManager.h \
    GameEngine.h \
    CallBack.h \
    CFGParser.h \
    Config.h \
    Debugger.h \
    Effects.h \
    Fade.h \
    GameState.h \
    LuaEngine.h \
    LuaState.h \
    Profiler.h \
    RenderWindow.h \
    GUI.h \
    GUIObject.h \
    TextObject.h \
    Drawable.h \
    ID.h \
    Asset.h

