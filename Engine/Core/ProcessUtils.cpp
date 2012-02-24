//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <libcpuid.h>

#ifdef WIN32
#include <windows.h>
#include <io.h>
#else
#include <unistd.h>
#endif

#ifdef _MSC_VER
#include <float.h>
#else
// From http://stereopsis.com/FPU.html

#define FPU_CW_PREC_MASK        0x0300
#define FPU_CW_PREC_SINGLE      0x0000
#define FPU_CW_PREC_DOUBLE      0x0200
#define FPU_CW_PREC_EXTENDED    0x0300
#define FPU_CW_ROUND_MASK       0x0c00
#define FPU_CW_ROUND_NEAR       0x0000
#define FPU_CW_ROUND_DOWN       0x0400
#define FPU_CW_ROUND_UP         0x0800
#define FPU_CW_ROUND_CHOP       0x0c00

inline unsigned GetFPUState()
{
    unsigned control = 0;
    __asm__ __volatile__ ("fnstcw %0" : "=m" (control));
    return control;
}

inline void SetFPUState(unsigned control)
{
    __asm__ __volatile__ ("fldcw %0" : : "m" (control));
}
#endif

#include "DebugNew.h"

#ifdef WIN32
static bool consoleOpened = false;
#endif
static String currentLine;
static Vector<String> arguments;
static Mutex staticMutex;

void GetCPUData(struct cpu_id_t* data)
{
    if (cpu_identify(0, data) < 0)
    {
        data->num_logical_cpus = 1;
        data->num_cores = 1;
    }
}

void InitFPU()
{
    // Make sure FPU is in round-to-nearest, single precision mode
    // This is needed for ODE to behave predictably in float mode
    #ifdef _MSC_VER
    _controlfp(_RC_NEAR | _PC_24, _MCW_RC | _MCW_PC);
    #else
    unsigned control = GetFPUState();
    control &= ~(FPU_CW_PREC_MASK | FPU_CW_ROUND_MASK);
    control |= (FPU_CW_PREC_SINGLE | FPU_CW_ROUND_NEAR);
    SetFPUState(control);
    #endif
}

void ErrorDialog(const String& title, const String& message)
{
    #ifdef WIN32
    MessageBoxW(0, WString(message).CString(), WString(title).CString(), 0);
    #else
    printf("%s\n", message.CString());
    #endif
}

void ErrorExit(const String& message, int exitCode)
{
    printf("%s", message.CString());
    exit(exitCode);
}

void OpenConsoleWindow()
{
    #ifdef WIN32
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
    #endif
}

void PrintLine(const String& str)
{
    printf("%s\n", str.CString());
}

void PrintLine(const char* str)
{
    printf("%s\n", str);
}

const Vector<String>& ParseArguments(const char* cmdLine)
{
    arguments.Clear();
    
    if (!cmdLine)
        return arguments;
    
    String cmdStr(cmdLine);
    unsigned cmdStart = 0, cmdEnd = 0;
    bool inCmd = false;
    bool inQuote = false;
    
    for (unsigned i = 0; i < cmdStr.Length(); ++i)
    {
        if (cmdStr[i] == '\"')
            inQuote = !inQuote;
        if (cmdStr[i] == ' ' && !inQuote)
        {
            if (inCmd)
            {
                inCmd = false;
                cmdEnd = i;
                arguments.Push(cmdStr.Substring(cmdStart, cmdEnd - cmdStart));
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
        cmdEnd = cmdStr.Length();
        arguments.Push(cmdStr.Substring(cmdStart, cmdEnd - cmdStart));
    }
    
    return arguments;
}

const Vector<String>& GetArguments()
{
    return arguments;
}

String GetConsoleInput()
{
    String ret;
    
    #ifdef WIN32
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
        if (record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown)
        {
            char c = record.Event.KeyEvent.uChar.AsciiChar;
            if (c)
            {
                if (c == '\b')
                {
                    printf("\b \b");
                    int length = currentLine.Length();
                    if (length)
                        currentLine.Resize(length - 1);
                }
                else if (c == '\r')
                {
                    printf("\n");
                    ret = currentLine;
                    currentLine.Clear();
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
    #else
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    for (;;)
    {
        int ch = fgetc(stdin);
        if (ch >= 0 && ch != '\n')
            ret += (char)ch;
        else
            break;
    }
    #endif
    
    return ret;
}

unsigned GetNumPhysicalCPUs()
{
    struct cpu_id_t data;
    GetCPUData(&data);
    return data.num_cores;
}

unsigned GetNumLogicalCPUs()
{
    struct cpu_id_t data;
    GetCPUData(&data);
    return data.num_logical_cpus;
}

Mutex& GetStaticMutex()
{
    return staticMutex;
}
