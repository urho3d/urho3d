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
    set (SOURCE_FILES ${SOURCE_FILES} ${RESOURCE_FILES})
endif ()

# Define dependency libs
set (LIBS ../Engine/Container ../Engine/Core ../Engine/Engine ../Engine/IO ../Engine/Math ../Engine/Resource ../Engine/Script)

# Setup target
if (WIN32)
    set (EXE_TYPE WIN32)
elseif (IOS)
    set (CMAKE_EXE_LINKER_FLAGS "-framework AudioToolbox -framework CoreAudio -framework CoreGraphics -framework Foundation -framework OpenGLES -framework QuartzCore -framework UIKit")
    set (EXE_TYPE MACOSX_BUNDLE)
elseif (APPLE)
    set (CMAKE_EXE_LINKER_FLAGS "-framework AudioUnit -framework Carbon -framework Cocoa -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL -framework CoreServices")
endif ()
setup_executable ()

# Define a custom target to check for resource modification
if (IOS)
    get_target_property (TARGET_LOC ${TARGET_NAME} LOCATION)
    string (REGEX REPLACE "/Contents/MacOS" "" TARGET_LOC ${TARGET_LOC})    # The regex replacement is temporary workaround to correct the wrong location caused by CMake/Xcode generator bug
    add_custom_target (RESOURCE_CHECK ALL
        \(\( `find ${RESOURCE_FILES} -newer ${TARGET_LOC} 2>/dev/null |wc -l` \)\) && touch -cm ${SOURCE_FILES} || exit 0
        COMMENT "This is a dummy target to check for changes in the Resource folders"
    )
    add_dependencies (${TARGET_NAME} RESOURCE_CHECK)
endif ()
