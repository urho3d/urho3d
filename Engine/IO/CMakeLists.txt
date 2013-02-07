# Define target name
set (TARGET_NAME IO)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)

if (APPLE AND NOT IOS)
    file (GLOB C_FILES *.m)
endif()

set (SOURCE_FILES ${CPP_FILES} ${C_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../Container ../Core ../Math)

# Setup target
enable_pch ()
setup_library ()
