# Open Asset Import Library (assimp)
# ----------------------------------------------------------------------
# Copyright (c) 2006-2019, assimp team
#
# All rights reserved.
#
# Redistribution and use of this software in source and binary forms,
# with or without modification, are permitted provided that the
# following conditions are met:
#
# * Redistributions of source code must retain the above
#   copyright notice, this list of conditions and the
#   following disclaimer.
#
# * Redistributions in binary form must reproduce the above
#   copyright notice, this list of conditions and the
#   following disclaimer in the documentation and/or other
#   materials provided with the distribution.
#
# * Neither the name of the assimp team, nor the names of its
#   contributors may be used to endorse or promote products
#   derived from this software without specific prior
#   written permission of the assimp team.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#----------------------------------------------------------------------

# Modified for Urho3D

SET(CMAKE_POLICY_DEFAULT_CMP0074 NEW)

CMAKE_MINIMUM_REQUIRED( VERSION 3.0 )

PROJECT( Assimp VERSION 5.0.0 )

# All supported options ###############################################
# Urho3D: removed shared lib, android/ios, package detection flags

OPTION( ASSIMP_DOUBLE_PRECISION
  "Set to ON to enable double precision processing"
  OFF
)
OPTION( ASSIMP_NO_EXPORT
  "Disable Assimp's export functionality."
  OFF
)
OPTION( INJECT_DEBUG_POSTFIX
  "Inject debug postfix in .a/.so/.dll lib names"
  ON
)
OPTION ( IGNORE_GIT_HASH
   "Don't call git to get the hash."
   ON
)

# Use subset of Windows.h
if (WIN32)
  ADD_DEFINITIONS( -DWIN32_LEAN_AND_MEAN )
endif()

IF(MSVC)
  OPTION( ASSIMP_INSTALL_PDB
    "Install MSVC debug files."
    ON
  )
  IF(NOT (MSVC_VERSION LESS 1900))
    # Multibyte character set is deprecated since at least MSVC2015 (possibly earlier)
    ADD_DEFINITIONS( -DUNICODE -D_UNICODE )
  ENDIF()
ENDIF(MSVC)

# Define here the needed parameters
SET (ASSIMP_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
SET (ASSIMP_VERSION_MINOR ${PROJECT_VERSION_MINOR})
SET (ASSIMP_VERSION_PATCH ${PROJECT_VERSION_PATCH})
SET (ASSIMP_VERSION ${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}.${ASSIMP_VERSION_PATCH})
SET (ASSIMP_SOVERSION 5)

SET( ASSIMP_PACKAGE_VERSION "0" CACHE STRING "the package-specific version used for uploading the sources" )

# Enable C++11 support globally
set_property( GLOBAL PROPERTY CXX_STANDARD 11 )

IF(NOT IGNORE_GIT_HASH)
  # Get the current working branch
  EXECUTE_PROCESS(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )

  # Get the latest abbreviated commit hash of the working branch
  EXECUTE_PROCESS(
    COMMAND git rev-parse --short=8 HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
ENDIF()

IF(NOT GIT_COMMIT_HASH)
    SET(GIT_COMMIT_HASH 0)
ENDIF(NOT GIT_COMMIT_HASH)

IF(ASSIMP_DOUBLE_PRECISION)
    ADD_DEFINITIONS(-DASSIMP_DOUBLE_PRECISION)
ENDIF(ASSIMP_DOUBLE_PRECISION)

CONFIGURE_FILE(
  ${CMAKE_CURRENT_LIST_DIR}/revision.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/revision.h
)

CONFIGURE_FILE(
  ${CMAKE_CURRENT_LIST_DIR}/include/assimp/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/assimp/config.h
)

# Urho3D: pulled up from zlib's CMakeLists.txt
CONFIGURE_FILE(
  ${CMAKE_CURRENT_SOURCE_DIR}/contrib/zlib/zconf.h.cmakein
  ${CMAKE_CURRENT_BINARY_DIR}/contrib/zlib/zconf.h @ONLY
)

# Explicitly turn off ASM686 and AMD64 cmake options.
# The AMD64 option causes a build failure on MSVC and the ASM builds seem to have problems:
#		https://github.com/madler/zlib/issues/41#issuecomment-125848075
# Also prevents these options from "polluting" the cmake options if assimp is being
# included as a submodule.
set( ASM686 FALSE CACHE INTERNAL "Override ZLIB flag to turn off assembly" FORCE )
set( AMD64 FALSE CACHE INTERNAL "Override ZLIB flag to turn off assembly" FORCE )

INCLUDE_DIRECTORIES( BEFORE
  ./
  code/
  include
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/include
)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules" )

# Grouped compiler settings
IF ((CMAKE_C_COMPILER_ID MATCHES "GNU") AND NOT CMAKE_COMPILER_IS_MINGW)
  IF(NOT HUNTER_ENABLED)
    SET(CMAKE_CXX_FLAGS "-fPIC -std=c++0x ${CMAKE_CXX_FLAGS}")
    SET(CMAKE_C_FLAGS "-fPIC ${CMAKE_C_FLAGS}")
  ENDIF()
  # hide all not-exported symbols
  SET(CMAKE_CXX_FLAGS "-g -fvisibility=hidden -fno-strict-aliasing -Wall ${CMAKE_CXX_FLAGS}")
  SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
  SET(LIBSTDC++_LIBRARIES -lstdc++)
ELSEIF(MSVC)
  # enable multi-core compilation with MSVC
  ADD_COMPILE_OPTIONS(/MP)
  ADD_COMPILE_OPTIONS( /bigobj )
  # disable "elements of array '' will be default initialized" warning on MSVC2013
  IF(MSVC12)
    ADD_COMPILE_OPTIONS(/wd4351)
  ENDIF()
  SET(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Ob2 /DEBUG:FULL /Zi")
ELSEIF ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
  IF(NOT HUNTER_ENABLED)
    SET(CMAKE_CXX_FLAGS "-fPIC -std=c++11 ${CMAKE_CXX_FLAGS}")
    SET(CMAKE_C_FLAGS "-fPIC ${CMAKE_C_FLAGS}")
  ENDIF()
  SET(CMAKE_CXX_FLAGS "-g -fvisibility=hidden -fno-strict-aliasing -Wall -Wno-long-long ${CMAKE_CXX_FLAGS}" )
  SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
ELSEIF( CMAKE_COMPILER_IS_MINGW )
  IF (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0)
    message(FATAL_ERROR "MinGW is too old to be supported. Please update MinGW and try again.")
  ELSEIF(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.3)
    message(WARNING "MinGW is old, if you experience errors, update MinGW.")
  ENDIF()
  IF(NOT HUNTER_ENABLED)
    SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    SET(CMAKE_C_FLAGS "-fPIC ${CMAKE_C_FLAGS}")
  ENDIF()
  SET(CMAKE_CXX_FLAGS "-fvisibility=hidden -fno-strict-aliasing -Wall -Wno-long-long -Wa,-mbig-obj -O3 ${CMAKE_CXX_FLAGS}")
  SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
  ADD_DEFINITIONS( -U__STRICT_ANSI__ )
ENDIF()

# Urho3D: remove IOS settings

get_cmake_property(is_multi_config GENERATOR_IS_MULTI_CONFIG)

IF (INJECT_DEBUG_POSTFIX AND (is_multi_config OR CMAKE_BUILD_TYPE STREQUAL "Debug"))
  SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Debug Postfix for lib, samples and tools")
ELSE()
  SET(CMAKE_DEBUG_POSTFIX "" CACHE STRING "Debug Postfix for lib, samples and tools")
ENDIF()

IF ( ASSIMP_NO_EXPORT )
  ADD_DEFINITIONS( -DASSIMP_BUILD_NO_EXPORT)
  MESSAGE( STATUS "Build an import-only version of Assimp." )
ENDIF( ASSIMP_NO_EXPORT )

SET ( ASSIMP_BUILD_ARCHITECTURE "" CACHE STRING
  "describe the current architecture."
)
IF    ( ASSIMP_BUILD_ARCHITECTURE STREQUAL "")
ELSE  ( ASSIMP_BUILD_ARCHITECTURE STREQUAL "")
  ADD_DEFINITIONS ( -D'ASSIMP_BUILD_ARCHITECTURE="${ASSIMP_BUILD_ARCHITECTURE}"' )
ENDIF ( ASSIMP_BUILD_ARCHITECTURE STREQUAL "")

# ${CMAKE_GENERATOR}
SET ( ASSIMP_BUILD_COMPILER "" CACHE STRING
  "describe the current compiler."
)
IF    ( ASSIMP_BUILD_COMPILER STREQUAL "")
ELSE  ( ASSIMP_BUILD_COMPILER STREQUAL "")
  ADD_DEFINITIONS ( -D'ASSIMP_BUILD_COMPILER="${ASSIMP_BUILD_COMPILER}"' )
ENDIF ( ASSIMP_BUILD_COMPILER STREQUAL "")

MARK_AS_ADVANCED ( ASSIMP_BUILD_ARCHITECTURE ASSIMP_BUILD_COMPILER )

SET ( ASSIMP_BUILD_NONFREE_C4D_IMPORTER OFF CACHE BOOL
  "Build the C4D importer, which relies on the non-free Melange SDK."
)

IF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)
  IF ( MSVC )
    SET(C4D_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/contrib/Melange/includes")

    # pick the correct prebuilt library
    IF(MSVC15)
      SET(C4D_LIB_POSTFIX "_2017")
    ELSEIF(MSVC14)
      SET(C4D_LIB_POSTFIX "_2015")
    ELSEIF(MSVC12)
      SET(C4D_LIB_POSTFIX "_2013")
    ELSEIF(MSVC11)
      SET(C4D_LIB_POSTFIX "_2012")
    ELSEIF(MSVC10)
      SET(C4D_LIB_POSTFIX "_2010")
    ELSE()
      MESSAGE( FATAL_ERROR
        "C4D is currently only supported with MSVC 10, 11, 12, 14"
      )
    ENDIF()

    SET(C4D_LIB_BASE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/contrib/Melange/libraries/win")

    SET(C4D_DEBUG_LIBRARIES
      "${C4D_LIB_BASE_PATH}/melangelib${C4D_LIB_POSTFIX}/melangelib_debug.lib"
      "${C4D_LIB_BASE_PATH}/jpeglib${C4D_LIB_POSTFIX}/jpeglib_debug.lib"
    )
    SET(C4D_RELEASE_LIBRARIES
      "${C4D_LIB_BASE_PATH}/melangelib${C4D_LIB_POSTFIX}/melangelib_release.lib"
      "${C4D_LIB_BASE_PATH}/jpeglib${C4D_LIB_POSTFIX}/jpeglib_release.lib"
    )

    # winsock and winmm are necessary dependencies of melange (this is undocumented, but true.)
    SET(C4D_EXTRA_LIBRARIES WSock32.lib Winmm.lib)
  ELSE ()
    MESSAGE( FATAL_ERROR
      "C4D is currently only available on Windows with melange SDK installed in contrib/Melange"
    )
  ENDIF ( MSVC )
ELSE (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)
  ADD_DEFINITIONS( -DASSIMP_BUILD_NO_C4D_IMPORTER )
ENDIF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)

ADD_SUBDIRECTORY( code/ )
#ADD_SUBDIRECTORY(contrib/)
