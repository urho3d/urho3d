# Add this as include dir
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Include common to all samples
set (H_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Sample.h" "${CMAKE_CURRENT_SOURCE_DIR}/Sample.inl")

# Add samples
add_subdirectory(01_HelloWorld)
