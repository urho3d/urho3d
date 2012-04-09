# Define target name
set (TARGET_NAME Script)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Container ../Core ../IO ../Math ../Physics ../Resource ../Scene
    ../../ThirdParty/AngelScript/include ../../ThirdParty/Bullet/src 
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} AngelScript Container Core IO Math Physics Resource Scene)
enable_pch ()
finalize_lib ()