//
// Copyright (c) 2008-2022 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#if defined(_MSC_VER)

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
