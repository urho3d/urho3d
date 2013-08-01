# This script is being called by CMake during GCC build
# PLEASE DO NOT EDIT unless you know what you are doing
target=$1; shift
outdir=$1; shift
objdir=$1; shift
(( $# )) && rm -f $outdir/$target.obj
for object in $@; do
    echo -n "$objdir/$object " >>$outdir/$target.obj
done
