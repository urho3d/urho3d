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

#pragma once

#include "../Container/Str.h"

#include <cstdlib>

namespace Urho3D
{

class Mutex;

/// Initialize the FPU to round-to-nearest, single precision mode.
URHO3D_API void InitFPU();
/// Display an error dialog with the specified title and message.
URHO3D_API void ErrorDialog(const String& title, const String& message);
/// Exit the application with an error message to the console.
URHO3D_API void ErrorExit(const String& message = String::EMPTY, int exitCode = EXIT_FAILURE);
/// Open a console window.
URHO3D_API void OpenConsoleWindow();
/// Print Unicode text to the console. Will not be printed to the MSVC output window.
URHO3D_API void PrintUnicode(const String& str, bool error = false);
/// Print Unicode text to the console with a newline appended. Will not be printed to the MSVC output window.
URHO3D_API void PrintUnicodeLine(const String& str, bool error = false);
/// Print ASCII text to the console with a newline appended. Uses printf() to allow printing into the MSVC output window.
URHO3D_API void PrintLine(const String& str, bool error = false);
/// Print ASCII text to the console with a newline appended. Uses printf() to allow printing into the MSVC output window.
URHO3D_API void PrintLine(const char* str, bool error = false);
/// Parse arguments from the command line. First argument is by default assumed to be the executable name and is skipped.
URHO3D_API const Vector<String>& ParseArguments(const String& cmdLine, bool skipFirstArgument = true);
/// Parse arguments from the command line.
URHO3D_API const Vector<String>& ParseArguments(const char* cmdLine);
/// Parse arguments from a wide char command line.
URHO3D_API const Vector<String>& ParseArguments(const WString& cmdLine);
/// Parse arguments from a wide char command line.
URHO3D_API const Vector<String>& ParseArguments(const wchar_t* cmdLine);
/// Parse arguments from argc & argv.
URHO3D_API const Vector<String>& ParseArguments(int argc, char** argv);
/// Return previously parsed arguments.
URHO3D_API const Vector<String>& GetArguments();
/// Read input from the console window. Return empty if no input.
URHO3D_API String GetConsoleInput();
/// Return the runtime platform identifier, or (?) if not identified.
URHO3D_API String GetPlatform();
/// Return the number of physical CPU cores.
URHO3D_API unsigned GetNumPhysicalCPUs();
/// Return the number of logical CPUs (different from physical if hyperthreading is used.)
URHO3D_API unsigned GetNumLogicalCPUs();
/// Set minidump write location as an absolute path. If empty, uses default (UserProfile/AppData/Roaming/urho3D/crashdumps) Minidumps are only supported on MSVC compiler.
URHO3D_API void SetMiniDumpDir(const String& pathName);
/// Return minidump write location.
URHO3D_API String GetMiniDumpDir();
/// Return the total amount of usable memory in bytes.
URHO3D_API unsigned long long GetTotalMemory();
/// Return the name of the currently logged in user, or (?) if not identified.
URHO3D_API String GetLoginName();
/// Return the name of the running machine.
URHO3D_API String GetHostName();
/// Return the version of the currently running OS, or (?) if not identified.
URHO3D_API String GetOSVersion();
}
