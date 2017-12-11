@echo off
::run cmake
call cmake_emscripten.bat Build/WebGL -DURHO3D_SAMPLES=0
::build
call cd Build\WebGL
call make -j4
@echo on