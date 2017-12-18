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

#include "../Precompiled.h"

#include "../Core/Profiler.h"
#include "../IO/SystemFile.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"

#ifdef __ANDROID__
#include <SDL/SDL_rwops.h>
#endif

#include <cstdio>
#include <LZ4/lz4.h>

#include "../DebugNew.h"

namespace Urho3D
{

#ifdef _WIN32
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

#ifdef __ANDROID__
const char* APK = "/apk/";
static const unsigned READ_BUFFER_SIZE = 32768;
#endif
static const unsigned SKIP_BUFFER_SIZE = 1024;

SystemFile::SystemFile(Context* context) :
    File(context),
    handle_(nullptr),
#ifdef __ANDROID__
    assetHandle_(0),
#endif
    readBufferOffset_(0),
    readBufferSize_(0),
    checksum_(0),
    readSyncNeeded_(false),
    writeSyncNeeded_(false)
{
}

SystemFile::SystemFile(Context* context, const String& fileName, FileMode mode) :
    File(context),
    handle_(nullptr),
#ifdef __ANDROID__
    assetHandle_(0),
#endif
    readBufferOffset_(0),
    readBufferSize_(0),
    checksum_(0),
    readSyncNeeded_(false),
    writeSyncNeeded_(false)
{
    Open(fileName, mode);
}

SystemFile::~SystemFile()
{
    Close();
}

bool SystemFile::Open(const String& fileName, FileMode mode)
{
    return OpenInternal(fileName, mode);
}

unsigned SystemFile::Read(void* dest, unsigned size)
{
    if (!IsOpen())
    {
        // If file not open, do not log the error further here to prevent spamming the stderr stream
        return 0;
    }

    if (mode_ == FILE_WRITE)
    {
        URHO3D_LOGERROR("File not opened for reading");
        return 0;
    }

    if (size + position_ > size_)
        size = size_ - position_;
    if (!size)
        return 0;

#ifdef __ANDROID__
    if (assetHandle_)
    {
        // Buffer file reads on Android for better performance
        if (!readBuffer_)
        {
            readBuffer_ = new unsigned char[READ_BUFFER_SIZE];
            readBufferOffset_ = 0;
            readBufferSize_ = 0;
        }

        unsigned sizeLeft = size;
        unsigned char* destPtr = (unsigned char*)dest;

        while (sizeLeft)
        {
            if (readBufferOffset_ >= readBufferSize_)
            {
                readBufferSize_ = Min(size_ - position_, READ_BUFFER_SIZE);
                readBufferOffset_ = 0;
                ReadInternal(readBuffer_.Get(), readBufferSize_);
            }

            unsigned copySize = Min((readBufferSize_ - readBufferOffset_), sizeLeft);
            memcpy(destPtr, readBuffer_.Get() + readBufferOffset_, copySize);
            destPtr += copySize;
            sizeLeft -= copySize;
            readBufferOffset_ += copySize;
            position_ += copySize;
        }

        return size;
    }
#endif


    // Need to reassign the position due to internal buffering when transitioning from writing to reading
    if (readSyncNeeded_)
    {
        SeekInternal(position_);
        readSyncNeeded_ = false;
    }

    if (!ReadInternal(dest, size))
    {
        // Return to the position where the read began
        SeekInternal(position_);
        URHO3D_LOGERROR("Error while reading from file " + GetName());
        return 0;
    }

    writeSyncNeeded_ = true;
    position_ += size;
    return size;
}

unsigned SystemFile::Seek(unsigned position)
{
    if (!IsOpen())
    {
        // If file not open, do not log the error further here to prevent spamming the stderr stream
        return 0;
    }

    // Allow sparse seeks if writing
    if (mode_ == FILE_READ && position > size_)
        position = size_;

    SeekInternal(position);
    position_ = position;
    readSyncNeeded_ = false;
    writeSyncNeeded_ = false;
    return position_;
}

unsigned SystemFile::Write(const void* data, unsigned size)
{
    if (!IsOpen())
    {
        // If file not open, do not log the error further here to prevent spamming the stderr stream
        return 0;
    }

    if (mode_ == FILE_READ)
    {
        URHO3D_LOGERROR("File not opened for writing");
        return 0;
    }

    if (!size)
        return 0;

    // Need to reassign the position due to internal buffering when transitioning from reading to writing
    if (writeSyncNeeded_)
    {
        fseek((FILE*)handle_, position_, SEEK_SET);
        writeSyncNeeded_ = false;
    }

    if (fwrite(data, size, 1, (FILE*)handle_) != 1)
    {
        // Return to the position where the write began
        fseek((FILE*)handle_, position_, SEEK_SET);
        URHO3D_LOGERROR("Error while writing to file " + GetName());
        return 0;
    }

    readSyncNeeded_ = true;
    position_ += size;
    if (position_ > size_)
        size_ = position_;

    return size;
}

unsigned SystemFile::GetChecksum()
{
    if (checksum_)
        return checksum_;
#ifdef __ANDROID__
    if ((!handle_ && !assetHandle_) || mode_ == FILE_WRITE)
#else
    if (!handle_ || mode_ == FILE_WRITE)
#endif
        return 0;

    URHO3D_PROFILE(CalculateFileChecksum);

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

void SystemFile::Close()
{
#ifdef __ANDROID__
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
        handle_ = nullptr;
        position_ = 0;
        size_ = 0;
        checksum_ = 0;
    }
}

void SystemFile::Flush()
{
    if (handle_)
        fflush((FILE*)handle_);
}

bool SystemFile::IsOpen() const
{
#ifdef __ANDROID__
    return handle_ != 0 || assetHandle_ != 0;
#else
    return handle_ != nullptr;
#endif
}

bool SystemFile::OpenInternal(const String& fileName, FileMode mode)
{
    Close();

    readSyncNeeded_ = false;
    writeSyncNeeded_ = false;
    
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem && !fileSystem->CheckAccess(GetPath(fileName)))
    {
        URHO3D_LOGERRORF("Access denied to %s", fileName.CString());
        return false;
    }

    if (fileName.Empty())
    {
        URHO3D_LOGERROR("Could not open file with empty name");
        return false;
    }

#ifdef __ANDROID__
    if (URHO3D_IS_ASSET(fileName))
    {
        if (mode != FILE_READ)
        {
            URHO3D_LOGERROR("Only read mode is supported for Android asset files");
            return false;
        }

        assetHandle_ = SDL_RWFromFile(URHO3D_ASSET(fileName), "rb");
        if (!assetHandle_)
        {
            URHO3D_LOGERRORF("Could not open Android asset file %s", fileName.CString());
            return false;
        }
        else
        {
            fileName_ = fileName;
            mode_ = mode;
            position_ = 0;
            size_ = SDL_RWsize(assetHandle_);
            checksum_ = 0;
            return true;
        }
    }
#endif

#ifdef _WIN32
    handle_ = _wfopen(GetWideNativePath(fileName).CString(), openMode[mode]);
#else
    handle_ = fopen(GetNativePath(fileName).CString(), openMode[mode]);
#endif

    // If file did not exist in readwrite mode, retry with write-update mode
    if (mode == FILE_READWRITE && !handle_)
    {
#ifdef _WIN32
        handle_ = _wfopen(GetWideNativePath(fileName).CString(), openMode[mode + 1]);
#else
        handle_ = fopen(GetNativePath(fileName).CString(), openMode[mode + 1]);
#endif
    }

    if (!handle_)
    {
        URHO3D_LOGERRORF("Could not open file %s", fileName.CString());
        return false;
    }

    fseek((FILE*)handle_, 0, SEEK_END);
    long size = ftell((FILE*)handle_);
    fseek((FILE*)handle_, 0, SEEK_SET);
    if (size > M_MAX_UNSIGNED)
    {
        URHO3D_LOGERRORF("Could not open file %s which is larger than 4GB", fileName.CString());
        Close();
        size_ = 0;
        return false;
    }
    size_ = (unsigned)size;

    fileName_ = fileName;
    mode_ = mode;
    position_ = 0;
    checksum_ = 0;

    return true;
}

bool SystemFile::ReadInternal(void* dest, unsigned size)
{
#ifdef __ANDROID__
    if (assetHandle_)
    {
        return SDL_RWread(assetHandle_, dest, size, 1) == 1;
    }
    else
#endif
        return fread(dest, size, 1, (FILE*)handle_) == 1;
}

void SystemFile::SeekInternal(unsigned newPosition)
{
#ifdef __ANDROID__
    if (assetHandle_)
    {
        SDL_RWseek(assetHandle_, newPosition, SEEK_SET);
        // Reset buffering after seek
        readBufferOffset_ = 0;
        readBufferSize_ = 0;
    }
    else
#endif
        fseek((FILE*)handle_, newPosition, SEEK_SET);
}

}
