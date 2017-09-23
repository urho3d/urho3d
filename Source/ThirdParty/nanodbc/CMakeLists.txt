#
# Copyright (c) 2008-2017 the Urho3D project.
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

# nanodbc specific options
option (NANODBC_DISABLE_ASYNC "Disable async features entirely" OFF)
if (NANODBC_DISABLE_ASYNC)
    add_definitions (-DNANODBC_DISABLE_ASYNC)
endif ()
option (NANODBC_ENABLE_UNICODE "Enable Unicode support" OFF)
if (NANODBC_ENABLE_UNICODE)
    add_definitions (-DNANODBC_ENABLE_UNICODE)
    if (MSVC)
        # Sets "Use Unicode Character Set" property in Visual Studio projects
        add_definitions (-DUNICODE -D_UNICODE)
    endif ()
endif ()
option (NANODBC_ENABLE_WORKAROUND_NODATA "Enable SQL_NO_DATA workaround (see Issue #33)" OFF)
if (NANODBC_ENABLE_WORKAROUND_NODATA)
  add_definitions (-DNANODBC_ENABLE_WORKAROUND_NODATA)
endif ()

# Define source files
define_source_files (GLOB_CPP_PATTERNS nanodbc/*.cpp GLOB_H_PATTERNS nanodbc/*.h)

# Define dependency libs
if (ODBC_INCLUDE_DIRS)
    set (INCLUDE_DIRS . ${ODBC_INCLUDE_DIRS})
endif ()
if (ODBC_DEFINES)
    add_definitions (${ODBC_DEFINES})
endif ()

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library
install_header_files (DIRECTORY nanodbc/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/nanodbc FILES_MATCHING PATTERN *.h)  # Note: the trailing slash is significant
