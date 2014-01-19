# Define target name
set (TARGET_NAME StanHull)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})
set (AMALG_EXCLUDES .)

# Setup target
setup_library ()
