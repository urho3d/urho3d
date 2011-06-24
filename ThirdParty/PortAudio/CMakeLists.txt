# Define target name
set (TARGET_NAME PortAudio)

# Common source files
set (SOURCE_FILES
    src/common/pa_allocation.c
    src/common/pa_allocation.h
    src/common/pa_converters.c
    src/common/pa_converters.h
    src/common/pa_cpuload.c
    src/common/pa_cpuload.h
    src/common/pa_debugprint.c
    src/common/pa_debugprint.h
    src/common/pa_dither.c
    src/common/pa_dither.h
    src/common/pa_endianness.h
    src/common/pa_front.c
    src/common/pa_hostapi.h
    src/common/pa_memorybarrier.h
    src/common/pa_process.c
    src/common/pa_process.h
    src/common/pa_ringbuffer.c
    src/common/pa_ringbuffer.h
    src/common/pa_skeleton.c
    src/common/pa_stream.c
    src/common/pa_stream.h
    src/common/pa_trace.c
    src/common/pa_trace.h
    src/common/pa_types.h
    src/common/pa_util.h
)

include_directories (include src/common)

# OS specific source files
if (WIN32)
    add_definitions (-DPA_NO_ASIO -DPA_NO_WASAPI -DPA_NO_WDMKS -DPA_NO_WMME)
    set (SOURCE_FILES
        ${SOURCE_FILES}
        src/os/win/pa_win_hostapis.c
        src/os/win/pa_win_util.c
        src/os/win/pa_win_waveformat.c
        src/os/win/pa_win_wdmks_utils.c
        src/os/win/pa_win_wdmks_utils.h
        src/os/win/pa_x86_plain_converters.c
        src/os/win/pa_x86_plain_converters.h
        src/hostapi/dsound/pa_win_ds.c
        src/hostapi/dsound/pa_win_ds_dynlink.c
        src/hostapi/dsound/pa_win_ds_dynlink.h
    )
    include_directories (src/os/win)
elseif (UNIX)
    set (SOURCE_FILES
        ${SOURCE_FILES}
        src/os/unix/pa_unix_hostapis.c
        src/os/unix/pa_unix_util.c
        src/os/unix/pa_unix_util.h
    )
    
    include_directories (src/os/unix)
    
    if (APPLE)
        add_definitions (-DPA_USE_COREAUDIO)
        set (SOURCE_FILES
            ${SOURCE_FILES}
            src/hostapi/coreaudio/pa_mac_core.c
            src/hostapi/coreaudio/pa_mac_core_blocking.c
            src/hostapi/coreaudio/pa_mac_core_blocking.h
            src/hostapi/coreaudio/pa_mac_core_internal.h
            src/hostapi/coreaudio/pa_mac_core_utilities.c
            src/hostapi/coreaudio/pa_mac_core_utilities.h
        )
    else ()
        include (CheckIncludeFiles)
    
        add_definitions (-DPA_USE_ALSA -DPA_USE_OSS)
        check_include_files (sys/soundcard.h HAVE_SYS_SOUNDCARD_H)
        check_include_files (linux/soundcard.h HAVE_LINUX_SOUNDCARD_H)
        check_include_files (machine/soundcard.h HAVE_MACHINE_SOUNDCARD_H)
        if (HAVE_SYS_SOUNDCARD_H)
            add_definitions (-DHAVE_SYS_SOUNDCARD_H)
        endif ()
        if (HAVE_LINUX_SOUNDCARD_H)
            add_definitions (-DHAVE_LINUX_SOUNDCARD_H)
        endif ()
        if (HAVE_MACHINE_SOUNDCARD_H)
            add_definitions (-DHAVE_MACHINE_SOUNDCARD_H)
        endif ()
        
        set (SOURCE_FILES
            ${SOURCE_FILES}
            src/hostapi/alsa/pa_linux_alsa.c
            src/hostapi/oss/pa_unix_oss.c
            src/hostapi/oss/recplay.c
        )
   endif ()
endif ()

add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})

if (APPLE)
    find_library (AUDIOTOOLBOX_FW AudioToolBox)
    find_library (AUDIOUNIT_FW AudioUnit)
    find_library (COREAUDIO_FW CoreAudio)
    find_library (CORESERVICES_FW CoreServices)
    target_link_libraries (${TARGET_NAME} ${AUDIOTOOLBOX_FW} ${AUDIOUNIT_FW} ${COREAUDIO_FW} ${CORESERVICES_FW})    
elseif (UNIX)
    target_link_libraries (${TARGET_NAME} rt asound pthread)        
endif()








