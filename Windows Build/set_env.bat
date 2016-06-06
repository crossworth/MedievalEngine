@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64\vcvars64.bat"

SET CURRENTDIR=%~dp0
set path=%CURRENTDIR%;%path%
