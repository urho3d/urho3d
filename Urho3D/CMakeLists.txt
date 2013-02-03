# Define target name
set (TARGET_NAME Urho3D)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define resource files
if (APPLE)
    set (RESOURCE_FILES ${PROJECT_BINARY_DIR}/Bin/CoreData ${PROJECT_BINARY_DIR}/Bin/Data)
    set_source_files_properties(${RESOURCE_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
endif ()

# Include directories
include_directories (
    ../Engine/Container ../Engine/Core ../Engine/Engine ../Engine/IO ../Engine/Math ../Engine/Resource 
    ../Engine/Script
)

# Define target & libraries to link
if (WIN32)
    add_executable (${TARGET_NAME} WIN32 ${SOURCE_FILES})
elseif (IOS)
    set (CMAKE_EXE_LINKER_FLAGS "-framework AudioToolbox -framework CoreAudio -framework CoreGraphics -framework Foundation -framework OpenGLES -framework QuartzCore -framework UIKit")
    add_executable (${TARGET_NAME} MACOSX_BUNDLE ${SOURCE_FILES} ${RESOURCE_FILES})

    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        # If an empty file with name IOS_FORCE_COPY_RESOURCES is present at the project root folder, touch the resource folders so that they are always 'newer' than previous copied resource
        # folders in the bundle, thus forcing them to be copied again in the next build
        COMMAND [ -e ${PROJECT_BINARY_DIR}/IOS_FORCE_COPY_RESOURCES ] && sleep 1 && touch -cm ${RESOURCE_FILES} || exit 0

        # If an empty file with name IOS_FORCE_LINK is present at the project root folder, touch the main cpp file to force a relinking of the executable in next build
        COMMAND [ -e ${PROJECT_BINARY_DIR}/IOS_FORCE_LINK ] && sleep 1 && touch -cm ${CPP_FILES} || exit 0
    )
    set_target_properties(${TARGET_NAME} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
elseif (APPLE)
    set (CMAKE_EXE_LINKER_FLAGS "-framework AudioUnit -framework Carbon -framework Cocoa -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL -framework CoreServices")
    add_executable (${TARGET_NAME} ${SOURCE_FILES} ${RESOURCE_FILES})
else ()
    add_executable (${TARGET_NAME} ${SOURCE_FILES})
endif ()

target_link_libraries (${TARGET_NAME} Container Core Engine IO Math Resource Script)
finalize_exe ()
