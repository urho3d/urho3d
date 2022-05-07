// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#if defined(_MSC_VER) && defined(URHO3D_MINIDUMPS)

#include "../Precompiled.h"

#include "../Core/MiniDump.h"
#include "../Core/ProcessUtils.h"

#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include <time.h>
#include <windows.h>
#include <dbghelp.h>

namespace Urho3D
{

int WriteMiniDump(const char* applicationName, void* exceptionPointers)
{
    static bool miniDumpWritten = false;

    // In case of recursive or repeating exceptions, only write the dump once
    /// \todo This function should not allocate any dynamic memory
    if (miniDumpWritten)
        return EXCEPTION_EXECUTE_HANDLER;

    miniDumpWritten = true;

    MINIDUMP_EXCEPTION_INFORMATION info;
    info.ThreadId = GetCurrentThreadId();
    info.ExceptionPointers = (EXCEPTION_POINTERS*)exceptionPointers;
    info.ClientPointers = TRUE;

    static time_t sysTime;
    time(&sysTime);
    const char* dateTime = ctime(&sysTime);
    String dateTimeStr = String(dateTime);
    dateTimeStr.Replace("\n", "");
    dateTimeStr.Replace(":", "");
    dateTimeStr.Replace("/", "");
    dateTimeStr.Replace(' ', '_');

    String miniDumpDir = GetMiniDumpDir();
    String miniDumpName = miniDumpDir + String(applicationName) + "_" + dateTimeStr + ".dmp";

    CreateDirectoryW(WString(miniDumpDir).CString(), nullptr);
    HANDLE file = CreateFileW(WString(miniDumpName).CString(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ,
        nullptr, CREATE_ALWAYS, 0, nullptr);

    BOOL success = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file, MiniDumpWithDataSegs, &info, nullptr, nullptr);
    CloseHandle(file);

    if (success)
        ErrorDialog(applicationName, "An unexpected error occurred. A minidump was generated to " + miniDumpName);
    else
        ErrorDialog(applicationName, "An unexpected error occurred. Could not write minidump.");

    return EXCEPTION_EXECUTE_HANDLER;
}

}

#endif
