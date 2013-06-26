# Define target name
set (TARGET_NAME Script)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../Audio ../Container ../Core ../Engine ../Graphics ../Input ../IO ../Math ../Navigation ../Network ../Physics
    ../Resource ../Scene ../UI ../../ThirdParty/AngelScript/include)
set (INCLUDE_DIRS_ONLY ../../ThirdParty/Bullet/src ../../ThirdParty/kNet/include)

# Setup target
enable_pch ()
setup_library ()
