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

# For MSVC compiler, find Microsoft Direct3D installation in Windows SDK or in June 2010 DirectX SDK or later
# For MinGW compiler, assume MinGW not only comes with the necessary headers & libraries but also has the headers & libraries directories in its default search path
# (use 'echo |$MINGW_PREFIX-gcc -v -E -' and '$MINGW_PREFIX-gcc -print-search-dirs', respectively, to double check)
#
#  DIRECT3D_FOUND
#  DIRECT3D_INCLUDE_DIRS
#  DIRECT3D_LIBRARIES
#  DIRECT3D_DLL
#

# Microsoft SDK can be used on VS2012 and above; else fallback to search for the DirectX SDK
if (MSVC_VERSION GREATER 1600 OR MINGW)  # MinGW compiler toolchain is assumed to come with its own necessary headers and libraries for Direct3D
    # Try to find the compiler DLL from the Microsoft SDK
    if (MINGW)
        # Assume that 'libd3dcompiler.a' is a symlink pointing to 'libd3dcompiler_46.a' (See this discussion http://urho3d.prophpbb.com/topic504.html)
        # Anyway, we could not do anything else in the build system automation with version lower than 46 and libd3dcompiler_46.a is the latest supported version
        set (DLL_NAMES d3dcompiler_46.dll)
    else ()
        set (DLL_NAMES d3dcompiler_47.dll d3dcompiler_46.dll)
    endif ()
    if (CMAKE_CL_64)
        set (PATH_SUFFIX x64)
    else ()
        set (PATH_SUFFIX x86)
    endif ()
    find_file (DIRECT3D_DLL NAMES ${DLL_NAMES} PATHS
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v10.0;InstallationFolder]/Redist/D3D/${PATH_SUFFIX}"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v8.1;InstallationFolder]/Redist/D3D/${PATH_SUFFIX}"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v8.0;InstallationFolder]/Redist/D3D/${PATH_SUFFIX}"
        DOC "Direct3D DLL"
        NO_DEFAULT_PATH)    # Do not use default paths such as the PATH variable, to potentially avoid using a wrong architecture DLL
    if (DIRECT3D_DLL OR MINGW)
        if (URHO3D_D3D11)
            set (DIRECT3D_LIBRARIES d3d11 d3dcompiler dxgi dxguid)
        else ()
            set (DIRECT3D_LIBRARIES d3d9 d3dcompiler)
        endif ()
        unset (DIRECT3D_INCLUDE_DIRS)
    endif ()
    set (FAIL_MESSAGE "Could NOT find Direct3D using Windows SDK search paths")
    mark_as_advanced (DIRECT3D_DLL)
else ()
    # Try to find the DirectX SDK
    set (DIRECTX_INC_SEARCH_PATH
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
        "C:/Program Files/Microsoft DirectX SDK (June 2010)/Include"
        "$ENV{DIRECTX_ROOT}/Include"
        "$ENV{DXSDK_DIR}/Include")
    find_path (DIRECT3D_INCLUDE_DIRS NAMES d3dcompiler.h PATHS ${DIRECTX_INC_SEARCH_PATH} DOC "Direct3D include directory")
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
    if (URHO3D_D3D11)
        find_library (DIRECT3D_LIB_D3D11 NAMES d3d11 PATHS ${DIRECTX_LIB_SEARCH_PATH} DOC "Direct3D d3d11 library directory")
        find_library (DIRECT3D_LIB_D3DCOMPILER NAMES d3dcompiler PATHS ${DIRECTX_LIB_SEARCH_PATH} DOC "Direct3D d3dcompiler library directory")
        find_library (DIRECT3D_LIB_DXGI NAMES dxgi PATHS ${DIRECTX_LIB_SEARCH_PATH} DOC "Direct3D dxgi library directory")
        find_library (DIRECT3D_LIB_DXGUID NAMES dxguid PATHS ${DIRECTX_LIB_SEARCH_PATH} DOC "Direct3D dxguid library directory")
        if (DIRECT3D_INCLUDE_DIRS AND DIRECT3D_LIB_D3D11 AND DIRECT3D_LIB_D3DCOMPILER AND DIRECT3D_LIB_DXGI AND DIRECT3D_LIB_DXGUID)
            set (DIRECT3D_LIBRARIES ${DIRECT3D_LIB_D3D11} ${DIRECT3D_LIB_D3DCOMPILER} ${DIRECT3D_LIB_DXGI} ${DIRECT3D_LIB_DXGUID})
        endif ()
        mark_as_advanced (DIRECT3D_LIB_D3D11 DIRECT3D_LIB_D3DCOMPILER DIRECT3D_LIB_DXGI DIRECT3D_LIB_DXGUID)
    else ()
        find_library (DIRECT3D_LIB_D3D9 NAMES d3d9 PATHS ${DIRECTX_LIB_SEARCH_PATH} DOC "Direct3D d3d9 library directory")
        find_library (DIRECT3D_LIB_D3DCOMPILER NAMES d3dcompiler PATHS ${DIRECTX_LIB_SEARCH_PATH} DOC "Direct3D d3dcompiler library directory")
        if (DIRECT3D_INCLUDE_DIRS AND DIRECT3D_LIB_D3D9 AND DIRECT3D_LIB_D3DCOMPILER)
            set (DIRECT3D_LIBRARIES ${DIRECT3D_LIB_D3D9} ${DIRECT3D_LIB_D3DCOMPILER})
        endif ()
        mark_as_advanced (DIRECT3D_LIB_D3D9 DIRECT3D_LIB_D3DCOMPILER)
    endif ()
    set (FAIL_MESSAGE "Could NOT find Direct3D using DirectX SDK search paths")
endif ()

# DIRECT3D_INCLUDE_DIRS is not required for Windows SDK, it is required for DirectX SDK but it is implied when DIRECT3D_LIBRARIES can be set
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Direct3D REQUIRED_VARS DIRECT3D_LIBRARIES FAIL_MESSAGE ${FAIL_MESSAGE})

mark_as_advanced (DIRECT3D_INCLUDE_DIRS DIRECT3D_LIBRARIES)
