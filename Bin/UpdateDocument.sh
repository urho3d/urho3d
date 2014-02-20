cd $( dirname $0 )
BIN=`pwd`
cd ../Docs
echo "Dumping AngelScript API..."
$BIN/ScriptCompiler -dumpapi ScriptAPI.dox AngelScriptAPI.h
if [ $? -ne 0 ]; then exit 1; fi
echo "Dumping LuaScript API..."
out=`pwd`/LuaScriptAPI.dox
pushd ../Source/Engine/LuaScript/pkgs >/dev/null
$BIN/tolua++ -L ToDoxHook.lua -P -o $out $BIN/LuaPkgToDox.txt
if [ $? -ne 0 ]; then exit 1; fi
popd >/dev/null
echo "Converting Doxygen files to HTML..."
doxygen Doxyfile 1>/dev/null
echo "Finish."
