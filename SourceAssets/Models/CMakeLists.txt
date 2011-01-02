SET (ALL_MODELS)

add_model (Jack "-a")
add_model (Level "")
add_model (Mushroom "-a -lc0")
add_model (Ninja "-a")
add_model (Potion "")
add_model (SnowBall "")
add_model (SnowCrate "")

add_custom_target (Models ALL DEPENDS ${ALL_MODELS})
