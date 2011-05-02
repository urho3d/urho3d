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
#include "Mutex.h"
#include "ProcessUtils.h"
#include "StringUtils.h"

#include <cstdio>
#include <list>
#include <io.h>
#include <fcntl.h>
#include <time.h>
#include <windows.h>

// Enable SHGetSpecialFolderPath on MinGW
#ifndef _MSC_VER
#define _WIN32_IE 0x0400
#endif
#include <shlobj.h>

#ifdef ENABLE_MINIDUMPS
#include <dbghelp.h>
#endif

#include "DebugNew.h"

static bool miniDumpWritten = false;
static bool consoleOpened = false;
static std::string currentLine;
static std::vector<std::string> arguments;
static Mutex staticMutex;

void ErrorDialog(const char* title, const char* message)
{
    MessageBox(0, message, title, 0);
}

void OpenConsoleWindow()
{
    if (consoleOpened)
        return;
    
    AllocConsole();
    
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long)hOut, _O_TEXT);
    FILE* outFile = _fdopen(hCrt, "w");
    setvbuf(outFile, NULL, _IONBF, 1);
    *stdout = *outFile;
    
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long)hIn, _O_TEXT);
    FILE* inFile = _fdopen(hCrt, "r");
    setvbuf(inFile, NULL, _IONBF, 128);
    *stdin = *inFile;
    
    consoleOpened = true;
}

Mutex& GetStaticMutex()
{
    return staticMutex;
}

const std::vector<std::string>& ParseArguments(const char* cmdLine)
{
    arguments.clear();
    
    if (!cmdLine)
        return arguments;
    
    std::string cmdStr(cmdLine);
    unsigned cmdStart, cmdEnd;
    bool inCmd = false;
    bool inQuote = false;
    
    for (unsigned i = 0; i < cmdStr.length(); ++i)
    {
        if (cmdStr[i] == '\"')
            inQuote = !inQuote;
        if ((cmdStr[i] == ' ') && (!inQuote))
        {
            if (inCmd)
            {
                inCmd = false;
                cmdEnd = i;
                arguments.push_back(cmdStr.substr(cmdStart, cmdEnd - cmdStart));
            }
        }
        else
        {
            if (!inCmd)
            {
                inCmd = true;
                cmdStart = i;
            }
        }
    }
    if (inCmd)
    {
        cmdEnd = cmdStr.length();
        arguments.push_back(cmdStr.substr(cmdStart, cmdEnd - cmdStart));
    }
    
    return arguments;
}

const std::vector<std::string>& GetArguments()
{
    return arguments;
}

std::string GetConsoleInput()
{
    std::string ret;
    
    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
    if (input == INVALID_HANDLE_VALUE)
        return ret;
    
    // Use char-based input
    SetConsoleMode(input, ENABLE_PROCESSED_INPUT);
    
    INPUT_RECORD record;
    DWORD events = 0;
    DWORD readEvents = 0;
    
    if (!GetNumberOfConsoleInputEvents(input, &events))
        return ret;
    
    while (events--)
    {
        ReadConsoleInput(input, &record, 1, &readEvents);
        if ((record.EventType == KEY_EVENT) && (record.Event.KeyEvent.bKeyDown))
        {
            char c = record.Event.KeyEvent.uChar.AsciiChar;
            if (c)
            {
                if (c == '\b')
                {
                    printf("\b \b");
                    int length = currentLine.length();
                    if (length)
                        currentLine.resize(length - 1);
                }
                else if (c == '\r')
                {
                    printf("\n");
                    ret = currentLine;
                    currentLine.clear();
                    return ret;
                }
                else
                {
                    // We have disabled echo, so echo manually
                    printf("%c", c);
                    currentLine += c;
                }
            }
        }
    }
    
    return ret;
}

unsigned GetNumCPUCores()
{
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return info.dwNumberOfProcessors;
}

#ifdef ENABLE_MINIDUMPS
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
    std::string dateTimeStr = std::string(dateTime);
    ReplaceInPlace(dateTimeStr, "\n", "");
    ReplaceInPlace(dateTimeStr, ":", "");
    ReplaceInPlace(dateTimeStr, "/", "");
    ReplaceInPlace(dateTimeStr, ' ', '_');
    
    char pathName[MAX_PATH];
    pathName[0] = 0;
    SHGetSpecialFolderPath(0, pathName, CSIDL_PERSONAL, 0);
    std::string applicationNameStr(applicationName);
    std::string miniDumpDir = std::string(pathName) + "\\" + applicationNameStr;
    std::string miniDumpName = miniDumpDir + "\\" + applicationNameStr + "_" + dateTimeStr + ".dmp";
    
    CreateDirectory(miniDumpDir.c_str(), 0);
    HANDLE file = CreateFile(miniDumpName.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ,
        0, CREATE_ALWAYS, 0, 0);
    
    BOOL success = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file, MiniDumpWithDataSegs, &info, 0, 0);
    CloseHandle(file);
    
    if (success)
        ErrorDialog(applicationName, std::string("An unexpected error occurred. A minidump was generated to " + miniDumpName).c_str());
    else
        ErrorDialog(applicationName, "An unexpected error occurred. Could not write minidump.");
    
    return EXCEPTION_EXECUTE_HANDLER;
}
#endif
