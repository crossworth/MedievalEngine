@REM @Author: Pedro Henrique
@REM @Email: system.pedrohenrique@gmail.com
@REM @Date:   2016-06-05 23:46:25
@REM @Last Modified by:   Pedro Henrique
@REM Modified time: 2016-06-06 18:27:30

@echo off

echo.
echo MedievalEngine Windows Dependencies Helper
echo Pedro Henrique - system.pedrohenrique@gmail.com
echo.
echo ===================================================================
echo This script will install all dependencies (Lua 5.3.2, SFML 2.3.2)
echo ===================================================================
echo.

SET CURRENTDIR=%cd%

if exist "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64\vcvars64.bat" (
	echo Visual Studio found, preparing to install the MedievalEngine dependencies
	call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64\vcvars64.bat"

	REM Download lua and compile it
	REM Download SFML and compile it
	REM Copy both to a default place

	call "%CURRENTDIR%/../tools/wget/wget.exe" --no-check-certificate "https://www.lua.org/ftp/lua-5.3.2.tar.gz"
	call "%CURRENTDIR%/../tools/wget/wget.exe" --no-check-certificate "http://www.sfml-dev.org/files/SFML-2.3.2-windows-vc14-64-bit.zip"
	
	call "%CURRENTDIR%/../tools/tartool/TarTool.exe" lua-5.3.2.tar.gz lua
	call unzip SFML-2.3.2-windows-vc14-64-bit.zip -d sfml

	if not exist "C:\Deps" mkdir C:\Deps

	REM Build Lua
	pushd lua
		pushd lua-5.3.2
			pushd src
				cl /MD /O2 /c /DLUA_BUILD_AS_DLL *.c
				ren lua.obj lua.o
				ren luac.obj luac.o
				link /DLL /IMPLIB:lua5.3.2.lib /OUT:lua5.3.2.dll *.obj 
				link /OUT:lua.exe lua.o lua5.3.2.lib 
				lib /OUT:lua5.3.2-static.lib *.obj
				link /OUT:luac.exe luac.o lua5.3.2-static.lib

				if not exist "C:\Deps\Lua" mkdir C:\Deps\Lua
				if not exist "C:\Deps\Lua\libs" mkdir C:\Deps\Lua\libs
				if not exist "C:\Deps\Lua\include" mkdir C:\Deps\Lua\include

				mv *.exe C:\Deps\Lua\
				mv *.dll C:\Deps\Lua\
				mv *.lib C:\Deps\Lua\libs
				mv *.h C:\Deps\Lua\include\
			popd
		popd
	popd

	pushd sfml
		pushd SFML-2.3.2
			if not exist "C:\Deps\SFML" mkdir C:\Deps\SFML
			if not exist "C:\Deps\SFML\libs" mkdir C:\Deps\SFML\libs
			if not exist "C:\Deps\SFML\include" mkdir C:\Deps\SFML\include

			mv bin/* C:\Deps\SFML
			mv include/* C:\Deps\SFML\include
			mv lib/* C:\Deps\SFML\libs
		popd
	popd

	del lua-5.3.2.tar.gz
	del SFML-2.3.2-windows-vc14-64-bit.zip

	rmdir /S /Q lua
	rmdir /S /Q sfml

	echo.
	echo.
	echo Dependencies installed on C:\Deps
) else (
    echo Ops, we could not find an installation of Visual Studio 2015, try install it first.
    echo If you have installed Visual Studio 2015, maybe you're running a 32bits system, which it's not supported at this time
)