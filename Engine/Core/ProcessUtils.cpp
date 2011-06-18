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

#include <cstdio>
#include <list>
#include <io.h>
#include <fcntl.h>
#include <time.h>

#ifdef WIN32
#include <Windows.h>
#endif

#ifdef USE_SDL
#include <SDL.h>
#endif

#include "DebugNew.h"

static bool consoleOpened = false;
static String currentLine;
static Vector<String> arguments;
static Mutex staticMutex;

void ErrorDialog(const char* title, const char* message)
{
    #ifdef WIN32
    MessageBox(0, message, title, 0);
    #else
    printf("%s", message);
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

Mutex& GetStaticMutex()
{
    return staticMutex;
}

const Vector<String>& ParseArguments(const char* cmdLine)
{
    arguments.Clear();
    
    if (!cmdLine)
        return arguments;
    
    String cmdStr(cmdLine);
    unsigned cmdStart, cmdEnd;
    bool inCmd = false;
    bool inQuote = false;
    
    for (unsigned i = 0; i < cmdStr.Length(); ++i)
    {
        if (cmdStr[i] == '\"')
            inQuote = !inQuote;
        if ((cmdStr[i] == ' ') && (!inQuote))
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
        if ((record.EventType == KEY_EVENT) && (record.Event.KeyEvent.bKeyDown))
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
        if (ch >= 0)
            ret += (char)ch;
        else
            break;
    }
    #endif
    
    return ret;
}

unsigned GetNumCPUCores()
{
    #ifndef USE_SDL
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return info.dwNumberOfProcessors;
    #else
    return SDL_GetCPUCount();
    #endif
}
