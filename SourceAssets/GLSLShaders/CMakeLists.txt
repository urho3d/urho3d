set (ALL_SHADERS)

add_shader (Ambient)
add_shader (Basic)
add_shader (BlinnPhong)
add_shader (Shadow)
add_shader (Stencil)
add_shader (Unlit)
add_shader (Volumetric)

add_custom_target (Shaders ALL DEPENDS ${ALL_SHADERS})
