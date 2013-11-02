# Define target name
set (TARGET_NAME LZ4)

# Define source files
file (GLOB C_FILES *.c)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${C_FILES} ${H_FILES})
if (DEST_INCLUDE_DIR)
    install (FILES ${H_FILES} DESTINATION ${DEST_INCLUDE_DIR}/LZ4)
endif ()

# Setup target
setup_library ()
