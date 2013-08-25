# Define target name
set (TARGET_NAME 14_SoundEffects)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES} ${COMMON_SAMPLE_H_FILES})

# Setup target with resource copying
setup_main_executable ()
