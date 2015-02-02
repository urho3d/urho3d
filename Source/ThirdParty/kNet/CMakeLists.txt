# Copyright 2010 Jukka Jylänki

#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at

#      http://www.apache.org/licenses/LICENSE-2.0

#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

# Modified by Lasse Oorni and Yao Wei Tjong for Urho3D

set (TARGET_NAME kNet)

file (GLOB kNetSourceFiles src/*.cpp)
file (GLOB kNetHeaderFiles include/*.h include/kNet/*.h include/kNet/*.inl)

if (WIN32)
   file (GLOB kNetWin32SourceFiles src/win32/*.cpp)
   file (GLOB kNetWin32HeaderFiles include/kNet/win32/*.h)

   if (USE_BOOST)
      list (REMOVE_ITEM kNetWin32SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/src/win32/W32Thread.cpp)
   endif ()

   list (APPEND kNetSourceFiles ${kNetWin32SourceFiles})
   list (APPEND kNetHeaderFiles ${kNetWin32HeaderFiles})

   add_definitions (-D_WINSOCKAPI_)
   add_definitions (-D_CRT_SECURE_NO_WARNINGS)
   add_definitions (-DKNET_MEMORY_LEAK_CHECK)
elseif (UNIX)
   file (GLOB kNetUnixSourceFiles src/unix/*.cpp)
   file (GLOB kNetUnixHeaderFiles include/*.h include/kNet/*.h include/kNet/unix/*.h)

   if (USE_BOOST)
      list (REMOVE_ITEM kNetUnixSourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/src/unix/UnixThread.cpp)
   endif ()

   list (APPEND kNetSourceFiles ${kNetUnixSourceFiles})
   list (APPEND kNetHeaderFiles ${kNetUnixHeaderFiles})

   add_definitions (-DKNET_UNIX)
endif ()

# Urho3D: set DEBUG_CPP_NAME only on Windows, Xcode project file can not be opened if this is included
if (WIN32)
    foreach (srcFile ${kNetSourceFiles})
        get_filename_component (baseName ${srcFile} NAME)
        set_source_files_properties (${srcFile} PROPERTIES COMPILE_FLAGS "-DDEBUG_CPP_NAME=\"\\\"${baseName}\"\\\"")
    endforeach ()
endif ()

# Define source files
set (SOURCE_FILES ${kNetSourceFiles} ${kNetHeaderFiles})

# Define dependency libs
set (INCLUDE_DIRS include)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (install dependency for Urho3D/Network/Connection.h and Urho3D/Network/Network.h)
install_header_files (DIRECTORY include/kNet/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/kNet FILES_MATCHING PATTERN *.h *.inl USE_FILE_SYMLINK)     # Note: the trailing slash is significant
file (GLOB kNetHeaderFiles include/*.h)
install_header_files (FILES ${kNetHeaderFiles} DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/kNet)
