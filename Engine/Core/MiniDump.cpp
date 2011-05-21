//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"

#ifdef ENABLE_MINIDUMPS

#include "ProcessUtils.h"

#include <cstdio>
#include <list>
#include <io.h>
#include <fcntl.h>
#include <time.h>
#include <Windows.h>
#include <DbgHelp.h>

// Enable SHGetSpecialFolderPath on MinGW
#ifndef _MSC_VER
#define _WIN32_IE 0x0400
#endif
#include <ShlObj.h>

static bool miniDumpWritten = false;

int WriteMiniDump(const char* applicationName, void* exceptionPointers)
{
    // In case of recursive or repeating exceptions, only write the dump once
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
    dateTimeStr.ReplaceInPlace("\n", "");
    dateTimeStr.ReplaceInPlace(":", "");
    dateTimeStr.ReplaceInPlace("/", "");
    dateTimeStr.ReplaceInPlace(' ', '_');
    
    char pathName[MAX_PATH];
    pathName[0] = 0;
    SHGetSpecialFolderPath(0, pathName, CSIDL_PERSONAL, 0);
    String applicationNameStr(applicationName);
    String miniDumpDir = String(pathName) + "\\" + applicationNameStr;
    String miniDumpName = miniDumpDir + "\\" + applicationNameStr + "_" + dateTimeStr + ".dmp";
    
    CreateDirectory(miniDumpDir.CString(), 0);
    HANDLE file = CreateFile(miniDumpName.CString(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ,
        0, CREATE_ALWAYS, 0, 0);
    
    BOOL success = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file, MiniDumpWithDataSegs, &info, 0, 0);
    CloseHandle(file);
    
    if (success)
        ErrorDialog(applicationName, String("An unexpected error occurred. A minidump was generated to " + miniDumpName).CString());
    else
        ErrorDialog(applicationName, "An unexpected error occurred. Could not write minidump.");
    
    return EXCEPTION_EXECUTE_HANDLER;
}
#endif
