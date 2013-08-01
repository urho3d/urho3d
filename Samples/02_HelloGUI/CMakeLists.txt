# Define target name
set (TARGET_NAME 02_HelloGUI)

# Define source files
set (H_FILES HelloGUI.h)
set (CPP_FILES HelloGUI.cpp)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES} ${COMMON_SAMPLE_H_FILES})

# Setup target with resource copying
setup_main_executable ()
