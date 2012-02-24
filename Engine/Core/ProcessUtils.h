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

#pragma once

#include "Str.h"

class Mutex;

/// Initialize the FPU to round-to-nearest, single precision mode.
void InitFPU();
/// Display an error dialog with the specified title and message.
void ErrorDialog(const String& title, const String& message);
/// Exit the application with an error message to the console.
void ErrorExit(const String& message, int exitCode = 1);
/// Open a console window.
void OpenConsoleWindow();
/// Print to the console. A newline will be added automatically.
void PrintLine(const String& str);
/// Print to the console. A newline will be added automatically.
void PrintLine(const char* str);
/// Parse arguments from the command line.
const Vector<String>& ParseArguments(const String& cmdLine);
/// Parse arguments from the command line.
const Vector<String>& ParseArguments(const char* cmdLine);
/// Parse arguments from a wide char command line.
const Vector<String>& ParseArguments(const WString& cmdLine);
/// Parse arguments from a wide char command line.
const Vector<String>& ParseArguments(const wchar_t* cmdLine);
/// Parse arguments from argc & argv
const Vector<String>& ParseArguments(int argc, char** argv);
/// Return previously parsed arguments.
const Vector<String>& GetArguments();
/// Read input from the console window. Return empty if no input.
String GetConsoleInput();
/// Return the number of physical CPU cores.
unsigned GetNumPhysicalCPUs();
/// Return the number of logical CPUs (different from physical if hyperthreading is used.)
unsigned GetNumLogicalCPUs();
/// Return the static library init/shutdown mutex.
Mutex& GetStaticMutex();
