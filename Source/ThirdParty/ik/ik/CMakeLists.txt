include (CheckIncludeFiles)

set (IK_BUILD_TYPE "STATIC")
check_include_files ("stdint.h" HAVE_STDINT_H)

# memory debugging
if (CMAKE_BUILD_TYPE MATCHES Debug)
    option (IK_MEMORY_DEBUGGING "Global switch for memory options. Keeps track of the number of allocations and de-allocations and prints a report when the program shuts down" ON)
else ()
    option (IK_MEMORY_DEBUGGING "Global switch for memory options. Keeps track of the number of allocations and de-allocations and prints a report when the program shuts down" OFF)
endif ()
if (IK_MEMORY_DEBUGGING)
    if(${CMAKE_BUILD_TYPE} MATCHES Debug)
        option (IK_MEMORY_BACKTRACE "Generates backtraces for every malloc(), making it easy to track down memory leaks" ON)
    else ()
        option (IK_MEMORY_BACKTRACE "Generates backtraces for every malloc(), making it easy to track down memory leaks" OFF)
    endif ()
else ()
    option (IK_MEMORY_BACKTRACE "Generates backtraces for every malloc(), making it easy to track down memory leaks" OFF)
endif ()

set (IK_REAL "float" CACHE STRING "Type to use for real numbers")
option (IK_DOT_OUTPUT "When enabled, the generated chains are dumped to DOT for debug purposes" OFF)

configure_file ("include/ik/export.h.in"
                "include/ik/gen/export.h")
configure_file ("include/ik/config.h.in"
                "include/ik/gen/config.h")

include_directories ("${CMAKE_CURRENT_BINARY_DIR}/include")

###############################################################################
# compiler flags
###############################################################################

if (${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
    add_definitions (-W -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -fno-math-errno -ffast-math)
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
    add_definitions (-W -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -fno-math-errno -ffast-math)
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "Intel")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
    add_definitions (-D_CRT_SECURE_NO_WARNINGS)
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        STRING(REGEX REPLACE "/MDd" "" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
        add_definitions (-MTd)
    elseif (CMAKE_BUILD_TYPE MATCHES Release)
        STRING(REGEX REPLACE "/MD" "" CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
        add_definitions (-MT)
    endif ()
endif ()

###############################################################################
# source files and library definition
###############################################################################

file (GLOB IK_HEADERS "include/ik/*.h")
file (GLOB IK_SOURCES "src/*.c")

list (APPEND IK_HEADERS
    "include/ik/config.h.in"
    "include/ik/export.h.in")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    file (GLOB IK_PLATFORM_SOURCES "src/platform/linux/*.c")
endif ()
list (APPEND IK_SOURCES ${IK_PLATFORM_SOURCES})

include_directories ("include")

add_library (ik ${IK_BUILD_TYPE}
    ${IK_HEADERS}
    ${IK_SOURCES}
)

# The library is being built
add_definitions (-DIK_BUILDING)

###############################################################################
# install targets
###############################################################################

install (
    TARGETS
        ik
    LIBRARY DESTINATION
        "lib"
    RUNTIME DESTINATION
        "bin"
    ARCHIVE DESTINATION
        "lib"
)
