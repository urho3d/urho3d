# Define target name
set (TARGET_NAME Core)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Container ../Math
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Container Math)

if (USE_SDL)
    target_link_libraries (${TARGET_NAME} SDL)
else ()
    target_link_libraries (${TARGET_NAME} winmm.lib)
endif ()

if (ENABLE_MINIDUMPS)
    target_link_libraries (${TARGET_NAME} dbghelp.lib)
endif ()

enable_pch ()
finalize_lib ()
