# Define target name
set (TARGET_NAME UI)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../Container ../Core ../Graphics ../Input ../IO ../Math ../Resource ../Scene ../../ThirdParty/FreeType/include)

# Setup target
enable_pch ()
setup_library ()
