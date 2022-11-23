# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME FreeType)

add_definitions (-DFT2_BUILD_LIBRARY)

# Rename z_verbose and z_error symbols to prevent Clang duplicate symbol linker error (clash with Assimp) on debug build
if (XCODE OR CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions (-Dz_verbose=ft2_z_verbose -Dz_error=ft2_z_error)
endif ()

# Define source files
set (SOURCE_FILES
    src/autofit/autofit.c
    src/base/ftbase.c
    src/base/ftbbox.c
    src/base/ftbitmap.c
    src/base/ftfntfmt.c
    src/base/ftfstype.c
    src/base/ftgasp.c
    src/base/ftglyph.c
    src/base/ftgxval.c
    src/base/ftinit.c
    src/base/ftlcdfil.c
    src/base/ftmm.c
    src/base/ftotval.c
    src/base/ftpatent.c
    src/base/ftpfr.c
    src/base/ftstroke.c
    src/base/ftsynth.c
    src/base/ftsystem.c
    src/base/fttype1.c
    src/base/ftwinfnt.c
    src/bdf/bdf.c
    src/bzip2/ftbzip2.c
    src/cache/ftcache.c
    src/cff/cff.c
    src/cid/type1cid.c
    src/gxvalid/gxvalid.c
    src/gzip/ftgzip.c
    src/lzw/ftlzw.c
    src/otvalid/otvalid.c
    src/pcf/pcf.c
    src/pfr/pfr.c
    src/psaux/psaux.c
    src/pshinter/pshinter.c
    src/psnames/psmodule.c
    src/raster/raster.c
    src/sfnt/sfnt.c
    src/smooth/smooth.c
    src/truetype/truetype.c
    src/type1/type1.c
    src/type42/type42.c
    src/winfonts/winfnt.c)

# Define dependency libs
set (INCLUDE_DIRS include)

# Setup target
setup_library ()

# Install headers for building the Urho3D library
install_header_files (DIRECTORY include/freetype DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty FILES_MATCHING PATTERN *.h BUILD_TREE_ONLY)
install_header_files (FILES include/ft2build.h DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty FILES_MATCHING PATTERN *.h BUILD_TREE_ONLY)
