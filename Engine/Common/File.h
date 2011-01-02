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

struct PackageEntry;

//! A file opened either through the filesystem or from within a package file
class File : public RefCounted, public Deserializer, public Serializer
{
public:
    //! Construct and open the file with the specified name and open mode
    File(const std::string& fileName, FileMode mode = FILE_READ);
    //! Construct by specifying an entry within a package file
    File(const std::string& fileName, File* packageFile, const PackageEntry& entry);
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
    
private:
    //! File handle
    FILE* mHandle;
    //! Pointer to package file if opened from within a package
    WeakPtr<File> mPackageFile;
    //! File name
    std::string mFileName;
    //! Open mode
    FileMode mMode;
    //! Start position within a package file
    unsigned mOffset;
    //! Content checksum
    unsigned mChecksum;
};

//! Check if a file exists
bool fileExists(const std::string& fileName);
//! Create a directory
void createDirectory(const std::string& pathName);
//! Scan a directory for specified files
std::vector<std::string> scanDirectory(const std::string& pathName, const std::string& filter, bool recursive);
//! Register a path as being allowed to access
void registerDirectory(const std::string& pathName);
//! Check if a path is allowed to be accessed. If no paths defined, all are allowed
bool checkDirectoryAccess(const std::string& pathName);
//! Split a full path to path, filename and extension. Optionally convert the extension to lowercase
void splitPath(const std::string& fullPath, std::string& pathName, std::string& fileName, std::string& extension, bool lowerCaseExtension = true);
//! Return the path from a full path
std::string getPath(const std::string& fullPath);
//! Return the filename from a full path
std::string getFileName(const std::string& fullPath);
//! Return the extension from a full path and optionally convert to lowercase
std::string getExtension(const std::string& fullPath, bool lowerCaseExtension = true);
//! Return the filename and extension from a full path. Optionally convert the extension to lowercase
std::string getFileNameAndExtension(const std::string& fullPath, bool lowerCaseExtension = true);
//! Fix a path so that it contains a slash in the end, and convert backslashes to slashes
std::string fixPath(const std::string& pathName);
//! Convert a path to the format required by the operating system
std::string getOSPath(const std::string& pathName, bool forNativeApi = false);

#endif // COMMON_FILE_H
