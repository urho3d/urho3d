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

#include "Deserializer.h"
#include "Serializer.h"
#include "Object.h"

/// File open mode
enum FileMode
{
    FILE_READ = 0,
    FILE_WRITE,
    FILE_READWRITE
};

class PackageFile;

/// File opened either through the filesystem or from within a package file
class File : public Object, public Deserializer, public Serializer
{
    OBJECT(File);
    
public:
    /// Construct
    File(Context* context);
    /// Construct and open
    File(Context* context, const std::string& fileName, FileMode mode = FILE_READ);
    /// Construct and open from a package file
    File(Context* context, PackageFile* package, const std::string& fileName);
    /// Destruct. Close the file if open
    virtual ~File();
    
    /// Read bytes from the file
    virtual unsigned Read(void* dest, unsigned size);
    /// Set position from the beginning of the file
    virtual unsigned Seek(unsigned position);
    /// Write bytes to the file
    virtual unsigned Write(const void* data, unsigned size);
    /// Return the file name
    virtual const std::string& GetName() const { return fileName_; }
    
    /// Open a filesystem file. Return true if successful
    bool Open(const std::string& fileName, FileMode mode = FILE_READ);
    /// Open from within a package file. Return true if successful
    bool Open(PackageFile* package, const std::string& fileName);
    /// Close the file
    void Close();
    /// Change the file name. Used by the resource system
    void SetName(const std::string& name);
    
    /// Return the open mode
    FileMode GetMode() const { return mode_; }
    /// Return whether is open
    bool IsOpen() const { return handle_ != 0; }
    /// Return a checksum of the file contents, using the SDBM hash algorithm
    unsigned GetChecksum();
    
    /// Return the file handle
    void* GetHandle() const { return handle_; }
    
private:
    /// File name
    std::string fileName_;
    /// Open mode
    FileMode mode_;
    /// File handle
    void* handle_;
    /// Start position within a package file, 0 for regular files
    unsigned offset_;
    /// Content checksum
    unsigned checksum_;
};
