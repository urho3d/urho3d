//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "FileSystem.h"
#include "Log.h"
#include "PackageFile.h"
#include "Profiler.h"

#include <cstdio>

#include "DebugNew.h"

#ifdef WIN32
static const wchar_t* openMode[] =
{
    L"rb",
    L"wb",
    L"w+b"
};
#else
static const char* openMode[] =
{
    "rb",
    "wb",
    "w+b"
};
#endif

#ifdef ANDROID
static const unsigned READ_BUFFER_SIZE = 1024;
#endif

OBJECTTYPESTATIC(File);

File::File(Context* context) :
    Object(context),
    mode_(FILE_READ),
    handle_(0),
    #ifdef ANDROID
    assetHandle_(0),
    readBufferOffset_(0),
    readBufferSize_(0),
    #endif
    offset_(0),
    checksum_(0)
{
}

File::File(Context* context, const String& fileName, FileMode mode) :
    Object(context),
    mode_(FILE_READ),
    handle_(0),
    #ifdef ANDROID
    assetHandle_(0),
    readBufferOffset_(0),
    readBufferSize_(0),
    #endif
    offset_(0),
    checksum_(0)
{
    Open(fileName, mode);
}

File::File(Context* context, PackageFile* package, const String& fileName) :
    Object(context),
    mode_(FILE_READ),
    handle_(0),
    #ifdef ANDROID
    assetHandle_(0),
    readBufferOffset_(0),
    readBufferSize_(0),
    #endif
    offset_(0),
    checksum_(0)
{
    Open(package, fileName);
}

File::~File()
{
    Close();
}

bool File::Open(const String& fileName, FileMode mode)
{
    Close();
    
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem && !fileSystem->CheckAccess(GetPath(fileName)))
    {
        LOGERROR("Access denied to " + fileName);
        return false;
    }
    
    #ifdef ANDROID
    if (fileName.StartsWith("/apk/"))
    {
        if (mode != FILE_READ)
        {
            LOGERROR("Only read mode is supported for asset files");
            return false;
        }
        
        assetHandle_ = SDL_RWFromFile(fileName.Substring(5).CString(), "rb");
        if (!assetHandle_)
        {
            LOGERROR("Could not open asset file " + fileName);
            return false;
        }
        else
        {
            fileName_ = fileName;
            mode_ = mode;
            position_ = 0;
            offset_ = 0;
            checksum_ = 0;
            size_ = assetHandle_->hidden.androidio.size;
            readBuffer_ = new unsigned char[READ_BUFFER_SIZE];
            readBufferOffset_ = 0;
            readBufferSize_ = 0;
            return true;
        }
    }
    #endif
    
    #ifdef WIN32
    handle_ = _wfopen(GetWideNativePath(fileName).CString(), openMode[mode]);
    #else
    handle_ = fopen(GetNativePath(fileName).CString(), openMode[mode]);
    #endif
    
    if (!handle_)
    {
        LOGERROR("Could not open file " + fileName);
        return false;
    }
    
    fileName_ = fileName;
    mode_ = mode;
    position_ = 0;
    offset_ = 0;
    checksum_ = 0;
    
    fseek((FILE*)handle_, 0, SEEK_END);
    size_ = ftell((FILE*)handle_);
    fseek((FILE*)handle_, 0, SEEK_SET);
    return true;
}

bool File::Open(PackageFile* package, const String& fileName)
{
    Close();
    
    if (!package)
        return false;
    
    const PackageEntry* entry = package->GetEntry(fileName);
    if (!entry)
        return false;
    
    #ifdef WIN32
    handle_ = _wfopen(GetWideNativePath(package->GetName()).CString(), L"rb");
    #else
    handle_ = fopen(GetNativePath(package->GetName()).CString(), "rb");
    #endif
    if (!handle_)
    {
        LOGERROR("Could not open package file " + fileName);
        return false;
    }
    
    fileName_ = fileName;
    mode_ = FILE_READ;
    offset_ = entry->offset_;
    checksum_ = entry->checksum_;
    position_ = 0;
    size_ = entry->size_;
    
    fseek((FILE*)handle_, offset_, SEEK_SET);
    return true;
}

unsigned File::Read(void* dest, unsigned size)
{
    if (mode_ == FILE_WRITE)
    {
        LOGERROR("File not opened for reading");
        return 0;
    }
    
    if (size + position_ > size_)
        size = size_ - position_;
    if (!size)
        return 0;
    
    #ifdef ANDROID
    if (assetHandle_)
    {
        unsigned sizeLeft = size;
        unsigned char* destPtr = (unsigned char*)dest;
        
        while (sizeLeft)
        {
            if (readBufferOffset_ >= readBufferSize_)
            {
                readBufferSize_ = Min((int)size_ - position_, (int)READ_BUFFER_SIZE);
                readBufferOffset_ = 0;
                SDL_RWread(assetHandle_, readBuffer_.Get(), readBufferSize_, 1);
            }
            
            unsigned copySize = Min((int)(readBufferSize_ - readBufferOffset_), (int)sizeLeft);
            memcpy(destPtr, readBuffer_.Get() + readBufferOffset_, copySize);
            destPtr += copySize;
            sizeLeft -= copySize;
            readBufferOffset_ += copySize;
            position_ += copySize;
        }
        
        return size;
    }
    #endif
    
    if (!handle_)
    {
        LOGERROR("File not open");
        return 0;
    }
    
    size_t ret = fread(dest, size, 1, (FILE*)handle_);
    if (ret != 1)
    {
        // Return to the position where the read began
        fseek((FILE*)handle_, position_ + offset_, SEEK_SET);
        LOGERROR("Error while reading from file " + GetName());
        return 0;
    }
    
    position_ += size;
    return size;
}

unsigned File::Seek(unsigned position)
{
    // Allow sparse seeks if writing
    if (mode_ == FILE_READ && position > size_)
        position = size_;
    
    #ifdef ANDROID
    if (assetHandle_)
    {
        SDL_RWseek(assetHandle_, position, SEEK_SET);
        position_ = position;
        readBufferOffset_ = 0;
        readBufferSize_ = 0;
        return position_;
    }
    #endif
    
    if (!handle_)
    {
        LOGERROR("File not open");
        return 0;
    }
    
    fseek((FILE*)handle_, position + offset_, SEEK_SET);
    position_ = position;
    return position_;
}

unsigned File::Write(const void* data, unsigned size)
{
    if (mode_ == FILE_READ)
    {
        LOGERROR("File not opened for writing");
        return 0;
    }
    
    if (!handle_)
    {
        LOGERROR("File not open");
        return 0;
    }
    
    if (!size)
        return 0;
    
    if (fwrite(data, size, 1, (FILE*)handle_) != 1)
    {
        // Return to the position where the write began
        fseek((FILE*)handle_, position_ + offset_, SEEK_SET);
        LOGERROR("Error while writing to file " + GetName());
        return 0;
    }
    
    position_ += size;
    if (position_ > size_)
        size_ = position_;
    
    return size;
}

unsigned File::GetChecksum()
{
    if (offset_ || checksum_)
        return checksum_;
    if (!handle_)
        return 0;
    
    PROFILE(CalculateFileChecksum);
    
    unsigned oldPos = position_;
    checksum_ = 0;
    
    Seek(0);
    while (!IsEof())
    {
        unsigned char block[1024];
        unsigned readBytes = Read(block, 1024);
        for (unsigned i = 0; i < readBytes; ++i)
            checksum_ = SDBMHash(checksum_, block[i]);
    }
    
    Seek(oldPos);
    return checksum_;
}

void File::Close()
{
    #ifdef ANDROID
    if (assetHandle_)
    {
        SDL_RWclose(assetHandle_);
        assetHandle_ = 0;
        readBuffer_.Reset();
    }
    #endif
    
    if (handle_)
    {
        fclose((FILE*)handle_);
        handle_ = 0;
        position_ = 0;
        size_ = 0;
        offset_ = 0;
        checksum_ = 0;
    }
}

void File::Flush()
{
    if (handle_)
        fflush((FILE*)handle_);
}

void File::SetName(const String& name)
{
    fileName_ = name;
}
