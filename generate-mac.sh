#!/bin/bash

local RESULT=0
local ENV=0

clear
echo Generate project files for...
echo 1. codelite
echo 2. gmake
echo 3. vs
echo 4. xcode4

read -p "Enter which to select: " RESULT

if   [ "$RESULT" == "1" ] || [ "$RESULT" == "codelite" ]; then
	ENV=codelite

elif [ "$RESULT" == "2" ] || [ "$RESULT" == "gmake"    ]; then
	clear
	echo Select gmake version:
	echo 1. gmake
	echo 2. gmake2

	read -p "Enter which gmake version to select: " RESULT

	if   [ "$RESULT" == "1" ] || [ "$RESULT" == "gmake"  ]; then
		ENV=gmake
	elif [ "$RESULT" == "2" ] || [ "$RESULT" == "gmake2" ]; then
		ENV=gmake2
	else
		echo ERROR: Invalid input!
		exit 1
	fi

elif [ "$RESULT" == "3" ] || [ "$RESULT" == "vs"       ]; then
	clear
	echo Select VisualStudio version:
	echo 1. 2005
	echo 2. 2008
	echo 3. 2010
	echo 4. 2012
	echo 5. 2013
	echo 6. 2015
	echo 7. 2017
	echo 8. 2019
	echo 9. 2022

	read -p "Enter VS version: " RESULT

	if   [ "$RESULT" == "1" ] || [ "$RESULT" == "2005" ]; then
		ENV=vs2005
	elif [ "$RESULT" == "2" ] || [ "$RESULT" == "2008" ]; then
		ENV=vs2008
	elif [ "$RESULT" == "3" ] || [ "$RESULT" == "2010" ]; then
		ENV=vs2010
	elif [ "$RESULT" == "4" ] || [ "$RESULT" == "2012" ]; then
		ENV=vs2012
	elif [ "$RESULT" == "5" ] || [ "$RESULT" == "2013" ]; then
		ENV=vs2013
	elif [ "$RESULT" == "6" ] || [ "$RESULT" == "2015" ]; then
		ENV=vs2015
	elif [ "$RESULT" == "7" ] || [ "$RESULT" == "2017" ]; then
		ENV=vs2017
	elif [ "$RESULT" == "8" ] || [ "$RESULT" == "2019" ]; then
		ENV=vs2019
	elif [ "$RESULT" == "9" ] || [ "$RESULT" == "2022" ]; then
		ENV=vs2022
	else
		echo ERROR: Invalid input!
		exit 1
	fi

elif [ "$RESULT" == "4" ] || [ "$RESULT" == "xcode4"   ]; then
	ENV=xcode4

else
	echo ERROR: Invalid input!
	exit 1
fi

clear
echo Generating files for $ENV
echo ------------------------------------------
./external/premake/bin/mac/premake5 $ENV

read -p "Press [Enter] to exit..."
exit 0