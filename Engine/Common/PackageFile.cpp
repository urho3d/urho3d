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

#include "Precompiled.h"
#include "Log.h"
#include "PackageFile.h"
#include "StringUtils.h"

PackageFile::PackageFile(const std::string& fileName) :
    mFileName(fileName),
    mNameHash(StringHash(fileName))
{
    File file(mFileName);
    mTotalSize = file.getSize();
    
    // Register the reverse mapping for the hashed file name
    registerHash(mFileName);
    
    // Read the directory
    unsigned numFiles = file.readUInt();
    mChecksum = file.readUInt();
    
    for (unsigned i = 0; i < numFiles; ++i)
    {
        std::string entryName = file.readString();
        PackageEntry newEntry;
        newEntry.mOffset = file.readUInt();
        newEntry.mSize = file.readUInt();
        newEntry.mChecksum = file.readUInt();
        if (newEntry.mOffset + newEntry.mSize > file.getSize())
            EXCEPTION("File entry " + fileName + " outside package file");
        mEntries[toLower(entryName)] = newEntry;
    }
}

PackageFile::~PackageFile()
{
}

bool PackageFile::exists(const std::string& fileName) const
{
    return mEntries.find(toLower(fileName)) != mEntries.end();
}

const PackageEntry& PackageFile::getEntry(const std::string& fileName) const
{
    std::map<std::string, PackageEntry>::const_iterator i = mEntries.find(toLower(fileName));
    if (i == mEntries.end())
        EXCEPTION("File " + fileName + " not found in package " + getName());
    
    return i->second;
}
