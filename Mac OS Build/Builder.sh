#!/bin/bash

# MedievalEngine Mac OS X Builder and Installer Helper
# Pedro Henrique - 2016
# system.pedrohenrique@gmail.com
# pedrohenrique.ninja


clang_check="$(clang --version)"
clang_check="Apple LLVM version"

if [[ ! $clang_check =~ $clang_check ]]; then
    printf "Xcode command line tools not installed\n"
    exit 1
fi


LUA_LIBS_PATH=""
LUA_INCLUDE_PATH=""

SFML_LIBS_PATH=""
SFML_FRAMEWORKS_PATH=""
SFML_INCLUDE_PATH=""

generateMakeFile () {
    lib_dir="/usr/local/lib"

    if [ "$SFML_LIBS_PATH" == "" ] && [ -d "$lib_dir" ]; then
        SFML_LIBS_PATH=$lib_dir
    fi

    include_dir="/usr/local/lib"

    if [ "$SFML_INCLUDE_PATH" == "" ] && [ -d "$include_dir" ]; then
        SFML_INCLUDE_PATH=$include_dir
    fi


    if [ "$SFML_LIBS_PATH" == "" ]; then
        printf "Library path not set, please inform the library path:\n"
        read -e SFML_LIBS_PATH
    fi

    if [ "$SFML_INCLUDE_PATH" == "" ]; then
        printf "Include path not set, please inform the include path:\n"
        read -e SFML_INCLUDE_PATH
    fi

    if [ "$LUA_LIBS_PATH" != "$SFML_LIBS_PATH" ]; then
        SFML_LIBS_PATH="$SFML_LIBS_PATH $LUA_LIBS_PATH"
    fi

    if [ "$SFML_INCLUDE_PATH" != "$LUA_INCLUDE_PATH" ]; then
        SFML_INCLUDE_PATH="$SFML_INCLUDE_PATH $LUA_INCLUDE_PATH"
    fi

    PATH_MEDIEVAL_ENGINE_SOURCE_FILES=""

    src_dir_check="../src"

    if [ -d "$src_dir_check" ]; then
      PATH_MEDIEVAL_ENGINE_SOURCE_FILES=$src_dir_check
    else
        printf "Enter the path for the MedievalEngine's source files:\n"
        read -e PATH_MEDIEVAL_ENGINE_SOURCE_FILES
    fi
    PATH_MEDIEVAL_ENGINE_SOURCE_FILES=$(cd $PATH_MEDIEVAL_ENGINE_SOURCE_FILES; pwd)

    eval PATH_MEDIEVAL_ENGINE_SOURCE_FILES=$PATH_MEDIEVAL_ENGINE_SOURCE_FILES

    ALL_FILES=$(find -L "${PATH_MEDIEVAL_ENGINE_SOURCE_FILES}" -name \*.c -or -name \*.cpp -or -name \*.mm)

    
    ALL_FILES=$(echo $ALL_FILES | sed -e 's#'"${PATH_MEDIEVAL_ENGINE_SOURCE_FILES}"'#$(PATH_SOURCE_FILES)/#g')
    ALL_FILES=$(echo $ALL_FILES | sed 's#//*#/#g')
    ALL_FILES=$(echo $ALL_FILES | sed -e 's#$(PATH_SOURCE_FILES)/main.cpp##g')
    
    MAKE_FILE=$(echo -e "# MedievalEngine 2016 - Auto Generated Makefile
# Pedro Henrique - system.pedrohenrique@gmail.com

PATH_SOURCE_FILES = ${PATH_MEDIEVAL_ENGINE_SOURCE_FILES}

CC         = clang++
CFLAGS     = -g -Wall -Wno-switch -O0 -std=c++14
INCLUDES   = -I \$(PATH_SOURCE_FILES) -I ${SFML_INCLUDE_PATH} -I \$(PATH_SOURCE_FILES)/extlibs
LFLAGS     = -L ${SFML_LIBS_PATH}
LIBS       = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-network -llua
FRAMEWORKS = -framework Cocoa

SRC_FILES   = ${ALL_FILES}
SRC_MAIN    = \$(PATH_SOURCE_FILES)/main.cpp
OBJ_FILES   = \$(patsubst %.mm,%.o,\$(patsubst %.cpp,%.o,\$(patsubst %.c,%.o,\$(SRC_FILES))))

OUTPUT_FILE = MedievalEngine

all: \$(OUTPUT_FILE) run

print-%  : ; @echo \$* = \$(\$*)

%.o : %.mm
\t\$(CC) \$(CFLAGS) \$(INCLUDES) -c $<
\tmv \$(shell basename \$< | sed -e 's/.mm/'.o'/g') \$(shell dirname $<)

%.o: %.c
\t\$(CC) \$(CFLAGS) \$(INCLUDES) -c $<
\tmv \$(shell basename $< | sed -e 's/.c/'.o'/g') \$(shell dirname $<)

%.o: %.cpp
\t\$(CC) \$(CFLAGS) \$(INCLUDES) -c $<
\tmv \$(shell basename \$< | sed -e 's/.cpp/'.o'/g') \$(shell dirname $<)

\$(OUTPUT_FILE): \$(OBJ_FILES)
\t\$(CC) \$^ \$(CFLAGS) \$(LFLAGS) \$(INCLUDES) \$(LIBS) \$(FRAMEWORKS) \$(SRC_MAIN) -o \$@
\tmv \$@ \$(PATH_SOURCE_FILES)/../bin

run:
\tcd \$(PATH_SOURCE_FILES)/../bin && ./\$(OUTPUT_FILE)

clean:
\tcd \$(PATH_SOURCE_FILES)
\trm -rf \$(PATH_SOURCE_FILES)/\$(OUTPUT_FILE) \$(PATH_SOURCE_FILES)/*.dSYM
\tfind \$(PATH_SOURCE_FILES)/. -type f -name '*.o' -delete")


    echo "$MAKE_FILE" > "Makefile"

    printf "Makefile generated\n"
}


printf "\n"

printf "MedievalEngine Mac OS X Builder and Installer Helper\n"
printf "Pedro Henrique - system.pedrohenrique@gmail.com\n"
printf "\n"
printf "============================================================\n"
printf "1 - Install all dependencies (Lua 5.3.2, SFML 2.3.2)\n"
printf "2 - Generate Makefile\n"
printf "============================================================\n"

if [ "$1" == "makefile" ] || [ "$1" == 2 ]; then
    option=2
elif [ "$1" == "install" ] || [ "$1" == 1 ]; then
    option=1
else
    read -p "Select an option: " option
fi

if [ "$option" == 1 ]; then
    printf "This script will install the following dependencies\n"
    printf "\tLua 5.3.2\n"
    printf "\tSFML 2.3.2\n"

    printf "Downloading Lua\n"

    curl -sS -R -O -L "http://www.lua.org/ftp/lua-5.3.2.tar.gz" > /dev/null
    tar -zxf "lua-5.3.2.tar.gz" > /dev/null
    cd "lua-5.3.2"

    printf "Compiling Lua\n"
    sudo make macosx test > /dev/null
    make_macosx_output="$(sudo make install | grep -E -i 'mkdir -p')"
    
    regex_lua_paths="-p ([\/[:alpha:]]+) ([\/[:alpha:]]+) ([\/[:alpha:]]+)"

    if [[ $make_macosx_output =~ $regex_lua_paths ]]; then
        printf "Lua header files on ${BASH_REMATCH[2]}\n"
        printf "Lua libs files on ${BASH_REMATCH[3]}\n"

        LUA_INCLUDE_PATH="${BASH_REMATCH[2]}"
        LUA_LIBS_PATH="${BASH_REMATCH[3]}"
    else
        printf "Lua installed on ${make_macosx_output}\n"
    fi

    cd ".."
    rm -rf "lua-5.3.2"
    rm -rf "lua-5.3.2.tar.gz"

    printf "Downloading SFML\n"
    curl -sS -R -O -L "http://www.sfml-dev.org/files/SFML-2.3.2-osx-clang-universal.tar.gz" > /dev/null
    tar -zxf "SFML-2.3.2-osx-clang-universal.tar.gz" > /dev/null
    cd "SFML-2.3.2-osx-clang-universal"

    sudo rm -rf "/Library/Frameworks/SFML.framework"
    sudo rm -rf "/Library/Frameworks/sfml-audio.framework"
    sudo rm -rf "/Library/Frameworks/sfml-graphics.framework"
    sudo rm -rf "/Library/Frameworks/sfml-network.framework"
    sudo rm -rf "/Library/Frameworks/sfml-system.framework"
    sudo rm -rf "/Library/Frameworks/sfml-window.framework"
    sudo rm -rf "/Library/Frameworks/FLAC.framework"
    sudo rm -rf "/Library/Frameworks/OpenAL.framework"
    sudo rm -rf "/Library/Frameworks/freetype.framework"
    sudo rm -rf "/Library/Frameworks/ogg.framework"
    sudo rm -rf "/Library/Frameworks/vorbis.framework"
    sudo rm -rf "/Library/Frameworks/vorbisenc.framework"
    sudo rm -rf "/Library/Frameworks/vorbisfile.framework"


    sudo cp lib/* /usr/local/lib/
    sudo cp -R include/* /usr/local/include/
    sudo cp -R Frameworks/* /Library/Frameworks
    sudo cp -R extlibs/* /Library/Frameworks


    SFML_LIBS_PATH="/usr/local/lib/"
    SFML_INCLUDE_PATH="/usr/local/include/"
    SFML_FRAMEWORKS_PATH="/Library/Frameworks"

    cd ".."
    rm -rf "SFML-2.3.2-osx-clang-universal"
    rm -rf "SFML-2.3.2-osx-clang-universal.tar.gz"


    printf "SFML header files on ${SFML_INCLUDE_PATH}\n"
    printf "SFML libs files on ${SFML_LIBS_PATH}\n"
    printf "SFML Framework files on ${SFML_FRAMEWORKS_PATH}\n"


    read -p "Do you want to generate the Makefile for this configuration(Y/n)? " gen_make_file

    if echo "$gen_make_file" | grep -iq "^y"; then
        generateMakeFile
    fi

elif [ "$option" == 2 ]; then
    generateMakeFile
else
    printf "No option selected\n"
    exit 1
fi

