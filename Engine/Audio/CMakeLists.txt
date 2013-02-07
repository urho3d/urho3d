# Define target name
set (TARGET_NAME Audio)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../Container ../Core ../Graphics ../IO ../Math ../Resource ../Scene ../../ThirdParty/STB)
set (LINK_LIBS_ONLY SDL)

# Setup target
enable_pch ()
setup_library ()
