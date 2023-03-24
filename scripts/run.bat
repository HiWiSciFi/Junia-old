@ECHO OFF
IF NOT EXIST "../build/Editor/Release/Editor" (
	CALL ".\clean.bat"
	CALL ".\build.bat"
)

CD "../build/Editor/Release"
ECHO Starting Editor application...
ECHO -------------------------------------------------------------------------------
.\Editor.exe
CD "../../../scripts"
