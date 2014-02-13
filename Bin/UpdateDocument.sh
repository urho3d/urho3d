cd $( dirname $0 )
CD=`pwd`
cd $CD/../Docs
echo "Dumping AngelScript API..."
../Bin/ScriptCompiler -dumpapi ScriptAPI.dox AngelScriptAPI.h
if [ $? -ne 0 ]; then exit 1; fi
cd $CD/../Source/Engine/LuaScript/pkgs
echo "Dumping LuaScript API..."
../../../../Bin/tolua++ -L ToDoxHook.lua -P -o ../../../../Docs/LuaScriptAPI.dox Urho3D.tolua
if [ $? -ne 0 ]; then exit 1; fi
cd $CD/../Docs
echo "Converting Doxygen files to HTML..."
doxygen Doxyfile 1>/dev/null
echo "Finish."
