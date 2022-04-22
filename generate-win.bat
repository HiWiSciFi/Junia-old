@ECHO OFF
setlocal enabledelayedexpansion

:start

CLS
ECHO Generate project files for...
ECHO 1. codelite
ECHO 2. gmake
ECHO 3. vs
ECHO 4. xcode4

SET /p result=Enter which to select: 

IF "!result!" == "1"        SET eval=1
IF "!result!" == "codelite" SET eval=1
IF "!result!" == "2"        SET eval=2
IF "!result!" == "gmake"    SET eval=2
IF "!result!" == "3"        SET eval=3
IF "!result!" == "vs"       SET eval=3
IF "!result!" == "4"        SET eval=4
IF "!result!" == "xcode4"   SET eval=4

IF !eval! == 1 SET env=codelite & goto selected
IF !eval! == 2 (
	CLS
	ECHO Select gmake version:
	ECHO 1. gmake
	ECHO 2. gmake2

	SET /p result=Enter which gmake version to select: 

	IF "!result!" == "1"      SET env=gmake  & goto selected
	IF "!result!" == "gmake"  SET env=gmake  & goto selected
	IF "!result!" == "2"      SET env=gmake2 & goto selected
	IF "!result!" == "gmake2" SET env=gmake2 & goto selected
	goto error
)
IF !eval! == 3 (
	CLS
	ECHO Select VisualStudio version:
	ECHO 1. 2005
	ECHO 2. 2008
	ECHO 3. 2010
	ECHO 4. 2012
	ECHO 5. 2013
	ECHO 6. 2015
	ECHO 7. 2017
	ECHO 8. 2019
	ECHO 9. 2022

	SET /p result=Enter VS version: 

	IF "!result!" == "1"    SET env=vs2005 & goto selected
	IF "!result!" == "2005" SET env=vs2005 & goto selected
	IF "!result!" == "2"    SET env=vs2008 & goto selected
	IF "!result!" == "2008" SET env=vs2008 & goto selected
	IF "!result!" == "3"    SET env=vs2010 & goto selected
	IF "!result!" == "2010" SET env=vs2010 & goto selected
	IF "!result!" == "4"    SET env=vs2012 & goto selected
	IF "!result!" == "2012" SET env=vs2012 & goto selected
	IF "!result!" == "5"    SET env=vs2013 & goto selected
	IF "!result!" == "2013" SET env=vs2013 & goto selected
	IF "!result!" == "6"    SET env=vs2015 & goto selected
	IF "!result!" == "2015" SET env=vs2015 & goto selected
	IF "!result!" == "7"    SET env=vs2017 & goto selected
	IF "!result!" == "2017" SET env=vs2017 & goto selected
	IF "!result!" == "8"    SET env=vs2019 & goto selected
	IF "!result!" == "2019" SET env=vs2019 & goto selected
	IF "!result!" == "9"    SET env=vs2022 & goto selected
	IF "!result!" == "2022" SET env=vs2022 & goto selected
	goto error
)
IF !eval! == 4 SET env=xcode4 & goto selected
goto error

:selected
CLS
ECHO Generating files for !env!
ECHO ------------------------------------------
CALL .\external\premake\bin\windows\premake5.exe !env!
goto end

:error
CLS
ECHO "!result!" is not a valid option!
PAUSE
goto start

:end
PAUSE