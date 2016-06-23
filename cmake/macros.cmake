#
# Simple DirectMedia Layer
# Copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
# claim that you wrote the original software. If you use this software
# in a product, an acknowledgment in the product documentation would be
# appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
# misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#

# Modified by Yao Wei Tjong for Urho3D, the modified portion is licensed under below license

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

macro(SET_OPTION _NAME _DESC)
  list(APPEND ALLOPTIONS ${_NAME})
  if(${ARGC} EQUAL 3)
    set(_DEFLT ${ARGV2})
  else()
    set(_DEFLT OFF)
  endif()
  option(${_NAME} ${_DESC} ${_DEFLT})
endmacro()

macro(DEP_OPTION _NAME _DESC _DEFLT _DEPTEST _FAILDFLT)
  list(APPEND ALLOPTIONS ${_NAME})
  cmake_dependent_option(${_NAME} ${_DESC} ${_DEFLT} ${_DEPTEST} ${_FAILDFLT})
endmacro()

macro(OPTION_STRING _NAME _DESC _VALUE)
  list(APPEND ALLOPTIONS ${_NAME})
  set(${_NAME} ${_VALUE} CACHE STRING "${_DESC}")
  set(HAVE_${_NAME} ${_VALUE})
ENDMACRO()

# Message Output
macro(MESSAGE_WARN _TEXT)
  message(STATUS "*** WARNING: ${_TEXT}")
endmacro()

macro(MESSAGE_ERROR _TEXT)
  message(FATAL_ERROR "*** ERROR: ${_TEXT}")
endmacro()

macro(MESSAGE_BOOL_OPTION _NAME _VALUE)
  # Urho3D - accept extra paddding argument
  if (NOT ${ARGN} STREQUAL \t)
    set(_PAD ${ARGN})
  else ()
    set(_PAD \t)
  endif ()
  if(${_VALUE})
    message(STATUS "  ${_NAME}:${_PAD}ON")
  else()
    message(STATUS "  ${_NAME}:${_PAD}OFF")
  endif()
endmacro()

macro(MESSAGE_TESTED_OPTION _NAME)
  set(_REQVALUE ${${_NAME}})
  set(_PAD " ")
  if(${ARGC} EQUAL 2)
    set(_PAD ${ARGV1})
  endif()
  if(NOT HAVE_${_NAME})
    set(HAVE_${_NAME} OFF)
  elseif("${HAVE_${_NAME}}" MATCHES "1|TRUE|YES|Y")
    set(HAVE_${_NAME} ON)
  endif()
  message(STATUS "  ${_NAME}${_PAD}(Wanted: ${_REQVALUE}): ${HAVE_${_NAME}}")
endmacro()

macro(LISTTOSTR _LIST _OUTPUT)
  if(${ARGC} EQUAL 3)
    # prefix for each element
    set(_LPREFIX ${ARGV2})
  else()
    set(_LPREFIX "")
  endif()
  # Do not use string(REPLACE ";" " ") here to avoid messing up list
  # entries
  foreach(_ITEM ${${_LIST}})
    set(${_OUTPUT} "${_LPREFIX}${_ITEM} ${${_OUTPUT}}")
  endforeach()
endmacro()

macro(CHECK_OBJC_SOURCE_COMPILES SOURCE VAR)
  set(PREV_REQUIRED_DEFS "${CMAKE_REQUIRED_DEFINITIONS}")
  set(CMAKE_REQUIRED_DEFINITIONS "-x objective-c ${PREV_REQUIRED_DEFS}")
  CHECK_C_SOURCE_COMPILES(${SOURCE} ${VAR})
  set(CMAKE_REQUIRED_DEFINITIONS "${PREV_REQUIRED_DEFS}")
endmacro()

