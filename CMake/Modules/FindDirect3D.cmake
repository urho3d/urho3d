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

# For MSVC compiler, find Microsoft DirectX installation (need June 2010 SDK or later, or a Windows SDK)
# For MinGW compiler, assume MinGW not only comes with the necessary headers & libraries but also has the headers & libraries directories in its default search path
# (use 'echo |gcc -v -E -' and 'gcc -print-search-dirs', respectively, to double check)
#
#  DIRECT3D_FOUND
#  DIRECT3D_INCLUDE_DIRS
#  DIRECT3D_LIBRARIES
#  DIRECT3D_DLL
#

if (NOT WIN32 OR DIRECT3D_FOUND)
    return ()
endif ()

if (MSVC)
    # Prefer to use MS Windows SDK, so search for it first
    if (CMAKE_CL_64)
        set (PATH_SUFFIX x64)
    else ()
        set (PATH_SUFFIX x86)
    endif ()
    # Only need to search the DLL as a proxy for the presence of the MS Windows SDK
    find_file (DIRECT3D_DLL d3dcompiler_47.dll d3dcompiler_46.dll PATHS
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v8.1;InstallationFolder]/Redist/D3D/${PATH_SUFFIX}"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v8.0;InstallationFolder]/Redist/D3D/${PATH_SUFFIX}")
    if (DIRECT3D_DLL)
        if (NOT URHO3D_D3D11)
            set (DIRECT3D_LIBRARIES d3d9 d3dcompiler)
        else ()
            set (DIRECT3D_LIBRARIES d3d11 d3dcompiler dxgi dxguid)
        endif ()
        unset (DIRECT3D_INCLUDE_DIRS)
        set (DIRECT3D_FOUND 1)
    elseif (MSVC_VERSION LESS 1700 OR NOT URHO3D_D3D11)
        # To avoid incompatibility between DirectX SDK and Windows SDK defines and the resulting warning spam,
        # only search for the DirectX SDK when using Visual Studion lower than VS2012 or when using D3D9
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
        if (NOT URHO3D_D3D11)
            find_library (DIRECT3D_LIB_D3D9 NAMES d3d9 PATHS ${DIRECTX_LIB_SEARCH_PATH})
            find_library (DIRECT3D_LIB_D3DCOMPILER NAMES d3dcompiler PATHS ${DIRECTX_LIB_SEARCH_PATH})
            if (DIRECT3D_INCLUDE_DIRS AND DIRECT3D_LIB_D3D9 AND DIRECT3D_LIB_D3DCOMPILER)
                set (DIRECT3D_LIBRARIES ${DIRECT3D_LIB_D3D9} ${DIRECT3D_LIB_D3DCOMPILER})
                set (DIRECT3D_FOUND 1)
            endif ()
        else ()
            find_library (DIRECT3D_LIB_D3D11 NAMES d3d11 PATHS ${DIRECTX_LIB_SEARCH_PATH})
            find_library (DIRECT3D_LIB_D3DCOMPILER NAMES d3dcompiler PATHS ${DIRECTX_LIB_SEARCH_PATH})
            find_library (DIRECT3D_LIB_DXGI NAMES dxgi PATHS ${DIRECTX_LIB_SEARCH_PATH})
            find_library (DIRECT3D_LIB_DXGUID NAMES dxguid PATHS ${DIRECTX_LIB_SEARCH_PATH})
            if (DIRECT3D_INCLUDE_DIRS AND DIRECT3D_LIB_D3D11 AND DIRECT3D_LIB_D3DCOMPILER AND DIRECT3D_LIB_DXGI AND DIRECT3D_LIB_DXGUID)
                set (DIRECT3D_LIBRARIES ${DIRECT3D_LIB_D3D11} ${DIRECT3D_LIB_D3DCOMPILER} ${DIRECT3D_LIB_DXGI} ${DIRECT3D_LIB_DXGUID})
                set (DIRECT3D_FOUND 1)
            endif ()
        endif ()
    endif ()
endif ()

if (DIRECT3D_FOUND)
    include (FindPackageMessage)
    FIND_PACKAGE_MESSAGE (Direct3D "Found Direct3D: ${DIRECT3D_LIBRARIES} ${DIRECT3D_INCLUDE_DIRS}" "[${DIRECT3D_LIBRARIES}][${DIRECT3D_INCLUDE_DIRS}]")
elseif (Direct3D_FIND_REQUIRED)
    message (FATAL_ERROR "Could not find Direct3D in Windows SDK and DirectX SDK")
endif ()

mark_as_advanced (DIRECT3D_INCLUDE_DIRS DIRECT3D_LIBRARIES DIRECT3D_DLL)
