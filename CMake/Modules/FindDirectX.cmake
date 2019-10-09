#
# Copyright (c) 2008-2019 the Urho3D project.
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
#  USE_WINSDK_DIRECTX (TRUE when using Windows SDK or FALSE when using DirectX SDK; not defined when using MinGW)
#
# When corresponding component is being searched for and found:
#  DirectX_D3D_FOUND (Currently synonym to DirectX_D3D9_FOUND)
#  DirectX_D3D9_FOUND
#  DirectX_D3D11_FOUND
#  DirectX_DInput_FOUND
#  DirectX_DSound_FOUND
#  DirectX_XInput_FOUND
#
# When any of the Direct3D components is being searched for and found:
#  DIRECT3D_LIBRARIES
#  DIRECT3D_DLL
#

set (DIRECTX_HEADERS d3dcompiler.h d3d9.h d3d11.h ddraw.h dsound.h dinput.h dxgi.h xinput.h)

# When corresponding header listed above is found:
#  HAVE_<UPCASE_NAME>_H
#  HAVE_XINPUT_GAMEPAD_EX
#  HAVE_XINPUT_STATE_EX
#  HAVE_D3D_H (Currently synonym to HAVE_D3D9_H)
#

# Optional input variables (see corresponding code comments for details):
#  DIRECTX_INC_SEARCH_PATHS
#  DIRECTX_LIB_SEARCH_PATHS
#  DIRECT3D_DLL_REDIST_SEARCH_PATHS
#

if (CMAKE_CL_64)
    set (PATH_SUFFIX x64)
else ()
    set (PATH_SUFFIX x86)
endif ()
set (CMAKE_REQUIRED_INCLUDES_SAVED ${CMAKE_REQUIRED_INCLUDES})

# Version older than VS2012 fallbacks to search for the DirectX SDK
if (NOT MSVC_VERSION GREATER 1600 OR MINGW)     # MinGW reuses the logic below to check for the existence of DirectX headers and libraries
    if (MINGW)
        # Intentionally searching for d3dcompiler(_XX) libraries in this particular order, avoiding unversioned d3dcompiler library so we know exactly which DLL to use
        set (D3DCOMPILER_NAMES d3dcompiler_47 d3dcompiler_46 d3dcompiler_43 d3dcompiler_42)
        if (NOT MINGW_SYSROOT)
            if (DEFINED ENV{MINGW_SYSROOT})
                file (TO_CMAKE_PATH $ENV{MINGW_SYSROOT} MINGW_SYSROOT)
            else ()
                execute_process (COMMAND ${CMAKE_COMMAND} -E echo "#include <_mingw.h>" COMMAND ${CMAKE_C_COMPILER} -E -M - OUTPUT_FILE ${CMAKE_BINARY_DIR}/find_mingw_sysroot_output ERROR_QUIET)
                file (STRINGS ${CMAKE_BINARY_DIR}/find_mingw_sysroot_output MINGW_SYSROOT REGEX _mingw\\.h)
                string (REGEX REPLACE "^[^ ]* *(.*)/include.*$" \\1 MINGW_SYSROOT "${MINGW_SYSROOT}")  # Stringify for string replacement
                string (REPLACE "\\ " " " MINGW_SYSROOT "${MINGW_SYSROOT}")
                execute_process (COMMAND ${CMAKE_COMMAND} -E remove find_mingw_sysroot_output)
            endif ()
            if (NOT EXISTS ${MINGW_SYSROOT})
                message (FATAL_ERROR "Could not find MinGW system root. "
                    "Use MINGW_SYSROOT environment variable or build option to specify the location of system root.")
            endif ()
            set (MINGW_SYSROOT ${MINGW_SYSROOT} CACHE PATH "Path to MinGW system root (MinGW only); should only be used when the system root could not be auto-detected" FORCE)
        endif ()
        # MinGW Cross-compiling uses CMAKE_FIND_ROOT_PATH while MinGW on Windows host uses CMAKE_PREFIX_PATH
        if (CMAKE_HOST_WIN32)
            set (CMAKE_PREFIX_PATH ${MINGW_SYSROOT})
        endif ()
        # MinGW does not usually need search paths as DirectX headers and libraries (when installed) are in its default search path
        # However, we do not explicitly unset the DIRECTX_INC_SEARCH_PATHS and DIRECTX_LIB_SEARCH_PATHS variables here, so module user could set these two variables externally when for some reasons the DirectX headers and libraries are not installed in MinGW default search path
    else ()
        set (D3DCOMPILER_NAMES d3dcompiler)
        # Module user could also prepopulate the DIRECTX_INC_SEARCH_PATHS and DIRECTX_LIB_SEARCH_PATHS variables externally when the following search paths do not work and the usage of DIRECTX_ROOT and DXSDK_DIR environment variables are not preferable
        list (APPEND DIRECTX_INC_SEARCH_PATHS
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
            "C:/Program Files/Microsoft DirectX SDK (June 2010)/Include"
            $ENV{DIRECTX_ROOT}/Include
            $ENV{DXSDK_DIR}/Include)
        list (APPEND DIRECTX_LIB_SEARCH_PATHS
            "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/${PATH_SUFFIX}"
            "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib/${PATH_SUFFIX}"
            $ENV{DIRECTX_ROOT}/Lib/${PATH_SUFFIX}
            $ENV{DXSDK_DIR}/Lib/${PATH_SUFFIX})
        if (NOT CMAKE_CL_64)
            list (APPEND DIRECTX_LIB_SEARCH_PATHS
                "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib"
                "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib"
                $ENV{DIRECTX_ROOT}/Lib
                $ENV{DXSDK_DIR}/Lib)
        endif ()
    endif ()
    find_path (DIRECTX_INCLUDE_DIRS NAMES ${DIRECTX_HEADERS} PATHS ${DIRECTX_INC_SEARCH_PATHS} DOC "DirectX include directory" CMAKE_FIND_ROOT_PATH_BOTH)
    if (DIRECTX_INCLUDE_DIRS)
        set (CMAKE_REQUIRED_INCLUDES ${DIRECTX_INCLUDE_DIRS})
        set (DIRECTX_LIBRARY_DIRS)
        set (DIRECT3D_LIBRARIES)
        find_library (DIRECTX_D3DCOMPILER NAMES ${D3DCOMPILER_NAMES} PATHS ${DIRECTX_LIB_SEARCH_PATHS} DOC "DirectX d3dcompiler library" CMAKE_FIND_ROOT_PATH_BOTH)
        if (DIRECTX_D3DCOMPILER)
            get_filename_component (NAME ${DIRECTX_D3DCOMPILER} NAME)
            string (REGEX REPLACE "^.*(d3dcompiler[_0-9]*).*$" \\1 D3DCOMPILER_LIB_NAME ${NAME})
            if (DirectX_FIND_REQUIRED_D3D11)
                set (DIRECT3D_LIB_NAMES d3d11 dxgi dxguid)
            else ()
                set (DIRECT3D_LIB_NAMES d3d9)
                if (NOT DirectX_FIND_REQUIRED_D3D AND NOT DirectX_FIND_REQUIRED_D3D9)
                    # When using OpenGL we still want to reuse the logic below to find the DirectX library directory
                    set (NO_DIRECT3D_COMPONENTS TRUE)
                endif ()
            endif ()
            foreach (NAME ${D3DCOMPILER_LIB_NAME} ${DIRECT3D_LIB_NAMES})
                string (REGEX REPLACE _[0-9]+$ "" BASE_NAME ${NAME})
                string (TOUPPER ${BASE_NAME} UPCASE_NAME)
                find_library (DIRECTX_${UPCASE_NAME} NAMES ${NAME} PATHS ${DIRECTX_LIB_SEARCH_PATHS} DOC "DirectX ${BASE_NAME} library" CMAKE_FIND_ROOT_PATH_BOTH)
                if (DIRECTX_${UPCASE_NAME})
                    get_filename_component (PATH ${DIRECTX_${UPCASE_NAME}} PATH)
                    list (APPEND DIRECTX_LIBRARY_DIRS ${PATH})      # All the libs should be found in a same place, but just in case
                    if (NOT NO_DIRECT3D_COMPONENTS)     # Discard the result when Direct3D component is not required
                        list (APPEND DIRECT3D_LIBRARIES ${NAME})
                    endif ()
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
                if (DirectX_FIND_REQUIRED_D3D11)
                    set (DirectX_D3D11_FOUND TRUE)
                elseif (DirectX_FIND_REQUIRED_D3D OR DirectX_FIND_REQUIRED_D3D9)
                    set (DirectX_D3D9_FOUND TRUE)
                    set (DirectX_D3D_FOUND TRUE)
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
if (MSVC_VERSION GREATER 1600 OR MINGW)     # MinGW reuses the logic below to find the runtime DLL for d3dcompiler library
    if (MINGW)
        # Search the corresponding DLL for the found d3dcompiler "import library"
        set (DIRECT3D_DLL_NAMES ${D3DCOMPILER_LIB_NAME}.dll)
        # Module user using older MinGW version could also prepopulate the DIRECT3D_DLL_REDIST_SEARCH_PATHS variable externally when the following search paths do not work, especially when older d3dcompiler_43.dll and d3dcompiler_42.dll is expected to be found elsewhere
    else ()
        set (DIRECT3D_DLL_NAMES d3dcompiler_47.dll d3dcompiler_46.dll)
        set (DIRECT3D_DLL_REDIST_SEARCH_PATHS)
    endif ()
    foreach (VERSION 10.0 8.1 8.0)
        list (APPEND DIRECT3D_DLL_REDIST_SEARCH_PATHS "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v${VERSION};InstallationFolder]/Redist/D3D/${PATH_SUFFIX}")
    endforeach ()
    find_file (DIRECT3D_DLL NAMES ${DIRECT3D_DLL_NAMES} PATHS ${DIRECT3D_DLL_REDIST_SEARCH_PATHS} DOC "Direct3D DLL"
        NO_DEFAULT_PATH)    # Do not use default paths such as the PATH variable, to potentially avoid using a wrong architecture DLL
    if (DIRECT3D_DLL AND NOT MINGW)
        set (USE_WINSDK_DIRECTX TRUE)
        set (HAVE_DIRECTX TRUE)
        if (DirectX_FIND_REQUIRED_D3D11)
            set (DIRECT3D_LIBRARIES d3dcompiler d3d11 dxgi dxguid)
            set (DirectX_D3D11_FOUND TRUE)
        elseif (DirectX_FIND_REQUIRED_D3D OR DirectX_FIND_REQUIRED_D3D9)
            set (DIRECT3D_LIBRARIES d3dcompiler d3d9)
            set (DirectX_D3D9_FOUND TRUE)
            set (DirectX_D3D_FOUND TRUE)
        endif ()
    endif ()
    mark_as_advanced (DIRECT3D_DLL)
    # The headers and libraries are in default search paths for both Windows SDK and MinGW, so set the search path variables to empty now
    set (DIRECTX_INCLUDE_DIRS "")   # Need to be very explicit here because these variables are cached on MinGW, this is one way to reset the variables without losing the cached values
    set (DIRECTX_LIBRARY_DIRS "")
    if (NOT DirectX_FIND_REQUIRED_D3D11 AND NOT DirectX_FIND_REQUIRED_D3D AND NOT DirectX_FIND_REQUIRED_D3D9)
        set (DIRECT3D_DLL "")
    endif ()
    if (NOT MINGW)
        set (FAIL_MESSAGE "Could NOT find DirectX using Windows SDK search paths")
    endif ()
endif ()

# For now take shortcut for the other DirectX components by just checking on the headers and not the libraries
include (CheckIncludeFiles)
include (CheckIncludeFileCXX)
include (CheckStructHasMember)
foreach (NAME ${DIRECTX_HEADERS})
    string (REPLACE . _ BASE_NAME ${NAME})
    string (TOUPPER ${BASE_NAME} UPCASE_NAME)
    if (NAME STREQUAL xinput.h)
        # Workaround an issue in finding xinput.h using check_include_file() as it depends on windows.h but not included it by itself in WinSDK
        check_include_files (windows.h\;${NAME} HAVE_${UPCASE_NAME})
        check_struct_has_member (XINPUT_GAMEPAD_EX wButtons xinput.h HAVE_XINPUT_GAMEPAD_EX)
        check_struct_has_member (XINPUT_STATE_EX dwPacketNumber xinput.h HAVE_XINPUT_STATE_EX)
    else ()
        check_include_file_cxx (${NAME} HAVE_${UPCASE_NAME})
    endif ()
endforeach ()
if (HAVE_D3D9_H)
    set (HAVE_D3D_H TRUE)
endif ()
foreach (COMPONENT DInput DSound XInput)
    string (TOUPPER ${COMPONENT} UPCASE_NAME)
    if (HAVE_${UPCASE_NAME}_H)
        set (DirectX_${COMPONENT}_FOUND TRUE)
        set (HAVE_DIRECTX TRUE)
    endif ()
endforeach ()
set (CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES_SAVED})

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (DirectX REQUIRED_VARS HAVE_DIRECTX HANDLE_COMPONENTS FAIL_MESSAGE ${FAIL_MESSAGE})
