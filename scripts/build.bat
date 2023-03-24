@ECHO OFF
CD ..
MKDIR build
CD build
ECHO Building Editor application and dependencies...
cmake ..
cmake --build . --config Release
ECHO Done.
CD ../scripts
