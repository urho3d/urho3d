dumpluaapi() {
    $CD/$1 -v 1>/dev/null 2>&1
    if [ $? -ne 0 ]; then return 1; fi
    echo "Dumping LuaScript API..."
    out=`pwd`/LuaScriptAPI.dox
    pushd ../Source/Engine/LuaScript/pkgs >/dev/null
    $CD/$1 pkgToDox.lua $out *.pkg
    if [ $? -ne 0 ]; then exit 1; fi
    popd >/dev/null
    return 0
}

cd $( dirname $0 )
CD=`pwd`
cd $CD/../Docs
echo "Dumping AngelScript API..."
../Bin/ScriptCompiler -dumpapi ScriptAPI.dox AngelScriptAPI.h
if [ $? -ne 0 ]; then exit 1; fi
for l in luajit lua; do dumpluaapi $l && break; done
if [ "$1" != "-a" ]; then exit 0; fi
echo "Converting Doxygen files to HTML..."
doxygen Doxyfile 1>/dev/null
echo "Finish."
