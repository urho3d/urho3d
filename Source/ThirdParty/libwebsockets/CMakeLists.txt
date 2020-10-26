#
# Copyright (c) 2008-2020 the Urho3D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

# Define target name
set (TARGET_NAME libwebsockets)

########
set(LWS_WITH_BUNDLED_ZLIB_DEFAULT OFF)
if (WIN32)
    set(LWS_WITH_BUNDLED_ZLIB_DEFAULT ON)
endif ()

set(LWS_ROLE_RAW 1)
set(LWS_WITH_POLL 1)

if (ESP_PLATFORM)
    set(LWS_ESP_PLATFORM 1)
    set(CMAKE_TOOLCHAIN_FILE contrib/cross-esp32.cmake)
    set(LWIP_PROVIDE_ERRNO 1)
endif ()

#
# Select features recommended for PC distro packaging
#
option(LWS_WITH_DISTRO_RECOMMENDED "Enable features recommended for distro packaging" OFF)
option(LWS_FOR_GITOHASHI "Enable features recommended for use with gitohashi" OFF)


#
# Compiler features
#
option(DISABLE_WERROR "Avoid treating compiler warnings as fatal errors" OFF)

#
# Major individual features
#
option(LWS_WITH_CLIENT "Compile with network-related code" ON)
option(LWS_WITH_NETWORK "Compile with network-related code" ON)
option(LWS_ROLE_H1 "Compile with support for http/1 (needed for ws)" ON)
option(LWS_ROLE_WS "Compile with support for websockets" ON)
option(LWS_ROLE_MQTT "Build with support for MQTT client" OFF)
option(LWS_ROLE_DBUS "Compile with support for DBUS" OFF)
option(LWS_ROLE_RAW_PROXY "Raw packet proxy" OFF)
option(LWS_ROLE_RAW_FILE "Compile with support for raw files" OFF)
option(LWS_WITH_HTTP2 "Compile with server support for HTTP/2" OFF)
option(LWS_WITH_LWSWS "Libwebsockets Webserver" OFF)
option(LWS_WITH_CGI "Include CGI (spawn process with network-connected stdin/out/err) APIs" OFF)
option(LWS_IPV6 "Compile with support for ipv6" OFF)
option(LWS_UNIX_SOCK "Compile with support for UNIX domain socket if OS supports it" ON)
option(LWS_WITH_PLUGINS "Support plugins for protocols and extensions (implies LWS_WITH_PLUGINS_API)" OFF)
option(LWS_WITH_HTTP_PROXY "Support for active HTTP proxying" OFF)
option(LWS_WITH_ZIP_FOPS "Support serving pre-zipped files" OFF)
option(LWS_WITH_SOCKS5 "Allow use of SOCKS5 proxy on client connections" OFF)
option(LWS_WITH_PEER_LIMITS "Track peers and restrict resources a single peer can allocate" OFF)
option(LWS_WITH_ACCESS_LOG "Support generating Apache-compatible access logs" OFF)
option(LWS_WITH_RANGES "Support http ranges (RFC7233)" OFF)
option(LWS_WITH_SERVER_STATUS "Support json + jscript server monitoring" OFF)
option(LWS_WITH_SERVER "Support json + jscript server monitoring" ON)
option(LWS_WITH_THREADPOOL "Managed worker thread pool support (relies on pthreads)" OFF)
option(LWS_WITH_HTTP_STREAM_COMPRESSION "Support HTTP stream compression" OFF)
option(LWS_WITH_HTTP_BROTLI "Also offer brotli http stream compression (requires LWS_WITH_HTTP_STREAM_COMPRESSION)" OFF)
option(LWS_WITH_ACME "Enable support for ACME automatic cert acquisition + maintenance (letsencrypt etc)" OFF)
option(LWS_WITH_HUBBUB "Enable libhubbub rewriting support" OFF)
option(LWS_WITH_ALSA "Enable alsa audio example" OFF)
option(LWS_WITH_GTK "Enable gtk example" OFF)
option(LWS_WITH_FTS "Full Text Search support" OFF)
option(LWS_WITH_SYS_ASYNC_DNS "Nonblocking internal IPv4 + IPv6 DNS resolver" OFF)
option(LWS_WITH_SYS_NTPCLIENT "Build in tiny ntpclient good for tls date validation and run via lws_system" OFF)
option(LWS_WITH_SYS_DHCP_CLIENT "Build in tiny DHCP client" OFF)
option(LWS_WITH_HTTP_BASIC_AUTH "Support Basic Auth" OFF)
option(LWS_WITH_HTTP_UNCOMMON_HEADERS "Include less common http header support" ON)
option(LWS_WITH_SYS_STATE "lws_system state support" ON)
option(LWS_WITH_SYS_SMD "Lws System Message Distribution" ON)

#
# Secure Streams
#
option(LWS_WITH_SECURE_STREAMS "Secure Streams protocol-agnostic API" OFF)
option(LWS_WITH_SECURE_STREAMS_PROXY_API "Secure Streams support to work across processes" OFF)
option(LWS_WITH_SECURE_STREAMS_SYS_AUTH_API_AMAZON_COM "Auth support for api.amazon.com" OFF)
option(LWS_WITH_SECURE_STREAMS_STATIC_POLICY_ONLY "Secure Streams Policy is hardcoded only" OFF)

#
# CTest options
#
#
# If you build with LWS_WITH_MINIMAL_EXAMPLES, you can use CTest / make test to run
# examples that can give a pass/fail response.  By default it runs tests both against
# a local server peer and warmcat.com, if your CI wants to do the tests but does not
# have internet routing, then you can still run a subset of tests with CTest / make
# test that only does local tests by disabling this option.
#
option(LWS_CTEST_INTERNET_AVAILABLE "CTest will performs tests that need the Internet" ON)

#
# TLS library options... all except mbedTLS are basically OpenSSL variants.
#
option(LWS_WITH_SSL "Include SSL support (defaults to OpenSSL or similar, mbedTLS if LWS_WITH_MBEDTLS is set)" ON)
option(LWS_WITH_MBEDTLS "Use mbedTLS (>=2.0) replacement for OpenSSL. When setting this, you also may need to specify LWS_MBEDTLS_LIBRARIES and LWS_MBEDTLS_INCLUDE_DIRS" OFF)
option(LWS_WITH_BORINGSSL "Use BoringSSL replacement for OpenSSL" OFF)
option(LWS_WITH_CYASSL "Use CyaSSL replacement for OpenSSL. When setting this, you also need to specify LWS_CYASSL_LIBRARIES and LWS_CYASSL_INCLUDE_DIRS" OFF)
option(LWS_WITH_WOLFSSL "Use wolfSSL replacement for OpenSSL. When setting this, you also need to specify LWS_WOLFSSL_LIBRARIES and LWS_WOLFSSL_INCLUDE_DIRS" OFF)
option(LWS_SSL_CLIENT_USE_OS_CA_CERTS "SSL support should make use of the OS-installed CA root certs" OFF)
#
# Event library options (may select multiple, or none for default poll()
#
option(LWS_WITH_LIBEV "Compile with support for libev" OFF)
option(LWS_WITH_LIBUV "Compile with support for libuv" OFF)
option(LWS_WITH_LIBEVENT "Compile with support for libevent" OFF)
option(LWS_WITH_GLIB "Compile with support for glib event loop" OFF)

if (UNIX)
    # since v4.1, on unix platforms default is build any event libs as runtime plugins
    option(LWS_WITH_EVLIB_PLUGINS "Compile event lib support into runtime-selected plugins" ON)
else ()
    # otherwise default to linking the event lib(s) to libwebsockets.so
    option(LWS_WITH_EVLIB_PLUGINS "Compile event lib support into runtime-selected plugins" OFF)
endif ()
#
# LWS Drivers
#

option(LWS_WITH_DRIVERS "With generic drivers for gpio, i2c, display etc" OFF)

#
# Static / Dynamic build options
#
option(LWS_WITH_STATIC "Build the static version of the library" ON)
option(LWS_WITH_SHARED "Build the shared version of the library" OFF)
option(LWS_LINK_TESTAPPS_DYNAMIC "Link the test apps to the shared version of the library. Default is to link statically" OFF)
option(LWS_STATIC_PIC "Build the static version of the library with position-independent code" OFF)
#
# Specific platforms
#
option(LWS_WITH_ESP32 "Build for ESP32" OFF)
option(LWS_PLAT_OPTEE "Build for OPTEE" OFF)
option(LWS_PLAT_FREERTOS "Build for FreeRTOS" OFF)
option(LWS_PLAT_ANDROID "Android flavour of unix platform" OFF)

#
# Client / Server / Test Apps build control
#
option(LWS_WITHOUT_CLIENT "Don't build the client part of the library" OFF)
option(LWS_WITHOUT_SERVER "Don't build the server part of the library" OFF)
option(LWS_WITHOUT_TESTAPPS "Don't build the libwebsocket-test-apps" ON)
option(LWS_WITHOUT_TEST_SERVER "Don't build the test server" ON)
option(LWS_WITHOUT_TEST_SERVER_EXTPOLL "Don't build the test server version that uses external poll" ON)
option(LWS_WITHOUT_TEST_PING "Don't build the ping test application" ON)
option(LWS_WITHOUT_TEST_CLIENT "Don't build the client test application" ON)
#
# Extensions (permessage-deflate)
#
option(LWS_WITHOUT_EXTENSIONS "Don't compile with extensions" ON)
#
# Helpers + misc
#
option(LWS_WITHOUT_BUILTIN_GETIFADDRS "Don't use the BSD getifaddrs implementation from libwebsockets if it is missing (this will result in a compilation error) ... The default is to assume that your libc provides it. On some systems such as uclibc it doesn't exist." OFF)
option(LWS_FALLBACK_GETHOSTBYNAME "Also try to do dns resolution using gethostbyname if getaddrinfo fails" OFF)
option(LWS_WITHOUT_BUILTIN_SHA1 "Don't build the lws sha-1 (eg, because openssl will provide it" OFF)
option(LWS_WITHOUT_DAEMONIZE "Don't build the daemonization api" ON)
option(LWS_SSL_SERVER_WITH_ECDH_CERT "Include SSL server use ECDH certificate" OFF)
option(LWS_WITH_LEJP "With the Lightweight JSON Parser" ON)
option(LWS_WITH_SQLITE3 "Require SQLITE3 support" OFF)
option(LWS_WITH_STRUCT_JSON "Generic struct serialization to and from JSON" OFF)
option(LWS_WITH_STRUCT_SQLITE3 "Generic struct serialization to and from SQLITE3" OFF)
# broken atm
#option(LWS_WITH_SMTP "Provide SMTP support" OFF)
if (LWS_WITH_ESP32)
    option(LWS_WITH_DIR "Directory scanning api support" OFF)
    option(LWS_WITH_LEJP_CONF "With LEJP configuration parser as used by lwsws" OFF)
else()
    option(LWS_WITH_DIR "Directory scanning api support" ON)
    option(LWS_WITH_LEJP_CONF "With LEJP configuration parser as used by lwsws" ON)
endif()
option(LWS_WITH_NO_LOGS "Disable all logging other than _err and _user from being compiled in" OFF)
set(LWS_LOGGING_BITFIELD_SET 0 CACHE STRING "Bitfield describing which log levels to force included into the build")
set(LWS_LOGGING_BITFIELD_CLEAR 0 CACHE STRING "Bitfield describing which log levels to force removed from the build")
option(LWS_LOGS_TIMESTAMP "Timestamp at start of logs" ON)
option(LWS_AVOID_SIGPIPE_IGN "Android 7+ reportedly needs this" OFF)
option(LWS_WITH_STATS "Keep statistics of lws internal operations" OFF)
option(LWS_WITH_JOSE "JSON Web Signature / Encryption / Keys (RFC7515/6/) API" OFF)
option(LWS_WITH_GENCRYPTO "Enable support for Generic Crypto apis independent of TLS backend" OFF)
option(LWS_WITH_SELFTESTS "Selftests run at context creation" OFF)
option(LWS_WITH_GCOV "Build with gcc gcov coverage instrumentation" OFF)
option(LWS_WITH_EXPORT_LWSTARGETS "Export libwebsockets CMake targets.  Disable if they conflict with an outer cmake project." ON)
option(LWS_REPRODUCIBLE "Build libwebsockets reproducible. It removes the build user and hostname from the build" ON)
option(LWS_WITH_MINIMAL_EXAMPLES "Also build the normally standalone minimal examples, for QA" OFF)
option(LWS_WITH_LWSAC "lwsac Chunk Allocation api" ON)
option(LWS_WITH_CUSTOM_HEADERS "Store and allow querying custom HTTP headers (H1 only)" ON)
option(LWS_WITH_DISKCACHE "Hashed cache directory with lazy LRU deletion to size limit" OFF)
option(LWS_WITH_ASAN "Build with gcc runtime sanitizer options enabled (needs libasan)" OFF)
option(LWS_WITH_LEJP_CONF "With LEJP configuration parser as used by lwsws" OFF)
option(LWS_WITH_ZLIB "Include zlib support (required for extensions)" OFF)
option(LWS_WITH_BUNDLED_ZLIB "Use bundled zlib version (Windows only)" ${LWS_WITH_BUNDLED_ZLIB_DEFAULT})
option(LWS_WITH_MINIZ "Use miniz instead of zlib" OFF)
option(LWS_WITH_DEPRECATED_THINGS "Temporary workaround for deprecated apis" OFF)
option(LWS_WITH_SEQUENCER "lws_seq_t support" ON)
option(LWS_WITH_EXTERNAL_POLL "Support external POLL integration using callback messages (not recommended)" OFF)
option(LWS_WITH_LWS_DSH "Support lws_dsh_t Disordered Shared Heap" OFF)
option(LWS_CLIENT_HTTP_PROXYING "Support external http proxies for client connections" ON)
option(LWS_WITH_FILE_OPS "Support file operations vfs" ON)
option(LWS_WITH_DETAILED_LATENCY "Record detailed latency stats for each read and write" OFF)
option(LWS_WITH_UDP "Platform supports UDP" ON)
option(LWS_WITH_SPAWN "Spawn subprocesses with piped stdin/out/stderr" OFF)
option(LWS_WITH_FSMOUNT "Overlayfs and fallback mounting apis" OFF)
option(LWS_WITH_FANALYZER "Enable gcc -fanalyzer if compiler supports" OFF)
option(LWS_HTTP_HEADERS_ALL "Override header reduction optimization and include all like older lws versions" OFF)
option(LWS_WITH_SUL_DEBUGGING "Enable zombie lws_sul checking on object deletion" OFF)
option(LWS_WITH_PLUGINS_API "Build generic lws_plugins apis (see LWS_WITH_PLUGINS to also build protocol plugins)" OFF)

#
# to use miniz, enable both LWS_WITH_ZLIB and LWS_WITH_MINIZ
#
# End of user settings
#

# sets of sub-options implied by other options
#
set(LIB_LIST "")
set(LIB_LIST_AT_END)
set(LWS_LIBRARIES)

set(LWS_LIBRARY_VERSION "4.1.3")
set(LWS_LIBRARY_VERSION_MAJOR 4)
set(LWS_LIBRARY_VERSION_MINOR 1)
set(LWS_LIBRARY_VERSION_PATCH 3)

# Modfied for Urho3D to allow building libwebsockets with SSL support
if (URHO3D_SSL)
    message(STATUS "Adding SSL support for libwebsockets")
    set(LWS_OPENSSL_SUPPORT 1)
    set(LWS_WITH_SSL 1)
endif ()

include(CMakeLists-implied-options.txt)

macro(exports_to_parent_scope)
    foreach(file ${SOURCES})
        list(APPEND SOURCE_FILES "lib/${file}")
    endforeach(file)
    set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
    if (LIB_LIST)
        set(LIB_LIST ${LIB_LIST} PARENT_SCOPE)
    endif()
    get_property(_CURR DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
    set(_CMAKE_INC_LIST ${_CURR} PARENT_SCOPE)
    if (LWS_LIB_BUILD_INC_PATHS)
        set(LWS_LIB_BUILD_INC_PATHS ${LWS_LIB_BUILD_INC_PATHS} PARENT_SCOPE)
    endif()
endmacro()

macro(export_to_parent_intermediate)
    foreach(file ${SOURCES})
        list(APPEND SOURCE_FILES "lib/${file}")
    endforeach(file)
    set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
    if (LIB_LIST)
        set(LIB_LIST ${LIB_LIST} PARENT_SCOPE)
    endif()
    set(_CMAKE_INC_LIST ${_CMAKE_INC_LIST} PARENT_SCOPE)
    if (LWS_LIB_BUILD_INC_PATHS)
        set(LWS_LIB_BUILD_INC_PATHS ${LWS_LIB_BUILD_INC_PATHS} PARENT_SCOPE)
    endif()
endmacro()

macro(add_subdir_include_directories arg1)
    add_subdirectory(${arg1})
#    include_directories(${_CMAKE_INC_LIST})
#    list(APPEND INCLUDE_DIRECTORIES ${_CMAKE_INC_LIST})
    list(APPEND INCLUDE_DIRS lib/${arg1} lib/system/${arg1} lib/roles/${arg1})
    set(INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
endmacro()

macro(add_subdir_include_dirs arg1)
    add_subdirectory(${arg1})
    list(APPEND INCLUDE_DIRS lib/${arg1} lib/system/${arg1} lib/role/${arg1})
    set(INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
#    list(APPEND LWS_LIB_BUILD_INC_PATHS ${_CMAKE_INC_LIST})
#    list(APPEND INCLUDE_DIRECTORIES ${_CMAKE_INC_LIST})
endmacro()
########

# Define source files
add_subdirectory(lib)
#define_source_files (RECURSE GLOB_CPP_PATTERNS lib/*.c GLOB_H_PATTERNS src/*.h)

# Generate libwebsockets configuration file with defined macros
configure_file(
        cmake/lws_config.h.in
        "${PROJECT_BINARY_DIR}/Source/ThirdParty/libwebsockets/include/lws_config.h")

configure_file(
        cmake/lws_config_private.h.in
        "${PROJECT_BINARY_DIR}/Source/ThirdParty/libwebsockets/include/lws_config_private.h")

add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/include/lws_config.h
        ${PROJECT_BINARY_DIR}/include/libwebsockets
        ${PROJECT_BINARY_DIR}/include/libwebsockets.h
        COMMENT "Creating build include dir"
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/include/libwebsockets.h
        ${CMAKE_CURRENT_BINARY_DIR}/include/libwebsockets.h
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/include/libwebsockets/
        ${CMAKE_CURRENT_BINARY_DIR}/include/libwebsockets
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/lws_config.h
        ${CMAKE_CURRENT_BINARY_DIR}/include/lws_config.h
        MAIN_DEPENDENCY ${PROJECT_BINARY_DIR}/lws_config.h
)

list (APPEND INCLUDE_DIRS ${PROJECT_BINARY_DIR}/Source/ThirdParty/libwebsockets/include)

message (STATUS SOURCEFILES "${SOURCE_FILESs} - ${INCLUDE_DIRS}")
# Setup target
setup_library ()

# Install headers for building the Urho3D library
install_header_files (DIRECTORY include/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/libwebsockets FILES_MATCHING PATTERN *.h BUILD_TREE_ONLY)  # Note: the trailing slash is significant
