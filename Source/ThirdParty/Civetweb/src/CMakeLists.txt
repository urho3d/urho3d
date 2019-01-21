# The C API library
set( LIB_TYPE "STATIC" )

if (BUILD_SHARED_LIBS)
  set( LIB_TYPE "SHARED" )
endif()
add_library(civetweb-c-library ${LIB_TYPE} civetweb.cpp)
set_target_properties(civetweb-c-library PROPERTIES
  OUTPUT_NAME "civetweb"
  EXPORT_NAME "civetweb"
  VERSION ${CIVETWEB_VERSION}
  SOVERSION ${CIVETWEB_VERSION}
)
if (BUILD_SHARED_LIBS)
  target_compile_definitions(civetweb-c-library PRIVATE CIVETWEB_DLL_EXPORTS INTERFACE CIVETWEB_DLL_IMPORTS)
endif()
target_include_directories(
  civetweb-c-library PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
install(
  TARGETS civetweb-c-library
  EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT civetweb-c-library
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES
  ${PROJECT_SOURCE_DIR}/include/civetweb.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT civetweb-c-library)

# Need Windows sockets if available
find_package(WinSock)
if (WINSOCK_FOUND)
  target_link_libraries(civetweb-c-library WINSOCK::WINSOCK)
endif()

# We need threading
find_package(Threads)
target_link_libraries(civetweb-c-library ${CMAKE_THREAD_LIBS_INIT})

# Need the realtime library if we're using timers
find_package(LibRt)
if (CIVETWEB_ENABLE_WEBSOCKETS AND CIVETWEB_ENABLE_LUA AND LIBRT_FOUND)
  target_link_libraries(civetweb-c-library LIBRT::LIBRT)
endif()

# We need to link OpenSSL if not dynamically loading
if (CIVETWEB_ENABLE_SSL)
  if (CIVETWEB_ENABLE_SSL_DYNAMIC_LOADING)
    find_package(LibDl)
    if (LIBDL_FOUND)
      target_link_libraries(civetweb-c-library -ldl)
    endif()
  else()
    find_package(OpenSSL)
    include_directories(${OPENSSL_INCLUDE_DIR})
    message(STATUS "OpenSSL include directory: ${OPENSSL_INCLUDE_DIR}")
    target_link_libraries(civetweb-c-library ${OPENSSL_LIBRARIES})
  endif()
endif()

# The C++ API library
if (CIVETWEB_ENABLE_CXX)
  add_library(civetweb-cpp ${LIB_TYPE} CivetServer.cpp)
  set_target_properties(civetweb-cpp PROPERTIES
    EXPORT_NAME "civetweb-cpp"
    OUTPUT_NAME "civetweb-cpp"
    VERSION ${CIVETWEB_VERSION}
    SOVERSION ${CIVETWEB_VERSION}
  )
  if (BUILD_SHARED_LIBS)
    target_compile_definitions(civetweb-cpp PRIVATE CIVETWEB_CXX_DLL_EXPORTS INTERFACE CIVETWEB_CXX_DLL_IMPORTS)
  endif()
  target_link_libraries(
    civetweb-cpp PUBLIC
	civetweb-c-library)
  target_include_directories(
    civetweb-cpp PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
  install(
    TARGETS civetweb-cpp
    EXPORT ${PROJECT_NAME}-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT civetweb-cpp
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  install(FILES
    ${PROJECT_SOURCE_DIR}/include/CivetServer.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT civetweb-cpp)
endif()
