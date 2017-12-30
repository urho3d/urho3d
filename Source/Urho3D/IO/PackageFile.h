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

#include "../IO/FileSource.h"
#include "../IO/PackedFile.h"

namespace Urho3D
{

/// %File entry within the package file.
struct PackageEntry
{
    /// Offset from the beginning.
    unsigned offset_;
    /// File size.
    unsigned size_;
    /// File checksum.
    unsigned checksum_;
};

/// Stores files of a directory tree sequentially for convenient access.
class URHO3D_API PackageFile : public FileSource
{
    URHO3D_OBJECT(PackageFile, FileSource);

public:
    /// Construct.
    PackageFile(Context* context);
    /// Construct and open.
    PackageFile(Context* context, const String& fileName, unsigned startOffset = 0);
    /// Destruct.
    virtual ~PackageFile() override;

    /// Open the package file. Return true if successful.
    virtual bool Open(const String& fileName, unsigned startOffset);
    /// Open the package file. Return true if successful.
    virtual bool Open(const String& fileName) override { return Open(fileName, 0); }
    /// Check if a file exists within the package file. This will be case-insensitive on Windows and case-sensitive on other platforms.
    virtual bool Exists(const String& fileName) const override;
    /// Get a PackedFile from the package contents
    virtual PackedFile* GetNewFile(const String& fileName, FileMode mode = FILE_READ) override;
    /// Return the file entry corresponding to the name, or null if not found. This will be case-insensitive on Windows and case-sensitive on other platforms.
    const PackageEntry* GetEntry(const String& fileName) const;

    /// Return all file entries.
    const HashMap<String, PackageEntry>& GetEntries() const { return entries_; }

    /// Return number of files.
    virtual unsigned GetNumFiles() const override { return entries_.Size(); }

    /// Return total size of the package file.
    virtual unsigned GetTotalSize() const override { return totalSize_; }

    /// Return total data size from all the file entries in the package file.
    virtual unsigned GetTotalDataSize() const override { return totalDataSize_; }

    /// Return checksum of the package file contents.
    virtual unsigned GetChecksum() const override { return checksum_; }

    /// Return whether the files are compressed.
    virtual bool IsCompressed() const override { return compressed_; }

    /// Return list of file names in the package.
    virtual const Vector<String> GetEntryNames() const override { return entries_.Keys(); }

    /// Register object factory.
    static void RegisterObject(Context* context);

private:
    /// File entries.
    HashMap<String, PackageEntry> entries_;
    /// Package file total size.
    unsigned totalSize_;
    /// Total data size in the package using each entry's actual size if it is a compressed package file.
    unsigned totalDataSize_;
    /// Package file checksum.
    unsigned checksum_;
    /// Compressed flag.
    bool compressed_;
};

}
