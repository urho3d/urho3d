#
# Copyright (c) 2008-2015 the Urho3D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

# For MSVC compiler, find Microsoft DirectX installation (need June 2010 SDK or later)
# For MinGW compiler, assume MinGW not only comes with the necessary headers & libraries but also has the headers & libraries directories in its default search path
# (use 'echo |gcc -v -E -' and 'gcc -print-search-dirs', respectively, to double check)
#
#  DIRECT3D_FOUND
#  DIRECT3D_INCLUDE_DIRS
#  DIRECT3D_LIBRARIES
#

if (NOT WIN32 OR DIRECT3D_FOUND)
    return ()
endif ()

if (MSVC)
    set (DIRECTX_INC_SEARCH_PATH
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
        "C:/Program Files/Microsoft DirectX SDK (June 2010)/Include"
        "$ENV{DIRECTX_ROOT}/Include"
        "$ENV{DXSDK_DIR}/Include")
    find_path (DIRECT3D_INCLUDE_DIRS NAMES d3dcompiler.h PATHS ${DIRECTX_INC_SEARCH_PATH})

    if (CMAKE_CL_64)
        set (DIRECTX_LIB_SEARCH_PATH
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64"
            "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib/x64"
            "$ENV{DIRECTX_ROOT}/Lib/x64"
            "$ENV{DXSDK_DIR}/Lib/x64")
    else ()
        set (DIRECTX_LIB_SEARCH_PATH
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib"
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86"
            "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib"
            "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib/x86"
            "$ENV{DIRECTX_ROOT}/Lib"
            "$ENV{DIRECTX_ROOT}/Lib/x86"
            "$ENV{DXSDK_DIR}/Lib"
            "$ENV{DXSDK_DIR}/Lib/x86")
    endif ()
    find_library (DIRECT3D_LIB_D3D9 NAMES d3d9 PATHS ${DIRECTX_LIB_SEARCH_PATH})
    find_library (DIRECT3D_LIB_D3DCOMPILER NAMES d3dcompiler PATHS ${DIRECTX_LIB_SEARCH_PATH})

    if (DIRECT3D_INCLUDE_DIRS AND DIRECT3D_LIB_D3D9 AND DIRECT3D_LIB_D3DCOMPILER)
        set (DIRECT3D_LIBRARIES ${DIRECT3D_LIB_D3D9} ${DIRECT3D_LIB_D3DCOMPILER})
        set (DIRECT3D_FOUND 1)
    endif ()
endif ()

if (DIRECT3D_FOUND)
    include (FindPackageMessage)
    FIND_PACKAGE_MESSAGE (Direct3D "Found DirectX SDK: ${DIRECT3D_LIBRARIES} ${DIRECT3D_INCLUDE_DIRS}" "[${DIRECT3D_LIBRARIES}][${DIRECT3D_INCLUDE_DIRS}]")
else ()
    set (DIRECT3D_LIBRARIES d3d9 d3dcompiler)
    if (MSVC)
        message (STATUS "DirectX SDK not found. This is not fatal if a recent Windows SDK is installed")
    else ()
        message (STATUS "DirectX SDK is not being searched for MinGW. It is assumed that MinGW itself comes with the necessary headers & libraries for Direct3D")
    endif ()
endif ()

mark_as_advanced (DIRECT3D_INCLUDE_DIRS DIRECT3D_LIBRARIES)
