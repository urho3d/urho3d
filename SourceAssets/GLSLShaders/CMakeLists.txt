set (ALL_SHADERS)

add_shader (Ambient)
add_shader (Basic)
add_shader (Forward)
add_shader (GBuffer)
add_shader (Light)
add_shader (Shadow)
add_shader (Stencil)
add_shader (TemporalAA)

add_custom_target (Shaders ALL DEPENDS ${ALL_SHADERS})
