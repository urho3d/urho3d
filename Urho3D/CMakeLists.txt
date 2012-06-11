# Define target name
set (TARGET_NAME Urho3D)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Engine/Container ../Engine/Core ../Engine/Engine ../Engine/IO ../Engine/Math ../Engine/Resource 
    ../Engine/Script
)

# Define target & libraries to link
if (WIN32)
    add_executable (${TARGET_NAME} WIN32 ${SOURCE_FILES})
elseif (IOS)
    set (RESOURCE_DIR \${TARGET_BUILD_DIR}/\${FULL_PRODUCT_NAME})
    set (CMAKE_EXE_LINKER_FLAGS "-framework AudioToolbox -framework CoreAudio -framework CoreGraphics -framework Foundation -framework OpenGLES -framework QuartzCore -framework UIKit")
    add_executable (${TARGET_NAME} MACOSX_BUNDLE ${SOURCE_FILES})
    add_dependencies (${TARGET_NAME} Models Shaders)
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND mkdir -p ${RESOURCE_DIR}/CoreData
        COMMAND mkdir -p ${RESOURCE_DIR}/Data
        COMMAND ditto ${CMAKE_SOURCE_DIR}/Bin/CoreData ${RESOURCE_DIR}/CoreData
        COMMAND ditto ${CMAKE_SOURCE_DIR}/Bin/Data ${RESOURCE_DIR}/Data
    )
    set_target_properties(${TARGET_NAME} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
elseif (APPLE)
    set (CMAKE_EXE_LINKER_FLAGS "-framework AudioUnit -framework Carbon -framework Cocoa -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL")
    add_executable (${TARGET_NAME} ${SOURCE_FILES})
else ()
    add_executable (${TARGET_NAME} ${SOURCE_FILES})
endif ()

target_link_libraries (${TARGET_NAME} Container Core Engine IO Math Resource Script)
finalize_exe ()
