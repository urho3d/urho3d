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

#ifndef COMMON_PROCESSUTILS_H
#define COMMON_PROCESSUTILS_H

#include <string>
#include <vector>

//! Set the executable's location as the working directory
void setExecutableWorkingDirectory();
//! Open a console window
void openConsoleWindow();
//! Display an error dialog with the specified title and message
void errorDialog(const std::string& title, const std::string& message);
//! Parse arguments from a command line
void parseArguments(const char* cmdLine);
//! Return previously parsed arguments
const std::vector<std::string>& getArguments();
//! Read input from the console window. Return false if there was no input
bool getConsoleInput(std::string& line);
//! Return the user's document directory which should have read/write access for writing logs, savegames etc.
std::string getUserDocumentsDirectory();
//! Return the number of logical processors
unsigned getNumLogicalProcessors();

#ifdef ENABLE_MINIDUMPS
//! Write a minidump. Needs to be called from within a structured exception handler
int writeMiniDump(const char* applicationName, void* exceptionPointers);
#endif

#endif // COMMON_PROCESSUTILS_H
