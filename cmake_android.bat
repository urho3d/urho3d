@echo off
:: Define USE_MKLINK to 1 to enable out-of-source build
del /F Source\Android\CMakeCache.txt CMakeCache.txt
rd /S /Q Source\Android\CMakeFiles CMakeFiles
set "build=Source\Android"
set "source=.."
set "use_mklink="
:loop
if not "%1" == "" (
    if "%1" == "-DUSE_MKLINK" set "use_mklink=%~2"
    shift
    shift
    goto loop
)
if "%use_mklink%" == "1" (
    cmake -E make_directory android-Build
    del /F android-Build\CMakeCache.txt
    rd /S /Q android-Build\CMakeFiles
    set "build=android-Build"
    set "source=..\Source"
    for %%d in (CoreData Data) do mklink /D "Source\Android\assets\%%d" "..\..\..\Bin\%%d"
    for %%d in (src res assets) do mklink /D "android-Build\%%d" "..\Source\Android\%%d"
    for %%f in (AndroidManifest.xml build.xml project.properties) do mklink "android-Build\%%f" "..\Source\Android\%%f"
)
cmake -E copy_if_different Docs\Doxyfile.in Doxyfile
echo on
cmake -E chdir %build% cmake -G "Unix Makefiles" -DANDROID=1 -DCMAKE_TOOLCHAIN_FILE=%source%\cmake\Toolchains\android.toolchain.cmake -DLIBRARY_OUTPUT_PATH_ROOT=. %source% %*
