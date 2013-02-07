# Define target name
set (TARGET_NAME Script)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../Container ../Core ../IO ../Math ../Physics ../Resource ../Scene ../../ThirdParty/AngelScript/include)
set (INCLUDE_DIRS_ONLY ../../ThirdParty/Bullet/src)

# Setup target
enable_pch ()
setup_library ()
