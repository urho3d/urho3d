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

#pragma once

#include "Object.h"

#include <set>
#include <vector>

/// Return files
static const unsigned SCAN_FILES = 0x1;
/// Return directories
static const unsigned SCAN_DIRS = 0x2;
/// Return also hidden files
static const unsigned SCAN_HIDDEN = 0x4;

/// Subsystem for file and directory operations and access control
class FileSystem : public Object
{
    OBJECT(FileSystem);
    
public:
    /// Construct
    FileSystem(Context* context);
    /// Destruct
    ~FileSystem();
    
    /// Set the current working directory
    bool SetCurrentDir(const std::string& pathName);
    /// Create a directory
    bool CreateDir(const std::string& pathName);
    /// Run a program using the command interpreter, block until it exits and return the exit code. Will fail if any allowed paths are defined
    int SystemCommand(const std::string& commandLine);
    /// Run a specific program, block until it exists and return the exit code. Will fail if any allowed paths are defined
    int SystemRun(const std::string& fileName, const std::vector<std::string>& arguments);
    /// Open a file in an external program, with mode such as "edit" optionally specified. Will fail if any allowed paths are defined
    bool SystemOpen(const std::string& fileName, const std::string& mode = std::string());
    /// Copy a file. Return true if successful
    bool Copy(const std::string& srcFileName, const std::string& destFileName);
    /// Rename a file. Return true if successful
    bool Rename(const std::string& srcFileName, const std::string& destFileName);
    /// Delete a file. Return true if successful
    bool Delete(const std::string& fileName);
    /// Register a path as being allowed to access
    void RegisterPath(const std::string& pathName);
    
    /// Return the absolute current working directory
    std::string GetCurrentDir();
    /// Check if a path is allowed to be accessed. If no paths defined, all are allowed
    bool CheckAccess(const std::string& pathName);
    /// Check if a file exists
    bool FileExists(const std::string& fileName);
    /// Check if a directory exists
    bool DirExists(const std::string& pathName);
    /// Scan a directory for specified files
    void ScanDir(std::vector<std::string>& result, const std::string& pathName, const std::string& filter, unsigned flags, bool recursive);
    /// Return the program's directory
    std::string GetProgramDir();
    /// Return the user documents directory
    std::string GetUserDocumentsDir();
    /// Return the system fonts directory
    std::string GetSystemFontDir();
    
private:
    /// Scan directory, called internally
    void ScanDirInternal(std::vector<std::string>& result, std::string path, const std::string& startPath,
        const std::string& filter, unsigned flags, bool recursive);
    
    /// Allowed directories
    std::set<std::string> allowedPaths_;
};

/// Split a full path to path, filename and extension. The extension will be converted to lowercase
void SplitPath(const std::string& fullPath, std::string& pathName, std::string& fileName, std::string& extension);
/// Return the path from a full path
std::string GetPath(const std::string& fullPath);
/// Return the filename from a full path
std::string GetFileName(const std::string& fullPath);
/// Return the extension from a full path, converted to lowercase
std::string GetExtension(const std::string& fullPath);
/// Return the filename and extension from a full path. The extension will be converted to lowercase
std::string GetFileNameAndExtension(const std::string& fullPath);
/// Fix a path so that it contains a slash in the end, and convert backslashes to slashes
std::string AddTrailingSlash(const std::string& pathName);
/// Remove the slash or backslash from the end of a path if exists
std::string RemoveTrailingSlash(const std::string& pathName);
/// Return the parent path, or the path itself if not available
std::string GetParentPath(const std::string& pathName);
/// Convert a path to the format required by the operating system
std::string GetNativePath(const std::string& pathName, bool forNativeApi = false);
