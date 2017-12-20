@echo off
::run cmake
call cmake_vs2015.bat Build/Win64 -DURHO3D_64BIT=1 -DURHO3D_C++11=1 -DURHO3D_OPENGL=1 -DURHO3D_LUA=0 -DURHO3D_SAMPLES=0
::build
start "" "C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild.exe" .\Build\Win64\Urho3D.sln /p:Configuration=Release /maxcpucount:4
start "" "C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild.exe" .\Build\Win64\Urho3D.sln /p:Configuration=Debug /maxcpucount:4    
@echo on