# Define target name
set (TARGET_NAME AssetImporter)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../../Engine/Core ../../Engine/Graphics ../../Engine/IO ../../Engine/Math ../../Engine/Resource
    ../../Engine/Physics ../../Engine/Scene ../../ThirdParty/Assimp/include
)

# Define target & libraries to link
add_executable (${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Assimp Core Graphics IO Math Physics Scene Resource ${DBGHELP_LIB})
finalize_exe ()

