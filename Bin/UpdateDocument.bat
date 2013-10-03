@echo off
@echo "Dumping Script API..."
ScriptCompiler -dumpapi ../Docs/ScriptAPI.dox
if errorlevel 1 exit /B 1
if not "%1" == "-a" exit /B 0
@echo "Converting Doxygen files to HTML..."
cd .. && doxygen Doxyfile 1>nul
@echo "Finish."
