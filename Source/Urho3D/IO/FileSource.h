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

#include "../Core/Object.h"
#include "../IO/File.h"

namespace Urho3D
{

/// Base class representing a source of a kind of file. Exists must be implemented.
class URHO3D_API FileSource : public Object
{
    URHO3D_OBJECT(FileSource, Object);

public:
    /// Construct.
    FileSource(Context* context);
    /// Destruct.
    virtual ~FileSource() override { }

    /// Check if a file exists within the package file. This should be case-insensitive on Windows and case-sensitive on other platforms.
    virtual bool Exists(const String& fileName) const = 0;

    /// Return list of file names in the package, if available. Otherwise must store list of used resource names and use those.
    virtual const Vector<String> GetEntryNames() const = 0;

    /// Opens a new file of the kind associate with this type of file source with the given name.
    virtual File* GetNewFile(const String& fileName, FileMode mode = FILE_READ) = 0;

    /// Opens a file with the given name and returns a file shared pointer from the source.
    SharedPtr<File> GetFile(const String& fileName, FileMode mode = FILE_READ);

    /// Open the package file, if applicable.
    virtual bool Open(const String& filename) { return true; }

    // TODO: NEL: Possibly replace the -1 with a 0 and add a separate [Is]Loaded() or LoadSuccessful() function
    /// Return number of files if available. Should return non-zero if load successful.
    virtual unsigned GetNumFiles() const { return -1; }

    /// Return total size of the package file or 0 if unavailable.
    virtual unsigned GetTotalSize() const { return 0; }

    /// Return total data size from all the file entries in the package file or 0 if unavailable.
    virtual unsigned GetTotalDataSize() const { return 0; }

    /// Return checksum of the package file contents or 0 if unavailable.
    virtual unsigned GetChecksum() const { return 0; }

    /// Return whether the files are compressed. Default false.
    virtual bool IsCompressed() const { return false; }

    /// Return the package file name.
    const String& GetName() const { return fileName_; }

    /// Return hash of the package file name.
    StringHash GetNameHash() const { return nameHash_; }

protected:
    void SetName(const String& name) {
        fileName_ = name;
        nameHash_ = fileName_;
    }

    /// File name.
    String fileName_;
    /// Package file name hash.
    StringHash nameHash_;
};

}
