@echo off

SET CURRENTDIR=%~dp0
SET BIN_PATH="%CURRENTDIR%..\bin"

pushd %BIN_PATH%
	START "MedievalEngine" "MedievalEngine.exe"
popd