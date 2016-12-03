set (FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/Config.h")

file (WRITE ${FILE_NAME} "#pragma once")

get_directory_property (URHO3D_COMPILE_DEFINITIONS COMPILE_DEFINITIONS)
list (REMOVE_ITEM URHO3D_COMPILE_DEFINITIONS HAVE_STDINT_H GLEW_STATIC GLEW_NO_GLU URHO3D_IS_BUILDING ODBC_3_OR_LATER ASSET_DIR_INDICATOR)
string (REPLACE ";" "\n#define " URHO3D_COMPILE_DEFINITIONS "#define ${URHO3D_COMPILE_DEFINITIONS}")
file (APPEND ${FILE_NAME} "\n\n${URHO3D_COMPILE_DEFINITIONS}")

define_dependency_libs (${TARGET_NAME})
string (REPLACE ";" "\")\n#    pragma comment(lib, \"" FORMAT_LIBS "#    pragma comment(lib, \"${LIBS}\")")
file (APPEND ${FILE_NAME} "\n")
file (APPEND ${FILE_NAME} "\n#ifdef _MSC_VER")
file (APPEND ${FILE_NAME} "\n#    ifdef _DEBUG")
file (APPEND ${FILE_NAME} "\n#        pragma comment(lib, \"Urho3D_d\")")
file (APPEND ${FILE_NAME} "\n#    else")
file (APPEND ${FILE_NAME} "\n#        pragma comment(lib, \"Urho3D\")")
file (APPEND ${FILE_NAME} "\n#    endif")
file (APPEND ${FILE_NAME} "\n${FORMAT_LIBS}")
file (APPEND ${FILE_NAME} "\n#endif")

install_header_files (FILES ${FILE_NAME} DESTINATION ${DEST_INCLUDE_DIR})
