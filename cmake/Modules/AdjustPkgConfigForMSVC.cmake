# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# VS generator is multi-config, we need to use the CMake generator expression to get the correct target linker filename during post build step

configure_file (Urho3D.pc.msvc Urho3D.pc @ONLY)
