//
// Copyright (c) 2008-2017 the Urho3D project.
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
#include "../Core/Object.h"
#include "../IO/File.h"

#ifdef __ANDROID__
struct SDL_RWops;
#endif

namespace Urho3D
{

#ifdef __ANDROID__
extern const char* APK;

// Macro for checking if a given pathname is inside APK's assets directory
#define URHO3D_IS_ASSET(p) p.StartsWith(APK)
// Macro for truncating the APK prefix string from the asset pathname and at the same time patching the directory name components (see custom_rules.xml)
#ifdef ASSET_DIR_INDICATOR
#define URHO3D_ASSET(p) p.Substring(5).Replaced("/", ASSET_DIR_INDICATOR "/").CString()
#else
#define URHO3D_ASSET(p) p.Substring(5).CString()
#endif
#endif

/// %SystemFile opened either through the filesystem or from within a package file.
/// TODO: would SystemFile be a prefered name?
class URHO3D_API SystemFile : public File
{
    URHO3D_OBJECT(SystemFile, File);

public:
    /// Construct.
    SystemFile(Context* context);
    /// Construct and open a filesystem file.
    SystemFile(Context* context, const String& fileName, FileMode mode = FILE_READ);
    /// Construct and open a filesystem file. FilseSource* ignored.
    SystemFile(Context* context, FileSource*, const String& fileName, FileMode mode = FILE_READ);
    /// Destruct. Close the file if open.
    virtual ~SystemFile() override;

    /// Read bytes from the file. Return number of bytes actually read.
    virtual unsigned Read(void* dest, unsigned size) override;
    /// Set position from the beginning of the file.
    virtual unsigned Seek(unsigned position) override;
    /// Write bytes to the file. Return number of bytes actually written.
    virtual unsigned Write(const void* data, unsigned size) override;

    /// Return a checksum of the file contents using the SDBM hash algorithm.
    virtual unsigned GetChecksum() override;

    /// Open a filesystem file. Return true if successful.
    bool Open(FileSource* source, const String& fileName, FileMode mode = FILE_READ) { return Open(fileName, mode); }
    /// Open a filesystem file. Return true if successful.
    bool Open(const String& fileName, FileMode mode = FILE_READ);
    /// Close the file.
    void Close();
    /// Flush any buffered output to the file.
    void Flush();

    /// Return whether is open.
    bool IsOpen() const;

    /// Return the file handle.
    void* GetHandle() const { return handle_; }

    /// Return whether the file originates from a package.
    bool IsPackaged() const { return false; }

private:
    /// Open file internally using either C standard IO functions or SDL RWops for Android asset files. Return true if successful.
    bool OpenInternal(const String& fileName, FileMode mode);
    /// Perform the file read internally using either C standard IO functions or SDL RWops for Android asset files. Return true if successful.
    bool ReadInternal(void* dest, unsigned size);
    /// Seek in file internally using either C standard IO functions or SDL RWops for Android asset files.
    void SeekInternal(unsigned newPosition);

    /// File handle.
    void* handle_;
#ifdef __ANDROID__
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
    /// Content checksum.
    unsigned checksum_;
    /// Synchronization needed before read -flag.
    bool readSyncNeeded_;
    /// Synchronization needed before write -flag.
    bool writeSyncNeeded_;
};

}
