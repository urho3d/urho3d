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

#ifndef COMMON_PACKAGEFILE_H
#define COMMON_PACKAGEFILE_H

#include "File.h"

#include <map>

//! File entry within the package file
struct PackageEntry
{
    unsigned mOffset;
    unsigned mSize;
    unsigned mChecksum;
};

//! Stores files of a directory tree sequentially for convenient access
class PackageFile : public RefCounted
{
public:
    //! Construct and read the package file directory
    PackageFile(const std::string& fileName);
    //! Destruct. Close the package file
    virtual ~PackageFile();
    
    //! Check if a file exists within the package file
    bool exists(const std::string& fileName) const;
    //! Return the file entry corresponding to the name. Throw an exception if not found
    const PackageEntry& getEntry(const std::string& fileName) const;
    //! Return all file entries
    const std::map<std::string, PackageEntry>& getEntries() const { return mEntries; }
    //! Return the package file name
    const std::string& getName() const { return mFileName; }
    //! Return hash of the package file name
    StringHash getNameHash() const { return mNameHash; }
    //! Return number of files
    unsigned getNumFiles() const { return mEntries.size(); }
    //! Return total size of the package file
    unsigned getTotalSize() const { return mTotalSize; }
    //! Return checksum of the package file contents
    unsigned getChecksum() const { return mChecksum; }
    
private:
    //! File entries
    std::map<std::string, PackageEntry> mEntries;
    //! File name
    std::string mFileName;
    //! Package file name hash
    StringHash mNameHash;
    //! Package file total size
    unsigned mTotalSize;
    //! Package file checksum
    unsigned mChecksum;
};

#endif // COMMON_PACKAGEFILE_H
