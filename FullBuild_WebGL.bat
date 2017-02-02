@echo off
::run cmake
call cmake_emscripten.bat Build/WebGL -DURHO3D_64BIT=1 -DURHO3D_C++11=1 -DURHO3D_OPENGL=1 -DURHO3D_LUA=0 -DURHO3D_SAMPLES=0
::build
call cd Build\WebGL
call make -j4
@echo on