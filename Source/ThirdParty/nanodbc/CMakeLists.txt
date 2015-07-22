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

# Define target name
set (TARGET_NAME nanodbc)

add_definitions (-DNANODBC_USE_UNICODE)

# Define source files
define_source_files (GLOB_CPP_PATTERNS src/*.cpp GLOB_H_PATTERNS src/*.h)

# On Unix-like host system, find the ODBC config tool
if (NOT CMAKE_WIN32_HOST)
	find_program (ODBC_CONFIG NAMES odbc_config iodbc-config DOC "ODBC config tool" NO_CMAKE_FIND_ROOT_PATH)
	if (NOT ODBC_CONFIG)
		message (FATAL_ERROR "Could not find ODBC config tool, please install the development package of unixODBC or libiodbc")
	endif ()

	# Get ODBC compile and link flags
#TODO	execute_process(COMMAND ${ODBC_CONFIG} --libs OUTPUT_VARIABLE ODBC_LINK_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
	execute_process(COMMAND ${ODBC_CONFIG} --cflags OUTPUT_VARIABLE ODBC_COMPILE_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
    set (TARGET_PROPERTIES COMPILE_FLAGS ${ODBC_COMPILE_FLAGS})
endif ()

# Setup target
setup_library ()

# Install headers for building the Urho3D library
install_header_files (DIRECTORY src/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/nanodbc FILES_MATCHING PATTERN *.h)  # Note: the trailing slash is significant
