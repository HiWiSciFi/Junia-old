#!/bin/bash
cd ..
mkdir -p build
cd build
echo Building Editor application and dependencies...
cmake ..
cmake --build .
echo Done.

