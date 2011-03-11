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

#ifndef COMMON_FILE_H
#define COMMON_FILE_H

#include "Deserializer.h"
#include "Serializer.h"
#include "SharedPtr.h"

#include <cstdio>
#include <set>

//! File open mode
enum FileMode
{
    FILE_READ = 0,
    FILE_WRITE,
    FILE_READWRITE
};

//! Return files
static const unsigned SCAN_FILES = 1;
//! Return directories
static const unsigned SCAN_DIRECTORIES = 2;
//! Return also hidden files
static const unsigned SCAN_HIDDEN = 4;

class PackageFile;

//! A file opened either through the filesystem or from within a package file
class File : public RefCounted, public Deserializer, public Serializer
{
public:
    //! Construct and open the file with the specified name and open mode
    File(const std::string& fileName, FileMode mode = FILE_READ);
    //! Construct by specifying a package file source
    File(const PackageFile& package, const std::string& fileName);
    //! Destruct. Close the file if open
    virtual ~File();
    
    //! Read bytes from the file
    virtual void read(void* dest, unsigned size);
    //! Set position from the beginning of the file
    virtual unsigned seek(unsigned position);
    //! Write bytes to the file
    virtual void write(const void* data, unsigned size);
    //! Return the file name
    virtual const std::string& getName() const { return mFileName; }
    
    //! Close the file. Can not be re-opened without constructing another File
    void close();
    //! Change the file name. Used by the resource system
    void setName(const std::string& name);
    //! Return the open mode
    FileMode getMode() const { return mMode; }
    //! Return a checksum of the file contents, using the SDBM hash algorithm
    unsigned getChecksum();
    
    //! Return the file handle
    FILE* getHandle() const { return mHandle; }
    
private:
    //! File handle
    FILE* mHandle;
    //! File name
    std::string mFileName;
    //! Open mode
    FileMode mMode;
    //! Start position within a package file, 0 for regular files
    unsigned mOffset;
    //! Content checksum
    unsigned mChecksum;
};

//! Check if a file exists
bool fileExists(const std::string& fileName);
//! Check if a directory exists
bool directoryExists(const std::string& pathName);
//! Scan a directory for specified files
void scanDirectory(std::vector<std::string>& result, const std::string& pathName, const std::string& filter, unsigned flags, bool recursive);
//! Return the absolute current directory
std::string getCurrentDirectory();
//! Set the current directory
bool setCurrentDirectory(const std::string& pathName);
//! Create a directory
bool createDirectory(const std::string& pathName);
//! Execute an external command, block until it exists and return the exit code. Will fail if any allowed paths are defined
int systemCommand(const std::string& commandLine);
//! Open a file in an external program, with mode such as "edit" optionally specified. Will fail if any allowed paths are defined
bool systemOpenFile(const std::string& fileName, const std::string& mode = std::string());
//! Copy a file. Return true if successful
bool copyFile(const std::string& srcFileName, const std::string& destFileName);
//! Register a path as being allowed to access
void registerDirectory(const std::string& pathName);
//! Check if a path is allowed to be accessed. If no paths defined, all are allowed
bool checkDirectoryAccess(const std::string& pathName);
//! Split a full path to path, filename and extension. The extension will be converted to lowercase
void splitPath(const std::string& fullPath, std::string& pathName, std::string& fileName, std::string& extension);
//! Return the path from a full path
std::string getPath(const std::string& fullPath);
//! Return the filename from a full path
std::string getFileName(const std::string& fullPath);
//! Return the extension from a full path, converted to lowercase
std::string getExtension(const std::string& fullPath);
//! Return the filename and extension from a full path. The extension will be converted to lowercase
std::string getFileNameAndExtension(const std::string& fullPath);
//! Fix a path so that it contains a slash in the end, and convert backslashes to slashes
std::string fixPath(const std::string& pathName);
//! Remove the slash or backslash from the end of a path if exists
std::string unfixPath(const std::string& pathName);
//! Return the parent path, or the path itself if not available
std::string getParentPath(const std::string& pathName);
//! Return the absolute filename using the current working directory
std::string getAbsoluteFileName(const std::string& fileName);
//! Convert a path to the format required by the operating system
std::string getOSPath(const std::string& pathName, bool forNativeApi = false);

#endif // COMMON_FILE_H
