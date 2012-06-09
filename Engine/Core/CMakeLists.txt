# Define target name
set (TARGET_NAME Core)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Container ../Math ../../ThirdParty/LibCpuId/libcpuid
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Container Math)

if (NOT IOS)
    target_link_libraries (${TARGET_NAME} LibCpuId)
endif ()

if (WIN32)
    target_link_libraries (${TARGET_NAME} winmm.lib)
    if (ENABLE_MINIDUMPS)
        target_link_libraries (${TARGET_NAME} dbghelp.lib)
    endif ()
else ()
    target_link_libraries (${TARGET_NAME} pthread)
endif ()

enable_pch ()
finalize_lib ()
