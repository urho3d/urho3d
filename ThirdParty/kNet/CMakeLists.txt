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

# Modified by Lasse Öörni for Urho3D

# Generate a build configuration file to ensure the build flags match for the user of the library.
SET(BUILD_CONFIG_FILE include/kNetBuildConfig.h)
file(WRITE ${BUILD_CONFIG_FILE} "// This file is programmatically generated using CMake.\n// This file shows the compilation settings that were used to build kNet.\n// These need to match for the client code using kNet.\n")
file(APPEND ${BUILD_CONFIG_FILE} "#pragma once\n\n")

macro(AddCompilationDefine define)
   add_definitions(-D${define})
   file(APPEND ${BUILD_CONFIG_FILE} "#ifndef ${define}\n#define ${define}\n#endif\n\n")
endmacro()

#set(USE_BOOST TRUE)
#set(BOOST_ROOT "TODO_SpecifyYourBoostRootHereIfCMakeAutoSearchFails")

# TinyXML is embedded to the repository, so you can safely keep this true.
# However, it is not required for core kNet use, but only for the MessageCompiler tool, in which
# case you can disable it here by setting USE_TINYXML to FALSE, and excluding MessageCompiler from the build.
#set(USE_TINYXML TRUE)
set(TINYXML_ROOT "src/tinyxml")

# If you want to enable the use of visual debugging/profiling windows, uncomment the following line (must
# have Qt installed and set up)
#set(USE_QT TRUE)

# To enable specific flags only in debug mode, use the following syntax.
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DKNET_LOGGING_SUPPORT_ENABLED")

# If set, the function GetThreadId is not used, which was introduced to Kernel32.dll only in Windows Vista.
# Affects only Boost threads. When native Win32 threads are used, the id is stored on creation.
AddCompilationDefine(KNET_ENABLE_WINXP_SUPPORT)

if (NOT USE_BOOST) # USE_BOOST and KNET_THREAD_CHECKING_ENABLED are mutually exclusive, because boost::thread_id() does not work across .dll boundaries.
   # If set, extra code is inserted in debug mode to assert that certain thread race conditions don't occur.
   # (This can considerably slow down kNet performance)
   #AddCompilationDefine(KNET_THREAD_CHECKING_ENABLED)
endif()

# Enable internal LOG messaging if this flag is enabled. Comment this out to squeeze the last bit of 
# extra performance by avoiding all logging-related string operations.
#AddCompilationDefine(KNET_LOGGING_SUPPORT_ENABLED)

# Enable storing profiling data from different network level events.
#AddCompilationDefine(KNET_NETWORK_PROFILING)

# Urho3D does not need message priorities. Disable MaxHeap for improved performance.
AddCompilationDefine(KNET_NO_MAXHEAP)

if (USE_BOOST)
   AddCompilationDefine(KNET_USE_BOOST)

   if (WIN32)
      set(Boost_FIND_REQUIRED TRUE)
      set(Boost_FIND_QUIETLY TRUE)
      set(Boost_DEBUG FALSE)
      set(Boost_USE_MULTITHREADED TRUE)
      set(Boost_DETAILED_FAILURE_MSG FALSE)
      set(Boost_ADDITIONAL_VERSIONS "1.39.0" "1.40.0" "1.41.0" "1.42.0" "1.43.0" "1.44.0")
      set(Boost_USE_STATIC_LIBS TRUE)
   endif()
endif()

file(GLOB kNetSourceFiles ./src/*.cpp)
file(GLOB kNetHeaderFiles ./include/*.h ./include/kNet/*.h ./include/kNet/*.inl)

if (USE_TINYXML)
   AddCompilationDefine(KNET_USE_TINYXML)
   
   file(GLOB TinyXmlSourceFiles ${TINYXML_ROOT}/*.cpp)
   set(kNetSourceFiles ${kNetSourceFiles} ${TinyXmlSourceFiles})
   include_directories(${TINYXML_ROOT})
endif()

if (USE_QT)
   AddCompilationDefine(KNET_USE_QT)
   
   set(QT_USE_QTMAIN TRUE)
   set(QT_USE_QTUITOOLS TRUE)
   find_package(Qt4 REQUIRED)
   
   file(GLOB kNetMocHeaderFiles ./include/kNet/qt/*.h)
   file(GLOB kNetQtSourceFiles ./src/qt/*.cpp)
   file(GLOB kNetQtUiFiles ./ui/*.ui)
   QT4_WRAP_CPP(kNetMocSrcFiles ${kNetMocHeaderFiles})
   set(QT4_UI_OUTPUT_DIR ./include/kNet/qt/ui)
   
   MACRO(QT4_WRAP_UI_CUSTOM_OUTPUT outfiles)
     QT4_EXTRACT_OPTIONS(ui_files ui_options ${ARGN})
     FOREACH(it ${ui_files})
       GET_FILENAME_COMPONENT(outfile ${it} NAME_WE)
       GET_FILENAME_COMPONENT(infile ${it} ABSOLUTE)
       SET(outfile ${QT4_UI_OUTPUT_DIR}/ui_${outfile}.h)
       GET_FILENAME_COMPONENT(outfile ${outfile} ABSOLUTE)
       ADD_CUSTOM_COMMAND(OUTPUT ${outfile}
         COMMAND ${QT_UIC_EXECUTABLE}
         ARGS ${ui_options} -o ${outfile} ${infile}
         MAIN_DEPENDENCY ${infile})
       SET(${outfiles} ${${outfiles}} ${outfile})
     ENDFOREACH()    
   ENDMACRO()   
   
  include_directories(${QT4_UI_OUTPUT_DIR})
  QT4_WRAP_UI_CUSTOM_OUTPUT(kNetUiHeaderFiles ${kNetQtUiFiles})
  set(kNetSourceFiles ${kNetSourceFiles} ${kNetMocSrcFiles} ${kNetQtSourceFiles})
  set(kNetHeaderFiles ${kNetHeaderFiles} ${kNetMocHeaderFiles} ${kNetUiHeaderFiles})
  include(${QT_USE_FILE})
  set(kNetLinkLibraries ${kNetLinkLibraries} ${QT_LIBRARIES})
endif()

if (USE_BOOST)
   file(GLOB kNetBoostSourceFiles ./src/boost/*.cpp)
   set(kNetSourceFiles ${kNetSourceFiles} ${kNetBoostSourceFiles})
endif()

if (WIN32)
   file(GLOB kNetWin32SourceFiles ./src/win32/*.cpp)
   file(GLOB kNetWin32HeaderFiles ./include/kNet/win32/*.h)

   if (USE_BOOST)
      list(REMOVE_ITEM kNetWin32SourceFiles ${PROJECT_SOURCE_DIR}/./src/win32/W32Thread.cpp)
   endif()

   set(kNetSourceFiles ${kNetSourceFiles} ${kNetWin32SourceFiles})
   set(kNetHeaderFiles ${kNetHeaderFiles} ${kNetWin32HeaderFiles})

   add_definitions(-D_WINSOCKAPI_)
   add_definitions(-D_CRT_SECURE_NO_WARNINGS)
   add_definitions(-DKNET_MEMORY_LEAK_CHECK)
   
   set(kNetLinkLibraries ${kNetLinkLibraries} ws2_32.lib)
   
elseif (UNIX)
   file(GLOB kNetUnixSourceFiles ./src/unix/*.cpp)
   file(GLOB kNetUnixHeaderFiles ./include/*.h ./include/kNet/*.h ./include/kNet/unix/*.h)

   if (USE_BOOST)
      list(REMOVE_ITEM kNetUnixSourceFiles ${PROJECT_SOURCE_DIR}/./src/unix/UnixThread.cpp)
   else()
      set(kNetLinkLibraries ${kNetLinkLibraries} pthread)
   endif()

   set(kNetSourceFiles ${kNetSourceFiles} ${kNetUnixSourceFiles})
   set(kNetHeaderFiles ${kNetHeaderFiles} ${kNetUnixHeaderFiles})

   add_definitions(-DUNIX)
endif()

# Urho3D: set DEBUG_CPP_NAME only on Windows, at least Xcode project file can not be opened if this is included
if (WIN32)
    foreach(srcFile ${kNetSourceFiles})
        get_filename_component(baseName ${srcFile} NAME)
        set_source_files_properties(${srcFile} PROPERTIES COMPILE_FLAGS "-DDEBUG_CPP_NAME=\"\\\"${baseName}\"\\\"")
    endforeach()
endif ()

add_library(kNet STATIC ${kNetSourceFiles} ${kNetHeaderFiles})

# Add the main kNet include directory root folder to all projects.
include_directories(./include)

if (USE_BOOST)
   if (WIN32)
      find_package(Boost 1.38.0 COMPONENTS thread)
   else()
      find_package(Boost)
   endif()
   if (Boost_FOUND)
      include_directories(${Boost_INCLUDE_DIRS})
      link_directories(${Boost_LIBRARY_DIRS})
   else()
      message(FATAL_ERROR "Boost not found!")
   endif()
   
   set(kNetLinkLibraries ${kNetLinkLibraries} ${Boost_LIBRARIES})   
endif()

target_link_libraries(kNet ${kNetLinkLibraries})

#add_subdirectory(samples/ConnectFlood)
#add_subdirectory(samples/FileTransfer)
#add_subdirectory(samples/FirewallTest)
#add_subdirectory(samples/HelloClient)
#add_subdirectory(samples/HelloServer)
#add_subdirectory(samples/LatencyTest)
#add_subdirectory(samples/MessageCompiler)
#add_subdirectory(samples/SilenceTest)
#add_subdirectory(samples/SimpleChat)
#add_subdirectory(samples/SpeedTest)
#add_subdirectory(samples/TrashTalk)

#add_subdirectory(tests)

