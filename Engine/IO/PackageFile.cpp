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
#include "File.h"
#include "Log.h"
#include "PackageFile.h"
#include "StringUtils.h"

OBJECTTYPESTATIC(PackageFile);

PackageFile::PackageFile(Context* context) :
    Object(context),
    totalSize_(0),
    checksum_(0)
{
}

PackageFile::PackageFile(Context* context, const std::string& fileName) :
    Object(context),
    totalSize_(0),
    checksum_(0)
{
    Open(fileName);
}

PackageFile::~PackageFile()
{
}

bool PackageFile::Open(const std::string& fileName)
{
    SharedPtr<File> file(new File(context_, fileName));
    if (!file->IsOpen())
        return false;
    
    // Check ID, then read the directory
    if (file->ReadID() != "UPAK")
    {
        LOGERROR(fileName + " is not a valid package file");
        return false;
    }
    
    fileName_ = fileName;
    nameHash_ = StringHash(fileName_);
    totalSize_ = file->GetSize();
    
    unsigned numFiles = file->ReadUInt();
    checksum_ = file->ReadUInt();
    
    for (unsigned i = 0; i < numFiles; ++i)
    {
        std::string entryName = file->ReadString();
        PackageEntry newEntry;
        newEntry.offset_ = file->ReadUInt();
        newEntry.size_ = file->ReadUInt();
        newEntry.checksum_ = file->ReadUInt();
        if (newEntry.offset_ + newEntry.size_ > totalSize_)
            LOGERROR("File entry " + entryName + " outside package file");
        else
            entries_[ToLower(entryName)] = newEntry;
    }
    
    return true;
}

bool PackageFile::Exists(const std::string& fileName) const
{
    return entries_.find(ToLower(fileName)) != entries_.end();
}

const PackageEntry* PackageFile::GetEntry(const std::string& fileName) const
{
    std::map<std::string, PackageEntry>::const_iterator i = entries_.find(ToLower(fileName));
    if (i == entries_.end())
        return 0;
    
    return &i->second;
}
