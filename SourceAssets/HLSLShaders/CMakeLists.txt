set (ALL_SHADERS)

add_shader (Ambient)
add_shader (Basic)
add_shader (DeferredLight)
add_shader (ForwardLit)
add_shader (GBuffer)
add_shader (LitParticle)
add_shader (Material)
add_shader (Shadow)
add_shader (Stencil)
add_shader (Unlit)

add_custom_target (Shaders ALL DEPENDS ${ALL_SHADERS})
