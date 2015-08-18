TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
CONFIG += warn_off
CONFIG += c++11

OBJECTS_DIR = tmp

win32 {
    QMAKE_CXXFLAGS += -std=gnu++1y

    INCLUDEPATH += "C:\Program Files (x86)\SFML\include"
    INCLUDEPATH += "C:\Program Files (x86)\lua\include"

    LIBS += -L"C:\Program Files (x86)\SFML\lib" -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
    LIBS += -L"C:\Program Files (x86)\lua" -llua53
}

macx {
    QMAKE_CXX    += -std=c++11
    QMAKE_LFLAGS += -F/Library/Frameworks/

    INCLUDEPATH += /usr/include

    LIBS += -L "/usr/local/lib" -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -llua -ljpeg -framework freetype -framework ogg -framework FLAC -framework vorbis -framework vorbisenc -framework vorbisfile -framework OpenAL -framework CoreFoundation -framework CoreServices -framework Carbon -framework Cocoa -framework ApplicationServices -framework OpenGL -framework IOKit
}

SOURCES += main.cpp \
    Assets/Asset.cpp \
    Assets/AssetsManager.cpp \
    Assets/Texture.cpp \
    Helper/Log.cpp \
    Effects/Effects.cpp \
    Effects/Fade.cpp \
    Engine/GameState.cpp \
    Graphics/Drawable.cpp \
    GUI/GUI.cpp \
    GUI/GUIObject.cpp \
    GUI/TextObject.cpp \
    Helper/CFGParser.cpp \
    Helper/ID.cpp \
    Helper/Profiler.cpp \
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
    Assets/Sound.cpp \
    Effects/Strobe.cpp \
    Engine/GameStateManager.cpp \
    Engine/LoadingScreen.cpp \
    Events/Events.cpp

HEADERS += \
    Assets/Asset.h \
    Assets/AssetsManager.h \
    Assets/Texture.h \
    Helper/Log.h \
    Effects/Effects.h \
    Effects/Fade.h \
    Engine/GameState.h \
    Graphics/Drawable.h \
    GUI/GUI.h \
    GUI/GUIObject.h \
    GUI/TextObject.h \
    Helper/CFGParser.h \
    Helper/ID.h \
    Helper/Key.h \
    Helper/Profiler.h \
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
    Assets/Sound.h \
    Effects/Strobe.h \
    ThirdParty/sol/sol/debug.hpp \
    ThirdParty/sol/sol/default_construct.hpp \
    ThirdParty/sol/sol/demangle.hpp \
    ThirdParty/sol/sol/deprecate.hpp \
    ThirdParty/sol/sol/error.hpp \
    ThirdParty/sol/sol/function.hpp \
    ThirdParty/sol/sol/function_types.hpp \
    ThirdParty/sol/sol/object.hpp \
    ThirdParty/sol/sol/proxy.hpp \
    ThirdParty/sol/sol/reference.hpp \
    ThirdParty/sol/sol/resolve.hpp \
    ThirdParty/sol/sol/stack.hpp \
    ThirdParty/sol/sol/state.hpp \
    ThirdParty/sol/sol/table.hpp \
    ThirdParty/sol/sol/traits.hpp \
    ThirdParty/sol/sol/tuple.hpp \
    ThirdParty/sol/sol/types.hpp \
    ThirdParty/sol/sol/userdata.hpp \
    ThirdParty/sol/sol/userdata_traits.hpp \
    ThirdParty/sol/sol.hpp \
    Engine/GameStateManager.h \
    Engine/LoadingScreen.h \
    Events/Events.h

DISTFILES += \
    Documentation/init.txt \
    Documentation/events.txt \
    Documentation/lua_goal.txt

