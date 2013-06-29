# Define target name
set (TARGET_NAME LuaScript)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../../Engine/Audio ../../Engine/Container ../../Engine/Core ../../Engine/Engine ../../Engine/Graphics ../../Engine/Input ../../Engine/IO ../../Engine/Math ../../Engine/Navigation ../../Engine/Network ../../Engine/Physics
    ../../Engine/Resource ../../Engine/Scene ../../Engine/UI ../../ThirdParty/Lua ../../ThirdParty/Tolua++)
	
set (INCLUDE_DIRS_ONLY  ../../ThirdParty/Bullet/src ../../ThirdParty/kNet/include  ../../ThirdParty/Tolua++/include)

# Setup target
enable_pch()
setup_library ()
