# Modified by Lasse Öörni for Urho3D

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libglfw.pc.cmake 
               ${CMAKE_CURRENT_BINARY_DIR}/libglfw.pc @ONLY)

include_directories(.
                    ..
                    ${GLFW_INCLUDE_DIR})

set(cocoa_SOURCES cocoa_enable.m
                  cocoa_fullscreen.m
                  cocoa_gamma.m
                  cocoa_init.m
                  cocoa_joystick.m
                  cocoa_opengl.m
                  cocoa_time.m
                  cocoa_window.m)

# For some reason, CMake doesn't know about .m
set_source_files_properties(${cocoa_SOURCES} PROPERTIES LANGUAGE C)

set(libglfw_SOURCES ${common_SOURCES} ${cocoa_SOURCES})

add_library(GLFW STATIC ${libglfw_SOURCES})
target_link_libraries(GLFW ${GLFW_LIBRARIES})
set_target_properties(GLFW PROPERTIES
                      CLEAN_DIRECT_OUTPUT 1)

