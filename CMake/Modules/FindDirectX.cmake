#
# Copyright (c) 2008-2016 the Urho3D project.
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

# For MSVC compiler, find Microsoft DirectX installation in Windows SDK or in June 2010 DirectX SDK or later
# For MinGW compiler, assume MinGW not only comes with the necessary headers & libraries but also has the headers & libraries directories in its default search path
# (use 'echo |$MINGW_PREFIX-gcc -v -E -' and '$MINGW_PREFIX-gcc -print-search-dirs', respectively, to double check)
# The MinGW headers on Linux host are usually shipped in a development package which should be installed automatically as part of the package dependency by the package manager when installing MinGW
# (in Debian-based it is 'mingw-w64-dev' and in RedHat-based 'mingw64-headers' for 64-bit; 'mingw-w64-i686-dev' and 'mingw32-headers', respectively, for 32-bit)
#
#  DIRECTX_FOUND (TRUE when any of the components is found)
#  DIRECTX_INCLUDE_DIRS
#  DIRECTX_LIBRARY_DIRS
#  HAVE_DIRECTX (Synonym to DIRECTX_FOUND)
#  USE_WINSDK_DIRECTX (TRUE when using Windows SDK or FALSE when using DirectX SDK; not defined on MinGW)
#
# When corresponding component is found:
#  DirectX_D3D_FOUND (Currently synonym to DirectX_D3D9_FOUND)
#  DirectX_D3D9_FOUND
#  DirectX_D3D11_FOUND
#  DirectX_DInput_FOUND
#  DirectX_DSound_FOUND
#  DirectX_XAudio2_FOUND
#  DirectX_XInput_FOUND
#
# When any of the Direct3D components is found:
#  DIRECT3D_LIBRARIES
#  DIRECT3D_DLL
#
# When corresponding header is found:
#  HAVE_D3DCOMPILER_H
#  HAVE_D3D_H (Currently synonym to HAVE_D3D9_H)
#  HAVE_D3D9_H
#  HAVE_D3D11_H
#  HAVE_DDRAW_H
#  HAVE_DSOUND_H
#  HAVE_DINPUT_H
#  HAVE_DXGI_H
#  HAVE_XAUDIO2_H
#  HAVE_XINPUT_H
#

set (DIRECTX_HEADERS d3dcompiler.h d3d9.h d3d11.h ddraw.h dsound.h dinput.h dxgi.h xaudio2.h xinput.h)
if (CMAKE_CL_64)
    set (PATH_SUFFIX x64)
else ()
    set (PATH_SUFFIX x86)
endif ()
set (CMAKE_REQUIRED_INCLUDES_SAVED ${CMAKE_REQUIRED_INCLUDES})

# Version older than VS2012 fallbacks to search for the DirectX SDK
if (NOT MSVC_VERSION GREATER 1600 OR MINGW)     # MinGW meets both conditional checks intentionally
    if (MINGW)
        # Intentionally searching for d3dcompiler(_XX) libraries in this particular order because currently the libd3dcompiler.a is an "import library" for d3dcompiler_43.dll, so we want to use libd3dcompiler_47.a or libd3dcompiler_46.a when they are available instead
        set (D3DCOMPILER_NAMES d3dcompiler_47 d3dcompiler_46 d3dcompiler)
        # MinGW does not need search paths as DirectX headers and libraries (when installed) are in its default search path
        # However, we do not explicitly unset the DIRECTX_INC_SEARCH_PATH and DIRECTX_LIB_SEARCH_PATH variables here, so module user could set these two variables externally when for some reasons the DirectX headers and libraries are not installed in MinGW default search path
    else ()
        set (D3DCOMPILER_NAMES d3dcompiler)
        # Module user could also prepopulate the DIRECTX_INC_SEARCH_PATH and DIRECTX_LIB_SEARCH_PATH variables externally when the following search paths does not work and the usage of DIRECTX_ROOT and DXSDK_DIR environment variable is not preferable
        list (APPEND DIRECTX_INC_SEARCH_PATH
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
            "C:/Program Files/Microsoft DirectX SDK (June 2010)/Include"
            $ENV{DIRECTX_ROOT}/Include
            $ENV{DXSDK_DIR}/Include)
        list (APPEND DIRECTX_LIB_SEARCH_PATH
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/${PATH_SUFFIX}"
            "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib/${PATH_SUFFIX}"
            $ENV{DIRECTX_ROOT}/Lib/${PATH_SUFFIX}
            $ENV{DXSDK_DIR}/Lib/${PATH_SUFFIX})
        if (NOT CMAKE_CL_64)
            list (APPEND DIRECTX_LIB_SEARCH_PATH
                "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib"
                "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib"
                $ENV{DIRECTX_ROOT}/Lib
                $ENV{DXSDK_DIR}/Lib)
        endif ()
    endif ()
    find_path (DIRECTX_INCLUDE_DIRS NAMES ${DIRECTX_HEADERS} PATHS ${DIRECTX_INC_SEARCH_PATH} DOC "DirectX include directory")
    if (DIRECTX_INCLUDE_DIRS)
        set (CMAKE_REQUIRED_INCLUDES ${DIRECTX_INCLUDE_DIRS})
        set (DIRECTX_LIBRARY_DIRS)
        set (DIRECT3D_LIBRARIES)
        if (NOT URHO3D_OPENGL)
            find_library (DIRECTX_D3DCOMPILER NAMES ${D3DCOMPILER_NAMES} PATHS ${DIRECTX_LIB_SEARCH_PATH} DOC "DirectX d3dcompiler library")
            if (DIRECTX_D3DCOMPILER)
                get_filename_component (NAME ${DIRECTX_D3DCOMPILER} NAME)
                string (REGEX REPLACE "^.*(d3dcompiler[_0-9]*).*$" \\1 D3DCOMPILER_LIB_NAME ${NAME})
                if (URHO3D_D3D11)
                    set (DIRECT3D_LIB_NAMES d3d11 dxgi dxguid)
                else ()
                    set (DIRECT3D_LIB_NAMES d3d9)
                endif ()
                foreach (NAME ${D3DCOMPILER_LIB_NAME} ${DIRECT3D_LIB_NAMES})
                    string (REGEX REPLACE _[0-9]+$ "" BASE_NAME ${NAME})
                    string (TOUPPER ${BASE_NAME} UPCASE_NAME)
                    find_library (DIRECTX_${UPCASE_NAME} NAMES ${NAME} PATHS ${DIRECTX_LIB_SEARCH_PATH} DOC "DirectX ${BASE_NAME} library")
                    if (DIRECTX_${UPCASE_NAME})
                        get_filename_component (PATH ${DIRECTX_${UPCASE_NAME}} PATH)
                        list (APPEND DIRECTX_LIBRARY_DIRS ${PATH})      # All the libs should be found in a same place, but just in case
                        list (APPEND DIRECT3D_LIBRARIES ${NAME})
                    else ()
                        set (MISSING_DIRECT3D_LIB TRUE)
                    endif ()
                    mark_as_advanced (DIRECTX_${UPCASE_NAME})
                endforeach ()
                if (NOT MISSING_DIRECT3D_LIB)
                    if (NOT MINGW)
                        set (USE_WINSDK_DIRECTX FALSE)
                    endif ()
                    set (HAVE_DIRECTX TRUE)
                    if (URHO3D_D3D11)
                        set (DirectX_D3D11_FOUND TRUE)
                    else ()
                        set (DirectX_D3D9_FOUND TRUE)
                        set (DirectX_D3D_FOUND TRUE)
                    endif ()
                endif ()
            endif ()
        endif ()
        if (DIRECTX_LIBRARY_DIRS)
            list (REMOVE_DUPLICATES DIRECTX_LIBRARY_DIRS)
        endif ()
    endif ()
    if (MINGW)
        set (FAIL_MESSAGE "Could NOT find DirectX using MinGW default search paths")
    else ()
        set (FAIL_MESSAGE "Could NOT find DirectX using DirectX SDK default search paths")
    endif ()
    mark_as_advanced (DIRECTX_INCLUDE_DIRS)
endif ()

# Windows SDK can be used on VS2012 and above
if (MSVC_VERSION GREATER 1600 OR MINGW)     # MinGW meets both conditional checks intentionally
    if (NOT URHO3D_OPENGL)
        if (MINGW)
            # Search the corresponding DLL for the found d3dcompiler "import library"
            if (D3DCOMPILER_LIB_NAME STREQUAL d3dcompiler)
                set (DIRECT3D_DLL_NAMES d3dcompiler_43.dll)
            else ()
                set (DIRECT3D_DLL_NAMES ${D3DCOMPILER_LIB_NAME}.dll)
            endif ()
        else ()
            set (DIRECT3D_DLL_NAMES d3dcompiler_47.dll d3dcompiler_46.dll)
        endif ()
        find_file (DIRECT3D_DLL NAMES ${DIRECT3D_DLL_NAMES} PATHS
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v10.0;InstallationFolder]/Redist/D3D/${PATH_SUFFIX}"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v8.1;InstallationFolder]/Redist/D3D/${PATH_SUFFIX}"
            "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v8.0;InstallationFolder]/Redist/D3D/${PATH_SUFFIX}"
            DOC "Direct3D DLL"
            NO_DEFAULT_PATH)    # Do not use default paths such as the PATH variable, to potentially avoid using a wrong architecture DLL
        if (DIRECT3D_DLL AND NOT MINGW)
            set (USE_WINSDK_DIRECTX TRUE)
            set (HAVE_DIRECTX TRUE)
            if (URHO3D_D3D11)
                set (DIRECT3D_LIBRARIES d3dcompiler d3d11 dxgi dxguid)
                set (DirectX_D3D11_FOUND TRUE)
            else ()
                set (DIRECT3D_LIBRARIES d3dcompiler d3d9)
                set (DirectX_D3D9_FOUND TRUE)
                set (DirectX_D3D_FOUND TRUE)
            endif ()
            # The headers and libraries are in Windows default search paths
            unset (DIRECTX_INCLUDE_DIRS)
            unset (DIRECTX_LIBRARY_DIRS)
            set (FAIL_MESSAGE "Could NOT find DirectX using Windows SDK search paths")
        endif ()
        mark_as_advanced (DIRECT3D_DLL)
    endif ()
endif ()

# For now take shortcut for the other DirectX components by just checking on the headers and not the libraries
include (CheckIncludeFiles)
include (CheckIncludeFile)
foreach (NAME ${DIRECTX_HEADERS})
    string (REPLACE . _ BASE_NAME ${NAME})
    string (TOUPPER ${BASE_NAME} UPCASE_NAME)
    if (NAME STREQUAL xinput.h)
        # Workaround an issue in finding xinput.h using check_include_file() as it depends on windows.h but not included it by itself in WinSDK
        check_include_files (windows.h\;${NAME} HAVE_${UPCASE_NAME})
    else ()
        check_include_file (${NAME} HAVE_${UPCASE_NAME})
    endif ()
endforeach ()
if (HAVE_D3D9_H)
    set (HAVE_D3D_H TRUE)
endif ()
foreach (COMPONENT DInput DSound XAudio2 XInput)
    string (TOUPPER ${COMPONENT} UPCASE_NAME)
    if (HAVE_${UPCASE_NAME}_H)
        set (DirectX_${COMPONENT}_FOUND TRUE)
        set (HAVE_DIRECTX TRUE)
    endif ()
endforeach ()
set (CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES_SAVED})

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (DirectX REQUIRED_VARS HAVE_DIRECTX HANDLE_COMPONENTS FAIL_MESSAGE ${FAIL_MESSAGE})
