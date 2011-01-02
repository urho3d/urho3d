# Define target name
set (TARGET_NAME ODE)

# Define source files
file (GLOB CPP_FILES
    ode/src/*.cpp ode/src/joints/*.cpp OPCODE/*.cpp OPCODE/Ice/*.cpp
)
file (GLOB C_FILES
    ode/src/*.c
)
file (GLOB H_FILES
    include/ode/*.h ode/src/*.h ode/src/joints/*.h OPCODE/*.h OPCODE/Ice/*.h
)
set (SOURCE_FILES ${CPP_FILES} ${C_FILES} ${H_FILES})

add_definitions (-DODE_LIB)

# Include directories
include_directories (
    include ode/src OPCODE
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
finalize_lib ()