//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "HashSet.h"

namespace Urho3D
{

/// Return files.
static const unsigned SCAN_FILES = 0x1;
/// Return directories.
static const unsigned SCAN_DIRS = 0x2;
/// Return also hidden files.
static const unsigned SCAN_HIDDEN = 0x4;

/// Subsystem for file and directory operations and access control.
class FileSystem : public Object
{
    OBJECT(FileSystem);
    
public:
    /// Construct.
    FileSystem(Context* context);
    /// Destruct.
    ~FileSystem();
    
    /// Set the current working directory.
    bool SetCurrentDir(const String& pathName);
    /// Create a directory.
    bool CreateDir(const String& pathName);
    /// Run a program using the command interpreter, block until it exits and return the exit code. Will fail if any allowed paths are defined.
    int SystemCommand(const String& commandLine);
    /// Run a specific program, block until it exits and return the exit code. Will fail if any allowed paths are defined.
    int SystemRun(const String& fileName, const Vector<String>& arguments);
    /// Open a file in an external program, with mode such as "edit" optionally specified. Will fail if any allowed paths are defined.
    bool SystemOpen(const String& fileName, const String& mode = String::EMPTY);
    /// Copy a file. Return true if successful.
    bool Copy(const String& srcFileName, const String& destFileName);
    /// Rename a file. Return true if successful.
    bool Rename(const String& srcFileName, const String& destFileName);
    /// Delete a file. Return true if successful.
    bool Delete(const String& fileName);
    /// Register a path as allowed to access. If no paths are registered, all are allowed.
    void RegisterPath(const String& pathName);
    
    /// Return the absolute current working directory.
    String GetCurrentDir() const;
    /// Return whether paths have been registered.
    bool HasRegisteredPaths() const { return allowedPaths_.Size() > 0; }
    /// Check if a path is allowed to be accessed. If no paths are registered, all are allowed.
    bool CheckAccess(const String& pathName) const;
    /// Returns the file's last modified time as seconds since 1.1.1970, or 0 if can not be accessed.
    unsigned GetLastModifiedTime(const String& fileName) const;
    /// Check if a file exists.
    bool FileExists(const String& fileName) const;
    /// Check if a directory exists.
    bool DirExists(const String& pathName) const;
    /// Scan a directory for specified files.
    void ScanDir(Vector<String>& result, const String& pathName, const String& filter, unsigned flags, bool recursive) const;
    /// Return the program's directory.
    String GetProgramDir() const;
    /// Return the user documents directory.
    String GetUserDocumentsDir() const;
    
private:
    /// Scan directory, called internally.
    void ScanDirInternal(Vector<String>& result, String path, const String& startPath, const String& filter, unsigned flags, bool recursive) const;
    
    /// Allowed directories.
    HashSet<String> allowedPaths_;
};

/// Split a full path to path, filename and extension. The extension will be converted to lowercase.
void SplitPath(const String& fullPath, String& pathName, String& fileName, String& extension);
/// Return the path from a full path.
String GetPath(const String& fullPath);
/// Return the filename from a full path.
String GetFileName(const String& fullPath);
/// Return the extension from a full path, converted to lowercase.
String GetExtension(const String& fullPath);
/// Return the filename and extension from a full path. The extension will be converted to lowercase.
String GetFileNameAndExtension(const String& fullPath);
/// Replace the extension of a file name with another.
String ReplaceExtension(const String& fullPath, const String& newExtension);
/// Add a slash at the end of the path if missing and convert to internal format (use slashes.)
String AddTrailingSlash(const String& pathName);
/// Remove the slash from the end of a path if exists and convert to internal format (use slashes.)
String RemoveTrailingSlash(const String& pathName);
/// Return the parent path, or the path itself if not available.
String GetParentPath(const String& pathName);
/// Convert a path to internal format (use slashes.)
String GetInternalPath(const String& pathName);
/// Convert a path to the format required by the operating system.
String GetNativePath(const String& pathName);
/// Convert a path to the format required by the operating system in wide characters
WString GetWideNativePath(const String& pathName);

}
