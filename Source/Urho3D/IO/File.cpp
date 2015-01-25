//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "../IO/File.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../IO/PackageFile.h"
#include "../Core/Profiler.h"

#include <cstdio>
#include <LZ4/lz4.h>

#include "../DebugNew.h"

namespace Urho3D
{

#ifdef WIN32
static const wchar_t* openMode[] =
{
    L"rb",
    L"wb",
    L"r+b",
    L"w+b"
};
#else
static const char* openMode[] =
{
    "rb",
    "wb",
    "r+b",
    "w+b"
};
#endif

#ifdef ANDROID
static const unsigned READ_BUFFER_SIZE = 32768;
#endif
static const unsigned SKIP_BUFFER_SIZE = 1024;

File::File(Context* context) :
    Object(context),
    mode_(FILE_READ),
    handle_(0),
    #ifdef ANDROID
    assetHandle_(0),
    #endif
    readBufferOffset_(0),
    readBufferSize_(0),
    offset_(0),
    checksum_(0),
    compressed_(false),
    readSyncNeeded_(false),
    writeSyncNeeded_(false)
{
}

File::File(Context* context, const String& fileName, FileMode mode) :
    Object(context),
    mode_(FILE_READ),
    handle_(0),
    #ifdef ANDROID
    assetHandle_(0),
    #endif
    readBufferOffset_(0),
    readBufferSize_(0),
    offset_(0),
    checksum_(0),
    compressed_(false),
    readSyncNeeded_(false),
    writeSyncNeeded_(false)
{
    Open(fileName, mode);
}

File::File(Context* context, PackageFile* package, const String& fileName) :
    Object(context),
    mode_(FILE_READ),
    handle_(0),
    #ifdef ANDROID
    assetHandle_(0),
    #endif
    readBufferOffset_(0),
    readBufferSize_(0),
    offset_(0),
    checksum_(0),
    compressed_(false),
    readSyncNeeded_(false),
    writeSyncNeeded_(false)
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

    if (fileName.Empty())
    {
        LOGERROR("Could not open file with empty name");
        return false;
    }
    
    #ifdef WIN32
    handle_ = _wfopen(GetWideNativePath(fileName).CString(), openMode[mode]);
    #else
    handle_ = fopen(GetNativePath(fileName).CString(), openMode[mode]);
    #endif

    // If file did not exist in readwrite mode, retry with write-update mode
    if (mode == FILE_READWRITE && !handle_)
    {
        #ifdef WIN32
        handle_ = _wfopen(GetWideNativePath(fileName).CString(), openMode[mode + 1]);
        #else
        handle_ = fopen(GetNativePath(fileName).CString(), openMode[mode + 1]);
        #endif
    }
    
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
    compressed_ = false;
    readSyncNeeded_ = false;
    writeSyncNeeded_ = false;

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
    compressed_ = package->IsCompressed();
    readSyncNeeded_ = false;
    writeSyncNeeded_ = false;
    
    fseek((FILE*)handle_, offset_, SEEK_SET);
    return true;
}

unsigned File::Read(void* dest, unsigned size)
{
    #ifdef ANDROID
    if (!handle_ && !assetHandle_)
    #else
    if (!handle_)
    #endif
    {
        // Do not log the error further here to prevent spamming the stderr stream
        return 0;
    }

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
    if (compressed_)
    {
        unsigned sizeLeft = size;
        unsigned char* destPtr = (unsigned char*)dest;

        while (sizeLeft)
        {
            if (!readBuffer_ || readBufferOffset_ >= readBufferSize_)
            {
                unsigned char blockHeaderBytes[4];
                fread(blockHeaderBytes, sizeof blockHeaderBytes, 1, (FILE*)handle_);

                MemoryBuffer blockHeader(&blockHeaderBytes[0], sizeof blockHeaderBytes);
                unsigned unpackedSize = blockHeader.ReadUShort();
                unsigned packedSize = blockHeader.ReadUShort();

                if (!readBuffer_)
                {
                    readBuffer_ = new unsigned char[unpackedSize];
                    inputBuffer_ = new unsigned char[LZ4_compressBound(unpackedSize)];
                }

                /// \todo Handle errors
                fread(inputBuffer_.Get(), packedSize, 1, (FILE*)handle_);
                LZ4_decompress_fast((const char*)inputBuffer_.Get(), (char *)readBuffer_.Get(), unpackedSize);

                readBufferSize_ = unpackedSize;
                readBufferOffset_ = 0;
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

    // Need to reassign the position due to internal buffering when transitioning from writing to reading
    if (readSyncNeeded_)
    {
        fseek((FILE*)handle_, position_ + offset_, SEEK_SET);
        readSyncNeeded_ = false;
    }
    
    size_t ret = fread(dest, size, 1, (FILE*)handle_);
    if (ret != 1)
    {
        // Return to the position where the read began
        fseek((FILE*)handle_, position_ + offset_, SEEK_SET);
        LOGERROR("Error while reading from file " + GetName());
        return 0;
    }

    writeSyncNeeded_ = true;
    position_ += size;
    return size;
}

unsigned File::Seek(unsigned position)
{
    #ifdef ANDROID
    if (!handle_ && !assetHandle_)
    #else
    if (!handle_)
    #endif
    {
        // Do not log the error further here to prevent spamming the stderr stream
        return 0;
    }

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
    if (compressed_)
    {
        // Start over from the beginning
        if (position == 0)
        {
            position_ = 0;
            readBufferOffset_ = 0;
            readBufferSize_ = 0;
            fseek((FILE*)handle_, offset_, SEEK_SET);
        }
        // Skip bytes
        else if (position >= position_)
        {
            unsigned char skipBuffer[SKIP_BUFFER_SIZE];
            while (position > position_)
                Read(skipBuffer, Min((int)position - position_, (int)SKIP_BUFFER_SIZE));
        }
        else
            LOGERROR("Seeking backward in a compressed file is not supported");

        return position_;
    }

    fseek((FILE*)handle_, position + offset_, SEEK_SET);
    position_ = position;
    readSyncNeeded_ = false;
    writeSyncNeeded_ = false;
    return position_;
}

unsigned File::Write(const void* data, unsigned size)
{
    if (!handle_)
    {
        // Do not log the error further here to prevent spamming the stderr stream
        return 0;
    }

    if (mode_ == FILE_READ)
    {
        LOGERROR("File not opened for writing");
        return 0;
    }

    if (!size)
        return 0;

    // Need to reassign the position due to internal buffering when transitioning from reading to writing
    if (writeSyncNeeded_)
    {
        fseek((FILE*)handle_, position_ + offset_, SEEK_SET);
        writeSyncNeeded_ = false;
    }
    
    if (fwrite(data, size, 1, (FILE*)handle_) != 1)
    {
        // Return to the position where the write began
        fseek((FILE*)handle_, position_ + offset_, SEEK_SET);
        LOGERROR("Error while writing to file " + GetName());
        return 0;
    }

    readSyncNeeded_ = true;
    position_ += size;
    if (position_ > size_)
        size_ = position_;

    return size;
}

unsigned File::GetChecksum()
{
    if (offset_ || checksum_)
        return checksum_;
    #ifdef ANDROID
    if ((!handle_ && !assetHandle_) || mode_ == FILE_WRITE)
    #else
    if (!handle_ || mode_ == FILE_WRITE)
    #endif
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
    }
    #endif

    readBuffer_.Reset();
    inputBuffer_.Reset();

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

bool File::IsOpen() const
{
    #ifdef ANDROID
        return handle_ != 0 || assetHandle_ != 0;
    #else
        return handle_ != 0;
    #endif
}

}
