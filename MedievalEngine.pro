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
    Assets/Asset.cpp \
    Assets/AssetsManager.cpp \
    Assets/Texture.cpp \
    Helper/Log.cpp \
    Effects/Effects.cpp \
    Effects/Fade.cpp \
    Engine/GameEngine.cpp \
    Engine/GameState.cpp \
    Engine/LuaState.cpp \
    Graphics/Drawable.cpp \
    GUI/GUI.cpp \
    GUI/GUIObject.cpp \
    GUI/TextObject.cpp \
    Helper/CFGParser.cpp \
    Helper/ID.cpp \
    Helper/Profiler.cpp \
    Lua/CallBack.cpp \
    Lua/LuaEngine.cpp \
    Lua/luafunctions.cpp \
    Helper/Data2.cpp \
    Helper/Vect2.cpp \
    Helper/Vect3.cpp \
    Graphics/WindowInfo.cpp \
    Graphics/Window.cpp \
    Helper/Dir.cpp \
    Helper/Color.cpp \
    Engine/MedievalEngine.cpp \
    Helper/ArgumentsParser.cpp \
    Assets/Sprite.cpp \
    Assets/Font.cpp \
    Assets/Text.cpp \
    Assets/SpriteAnimation.cpp \
    Tests/HelperTests.cpp \
    Assets/Music.cpp \
    Audio/Audible.cpp \
    Assets/Sound.cpp

HEADERS += \
    Assets/Asset.h \
    Assets/AssetsManager.h \
    Assets/Texture.h \
    Helper/Log.h \
    Effects/Effects.h \
    Effects/Fade.h \
    Engine/GameEngine.h \
    Engine/GameState.h \
    Engine/LuaState.h \
    Graphics/Drawable.h \
    GUI/GUI.h \
    GUI/GUIObject.h \
    GUI/TextObject.h \
    Helper/CFGParser.h \
    Helper/ID.h \
    Helper/Key.h \
    Helper/Profiler.h \
    Lua/CallBack.h \
    Lua/LuaEngine.h \
    Lua/luafunctions.h \
    Helper/Vect2.h \
    Helper/Vect3.h \
    Helper/Data2.h \
    Graphics/WindowInfo.h \
    Config.h \
    Headers.h \
    Graphics/Window.h \
    Helper/Dir.h \
    Helper/Color.h \
    Engine/MedievalEngine.h \
    Helper/ArgumentsParser.h \
    Assets/Sprite.h \
    LogInc.h \
    Assets/Font.h \
    Assets/Text.h \
    Assets/SpriteAnimation.h \
    ThirdParty/Catch.h \
    Assets/Music.h \
    Audio/Audible.h \
    Assets/Sound.h

