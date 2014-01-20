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

file (GLOB kNetSourceFiles ./src/*.cpp)
file (GLOB kNetHeaderFiles ./include/*.h ./include/kNet/*.h ./include/kNet/*.inl)

if (WIN32)
   file (GLOB kNetWin32SourceFiles ./src/win32/*.cpp)
   file (GLOB kNetWin32HeaderFiles ./include/kNet/win32/*.h)

   if (USE_BOOST)
      list (REMOVE_ITEM kNetWin32SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/./src/win32/W32Thread.cpp)
   endif ()

   set (kNetSourceFiles ${kNetSourceFiles} ${kNetWin32SourceFiles})
   set (kNetHeaderFiles ${kNetHeaderFiles} ${kNetWin32HeaderFiles})

   add_definitions (-D_WINSOCKAPI_)
   add_definitions (-D_CRT_SECURE_NO_WARNINGS)
   add_definitions (-DKNET_MEMORY_LEAK_CHECK)
elseif (UNIX)
   list (REMOVE_ITEM kNetSourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/./src/Clock.cpp)
   file (GLOB kNetUnixSourceFiles ./src/unix/*.cpp)
   file (GLOB kNetUnixHeaderFiles ./include/*.h ./include/kNet/*.h ./include/kNet/unix/*.h)

   if (USE_BOOST)
      list (REMOVE_ITEM kNetUnixSourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/./src/unix/UnixThread.cpp)
   endif ()

   set (kNetSourceFiles ${kNetSourceFiles} ${kNetUnixSourceFiles})
   set (kNetHeaderFiles ${kNetHeaderFiles} ${kNetUnixHeaderFiles})

   add_definitions (-DUNIX)
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
# Install dependency for Engine/Network/Connection.h and Engine/Network/Network.h
install (DIRECTORY include/ DESTINATION ${DEST_INCLUDE_DIR}/kNet USE_SOURCE_PERMISSIONS FILES_MATCHING PATTERN *.h PATTERN *.inl)     # Note: the trailing slash is significant
set (INSTALL_INCLUDE_DIRS ${INSTALL_INCLUDE_DIRS} kNet PARENT_SCOPE)
if (APPLE)
    set (AMALG_EXCLUDES UnixClock)
endif ()

# Define dependency libs
set (INCLUDE_DIRS_ONLY include)

# Setup target
setup_library ()
