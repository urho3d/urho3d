# Modified by Lasse Öörni for Urho3D

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libglfw.pc.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/libglfw.pc @ONLY)

include_directories(.
                    ..
                    ${GLFW_INCLUDE_DIR})

set(libglfw_SOURCES ${common_SOURCES}
                    x11_enable.c 
                    x11_fullscreen.c
                    x11_gamma.c
                    x11_init.c 
                    x11_joystick.c
                    x11_keysym2unicode.c
                    x11_opengl.c
                    x11_time.c 
                    x11_window.c)

add_library(GLFW STATIC ${libglfw_SOURCES})
target_link_libraries(GLFW ${GLFW_LIBRARIES})
set_target_properties(GLFW PROPERTIES
                      CLEAN_DIRECT_OUTPUT 1)
