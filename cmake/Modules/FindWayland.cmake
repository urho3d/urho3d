# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Find Wayland display server
#
#  WAYLAND_FOUND
#  WAYLAND_INCLUDE_DIRS
#  WAYLAND_CORE_PROTOCOL_DIR
#  WAYLAND_PROTOCOLS_DIR
#  WAYLAND_CLIENT
#  WAYLAND_SCANNER
#  WAYLAND_CURSOR
#  WAYLAND_EGL
#  EGL
#  XKB
#

find_path (WAYLAND_INCLUDE_DIRS NAMES wayland-client.h DOC "Wayland include directory")
find_path (WAYLAND_CORE_PROTOCOL_DIR NAMES wayland.xml PATHS /usr/share/wayland DOC "Wayland core protocol directory")
find_path (WAYLAND_PROTOCOLS_DIR NAMES stable unstable PATHS /usr/share/wayland-protocols DOC "Wayland protocol directory")
find_library (WAYLAND_CLIENT NAMES wayland-client DOC "Wayland client library")
find_program (WAYLAND_SCANNER NAMES wayland-scanner DOC "Wayland scanner host tool")
find_library (WAYLAND_CURSOR NAMES wayland-cursor DOC "Wayland compositor infrastructure - cursor library")
find_library (WAYLAND_EGL NAMES wayland-egl DOC "Wayland EGL library")
find_library (EGL NAMES EGL DOC "EGL library")
find_library (XKB NAMES xkbcommon DOC "Xkb common library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Wayland REQUIRED_VARS WAYLAND_CLIENT WAYLAND_SCANNER WAYLAND_CURSOR WAYLAND_EGL EGL XKB WAYLAND_INCLUDE_DIRS WAYLAND_CORE_PROTOCOL_DIR WAYLAND_PROTOCOLS_DIR FAIL_MESSAGE "Could NOT find Wayland display server")

mark_as_advanced (WAYLAND_INCLUDE_DIRS WAYLAND_CORE_PROTOCOL_DIR WAYLAND_PROTOCOLS_DIR WAYLAND_CLIENT WAYLAND_SCANNER WAYLAND_CURSOR WAYLAND_EGL EGL XKB)
