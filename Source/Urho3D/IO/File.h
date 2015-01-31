//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Container/ArrayPtr.h"
#include "../IO/Deserializer.h"
#include "../IO/Serializer.h"
#include "../Core/Object.h"

#ifdef ANDROID
#include <SDL/SDL_rwops.h>
#endif

namespace Urho3D
{

/// File open mode.
enum FileMode
{
    FILE_READ = 0,
    FILE_WRITE,
    FILE_READWRITE
};

class PackageFile;

/// %File opened either through the filesystem or from within a package file.
class URHO3D_API File : public Object, public Deserializer, public Serializer
{
    OBJECT(File);
    
public:
    /// Construct.
    File(Context* context);
    /// Construct and open a filesystem file.
    File(Context* context, const String& fileName, FileMode mode = FILE_READ);
    /// Construct and open from a package file.
    File(Context* context, PackageFile* package, const String& fileName);
    /// Destruct. Close the file if open.
    virtual ~File();
    
    /// Read bytes from the file. Return number of bytes actually read.
    virtual unsigned Read(void* dest, unsigned size);
    /// Set position from the beginning of the file.
    virtual unsigned Seek(unsigned position);
    /// Write bytes to the file. Return number of bytes actually written.
    virtual unsigned Write(const void* data, unsigned size);
    /// Return the file name.
    virtual const String& GetName() const { return fileName_; }
    /// Return a checksum of the file contents using the SDBM hash algorithm.
    virtual unsigned GetChecksum();
    
    /// Open a filesystem file. Return true if successful.
    bool Open(const String& fileName, FileMode mode = FILE_READ);
    /// Open from within a package file. Return true if successful.
    bool Open(PackageFile* package, const String& fileName);
    /// Close the file.
    void Close();
    /// Flush any buffered output to the file.
    void Flush();
    /// Change the file name. Used by the resource system.
    void SetName(const String& name);
    
    /// Return the open mode.
    FileMode GetMode() const { return mode_; }
    /// Return whether is open.
    bool IsOpen() const;
    /// Return the file handle.
    void* GetHandle() const { return handle_; }
    /// Return whether the file originates from a package.
    bool IsPackaged() const { return offset_ != 0; }
    
private:
    /// File name.
    String fileName_;
    /// Open mode.
    FileMode mode_;
    /// File handle.
    void* handle_;
    #ifdef ANDROID
    /// SDL RWops context for Android asset loading.
    SDL_RWops* assetHandle_;
    #endif
    /// Read buffer for Android asset or compressed file loading.
    SharedArrayPtr<unsigned char> readBuffer_;
    /// Decompression input buffer for compressed file loading.
    SharedArrayPtr<unsigned char> inputBuffer_;
    /// Read buffer position.
    unsigned readBufferOffset_;
    /// Bytes in the current read buffer.
    unsigned readBufferSize_;
    /// Start position within a package file, 0 for regular files.
    unsigned offset_;
    /// Content checksum.
    unsigned checksum_;
    /// Compression flag.
    bool compressed_;
    /// Synchronization needed before read -flag.
    bool readSyncNeeded_;
    /// Synchronization needed before write -flag.
    bool writeSyncNeeded_;
};

}
