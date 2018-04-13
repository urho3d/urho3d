#
# This file was taken from RakNet 4.082.
# Please see licenses/RakNet license.txt for the underlying license and related copyright.
#
#
#
# Modified work: Copyright (c) 2016, SLikeSoft UG (haftungsbeschränkt)
#
# This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
# license found in the license.txt file in the root directory of this source tree.
#

cmake_minimum_required(VERSION 2.6)

# project(SLikeNet)

# Define target name
set (TARGET_NAME SLikeNet)

add_definitions (-DRAKNET_ENABLE_STATIC)

# CMake policy settings
if( POLICY CMP0037 )
    cmake_policy(SET CMP0037 NEW) # CMake 3.0 warning: Target names should not be reserved and should match a validity pattern (aka: add_*-command target names)
endif()
if( POLICY CMP0042 )
    cmake_policy(SET CMP0042 NEW) # CMake 3.0 warning: Use @rpath in a target's install name.
endif()

# explicitly enable @rpath in the install name for any shared library being built (for cmake >=2.8.12 and <3.0 - it's enabled by default for >= 3.0)
# note that for cmake < 2.8.12 we do not use rpath but rather keep the RakNet 4.082 behavior
if( CMAKE_VERSION VERSION_LESS 3.0 )
    if(NOT (CMAKE_VERSION VERSION_LESS 2.8.12))
        # MACOSX_RPATH support was added in cmake 2.8.12
        set(CMAKE_MACOSX_RPATH 1)
    endif()
endif()


if( NOT APPLE )
# check 64 bit
if( CMAKE_SIZEOF_VOID_P MATCHES "4" )
  set( HAVE_64_BIT 0 )
else(  CMAKE_SIZEOF_VOID_P MATCHES "4")
  set( HAVE_64_BIT 1 )
endif(  CMAKE_SIZEOF_VOID_P MATCHES "4")
endif( NOT APPLE )

IF (WIN32 AND NOT UNIX)
    set (PROGRAMFILESX86 $ENV{PROGRAMFILES})
    string(REPLACE "\\" "/" PROGRAMFILESX86 "${PROGRAMFILESX86}")
ENDIF(WIN32 AND NOT UNIX)

IF (WIN32 AND NOT UNIX)
    set(RAKNET_LIBRARY_LIBS ws2_32.lib)
ELSE(WIN32 AND NOT UNIX)
    set(RAKNET_LIBRARY_LIBS pthread)
ENDIF(WIN32 AND NOT UNIX)

# enable C++11 language support for GCC
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#option( RAKNET_ENABLE_DLL       "Generate the DLL project if true."             TRUE )
#option( RAKNET_ENABLE_STATIC    "Generate the static library project if true."  TRUE )
#option( RAKNET_GENERATE_INCLUDE_ONLY_DIR "Setup a include/RakNet/ directory in which all the headers are copied." FALSE )

#set( RAKNETHEADERFILES ${RakNet_SOURCE_DIR}/Source ) #This name doesn't follow CMake conventions but for retro compatibility I'll let it there.

# if( RAKNET_GENERATE_INCLUDE_ONLY_DIR )
#     set( RAKNET_INCLUDE_ONLY_DIR ${RakNet_SOURCE_DIR}/include ) # this will be visible by client code
#     set( RAKNET_NAMED_INCLUDE_ONLY_DIR ${RAKNET_INCLUDE_ONLY_DIR}/RakNet )
#     message( STATUS "Setting up the ${RAKNET_NAMED_INCLUDE_ONLY_DIR} directory..." )
#     # Now setup the include/RakNet/*.h files.
#     file( MAKE_DIRECTORY ${RAKNET_NAMED_INCLUDE_ONLY_DIR} )
#     file( COPY ${RAKNETHEADERFILES}/ DESTINATION ${RAKNET_NAMED_INCLUDE_ONLY_DIR} FILES_MATCHING PATTERN "*.h"  )
#     message( STATUS "DONE: Setting up the ${RAKNET_NAMED_INCLUDE_ONLY_DIR} directory." )
# endif()

#set( RAKNET_INCLUDE_DIRS ${RAKNETHEADERFILES} ${RAKNET_INCLUDE_ONLY_DIR} ) # Visible from outside

include(./CmakeIncludes/CmakeMacros.txt)
FIXLINKOPTIONS()
if (NOT MINGW)
    FIXCOMPILEOPTIONS()
endif()

#set(RAKNET_COMMON_LIBS RakNetLibStatic)

# Define source files
file (GLOB_RECURSE CPP_FILES *.cpp source)
file (GLOB_RECURSE H_FILES *.h include)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS src/include)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (install dependency for Urho3D)
install_header_files (DIRECTORY src/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SLikeNet FILES_MATCHING PATTERN *.h USE_FILE_SYMLINK)
