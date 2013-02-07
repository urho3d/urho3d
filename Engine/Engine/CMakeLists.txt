# Define target name
set (TARGET_NAME Engine)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../Audio ../Container ../Core ../Graphics ../Input ../IO ../Math ../Network ../Physics ../Resource ../Scene ../Script ../UI)
set (INCLUDE_DIRS_ONLY ../../ThirdParty/AngelScript/include ../../ThirdParty/Bullet/src ../../ThirdParty/kNet/include)

# Setup target
enable_pch ()
setup_library ()
