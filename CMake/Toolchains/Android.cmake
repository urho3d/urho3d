#
# Copyright (c) 2016-2017 Yao Wei Tjong. All rights reserved.
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

# Modified by Yao Wei Tjong for Urho3D

#
# This CMake toolchain file is designed to work with both cmake-gui and cmake CLI.
# It is inspired from https://github.com/taka-no-me/android-cmake/android.toolchain.cmake,
# most of its options are kept for compatibility, however, the possible values for each option are not identical.
#
# Options:
#   ANDROID_NDK - path to the NDK root.
#     Can be set as environment variable.
#     NOTE: This option cannot be changed after the initial configuration/generation.
#
#   ANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-clang - the name of compiler toolchain to be used.
#     The possible values are derived from the prebuilt compiler toolchains in the Android NDK.
#     NOTE: This option cannot be changed after the initial configuration/generation.
#
#   ANDROID_ABI=armeabi-v7a - specifies the target Application Binary Interface (ABI).
#     This option nearly matches to the APP_ABI variable used by ndk-build tool from Android NDK.
#
#     Possible targets are:
#       1) For arm arch:
#          armeabi-v7a - ARMv7 based devices with hardware FPU instructions but software floating-point calling convention (softfp).
#          armeabi-v6 - ARMv6 based devices with hardware FPU instructions but software floating-point calling convention (softfp).
#          armeabi - ARMv5TE based CPU with software floating point operations (soft).
#
#          These ABI options can be combined with one of the below modifiers to specify which hardware FPU to use:
#          "with neon-vfpv4" - Use NEON SIMD and VFPv4.
#          "with neon" - Use NEON SIMD and VFPv3.
#          "with vfpv4" - Use VFPv4.
#          "with vfpv3" - Use VFPv3 (32 registers).
#          "with vfpv3-d16" - Use VFPv3 (16 registers). This is the default for ARMv7.
#          "with vfp" - Use VFPv2. This is the default and the only possible combination for ARMv6.
#
#       2) For aarch64 arch:
#          arm64-v8a - ARMv8 AArch64 instruction set.
#
#       3) For i686 arch:
#          x86 - IA-32 instruction set.
#
#       4) For x86_64 arch:
#          x86_64 - Intel64 instruction set.
#
#       5) For mipsel arch:
#          mips - MIPS32 instruction set.
#
#       6) For mips64el arch:
#          mips64 - MIPS64 instruction set.
#
#   ANDROID_NATIVE_API_LEVEL=android-9 - level of Android API compile for.
#     The default level is android-21 when targeting any of the 64-bit ABIs.
#     NOTE: The level must not be larger than android:minSdkVersion in AndroidManifest.xml.
#
#   ANDROID_FORCE_ARM_BUILD=OFF - set ON to generate 32-bit ARM instructions instead of Thumb.
#     This option is only available for arm arch.
#
#   ANDROID_STACK_PROTECTION=OFF - set ON to force the addition of a stack canary that checks for stack smashing.
#     When it is ON the generated binary may be larger in size and slower in performance.
#     Unlike ndk-build, it is defaulted to OFF.
#
#   ANDROID_NO_UNDEFINED=ON - set ON to show all undefined symbols as linker errors even if they are not used.
#
#   ANDROID_NOEXECSTACK=ON - set ON to enforce the NX (no execute) security feature in the generated machine code.
#
#   ANDROID_RELRO=ON - set ON to mark certain regions of the resulting executable or shared library as being read-only.
#
#   ANDROID_FATAL_WARNINGS=ON - set ON to treat all linker warnings as errors.
#
#   ANDROID_FORMAT_SECURITY=ON - set ON to provide compiler protection against format string vulnerabilities.
#
#   ANDROID_FUNCTION_LEVEL_LINKING=ON - set ON to split data/function sections and garbage collect unused sections at link time.
#     This option may be turned off to avoid potential debugging problems in Debug build configuration.
#
#   ANDROID_STL=system - specify the C++ STL runtime to use.
#     When ANDROID_STL_FORCE_FEATURES is ON then it auto-configures the RTTI and exceptions settings to ON for any runtime chosen,
#     except for default system runtime.
#     NOTE: Use shared runtime when your project contains multiple shared libraries or executables.
#           Otherwise, the build system does not define certain global uniquely, which can result in unpredictable runtime behavior.
#           This behavior may include crashes and failure to properly catch exceptions.
#
#     Possible values are:
#       system         -> Use the minimal system C++ runtime library. Implies -fno-rtti -fno-exceptions.
#       gabi++_static  -> Use the GAbi++ runtime as a static library.
#       gabi++_shared  -> Use the GAbi++ runtime as a shared library.
#       stlport_static -> Use the STLport runtime as a static library. STLport is licensed under BSD-like license.
#       stlport_shared -> Use the STLport runtime as a shared library.
#       gnustl_static  -> Use the GNU libstdc++ as a static library. GNU libstdc++ is licensed under GPLv3 + linking exception.
#       gnustl_shared  -> Use the GNU libstdc++ as a shared library.
#       c++_static     -> Use the LLVM libc++ runtime as a static library. LLVM libc++ is licensed under BSD-Like and MIT license.
#       c++_shared     -> Use the LLVM libc++ runtime as a shared library.
#
#   ANDROID_STL_FORCE_FEATURES=ON - automatically configure rtti and exceptions settings based on the chosen C++ STL runtime.
#     If disabled, then the user is responsible for setting ANDROID_RTTI and ANDROID_EXCEPTIONS options manually.
#
#   ANDROID_RTTI=ON - set ON to enable RTTI.
#     This option is only available when ANDROID_STL_FORCE_FEATURES is disabled.
#
#   ANDROID_EXCEPTIONS=ON - set ON to enable C++ exceptions.
#     This option is only available when ANDROID_STL_FORCE_FEATURES is disabled.
#

cmake_minimum_required (VERSION 3.2.3)
mark_as_advanced (CMAKE_TOOLCHAIN_FILE)
set (CMAKE_SYSTEM_NAME Android)
set (CMAKE_SYSTEM_VERSION 1)
set (CMAKE_POSITION_INDEPENDENT_CODE 1)
set (ANDROID 1)

# Prevent critical variables from changing after the initial configuration
if (CMAKE_CROSSCOMPILING)
    set (SAVED_ANDROID_NDK ${ANDROID_NDK} CACHE INTERNAL "Initial value for ANDROID_NDK")
    set (SAVED_ANDROID_TOOLCHAIN_NAME ${ANDROID_TOOLCHAIN_NAME} CACHE INTERNAL "Initial value for ANDROID_TOOLCHAIN_NAME")
    # Urho3D - save the initial values of CC and CXX environment variables
    set (SAVED_CC $ENV{CC} CACHE INTERNAL "Initial value for CC")
    set (SAVED_CXX $ENV{CXX} CACHE INTERNAL "Initial value for CXX")
    return ()
elseif ((SAVED_ANDROID_NDK AND NOT SAVED_ANDROID_NDK STREQUAL ANDROID_NDK) OR (SAVED_ANDROID_TOOLCHAIN_NAME AND NOT SAVED_ANDROID_TOOLCHAIN_NAME STREQUAL ANDROID_TOOLCHAIN_NAME))
    set (ANDROID_NDK ${SAVED_ANDROID_NDK} CACHE PATH "Path to Android NDK (Android platform only)" FORCE)
    set (ANDROID_TOOLCHAIN_NAME ${SAVED_ANDROID_TOOLCHAIN_NAME} CACHE STRING "Specify the name of compiler toolchain (Android platform only), possible values depends on installed Android NDK, default to Clang compiler toolchain" FORCE)
    message (FATAL_ERROR "ANDROID_NDK and ANDROID_TOOLCHAIN_NAME cannot be changed after the initial configuration/generation. "
        "Auto reverting to its initial value. If you wish to change it then the build tree would have to be regenerated from scratch.")
endif ()

# Workaround try_compile() limitation where it cannot see cache variables and it is a waste of time to reinit everything all over
get_property (IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE)
if (NOT IN_TRY_COMPILE)
    # Android NDK paths
    if (NOT SAVED_ANDROID_NDK)
        if (NOT ANDROID_NDK AND DEFINED ENV{ANDROID_NDK})
            file (TO_CMAKE_PATH $ENV{ANDROID_NDK} ANDROID_NDK)
        endif ()
        set (ANDROID_NDK ${ANDROID_NDK} CACHE PATH "Path to Android NDK (Android platform only)")
        if (NOT EXISTS ${ANDROID_NDK})
            message (FATAL_ERROR "Could not find Android NDK. "
                "Use ANDROID_NDK environment variable or build option to specify the location of Android NDK.")
        endif ()
    endif ()
    if (NOT ANDROID_NDK_VERSION)
        if (EXISTS ${ANDROID_NDK}/source.properties)
            file (STRINGS ${ANDROID_NDK}/source.properties LINE LIMIT_COUNT 1 REGEX [0-9]+\\.[0-9]+\\.[0-9]+)
        endif ()
        if (LINE MATCHES "([0-9]+\\.[0-9]+\\.[0-9]+)")
            set (ANDROID_NDK_VERSION ${CMAKE_MATCH_1} CACHE INTERNAL "Android NDK version")
        endif ()
        if (ANDROID_NDK_VERSION LESS 12)
            unset (ANDROID_NDK_VERSION CACHE)
            message (FATAL_ERROR "Unsupported Android NDK version. This toolchain file only supports Android NDK r12 onward.")
        endif ()
    endif ()
    set (ANDROID_NDK_TOOLCHAINS_CONFIG_PATH ${ANDROID_NDK}/build/core/toolchains)
    set (ANDROID_NDK_TOOLCHAINS_PATH ${ANDROID_NDK}/toolchains)
    if (NOT ANDROID_NDK_HOST_SYSTEM_NAME)
        file (GLOB ANDROID_NDK_HOST_SYSTEM_NAME RELATIVE ${ANDROID_NDK_TOOLCHAINS_PATH}/llvm/prebuilt ${ANDROID_NDK_TOOLCHAINS_PATH}/llvm/prebuilt/*)
        set (ANDROID_NDK_HOST_SYSTEM_NAME ${ANDROID_NDK_HOST_SYSTEM_NAME} CACHE INTERNAL "Android NDK host system name")
    endif ()
    set (ANDROID_NDK_TOOLCHAINS_SUBPATH /prebuilt/${ANDROID_NDK_HOST_SYSTEM_NAME})

    # Android compiler toolchains
    if (NOT SAVED_ANDROID_TOOLCHAIN_NAME)
        set (ANDROID_DEFAULT_TOOLCHAIN_NAME arm-linux-androideabi-clang)
        set (ANDROID_TOOLCHAIN_NAME ${ANDROID_DEFAULT_TOOLCHAIN_NAME} CACHE STRING "Specify the name of compiler toolchain (Android platform only), default to ${ANDROID_DEFAULT_TOOLCHAIN_NAME}")
        file (GLOB ANDROID_SUPPORTED_TOOLCHAINS RELATIVE ${ANDROID_NDK_TOOLCHAINS_CONFIG_PATH} ${ANDROID_NDK_TOOLCHAINS_CONFIG_PATH}/*)
        list (SORT ANDROID_SUPPORTED_TOOLCHAINS)
        set_property (CACHE ANDROID_TOOLCHAIN_NAME PROPERTY STRINGS ${ANDROID_SUPPORTED_TOOLCHAINS})
        list (FIND ANDROID_SUPPORTED_TOOLCHAINS "${ANDROID_TOOLCHAIN_NAME}" FOUND_INDEX)    # Stringify as the actual variable may be empty
        if (FOUND_INDEX EQUAL -1)
            string (REPLACE ";" "\", \"" PRINTABLE_ANDROID_SUPPORTED_TOOLCHAINS "\"${ANDROID_SUPPORTED_TOOLCHAINS}\"")
            message (FATAL_ERROR "Unrecognized '${ANDROID_TOOLCHAIN_NAME}' specified in the ANDROID_TOOLCHAIN_NAME option, "
                "supported values are: ${PRINTABLE_ANDROID_SUPPORTED_TOOLCHAINS}.")
        endif ()
        set (ANDROID_TOOLCHAIN_ROOT ${ANDROID_NDK_TOOLCHAINS_PATH}/${ANDROID_TOOLCHAIN_NAME}${ANDROID_NDK_TOOLCHAINS_SUBPATH})
        if (ANDROID_TOOLCHAIN_NAME MATCHES "-clang.*$")
            set (ANDROID_CLANG_TOOLCHAIN_ROOT ${ANDROID_NDK_TOOLCHAINS_PATH}/llvm${ANDROID_NDK_TOOLCHAINS_SUBPATH} CACHE INTERNAL "Clang toolchain root if using Clang")
            set (CLANG CLANG_ CACHE INTERNAL "Non empty if using Clang")
            # Check if it still depends on GCC toolchain for assembler and linker support (assume 4.9 is the last deprecated GCC version supported by Android NDK)
            file (STRINGS ${ANDROID_NDK_TOOLCHAINS_CONFIG_PATH}/${ANDROID_TOOLCHAIN_NAME}/setup.mk ANDROID_ROOT_${ANDROID_TOOLCHAIN_NAME} REGEX ^TOOLCHAIN_ROOT.*-4.9)
            if (ANDROID_ROOT_${ANDROID_TOOLCHAIN_NAME})
                string (REGEX REPLACE -clang.*$ -4.9 GCC_TOOLCHAIN_NAME "${ANDROID_TOOLCHAIN_NAME}")
                set (ANDROID_TOOLCHAIN_ROOT ${ANDROID_NDK_TOOLCHAINS_PATH}/${GCC_TOOLCHAIN_NAME}${ANDROID_NDK_TOOLCHAINS_SUBPATH})
            endif ()
        endif ()
        set (ANDROID_TOOLCHAIN_ROOT ${ANDROID_TOOLCHAIN_ROOT} CACHE INTERNAL "GCC toolchain root")
    endif ()
    string (REGEX REPLACE -[^-]+$ "" ANDROID_TOOLCHAIN_MACHINE_NAME "${ANDROID_TOOLCHAIN_NAME}")
    string (REGEX REPLACE -.*$|el "" MACHINE_ARCH "${ANDROID_TOOLCHAIN_MACHINE_NAME}")
    if (ANDROID_TOOLCHAIN_MACHINE_NAME MATCHES x86)
        string (REGEX REPLACE ^x86- i686- ANDROID_TOOLCHAIN_MACHINE_NAME "${ANDROID_TOOLCHAIN_MACHINE_NAME}-linux-android")
    endif ()

    # Android ABIs
    if (NOT ANDROID_ABI OR NOT ANDROID_ABI_SAVED STREQUAL ANDROID_ABI)
        set (ANDROID_SUPPORTED_ABIS_arm armeabi-v7a armeabi-v6 armeabi)
        set (ANDROID_SUPPORTED_ABIS_aarch64 arm64-v8a)
        set (ANDROID_SUPPORTED_ABIS_x86 x86)
        set (ANDROID_SUPPORTED_ABIS_x86_64 x86_64)
        set (ANDROID_SUPPORTED_ABIS_mips mips)
        set (ANDROID_SUPPORTED_ABIS_mips64 mips64)
        set (ANDROID_SUPPORTED_ABIS ${ANDROID_SUPPORTED_ABIS_${MACHINE_ARCH}})
        list (GET ANDROID_SUPPORTED_ABIS 0 DEFAULT_ANDROID_ABI)
        set (ANDROID_ABI ${DEFAULT_ANDROID_ABI} CACHE STRING "Specify target ABI (Android platform only), possible values depends on the target arch of the chosen Android compiler toolchain, default to first ABI of each target arch")
        set_property (CACHE ANDROID_ABI PROPERTY STRINGS ${ANDROID_SUPPORTED_ABIS})
        if (ANDROID_ABI MATCHES with)
            string (REGEX REPLACE ".+with (.+)" \\1 ANDROID_ABI_MODIFIER "${ANDROID_ABI}")
            if (MACHINE_ARCH STREQUAL arm)
                set (ANDROID_SUPPORTED_ARM_ABI_MODIFIERS neon-vfpv4 neon vfpv4 vfpv3 vfpv3-d16 vfp)
                list (FIND ANDROID_SUPPORTED_ARM_ABI_MODIFIERS "${ANDROID_ABI_MODIFIER}" FOUND_INDEX)   # Stringify as the variable may be empty
                if (FOUND_INDEX EQUAL -1)
                    string (REPLACE ";" "\", \"" PRINTABLE_ANDROID_SUPPORTED_ARM_ABI_MODIFIERS "\"${ANDROID_SUPPORTED_ARM_ABI_MODIFIERS}\"")
                    message (FATAL_ERROR "Unrecognized '${ANDROID_ABI_MODIFIER}' specified in the ANDROID_ABI option, "
                        "supported values are: ${PRINTABLE_ANDROID_SUPPORTED_ARM_ABI_MODIFIERS}.")
                endif ()
            else ()
                message (FATAL_ERROR "Unrecognized '${ANDROID_ABI_MODIFIER}' specified in the ANDROID_ABI option, "
                    "the chosen Android ABI does not support any modifiers.")
            endif ()
        endif ()
        string (REGEX REPLACE with.+ "" ANDROID_ABI_BASE "${ANDROID_ABI}")
        list (FIND ANDROID_SUPPORTED_ABIS "${ANDROID_ABI_BASE}" FOUND_INDEX)     # Stringify as the variable may be empty
        if (FOUND_INDEX EQUAL -1)
            string (REPLACE ";" "\", \"" PRINTABLE_ANDROID_SUPPORTED_ABIS "\"${ANDROID_SUPPORTED_ABIS}\"")
            message (FATAL_ERROR "Unrecognized '${ANDROID_ABI}' specified in the ANDROID_ABI option, "
                "supported values are: ${PRINTABLE_ANDROID_SUPPORTED_ABIS}.")
        endif ()
        set (ANDROID_ABI_SAVED ${ANDROID_ABI} CACHE INTERNAL "Last saved value for ANDROID_ABI")
        # Invalidate internal caches that depend on ANDROID_ABI, if any
        unset (ANDROID_STL_SAVED CACHE)     # This should cause ANDROID_STL option to be revalidated
        if (CLANG)
            set (INVALIDATE_CCT 1)
        endif ()
    endif ()
    # First, derive variable values based on chosen compiler toolchain
    set (ANDROID_NDK_ABI_NAME ${MACHINE_ARCH})
    set (ANDROID_ARCH_NAME ${MACHINE_ARCH})
    set (CMAKE_SYSTEM_PROCESSOR ${MACHINE_ARCH})
    string (REGEX REPLACE "^([^-]+).*$" \\1-none-linux-android ANDROID_LLVM_TRIPLE "${ANDROID_TOOLCHAIN_MACHINE_NAME}")
    # Then, handle exceptional cases based on chosen ABI
    if (ANDROID_ABI MATCHES armeabi-v7a)
        if (NOT ANDROID_ABI MATCHES with)
            set (ANDROID_ABI "armeabi-v7a with vfpv3-d16")  # This is the default case for armeabi-v7a
        endif ()
        set (ANDROID_NDK_ABI_NAME armeabi-v7a)
        set (CMAKE_SYSTEM_PROCESSOR armv7-a)
        set (ANDROID_LLVM_TRIPLE armv7-none-linux-androideabi)
    elseif (ANDROID_ABI MATCHES armeabi)
        set (ANDROID_NDK_ABI_NAME armeabi)
        if (ANDROID_ABI MATCHES -v6)
            set (ANDROID_ABI "armeabi-v6 with vfp")     # This is the default case for armeabi-v6
            set (CMAKE_SYSTEM_PROCESSOR armv6)
        else ()
            set (CMAKE_SYSTEM_PROCESSOR armv5te)
        endif ()
        set (ANDROID_LLVM_TRIPLE armv5te-none-linux-androideabi)
    elseif (ANDROID_ABI STREQUAL arm64-v8a)
        set (ANDROID_NDK_ABI_NAME arm64-v8a)
        set (ANDROID_ARCH_NAME arm64)
    elseif (ANDROID_ABI STREQUAL x86)
        set (CMAKE_SYSTEM_PROCESSOR i686)
    endif ()
    include (CMakeDependentOption)
    cmake_dependent_option (ANDROID_FORCE_ARM_BUILD "Use 32-bit ARM instructions instead of Thumb" FALSE "ANDROID_ARCH_NAME STREQUAL arm" FALSE)
    # Urho3D - comment out as Urho manages the runtime and library output directories in its own module
    #set (CMAKE_RUNTIME_OUTPUT_DIRECTORY {CMAKE_BINARY_DIR}/bin)
    #set (CMAKE_LIBRARY_OUTPUT_DIRECTORY {CMAKE_BINARY_DIR}/libs/${ANDROID_NDK_ABI_NAME})

    # Android API levels
    if (NOT ANDROID_NATIVE_API_LEVEL OR NOT ANDROID_NATIVE_API_LEVEL_SAVED STREQUAL ANDROID_NATIVE_API_LEVEL)
        set (ANDROID_DEFAULT_NDK_API_LEVEL_arm 9)
        set (ANDROID_DEFAULT_NDK_API_LEVEL_arm64 21)
        set (ANDROID_DEFAULT_NDK_API_LEVEL_x86 9)
        set (ANDROID_DEFAULT_NDK_API_LEVEL_x86_64 21)
        set (ANDROID_DEFAULT_NDK_API_LEVEL_mips 9)
        set (ANDROID_DEFAULT_NDK_API_LEVEL_mips64 21)
        set (ANDROID_DEFAULT_NDK_API_LEVEL ${ANDROID_DEFAULT_NDK_API_LEVEL_${ANDROID_ARCH_NAME}})
        set (ANDROID_NATIVE_API_LEVEL android-${ANDROID_DEFAULT_NDK_API_LEVEL} CACHE STRING "Specify target API level (Android platform only), default to 'android-9' on 32-bit ABIs, default to 'android-21' on 64-bit ABIs")
        if (NOT SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME})
            if (NOT SUPPORTED_NATIVE_API_LEVELS)
                file (GLOB SUPPORTED_NATIVE_API_LEVELS RELATIVE ${ANDROID_NDK}/platforms ${ANDROID_NDK}/platforms/android-*)
                string (REPLACE android- "" SUPPORTED_NATIVE_API_LEVELS "${SUPPORTED_NATIVE_API_LEVELS}")
                set (SUPPORTED_NATIVE_API_LEVELS ${SUPPORTED_NATIVE_API_LEVELS} CACHE INTERNAL "Supported Android native API levels")
            endif ()
            set (SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME} ${SUPPORTED_NATIVE_API_LEVELS})
            foreach (API_LEVEL ${SUPPORTED_NATIVE_API_LEVELS})
                if (API_LEVEL LESS ANDROID_DEFAULT_NDK_API_LEVEL OR API_LEVEL LESS 10)
                    list (REMOVE_ITEM SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME} ${API_LEVEL})
                endif ()
                if (NOT API_LEVEL LESS ANDROID_DEFAULT_NDK_API_LEVEL AND API_LEVEL LESS 10)
                    list (APPEND SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME} 0${API_LEVEL})    # Add 0 padding for sorting
                endif ()
            endforeach ()
            list (SORT SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME})
            string (REGEX REPLACE ";0*" ";android-" SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME} ";${SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME}}")
            string (REGEX REPLACE "^;" "" SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME} "${SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME}}")
            set (SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME} ${SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME}} CACHE INTERNAL "Supported Android native API levels for arch ${ANDROID_ARCH_NAME}")
        endif ()
        set_property (CACHE ANDROID_NATIVE_API_LEVEL PROPERTY STRINGS ${SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME}})
        list (FIND SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME} "${ANDROID_NATIVE_API_LEVEL}" FOUND_INDEX)   # Stringify as the actual variable may be empty
        if (FOUND_INDEX EQUAL -1)
            string (REPLACE ";" "\", \"" PRINTABLE_ANDROID_SUPPORTED_NATIVE_API_LEVELS "\"${SUPPORTED_NATIVE_API_LEVELS_${ANDROID_ARCH_NAME}}\"")
            message (FATAL_ERROR "Unsupported '${ANDROID_NATIVE_API_LEVEL}' specified in the ANDROID_NATIVE_API_LEVEL option, "
                "supported values are: ${PRINTABLE_ANDROID_SUPPORTED_NATIVE_API_LEVELS}.")
        endif ()
        set (ANDROID_NATIVE_API_LEVEL_SAVED ${ANDROID_NATIVE_API_LEVEL} CACHE INTERNAL "Last saved value for ANDROID_NATIVE_API_LEVEL")
    endif ()
    # Warn if the chosen level is larger than android:minSdkVersion, this check can only done in CMake rerun (after the build tree has been generated)
    string (REPLACE android- "" APP_PLATFORM_LEVEL "${ANDROID_NATIVE_API_LEVEL}")
    if (EXISTS ${CMAKE_BINARY_DIR}/AndroidManifest.xml)
        file (STRINGS ${CMAKE_BINARY_DIR}/AndroidManifest.xml LINE LIMIT_COUNT 1 REGEX android:minSdkVersion=)
        if (LINE MATCHES "android:minSdkVersion=\"([^\"]+)\"")
            set (APP_MIN_PLATFORM_LEVEL ${CMAKE_MATCH_1})
            if (APP_PLATFORM_LEVEL GREATER APP_MIN_PLATFORM_LEVEL)
                message (WARNING "ANDROID_NATIVE_API_LEVEL (${ANDROID_NATIVE_API_LEVEL}) is larger than android:minSdkVersion (${APP_MIN_PLATFORM_LEVEL}) in AndroidManifest.xml.")
            endif ()
        endif ()
    endif ()

    # System root
    set (CMAKE_SYSROOT ${ANDROID_NDK}/platforms/${ANDROID_NATIVE_API_LEVEL}/arch-${ANDROID_ARCH_NAME})

    # C++ STL runtimes
    option (ANDROID_STL_FORCE_FEATURES "Automatically configure rtti and exceptions support based on the chosen C++ STL runtime" TRUE)
    # Urho3D - always use RTTI due to dynamic cast usage in the codebase
    #cmake_dependent_option (ANDROID_RTTI "Set ON to enable RTTI" TRUE "NOT ANDROID_STL_FORCE_FEATURES" TRUE)
    set (ANDROID_RTTI 1)
    cmake_dependent_option (ANDROID_EXCEPTIONS "Set ON to enable C++ exceptions" TRUE "NOT ANDROID_STL_FORCE_FEATURES" TRUE)
    if (NOT FEATURE_SIGNATURE STREQUAL "${ANDROID_STL_FORCE_FEATURES}-${ANDROID_RTTI}-${ANDROID_EXCEPTIONS}")
        set (INVALIDATE_CCT 1)
        set (FEATURE_SIGNATURE "${ANDROID_STL_FORCE_FEATURES}-${ANDROID_RTTI}-${ANDROID_EXCEPTIONS}" CACHE INTERNAL "Signature when the C++ features are last cached")
    endif ()
    # Urho3D - warn if static runtime is chosen when using SHARED Urho3D library type
    if (URHO3D_LIB_TYPE STREQUAL SHARED AND ANDROID_STL MATCHES static)
        message (WARNING "Using static C++ STL runtime (${ANDROID_STL}) with SHARED Urho3D library type may result in unpredictable runtime behavior.")
    endif ()
    if (NOT ANDROID_STL OR NOT ANDROID_STL_SAVED STREQUAL ANDROID_STL)
        # Urho3D - default to use LLVM libc++ runtime
        #set (ANDROID_DEFAULT_STL system)
        if (URHO3D_LIB_TYPE STREQUAL SHARED)
            set (ANDROID_DEFAULT_STL c++_shared)
        else ()
            set (ANDROID_DEFAULT_STL c++_static)
        endif ()
        set (ANDROID_STL ${ANDROID_DEFAULT_STL} CACHE STRING "Specify the C++ STL runtime (Android platform only), default to ${ANDROID_DEFAULT_STL}; STLport may only be used when URHO3D_NETWORK is disabled")
        # Urho3D - proper C++ STL runtime is required to build Urho3D, exclude those that do not cut it
        #set (ANDROID_SUPPORTED_RUNTIMES system gabi++_static gabi++_shared stlport_static stlport_shared gnustl_static gnustl_shared c++_static c++_shared)
        set (ANDROID_SUPPORTED_RUNTIMES stlport_static stlport_shared gnustl_static gnustl_shared c++_static c++_shared)
        set_property (CACHE ANDROID_STL PROPERTY STRINGS ${ANDROID_SUPPORTED_RUNTIMES})
        list (FIND ANDROID_SUPPORTED_RUNTIMES "${ANDROID_STL}" FOUND_INDEX)     # Stringify as the actual variable may be empty
        if (FOUND_INDEX EQUAL -1)
            string (REPLACE ";" "\", \"" PRINTABLE_ANDROID_SUPPORTED_RUNTIMES "\"${ANDROID_SUPPORTED_RUNTIMES}\"")
            message (FATAL_ERROR "Unrecognized '${ANDROID_STL}' specified in the ANDROID_STL option, "
                "supported values are: ${PRINTABLE_ANDROID_SUPPORTED_RUNTIMES}.")
        endif ()
        if (ANDROID_STL STREQUAL system)
            if (ANDROID_STL_FORCE_FEATURES)
                set (ANDROID_RTTI 0)
                set (ANDROID_EXCEPTIONS 0)
            endif ()
            set (STL_LIBS stdc++)
            # If the 'system' runtime is used in combination with RTTI or C++ exceptions then automatically link against the GNU libsupc++ for now
            if (ANDROID_RTTI OR ANDROID_EXCEPTIONS)
                set (STL_LIBS ${STL_LIBS} supc++)
            endif ()
            set (STL_INCLUDE_DIRS ${ANDROID_NDK}/sources/cxx-stl/system/include)
        elseif (ANDROID_STL MATCHES gabi\\+\\+)
            set (STL_INCLUDE_DIRS ${ANDROID_NDK}/sources/cxx-stl/gabi++/include)
        elseif (ANDROID_STL MATCHES stlport)
            set (STL_LIBS ${ANDROID_STL})
            set (STL_LIBRARY_DIR ${ANDROID_NDK}/sources/cxx-stl/stlport/libs/${ANDROID_NDK_ABI_NAME})
            set (STL_INCLUDE_DIRS ${ANDROID_NDK}/sources/cxx-stl/stlport/stlport)   # This is not a typo!
        elseif (ANDROID_STL MATCHES gnustl)
            set (STL_LIBS ${ANDROID_STL} supc++)
            set (STL_LIBRARY_DIR ${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.9/libs/${ANDROID_NDK_ABI_NAME})
            set (STL_INCLUDE_DIRS ${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.9/include ${STL_LIBRARY_DIR}/include)
        elseif (ANDROID_STL MATCHES c\\+\\+)
            set (STL_LIBS c++)
            # TODO: Remove this once libgcc.a is not being used
            set (GCC_FIX "-Wl,-z,muldefs")
            set (STL_LIBRARY_DIR ${ANDROID_NDK}/sources/cxx-stl/llvm-libc++/libs/${ANDROID_NDK_ABI_NAME})
            if (EXISTS ${ANDROID_NDK}/sources/cxx-stl/llvm-libc++/libcxx)
                set (LIBCXX libcxx/)
                set (LIBCXXABI libcxxabi/)
            endif ()
            set (STL_INCLUDE_DIRS ${ANDROID_NDK}/sources/cxx-stl/llvm-libc++/${LIBCXX}include ${ANDROID_NDK}/sources/cxx-stl/llvm-libc++abi/${LIBCXXABI}include ${ANDROID_NDK}/sources/android/support/include)
        endif ()
        file (GLOB SHARED_LIBS ${CMAKE_BINARY_DIR}/libs/${ANDROID_NDK_ABI_NAME}/lib*_shared.so)
        if (SHARED_LIBS)
            execute_process (COMMAND ${CMAKE_COMMAND} -E remove ${SHARED_LIBS})
        endif ()
        if (ANDROID_STL MATCHES shared)
            execute_process (COMMAND ${CMAKE_COMMAND} -E copy_if_different ${STL_LIBRARY_DIR}/lib${ANDROID_STL}.so ${CMAKE_BINARY_DIR}/libs/${ANDROID_NDK_ABI_NAME}/lib${ANDROID_STL}.so)
        endif ()
        if (STL_LIBS)
            string (REPLACE ";" " -l" STL_LINKER_FLAGS ";${STL_LIBS}")
            if (ANDROID_STL MATCHES system|static)
                set (STL_LINKER_FLAGS "-Wl,-Bstatic ${STL_LINKER_FLAGS} -Wl,-Bdynamic")
            endif ()
            set (STL_LINKER_FLAGS "-L${STL_LIBRARY_DIR} ${STL_LINKER_FLAGS} ${GCC_FIX}")
        else ()
            set (STL_LINKER_FLAGS)
        endif ()
        foreach (VAR ANDROID_RTTI ANDROID_EXCEPTIONS STL_INCLUDE_DIRS STL_LIBRARY_DIR STL_LINKER_FLAGS)
            set (${VAR} ${${VAR}} CACHE INTERNAL "C++ STL runtimes")
        endforeach ()
        set (ANDROID_STL_SAVED ${ANDROID_STL} CACHE INTERNAL "Last saved value for ANDROID_STL")
    endif ()

    # Cross compiler tools
    if (CMAKE_HOST_WIN32)
        set (TOOL_EXT .exe)
    endif ()
    if (CLANG)
        set (C_COMPILER clang)
        set (CXX_COMPILER clang++)
    else ()
        set (COMPILER_PREFIX ${ANDROID_TOOLCHAIN_MACHINE_NAME}-)
        set (C_COMPILER gcc)
        set (CXX_COMPILER g++)
    endif ()
    if (NOT CMAKE_C_COMPILER)
        set (COMPILER_PATH ${ANDROID_${CLANG}TOOLCHAIN_ROOT}/bin)   # CLANG is empty when the compiler is not Clang
        if ("$ENV{USE_CCACHE}" AND NOT CMAKE_HOST_WIN32)
            execute_process (COMMAND whereis -b ccache COMMAND grep -o \\S*lib\\S* OUTPUT_VARIABLE CCACHE_SYMLINK ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
            if (CCACHE_SYMLINK AND EXISTS ${CCACHE_SYMLINK}/${COMPILER_PREFIX}${C_COMPILER} AND EXISTS ${CCACHE_SYMLINK}/${COMPILER_PREFIX}${CXX_COMPILER})
                set (COMPILER_PATH ${CCACHE_SYMLINK})
            else ()
                # Fallback to create the ccache symlink in the build tree itself
                execute_process (COMMAND which ccache RESULT_VARIABLE EXIT_CODE OUTPUT_VARIABLE CCACHE ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
                if (EXIT_CODE EQUAL 0 AND CCACHE)
                    foreach (TOOL ${C_COMPILER} ${CXX_COMPILER})
                        execute_process (COMMAND ${CMAKE_COMMAND} -E create_symlink ${CCACHE} ${CMAKE_BINARY_DIR}/${COMPILER_PREFIX}${TOOL})
                    endforeach ()
                    set (COMPILER_PATH ${CMAKE_BINARY_DIR})
                else ()
                    message (WARNING "ccache may not have been installed on this host system. "
                        "This is required to enable ccache support for Android NDK compiler toolchain. "
                        "CMake has been configured to use the actual compiler toolchain instead of ccache. "
                        "In order to rectify this, the build tree must be regenerated after installing ccache.")
                endif ()
            endif ()
            if (NOT COMPILER_PATH STREQUAL ${ANDROID_${CLANG}TOOLCHAIN_ROOT}/bin AND NOT $ENV{PATH} MATCHES ${ANDROID_${CLANG}TOOLCHAIN_ROOT}/bin)
                message (FATAL_ERROR "The bin directory containing the compiler toolchain (${ANDROID_${CLANG}TOOLCHAIN_ROOT}/bin) has not been added in the PATH environment variable. "
                    "This is required to enable ccache support for Android NDK compiler toolchain.")
            endif ()
        endif ()
        set (CMAKE_C_COMPILER ${COMPILER_PATH}/${COMPILER_PREFIX}${C_COMPILER}${TOOL_EXT} CACHE PATH "C compiler")
        set (CMAKE_CXX_COMPILER ${COMPILER_PATH}/${COMPILER_PREFIX}${CXX_COMPILER}${TOOL_EXT} CACHE PATH "C++ compiler")
        set (CMAKE_ASM_COMPILER ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOLCHAIN_MACHINE_NAME}-gcc${TOOL_EXT} CACHE PATH "assembler")
        set (CMAKE_STRIP ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOLCHAIN_MACHINE_NAME}-strip${TOOL_EXT} CACHE PATH "strip")
        set (CMAKE_AR ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOLCHAIN_MACHINE_NAME}-gcc-ar${TOOL_EXT} CACHE PATH "archive")
        set (CMAKE_LINKER ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOLCHAIN_MACHINE_NAME}-ld${TOOL_EXT} CACHE PATH "linker")
        set (CMAKE_NM ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOLCHAIN_MACHINE_NAME}-nm${TOOL_EXT} CACHE PATH "nm")
        set (CMAKE_OBJCOPY ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOLCHAIN_MACHINE_NAME}-objcopy${TOOL_EXT} CACHE PATH "objcopy")
        set (CMAKE_OBJDUMP ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOLCHAIN_MACHINE_NAME}-objdump${TOOL_EXT} CACHE PATH "objdump")
        set (CMAKE_RANLIB ${ANDROID_TOOLCHAIN_ROOT}/bin/${ANDROID_TOOLCHAIN_MACHINE_NAME}-ranlib${TOOL_EXT} CACHE PATH "ranlib")
    endif ()

    # Compiler and linker flags
    if (NOT CMAKE_C_FLAGS OR NOT FLAGS_SIGNATURE STREQUAL "${ANDROID_ABI}-${APP_PLATFORM_LEVEL}-${ANDROID_FORCE_ARM_BUILD}-${ANDROID_STACK_PROTECTION}-${ANDROID_NO_UNDEFINED}-${ANDROID_NOEXECSTACK}-${ANDROID_RELRO}-${ANDROID_FATAL_WARNINGS}-${ANDROID_FORMAT_SECURITY}-${ANDROID_FUNCTION_LEVEL_LINKING}-${ANDROID_STL}-${ANDROID_STL_FORCE_FEATURES}-${ANDROID_RTTI}-${ANDROID_EXCEPTIONS}")
        set (CMAKE_C_FLAGS "-fsigned-char -funwind-tables -no-canonical-prefixes")
        set (CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
        set (CMAKE_C_FLAGS_DEBUG "-O0 -g -DDEBUG -D_DEBUG")
        set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--build-id -Wl,--warn-shared-textrel")
        if (CLANG)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gcc-toolchain ${ANDROID_TOOLCHAIN_ROOT} -target ${ANDROID_LLVM_TRIPLE} -Wno-invalid-command-line-argument -Wno-unused-command-line-argument")
            set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-limit-debug-info")
        endif ()
        if (ANDROID_ABI MATCHES armeabi)
            if (CLANG)
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-integrated-as")
            endif ()
            if (ANDROID_ABI MATCHES -v7a)
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv7-a")
                set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--fix-cortex-a8")
            elseif (ANDROID_ABI MATCHES -v6)
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv6")
            else ()
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv5te -mtune=xscale")
            endif ()
            if (ANDROID_ABI MATCHES -v7a|-v6)
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=softfp")
            else ()
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msoft-float")
            endif ()
            foreach (FPU neon-vfpv4 neon vfpv4 vfpv3 vfpv3-d16 vfp)
                if (ANDROID_ABI MATCHES " ${FPU}$")
                    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpu=${FPU}")
                endif ()
            endforeach ()
            if (ANDROID_FORCE_ARM_BUILD)
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -marm")
            else ()
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthumb")
            endif ()
        elseif (ANDROID_ABI MATCHES mips)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -finline-functions -fmessage-length=0")
            if (NOT CLANG)
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-inline-functions-called-once -fgcse-after-reload -frerun-cse-after-loop -frename-registers")
            endif ()
            # Clang outputs mips32r2 by default, switch to mips32r1
            # TODO: Remove this once mipsel-linux-android target is changed in clang
            if (ANDROID_ABI STREQUAL mips)
                set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mips32")
            endif ()
        endif ()
        # The ld.bfd needs help to find the location of the rooted shared libraries while ld.gold doesn't
        # TODO: Remove this once gold linker is the default for all the archs or when it is not possible to switch to use ld.bfd
        set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath-link,\"${CMAKE_SYSROOT}/usr/lib\":\"${CMAKE_SYSROOT}/lib\":\"${STL_LIBRARY_DIR}\"")
        option (ANDROID_STACK_PROTECTION "Force the addition of a stack canary that checks for stack smashing")
        if (ANDROID_STACK_PROTECTION)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-strong")
        endif ()
        option (ANDROID_NO_UNDEFINED "Ensure that a binary doesn't reference undefined symbols" TRUE)
        if (ANDROID_NO_UNDEFINED)
            set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
        endif ()
        option (ANDROID_NOEXECSTACK "Enforce the NX (no execute) security feature in the generated machine code" TRUE)
        if (ANDROID_NOEXECSTACK)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wa,--noexecstack")
            set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,noexecstack")
        endif ()
        option (ANDROID_RELRO "Mark certain regions of the resulting executable or shared library as being read-only" TRUE)
        if (ANDROID_RELRO)
            set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,relro -Wl,-z,now")
        endif ()
        option (ANDROID_FATAL_WARNINGS "Treat all linker warnings as errors" TRUE)
        if (ANDROID_FATAL_WARNINGS)
            set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--fatal-warnings")
        endif ()
        option (ANDROID_FORMAT_SECURITY "Provide compiler protection against format string vulnerabilities" TRUE)
        if (ANDROID_FORMAT_SECURITY)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wformat -Werror=format-security")
        endif ()
        option (ANDROID_FUNCTION_LEVEL_LINKING "Split data/function sections and garbage collect unused sections at link time" TRUE)
        if (ANDROID_FUNCTION_LEVEL_LINKING)
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdata-sections -ffunction-sections")
            set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections")
        endif ()
        # RelWithDebInfo and MinSizeRel build configurations are just derivative of Release build configuration
        string (REPLACE -O3 "-O2 -g" CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE}")
        string (REPLACE -O3 -Os CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_RELEASE}")
        foreach (VAR _FLAGS _FLAGS_RELEASE _FLAGS_DEBUG _FLAGS_RELWITHDEBINFO _FLAGS_MINSIZEREL)
            set (CMAKE_C${VAR} ${CMAKE_C${VAR}} CACHE INTERNAL "C Compiler flags")
            set (CMAKE_CXX${VAR} ${CMAKE_C${VAR}} CACHE INTERNAL "CXX Compiler flags")
        endforeach ()
        # Only CXX compiler can accept these flags
        if (ANDROID_RTTI)
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti" CACHE INTERNAL "CXX Compiler flags")
        else ()
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti" CACHE INTERNAL "CXX Compiler flags")
        endif ()
        if (ANDROID_EXCEPTIONS)
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions" CACHE INTERNAL "CXX Compiler flags")
        else ()
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions" CACHE INTERNAL "CXX Compiler flags")
        endif ()
        set (CMAKE_EXE_LINKER_FLAGS -Wl,-z,nocopyreloc)
        if (NOT APP_PLATFORM_LEVEL LESS 16)
            set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pie")
        endif ()
        set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS}" CACHE INTERNAL "EXE linker flags")
        set (CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} CACHE INTERNAL "SHARED linker flags")
        set (CMAKE_MODULE_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} CACHE INTERNAL "MODULE linker flags")
        set (FLAGS_SIGNATURE "${ANDROID_ABI}-${APP_PLATFORM_LEVEL}-${ANDROID_FORCE_ARM_BUILD}-${ANDROID_STACK_PROTECTION}-${ANDROID_NO_UNDEFINED}-${ANDROID_NOEXECSTACK}-${ANDROID_RELRO}-${ANDROID_FATAL_WARNINGS}-${ANDROID_FORMAT_SECURITY}-${ANDROID_FUNCTION_LEVEL_LINKING}-${ANDROID_STL}-${ANDROID_STL_FORCE_FEATURES}-${ANDROID_RTTI}-${ANDROID_EXCEPTIONS}" CACHE INTERNAL "Signature when the compiler/linker flags are last cached")
    endif ()
    # Workaround try_compile() limitation
    set (ENV{CMAKE_SYSROOT} ${CMAKE_SYSROOT})
    set (ENV{STL_INCLUDE_DIRS} "${STL_INCLUDE_DIRS}")   # Stringify to keep the list together
    set (ENV{STL_LINKER_FLAGS} "${STL_LINKER_FLAGS}")
else ()
    set (CMAKE_SYSROOT $ENV{CMAKE_SYSROOT})
    set (STL_INCLUDE_DIRS $ENV{STL_INCLUDE_DIRS})
    set (STL_LINKER_FLAGS $ENV{STL_LINKER_FLAGS})
endif ()
include_directories (SYSTEM ${STL_INCLUDE_DIRS})
# Cannot use link_directories() and link_libraries() commands here because CMake will emit the linker flags in an undesirable order
# Workaround the problem by injecting the linker flags the last explicitly in the CMake build rules
# This is a hack as it relies on internal implementation, i.e. the hard-coded rules must be kept in sync manually with CMake's Modules/CMakeCXXInformation.cmake file
set (CMAKE_CXX_CREATE_SHARED_LIBRARY "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES> ${STL_LINKER_FLAGS}")
set (CMAKE_CXX_CREATE_SHARED_MODULE "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES> ${STL_LINKER_FLAGS}")
set (CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES> ${STL_LINKER_FLAGS}")

# Only search libraries and headers in sysroot
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Use response files on Windows host to avoid failure in the linking phase with too long command line
if (CMAKE_HOST_WIN32)
    set (CMAKE_C_USE_RESPONSE_FILE_FOR_OBJECTS 1)
    set (CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 1)
endif ()
