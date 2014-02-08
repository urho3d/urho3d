#This script compiles all lua files located in Data/LuaScripts folder

luaFiles=`find ./Data/LuaScripts -name "*.lua"` #Get files to compile

for f in $luaFiles; do
    echo $f
    ./luajit -b $f ${f%.*}.luc #Compile to .luc
done
