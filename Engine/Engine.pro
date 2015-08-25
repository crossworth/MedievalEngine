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
	Audio/Audible.cpp \
	Effects/Effects.cpp \
	Effects/Fade.cpp \
	Effects/Strobe.cpp \
	Engine/MedievalEngine.cpp \
	Events/Event.cpp \
	Events/Keyboard.cpp \
	Events/Mouse.cpp \
	GameState/GameState.cpp \
	GameState/GameStateManager.cpp \
	GameState/LoadingScreen.cpp \
	Graphics/Drawable.cpp \
	Graphics/Window.cpp \
	Graphics/WindowInfo.cpp \
	GUI/ButtonObject.cpp \
	GUI/GUI.cpp \
	GUI/GUIObject.cpp \
	GUI/ObjectWrapper.cpp \
	GUI/TextObject.cpp \
	GUI/TextScrollListObject.cpp \
	Helper/Area.cpp \
	Helper/ArgumentsParser.cpp \
	Helper/CFGParser.cpp \
	Helper/Clock.cpp \
	Helper/Color.cpp \
	Helper/ColorGradient.cpp \
	Helper/DATFile.cpp \
	Helper/Dir.cpp \
	Helper/Log.cpp \
	Helper/Profiler.cpp \
	Helper/Vect2.cpp \
	Helper/Vect3.cpp \
	Resources/Font.cpp \
	Resources/Music.cpp \
	Resources/Shape.cpp \
	Resources/Sound.cpp \
	Resources/Sprite.cpp \
	Resources/SpriteAnimation.cpp \
	Resources/Text.cpp \
	Resources/Texture.cpp \
    Resources/Resource.cpp \
    Resources/ResourceManager.cpp \
    Resources/ResourceIDGenerator.cpp \
    Helper/Kit.cpp

HEADERS += \
	Audio/Audible.h \
	Config.h \
	Effects/Effects.h \
	Effects/Fade.h \
	Effects/Strobe.h \
	Engine/MedievalEngine.h \
	Events/Event.h \
	Events/Keyboard.h \
	Events/Mouse.h \
	GameState/GameState.h \
	GameState/GameStateManager.h \
	GameState/LoadingScreen.h \
	Graphics/Drawable.h \
	Graphics/Window.h \
	Graphics/WindowInfo.h \
	GUI/ButtonObject.h \
	GUI/GUI.h \
	GUI/GUIObject.h \
	GUI/ObjectWrapper.h \
	GUI/TextObject.h \
	GUI/TextScrollListObject.h \
	Headers.h \
	Helper/Area.h \
	Helper/ArgumentsParser.h \
	Helper/CFGParser.h \
	Helper/Clock.h \
	Helper/Color.h \
	Helper/ColorGradient.h \
	Helper/DATFile.h \
	Helper/Dir.h \
	Helper/Log.h \
	Helper/Profiler.h \
	Helper/Types.h \
	Helper/Vect2.h \
	Helper/Vect3.h \
	LogInc.h \
	Resources/Font.h \
	Resources/Music.h \
	Resources/Shape.h \
	Resources/Sound.h \
	Resources/Sprite.h \
	Resources/SpriteAnimation.h \
	Resources/Text.h \
	Resources/Texture.h \
    Resources/Resource.h \
    Resources/ResourceManager.h \
    Resources/ResourceIDGenerator.h \
    Helper/Kit.h

DISTFILES += \
    Documentation/init.txt \
    Documentation/events.txt \
    Documentation/lua_goal.txt \
    Documentation/goals.txt \
    Documentation/Assets_file.txt \
    Documentation/Coding_standards.txt

