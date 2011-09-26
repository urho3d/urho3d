set (ALL_SHADERS)

add_shader (Basic)
add_shader (Forward)
add_shader (Shadow)
add_shader (Stencil)

add_custom_target (Shaders ALL DEPENDS ${ALL_SHADERS})
