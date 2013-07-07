# Define target name
set (TARGET_NAME Core)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../Container ../Math)

if (NOT IOS AND NOT ANDROID)
    set (INCLUDE_DIRS_ONLY ../../ThirdParty/LibCpuId/libcpuid)
    set (LINK_LIBS_ONLY LibCpuId)
endif ()

if (WIN32)
    set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} winmm.lib)
    if (ENABLE_MINIDUMPS)
        set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} dbghelp.lib)
    endif ()
elseif (NOT ANDROID)
    set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} pthread)
endif ()

# Setup target
enable_pch ()
setup_library ()

