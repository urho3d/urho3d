cd $( dirname $0 )/../Docs
echo "Dumping AngelScript API..."
../Bin/ScriptCompiler -dumpapi ScriptAPI.dox AngelScriptAPI.h
if [ $? -ne 0 ]; then exit 1; fi
lua -v 1>/dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "Dumping LuaScript API..."
    out=`pwd`/LuaScriptAPI.dox
    pushd ../Source/Engine/LuaScript/pkgs >/dev/null
    lua pkgToDox.lua $out *.pkg
    if [ $? -ne 0 ]; then exit 1; fi
    popd >/dev/null
fi
if [ "$1" != "-a" ]; then exit 0; fi
echo "Converting Doxygen files to HTML..."
doxygen Doxyfile 1>/dev/null
echo "Finish."
