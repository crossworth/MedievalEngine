# MedievalEngine 2016 - Auto Generated Makefile
# Pedro Henrique - system.pedrohenrique@gmail.com

PATH_SOURCE_FILES = /Volumes/Arquivos/Projects/MedievalEngine/src

CC         = clang++
CFLAGS     = -g -Wall -Wno-switch -O0 -std=c++14
INCLUDES   = -I $(PATH_SOURCE_FILES) -I /usr/local/lib  -I $(PATH_SOURCE_FILES)/extlibs
LFLAGS     = -L /usr/local/lib 
LIBS       = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-network -llua
FRAMEWORKS = -framework Cocoa

SRC_FILES   = $(PATH_SOURCE_FILES)/Audio/Audible.cpp $(PATH_SOURCE_FILES)/Effects/Fade.cpp $(PATH_SOURCE_FILES)/Effects/Shader.cpp $(PATH_SOURCE_FILES)/Effects/Strobe.cpp $(PATH_SOURCE_FILES)/Effects/Effect.cpp $(PATH_SOURCE_FILES)/Engine/MedievalEngine.cpp $(PATH_SOURCE_FILES)/Events/Keyboard.cpp $(PATH_SOURCE_FILES)/Events/Mouse.cpp $(PATH_SOURCE_FILES)/Events/Event.cpp $(PATH_SOURCE_FILES)/GUI/GUI.cpp $(PATH_SOURCE_FILES)/GUI/GUIEvent.cpp $(PATH_SOURCE_FILES)/GUI/TextListWidget.cpp $(PATH_SOURCE_FILES)/GUI/TextWidget.cpp $(PATH_SOURCE_FILES)/GUI/Widget.cpp $(PATH_SOURCE_FILES)/GUI/ButtonWidget.cpp $(PATH_SOURCE_FILES)/GameState/LoadingScreen.cpp $(PATH_SOURCE_FILES)/GameState/MenuScreen.cpp $(PATH_SOURCE_FILES)/GameState/OptionsScreen.cpp $(PATH_SOURCE_FILES)/GameState/GameState.cpp $(PATH_SOURCE_FILES)/GameState/GameStateManager.cpp $(PATH_SOURCE_FILES)/Graphics/Window.cpp $(PATH_SOURCE_FILES)/Graphics/WindowInfo.cpp $(PATH_SOURCE_FILES)/Graphics/Drawable.cpp $(PATH_SOURCE_FILES)/Graphics/RenderArea.cpp $(PATH_SOURCE_FILES)/Helper/CFGParser.cpp $(PATH_SOURCE_FILES)/Helper/Clipboard.cpp $(PATH_SOURCE_FILES)/Helper/Clipboard_imp_macos.mm $(PATH_SOURCE_FILES)/Helper/Clock.cpp $(PATH_SOURCE_FILES)/Helper/Color.cpp $(PATH_SOURCE_FILES)/Helper/ColorGradient.cpp $(PATH_SOURCE_FILES)/Helper/DATFile.cpp $(PATH_SOURCE_FILES)/Helper/Dir.cpp $(PATH_SOURCE_FILES)/Helper/KeyMapper.cpp $(PATH_SOURCE_FILES)/Helper/Kit.cpp $(PATH_SOURCE_FILES)/Helper/Log.cpp $(PATH_SOURCE_FILES)/Helper/OS.cpp $(PATH_SOURCE_FILES)/Helper/Profiler.cpp $(PATH_SOURCE_FILES)/Helper/Random.cpp $(PATH_SOURCE_FILES)/Helper/Strings.cpp $(PATH_SOURCE_FILES)/Helper/Vect2.cpp $(PATH_SOURCE_FILES)/Helper/Vect3.cpp $(PATH_SOURCE_FILES)/Helper/Area.cpp $(PATH_SOURCE_FILES)/Helper/ArgumentsParser.cpp $(PATH_SOURCE_FILES)/Helper/String.cpp  $(PATH_SOURCE_FILES)/Lua/LuaConsole.cpp $(PATH_SOURCE_FILES)/Lua/LuaAPI.cpp $(PATH_SOURCE_FILES)/Lua/LuaExportAPI.cpp $(PATH_SOURCE_FILES)/Resources/Resource.cpp $(PATH_SOURCE_FILES)/Resources/Music.cpp $(PATH_SOURCE_FILES)/Resources/MusicQueue.cpp $(PATH_SOURCE_FILES)/Resources/ResourceIDGenerator.cpp $(PATH_SOURCE_FILES)/Resources/ResourceManager.cpp $(PATH_SOURCE_FILES)/Resources/Shape.cpp $(PATH_SOURCE_FILES)/Resources/Sound.cpp $(PATH_SOURCE_FILES)/Resources/Sprite.cpp $(PATH_SOURCE_FILES)/Resources/SpriteAnimation.cpp $(PATH_SOURCE_FILES)/Resources/Text.cpp $(PATH_SOURCE_FILES)/Resources/Texture.cpp $(PATH_SOURCE_FILES)/Resources/Font.cpp
SRC_MAIN    = $(PATH_SOURCE_FILES)/main.cpp
OBJ_FILES   = $(patsubst %.mm,%.o,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SRC_FILES))))

OUTPUT_FILE = MedievalEngine

all: $(OUTPUT_FILE) run

print-%  : ; @echo $* = $($*)

%.o : %.mm
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
	mv $(shell basename $< | sed -e 's/.mm/'.o'/g') $(shell dirname $<)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
	mv $(shell basename $< | sed -e 's/.c/'.o'/g') $(shell dirname $<)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
	mv $(shell basename $< | sed -e 's/.cpp/'.o'/g') $(shell dirname $<)

$(OUTPUT_FILE): $(OBJ_FILES)
	$(CC) $^ $(CFLAGS) $(LFLAGS) $(INCLUDES) $(LIBS) $(FRAMEWORKS) $(SRC_MAIN) -o $@
	mv $@ $(PATH_SOURCE_FILES)/../bin

run:
	cd $(PATH_SOURCE_FILES)/../bin && ./$(OUTPUT_FILE)

clean:
	cd $(PATH_SOURCE_FILES)
	rm -rf $(PATH_SOURCE_FILES)/$(OUTPUT_FILE) $(PATH_SOURCE_FILES)/*.dSYM
	find $(PATH_SOURCE_FILES)/. -type f -name '*.o' -delete
