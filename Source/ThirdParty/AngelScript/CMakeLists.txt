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
set (TARGET_NAME AngelScript)

# Define source files
file (GLOB CPP_FILES
    source/*.cpp
)
file (GLOB H_FILES
    include/*.h source/*.h
)

if (IOS OR ANDROID OR RPI)
    enable_language (ASM)
    if (IOS)
        set (ASM_FILES source/as_callfunc_arm_xcode.S)
    else ()
        set (ASM_FILES source/as_callfunc_arm_gcc.S)
    endif ()
endif ()

if (MSVC AND URHO3D_64BIT)
    enable_language (ASM_MASM)
    # Commented out due to cmake bug
    #set (ASM_FILES source/as_callfunc_x64_msvc_asm.asm)
    # As a temporary workaround
    add_custom_command (OUTPUT as_callfunc_x64_msvc_asm.obj COMMAND ${CMAKE_ASM_MASM_COMPILER} -Fo ${CMAKE_CURRENT_BINARY_DIR}/as_callfunc_x64_msvc_asm.obj -c ${CMAKE_CURRENT_SOURCE_DIR}/source/as_callfunc_x64_msvc_asm.asm DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/as_callfunc_x64_msvc_asm.asm COMMENT "Temporary workaround for MASM") 
    set (ASM_FILES ${CMAKE_CURRENT_BINARY_DIR}/as_callfunc_x64_msvc_asm.obj ${CMAKE_CURRENT_SOURCE_DIR}/source/as_callfunc_x64_msvc_asm.asm)
endif ()

set (SOURCE_FILES ${CPP_FILES} ${ASM_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS include)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (install dependency for Urho3D/Script/APITemplates.h)
install_header_files (DIRECTORY include/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/AngelScript FILES_MATCHING PATTERN *.h)     # Note: the trailing slash is significant
