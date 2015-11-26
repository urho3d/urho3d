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

#include "../Precompiled.h"

#include "../IO/File.h"
#include "../IO/Log.h"
#include "../IO/PackageFile.h"

namespace Urho3D
{

PackageFile::PackageFile(Context* context) :
    Object(context),
    totalSize_(0),
    checksum_(0),
    compressed_(false)
{
}

PackageFile::PackageFile(Context* context, const String& fileName, unsigned startOffset) :
    Object(context),
    totalSize_(0),
    checksum_(0),
    compressed_(false)
{
    Open(fileName, startOffset);
}

PackageFile::~PackageFile()
{
}

bool PackageFile::Open(const String& fileName, unsigned startOffset)
{
#ifdef ANDROID
    if (URHO3D_IS_ASSET(fileName))
    {
        URHO3D_LOGERROR("Package files within the apk are not supported on Android");
        return false;
    }
#endif

    SharedPtr<File> file(new File(context_, fileName));
    if (!file->IsOpen())
        return false;

    // Check ID, then read the directory
    file->Seek(startOffset);
    String id = file->ReadFileID();
    if (id != "UPAK" && id != "ULZ4")
    {
        // If start offset has not been explicitly specified, also try to read package size from the end of file
        // to know how much we must rewind to find the package start
        if (!startOffset)
        {
            unsigned fileSize = file->GetSize();
            file->Seek((unsigned)(fileSize - sizeof(unsigned)));
            unsigned newStartOffset = fileSize - file->ReadUInt();
            if (newStartOffset < fileSize)
            {
                startOffset = newStartOffset;
                file->Seek(startOffset);
                id = file->ReadFileID();
            }
        }

        if (id != "UPAK" && id != "ULZ4")
        {
            URHO3D_LOGERROR(fileName + " is not a valid package file");
            return false;
        }
    }

    fileName_ = fileName;
    nameHash_ = fileName_;
    totalSize_ = file->GetSize();
    compressed_ = id == "ULZ4";

    unsigned numFiles = file->ReadUInt();
    checksum_ = file->ReadUInt();

    for (unsigned i = 0; i < numFiles; ++i)
    {
        String entryName = file->ReadString();
        PackageEntry newEntry;
        newEntry.offset_ = file->ReadUInt() + startOffset;
        newEntry.size_ = file->ReadUInt();
        newEntry.checksum_ = file->ReadUInt();
        if (!compressed_ && newEntry.offset_ + newEntry.size_ > totalSize_)
        {
            URHO3D_LOGERROR("File entry " + entryName + " outside package file");
            return false;
        }
        else
            entries_[entryName] = newEntry;
    }

    return true;
}

bool PackageFile::Exists(const String& fileName) const
{
    bool found = entries_.Find(fileName) != entries_.End();

#ifdef _WIN32
    // On Windows perform a fallback case-insensitive search
    if (!found)
    {
        for (HashMap<String, PackageEntry>::ConstIterator i = entries_.Begin(); i != entries_.End(); ++i)
        {
            if (!i->first_.Compare(fileName, false))
            {
                found = true;
                break;
            }
        }
    }
#endif

    return found;
}

const PackageEntry* PackageFile::GetEntry(const String& fileName) const
{
    HashMap<String, PackageEntry>::ConstIterator i = entries_.Find(fileName);
    if (i != entries_.End())
        return &i->second_;

#ifdef _WIN32
    // On Windows perform a fallback case-insensitive search
    else
    {
        for (HashMap<String, PackageEntry>::ConstIterator j = entries_.Begin(); j != entries_.End(); ++j)
        {
            if (!j->first_.Compare(fileName, false))
                return &j->second_;
        }
    }
#endif

    return 0;
}

}
