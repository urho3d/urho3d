//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/ProcessUtils.h"
#include "../Core/StringUtils.h"
#include "../IO/FileSystem.h"

#include <cstdio>
#include <fcntl.h>

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#if defined(IOS)
#include <mach/mach_host.h>
#elif defined(TVOS)
extern "C" unsigned SDL_TVOS_GetActiveProcessorCount();
#elif !defined(__linux__) && !defined(__EMSCRIPTEN__)
#include <LibCpuId/libcpuid.h>
#endif

#if defined(_WIN32)
#include <windows.h>
#include <io.h>
#if defined(_MSC_VER)
#include <float.h>
#include <Lmcons.h> // For UNLEN.
#elif defined(__MINGW32__)
#include <lmcons.h> // For UNLEN. Apparently MSVC defines "<Lmcons.h>" (with an upperscore 'L' but MinGW uses an underscore 'l').
#include <ntdef.h>
#endif
#elif defined(__linux__) && !defined(__ANDROID__)
#include <pwd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#elif defined(__APPLE__)
#include <sys/sysctl.h>
#include <SystemConfiguration/SystemConfiguration.h> // For the detection functions inside GetLoginName().
#endif
#ifndef _WIN32
#include <unistd.h>
#endif

#if defined(__EMSCRIPTEN__) && defined(__EMSCRIPTEN_PTHREADS__)
#include <emscripten/threading.h>
#endif

#if defined(__i386__)
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

#ifndef MINI_URHO
#include <SDL/SDL.h>
#endif

#include "../DebugNew.h"

namespace Urho3D
{

#ifdef _WIN32
static bool consoleOpened = false;
#endif
static String currentLine;
static Vector<String> arguments;
static String miniDumpDir;

#if defined(IOS)
static void GetCPUData(host_basic_info_data_t* data)
{
    mach_msg_type_number_t infoCount;
    infoCount = HOST_BASIC_INFO_COUNT;
    host_info(mach_host_self(), HOST_BASIC_INFO, (host_info_t)data, &infoCount);
}
#elif defined(__linux__)
struct CpuCoreCount
{
    unsigned numPhysicalCores_;
    unsigned numLogicalCores_;
};

// This function is used by all the target triplets with Linux as the OS, such as Android, RPI, desktop Linux, etc
static void GetCPUData(struct CpuCoreCount* data)
{
    // Sanity check
    assert(data);
    // At least return 1 core
    data->numPhysicalCores_ = data->numLogicalCores_ = 1;

    FILE* fp;
    int res;
    unsigned i, j;

    fp = fopen("/sys/devices/system/cpu/present", "r");
    if (fp)
    {
        res = fscanf(fp, "%d-%d", &i, &j);                          // NOLINT(cert-err34-c)
        fclose(fp);

        if (res == 2 && i == 0)
        {
            data->numPhysicalCores_ = data->numLogicalCores_ = j + 1;

            fp = fopen("/sys/devices/system/cpu/cpu0/topology/thread_siblings_list", "r");
            if (fp)
            {
                res = fscanf(fp, "%d,%d,%d,%d", &i, &j, &i, &j);    // NOLINT(cert-err34-c)
                fclose(fp);

                // Having sibling thread(s) indicates the CPU is using HT/SMT technology
                if (res > 1)
                    data->numPhysicalCores_ /= res;
            }
        }
    }
}

#elif !defined(__EMSCRIPTEN__) && !defined(TVOS)
static void GetCPUData(struct cpu_id_t* data)
{
    if (cpu_identify(nullptr, data) < 0)
    {
        data->num_logical_cpus = 1;
        data->num_cores = 1;
    }
}
#endif

void InitFPU()
{
    // Make sure FPU is in round-to-nearest, single precision mode
    // This ensures Direct3D and OpenGL behave similarly, and all threads behave similarly
#if defined(_MSC_VER) && defined(_M_IX86)
    _controlfp(_RC_NEAR | _PC_24, _MCW_RC | _MCW_PC);
#elif defined(__i386__)
    unsigned control = GetFPUState();
    control &= ~(FPU_CW_PREC_MASK | FPU_CW_ROUND_MASK);
    control |= (FPU_CW_PREC_SINGLE | FPU_CW_ROUND_NEAR);
    SetFPUState(control);
#endif
}

void ErrorDialog(const String& title, const String& message)
{
#ifndef MINI_URHO
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.CString(), message.CString(), nullptr);
#endif
}

void ErrorExit(const String& message, int exitCode)
{
    if (!message.Empty())
        PrintLine(message, true);

    exit(exitCode);
}

void OpenConsoleWindow()
{
#ifdef _WIN32
    if (consoleOpened)
        return;

    AllocConsole();

    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);

    consoleOpened = true;
#endif
}

void PrintUnicode(const String& str, bool error)
{
#if !defined(__ANDROID__) && !defined(IOS) && !defined(TVOS)
#ifdef _WIN32
    // If the output stream has been redirected, use fprintf instead of WriteConsoleW,
    // though it means that proper Unicode output will not work
    FILE* out = error ? stderr : stdout;
    if (!_isatty(_fileno(out)))
        fprintf(out, "%s", str.CString());
    else
    {
        HANDLE stream = GetStdHandle(error ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE);
        if (stream == INVALID_HANDLE_VALUE)
            return;
        WString strW(str);
        DWORD charsWritten;
        WriteConsoleW(stream, strW.CString(), strW.Length(), &charsWritten, nullptr);
    }
#else
    fprintf(error ? stderr : stdout, "%s", str.CString());
#endif
#endif
}

void PrintUnicodeLine(const String& str, bool error)
{
    PrintUnicode(str + "\n", error);
}

void PrintLine(const String& str, bool error)
{
    PrintLine(str.CString(), error);
}

void PrintLine(const char* str, bool error)
{
#if !defined(__ANDROID__) && !defined(IOS) && !defined(TVOS)
    fprintf(error ? stderr : stdout, "%s\n", str);
#endif
}

const Vector<String>& ParseArguments(const String& cmdLine, bool skipFirstArgument)
{
    arguments.Clear();

    unsigned cmdStart = 0, cmdEnd = 0;
    bool inCmd = false;
    bool inQuote = false;

    for (unsigned i = 0; i < cmdLine.Length(); ++i)
    {
        if (cmdLine[i] == '\"')
            inQuote = !inQuote;
        if (cmdLine[i] == ' ' && !inQuote)
        {
            if (inCmd)
            {
                inCmd = false;
                cmdEnd = i;
                // Do not store the first argument (executable name)
                if (!skipFirstArgument)
                    arguments.Push(cmdLine.Substring(cmdStart, cmdEnd - cmdStart));
                skipFirstArgument = false;
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
        cmdEnd = cmdLine.Length();
        if (!skipFirstArgument)
            arguments.Push(cmdLine.Substring(cmdStart, cmdEnd - cmdStart));
    }

    // Strip double quotes from the arguments
    for (unsigned i = 0; i < arguments.Size(); ++i)
        arguments[i].Replace("\"", "");

    return arguments;
}

const Vector<String>& ParseArguments(const char* cmdLine)
{
    return ParseArguments(String(cmdLine));
}

const Vector<String>& ParseArguments(const WString& cmdLine)
{
    return ParseArguments(String(cmdLine));
}

const Vector<String>& ParseArguments(const wchar_t* cmdLine)
{
    return ParseArguments(String(cmdLine));
}

const Vector<String>& ParseArguments(int argc, char** argv)
{
    String cmdLine;

    for (int i = 0; i < argc; ++i)
        cmdLine.AppendWithFormat("\"%s\" ", (const char*)argv[i]);

    return ParseArguments(cmdLine);
}

const Vector<String>& GetArguments()
{
    return arguments;
}

String GetConsoleInput()
{
    String ret;
#ifdef URHO3D_TESTING
    // When we are running automated tests, reading the console may block. Just return empty in that case
    return ret;
#else
#ifdef _WIN32
    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    if (input == INVALID_HANDLE_VALUE || output == INVALID_HANDLE_VALUE)
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
        ReadConsoleInputW(input, &record, 1, &readEvents);
        if (record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown)
        {
            unsigned c = record.Event.KeyEvent.uChar.UnicodeChar;
            if (c)
            {
                if (c == '\b')
                {
                    PrintUnicode("\b \b");
                    int length = currentLine.LengthUTF8();
                    if (length)
                        currentLine = currentLine.SubstringUTF8(0, length - 1);
                }
                else if (c == '\r')
                {
                    PrintUnicode("\n");
                    ret = currentLine;
                    currentLine.Clear();
                    return ret;
                }
                else
                {
                    // We have disabled echo, so echo manually
                    wchar_t out = c;
                    DWORD charsWritten;
                    WriteConsoleW(output, &out, 1, &charsWritten, nullptr);
                    currentLine.AppendUTF8(c);
                }
            }
        }
    }
#elif !defined(__ANDROID__) && !defined(IOS) && !defined(TVOS)
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
#endif
}

String GetPlatform()
{
#if defined(__ANDROID__)
    return "Android";
#elif defined(IOS)
    return "iOS";
#elif defined(TVOS)
    return "tvOS";
#elif defined(__APPLE__)
    return "macOS";
#elif defined(_WIN32)
    return "Windows";
#elif defined(RPI)
    return "Raspberry Pi";
#elif defined(__EMSCRIPTEN__)
    return "Web";
#elif defined(__linux__)
    return "Linux";
#else
    return "(?)";
#endif
}

unsigned GetNumPhysicalCPUs()
{
#if defined(IOS)
    host_basic_info_data_t data;
    GetCPUData(&data);
#if defined(TARGET_OS_SIMULATOR)
    // Hardcoded to dual-core on simulator mode even if the host has more
    return Min(2, data.physical_cpu);
#else
    return data.physical_cpu;
#endif
#elif defined(TVOS)
#if defined(TARGET_OS_SIMULATOR)
    return Min(2, SDL_TVOS_GetActiveProcessorCount());
#else
    return SDL_TVOS_GetActiveProcessorCount();
#endif
#elif defined(__linux__)
    struct CpuCoreCount data{};
    GetCPUData(&data);
    return data.numPhysicalCores_;
#elif defined(__EMSCRIPTEN__)
#ifdef __EMSCRIPTEN_PTHREADS__
    return emscripten_num_logical_cores();
#else
    return 1; // Targeting a single-threaded Emscripten build.
#endif
#else
    struct cpu_id_t data;
    GetCPUData(&data);
    return (unsigned)data.num_cores;
#endif
}

unsigned GetNumLogicalCPUs()
{
#if defined(IOS)
    host_basic_info_data_t data;
    GetCPUData(&data);
#if defined(TARGET_OS_SIMULATOR)
    return Min(2, data.logical_cpu);
#else
    return data.logical_cpu;
#endif
#elif defined(TVOS)
#if defined(TARGET_OS_SIMULATOR)
    return Min(2, SDL_TVOS_GetActiveProcessorCount());
#else
    return SDL_TVOS_GetActiveProcessorCount();
#endif
#elif defined(__linux__)
    struct CpuCoreCount data{};
    GetCPUData(&data);
    return data.numLogicalCores_;
#elif defined(__EMSCRIPTEN__)
#ifdef __EMSCRIPTEN_PTHREADS__
    return emscripten_num_logical_cores();
#else
    return 1; // Targeting a single-threaded Emscripten build.
#endif
#else
    struct cpu_id_t data;
    GetCPUData(&data);
    return (unsigned)data.num_logical_cpus;
#endif
}

void SetMiniDumpDir(const String& pathName)
{
    miniDumpDir = AddTrailingSlash(pathName);
}

String GetMiniDumpDir()
{
#ifndef MINI_URHO
    if (miniDumpDir.Empty())
    {
        char* pathName = SDL_GetPrefPath("urho3d", "crashdumps");
        if (pathName)
        {
            String ret(pathName);
            SDL_free(pathName);
            return ret;
        }
    }
#endif

    return miniDumpDir;
}

unsigned long long GetTotalMemory()
{
#if defined(__linux__) && !defined(__ANDROID__)
    struct sysinfo s{};
    if (sysinfo(&s) != -1)
        return s.totalram;
#elif defined(_WIN32)
    MEMORYSTATUSEX state;
    state.dwLength = sizeof(state);
    if (GlobalMemoryStatusEx(&state))
        return state.ullTotalPhys;
#elif defined(__APPLE__)
    unsigned long long memSize;
    size_t len = sizeof(memSize);
    int mib[2];
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    sysctl(mib, 2, &memSize, &len, NULL, 0);
    return memSize;
#endif
    return 0ull;
}

String GetLoginName()
{
#if defined(__linux__) && !defined(__ANDROID__)
    struct passwd *p = getpwuid(getuid());
    if (p != nullptr)
        return p->pw_name;
#elif defined(_WIN32)
    char name[UNLEN + 1];
    DWORD len = UNLEN + 1;
    if (GetUserName(name, &len))
        return name;
#elif defined(__APPLE__) && !defined(IOS) && !defined(TVOS)
    SCDynamicStoreRef s = SCDynamicStoreCreate(NULL, CFSTR("GetConsoleUser"), NULL, NULL);
    if (s != NULL)
    {
        uid_t u;
        CFStringRef n = SCDynamicStoreCopyConsoleUser(s, &u, NULL);
        CFRelease(s);
        if (n != NULL)
        {
            char name[256];
            Boolean b = CFStringGetCString(n, name, 256, kCFStringEncodingUTF8);
            CFRelease(n);

            if (b == true)
                return name;
        }
    }
#endif
    return "(?)";
}

String GetHostName()
{
#if (defined(__linux__) || defined(__APPLE__)) && !defined(__ANDROID__)
    char buffer[256];
    if (gethostname(buffer, 256) == 0)
        return buffer;
#elif defined(_WIN32)
    char buffer[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD len = MAX_COMPUTERNAME_LENGTH + 1;
    if (GetComputerName(buffer, &len))
        return buffer;
#endif
    return "(?)";
}

// Disable Windows OS version functionality when compiling mini version for Web, see https://github.com/urho3d/Urho3D/issues/1998
#if defined(_WIN32) && defined(HAVE_RTL_OSVERSIONINFOW) && !defined(MINI_URHO)
using RtlGetVersionPtr = NTSTATUS (WINAPI *)(PRTL_OSVERSIONINFOW);

static void GetOS(RTL_OSVERSIONINFOW *r)
{
    HMODULE m = GetModuleHandle("ntdll.dll");
    if (m)
    {
        RtlGetVersionPtr fPtr = (RtlGetVersionPtr) GetProcAddress(m, "RtlGetVersion");
        if (r && fPtr && fPtr(r) == 0)
            r->dwOSVersionInfoSize = sizeof *r;
    }
}
#endif

String GetOSVersion()
{
#if defined(__linux__) && !defined(__ANDROID__)
    struct utsname u{};
    if (uname(&u) == 0)
        return String(u.sysname) + " " + u.release;
#elif defined(_WIN32) && defined(HAVE_RTL_OSVERSIONINFOW) && !defined(MINI_URHO)
    RTL_OSVERSIONINFOW r;
    GetOS(&r);
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms724832(v=vs.85).aspx
    if (r.dwMajorVersion == 5 && r.dwMinorVersion == 0)
        return "Windows 2000";
    else if (r.dwMajorVersion == 5 && r.dwMinorVersion == 1)
        return "Windows XP";
    else if (r.dwMajorVersion == 5 && r.dwMinorVersion == 2)
        return "Windows XP 64-Bit Edition/Windows Server 2003/Windows Server 2003 R2";
    else if (r.dwMajorVersion == 6 && r.dwMinorVersion == 0)
        return "Windows Vista/Windows Server 2008";
    else if (r.dwMajorVersion == 6 && r.dwMinorVersion == 1)
        return "Windows 7/Windows Server 2008 R2";
    else if (r.dwMajorVersion == 6 && r.dwMinorVersion == 2)
        return "Windows 8/Windows Server 2012";
    else if (r.dwMajorVersion == 6 && r.dwMinorVersion == 3)
        return "Windows 8.1/Windows Server 2012 R2";
    else if (r.dwMajorVersion == 10 && r.dwMinorVersion == 0)
        return "Windows 10/Windows Server 2016";
    else
        return "Windows Unknown";
#elif defined(__APPLE__)
    char kernel_r[256];
    size_t size = sizeof(kernel_r);

    if (sysctlbyname("kern.osrelease", &kernel_r, &size, NULL, 0) != -1)
    {
        Vector<String> kernel_version = String(kernel_r).Split('.');
        String version = "macOS/Mac OS X ";
        int major = ToInt(kernel_version[0]);
        int minor = ToInt(kernel_version[1]);

        // https://en.wikipedia.org/wiki/Darwin_(operating_system)
        if (major == 18) // macOS Mojave
        {
            version += "Mojave ";
            switch(minor)
            {
                case 0: version += "10.14.0 "; break;
            }
        }
        else if (major == 17) // macOS High Sierra
        {
            version += "High Sierra ";
            switch(minor)
            {
                case 0: version += "10.13.0 "; break;
                case 2: version += "10.13.1 "; break;
                case 3: version += "10.13.2 "; break;
                case 4: version += "10.13.3 "; break;
                case 5: version += "10.13.4 "; break;
                case 6: version += "10.13.5 "; break;
                case 7: version += "10.13.6 "; break;
            }
        }
        else if (major == 16) // macOS Sierra
        {
            version += "Sierra ";
            switch(minor)
            {
                case 0: version += "10.12.0 "; break;
                case 1: version += "10.12.1 "; break;
                case 3: version += "10.12.2 "; break;
                case 4: version += "10.12.3 "; break;
                case 5: version += "10.12.4 "; break;
                case 6: version += "10.12.5 "; break;
                case 7: version += "10.12.6 "; break;
            }
        }
        else if (major == 15) // OS X El Capitan
        {
            version += "El Capitan ";
            switch(minor)
            {
                case 0: version += "10.11.0/10.11.1 "; break;
                case 2: version += "10.11.2 "; break;
                case 3: version += "10.11.3 "; break;
                case 4: version += "10.11.4 "; break;
                case 5: version += "10.11.5 "; break;
                case 6: version += "10.11.6 "; break;
            }
        }
        else if (major == 14) // OS X Yosemite
        {
            version += "Yosemite ";
            switch(minor)
            {
                case 0: version += "10.10.0 "; break;
                case 5: version += "10.10.5 "; break;
            }
        }
        else if (major == 13) // OS X Mavericks
        {
            version += "Mavericks ";
            switch(minor)
            {
                case 0: version += "10.9.0 "; break;
                case 4: version += "10.9.5 "; break;
            }
        }
        else if (major == 12) // OS X Mountain Lion
        {
            version += "Mountain Lion ";
            switch(minor)
            {
                case 0: version += "10.8.0 "; break;
                case 6: version += "10.8.5 "; break;
            }
        }
        else if (major == 11) // Mac OS X Lion
        {
            version += "Lion ";
            switch(minor)
            {
                case 0: version += "10.7.0 "; break;
                case 4: version += "10.7.5 "; break;
            }
        }
        else
        {
            version += "Unknown ";
        }

        return version + " (Darwin kernel " + kernel_version[0] + "." + kernel_version[1] + "." + kernel_version[2] + ")";
    }
#endif
    return "(?)";
}

}
