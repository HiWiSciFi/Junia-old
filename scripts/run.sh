#!/bin/bash

if [ ! -f ../build/Editor/Editor ]
then
	./clean.sh
	./build.sh
fi

cd ../build/Editor
echo Starting Editor application...
echo --------------------------------------------------------------------------------
./Editor

