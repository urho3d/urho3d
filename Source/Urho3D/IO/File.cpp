// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Profiler.h"
#include "../IO/File.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../IO/PackageFile.h"

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
static constexpr i32 READ_BUFFER_SIZE = 32768;
#endif
static constexpr i32 SKIP_BUFFER_SIZE = 1024;

static i32 FSeek64(FILE* stream, i64 offset, i32 origin)
{
#ifdef _MSC_VER
    return _fseeki64(stream, offset, origin);
#elif defined(__APPLE__)
    return fseeko(stream, offset, origin);
#else
    return fseeko64(stream, offset, origin);
#endif
}

static i64 FTell64(FILE* stream)
{
#ifdef _MSC_VER
    return _ftelli64(stream);
#elif defined(__APPLE__)
    return ftello64(stream);
#else
    return ftello64(stream);
#endif
}

File::File(Context* context) :
    Object(context),
    mode_(FILE_READ),
    handle_(nullptr),
#ifdef __ANDROID__
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
    handle_(nullptr),
#ifdef __ANDROID__
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
    handle_(nullptr),
#ifdef __ANDROID__
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
    return OpenInternal(fileName, mode);
}

bool File::Open(PackageFile* package, const String& fileName)
{
    if (!package)
        return false;

    const PackageEntry* entry = package->GetEntry(fileName);
    if (!entry)
        return false;

    bool success = OpenInternal(package->GetName(), FILE_READ, true);
    if (!success)
    {
        URHO3D_LOGERROR("Could not open package file " + fileName);
        return false;
    }

    name_ = fileName;
    offset_ = entry->offset_;
    checksum_ = entry->checksum_;
    size_ = entry->size_;
    compressed_ = package->IsCompressed();

    // Seek to beginning of package entry's file data
    SeekInternal(offset_);
    return true;
}

i32 File::Read(void* dest, i32 size)
{
    assert(size >= 0);

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
    if (assetHandle_ && !compressed_)
    {
        // If not using a compressed package file, buffer file reads on Android for better performance
        if (!readBuffer_)
        {
            readBuffer_ = new u8[READ_BUFFER_SIZE];
            readBufferOffset_ = 0;
            readBufferSize_ = 0;
        }

        i32 sizeLeft = size;
        u8* destPtr = (u8*)dest;

        while (sizeLeft)
        {
            if (readBufferOffset_ >= readBufferSize_)
            {
                readBufferSize_ = Min(size_ - position_, READ_BUFFER_SIZE);
                readBufferOffset_ = 0;
                ReadInternal(readBuffer_.Get(), readBufferSize_);
            }

            i32 copySize = Min((readBufferSize_ - readBufferOffset_), sizeLeft);
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
        i32 sizeLeft = size;
        u8* destPtr = (u8*)dest;

        while (sizeLeft)
        {
            if (!readBuffer_ || readBufferOffset_ >= readBufferSize_)
            {
                u8 blockHeaderBytes[4];
                ReadInternal(blockHeaderBytes, sizeof blockHeaderBytes);

                MemoryBuffer blockHeader(&blockHeaderBytes[0], sizeof blockHeaderBytes);
                i32 unpackedSize = blockHeader.ReadU16();
                i32 packedSize = blockHeader.ReadU16();

                if (!readBuffer_)
                {
                    readBuffer_ = new u8[unpackedSize];
                    inputBuffer_ = new u8[LZ4_compressBound(unpackedSize)];
                }

                /// \todo Handle errors
                ReadInternal(inputBuffer_.Get(), packedSize);
                LZ4_decompress_fast((const char*)inputBuffer_.Get(), (char*)readBuffer_.Get(), unpackedSize);

                readBufferSize_ = unpackedSize;
                readBufferOffset_ = 0;
            }

            i32 copySize = Min((readBufferSize_ - readBufferOffset_), sizeLeft);
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
        SeekInternal(position_ + offset_);
        readSyncNeeded_ = false;
    }

    if (!ReadInternal(dest, size))
    {
        // Return to the position where the read began
        SeekInternal(position_ + offset_);
        URHO3D_LOGERROR("Error while reading from file " + GetName());
        return 0;
    }

    writeSyncNeeded_ = true;
    position_ += size;
    return size;
}

i64 File::Seek(i64 position)
{
    assert(position >= 0);

    if (!IsOpen())
    {
        // If file not open, do not log the error further here to prevent spamming the stderr stream
        return 0;
    }

    // Allow sparse seeks if writing
    if (mode_ == FILE_READ && position > size_)
        position = size_;

    if (compressed_)
    {
        // Start over from the beginning
        if (position == 0)
        {
            position_ = 0;
            readBufferOffset_ = 0;
            readBufferSize_ = 0;
            SeekInternal(offset_);
        }
        // Skip bytes
        else if (position >= position_)
        {
            u8 skipBuffer[SKIP_BUFFER_SIZE];
            while (position > position_)
                Read(skipBuffer, Min(position - position_, SKIP_BUFFER_SIZE));
        }
        else
            URHO3D_LOGERROR("Seeking backward in a compressed file is not supported");

        return position_;
    }

    SeekInternal(position + offset_);
    position_ = position;
    readSyncNeeded_ = false;
    writeSyncNeeded_ = false;
    return position_;
}

i32 File::Write(const void* data, i32 size)
{
    assert(size >= 0);

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
        FSeek64((FILE*)handle_, position_ + offset_, SEEK_SET);
        writeSyncNeeded_ = false;
    }

    if (fwrite(data, size, 1, (FILE*)handle_) != 1)
    {
        // Return to the position where the write began
        FSeek64((FILE*)handle_, position_ + offset_, SEEK_SET);
        URHO3D_LOGERROR("Error while writing to file " + GetName());
        return 0;
    }

    readSyncNeeded_ = true;
    position_ += size;
    if (position_ > size_)
        size_ = position_;

    return size;
}

hash32 File::GetChecksum()
{
    if (offset_ || checksum_)
        return checksum_;
#ifdef __ANDROID__
    if ((!handle_ && !assetHandle_) || mode_ == FILE_WRITE)
#else
    if (!handle_ || mode_ == FILE_WRITE)
#endif
        return 0;

    URHO3D_PROFILE(CalculateFileChecksum);

    i64 oldPos = position_;
    checksum_ = 0;

    Seek(0);
    while (!IsEof())
    {
        u8 block[1024];
        i32 readBytes = Read(block, 1024);
        for (i32 i = 0; i < readBytes; ++i)
            checksum_ = SDBMHash(checksum_, block[i]);
    }

    Seek(oldPos);
    return checksum_;
}

void File::Close()
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
        offset_ = 0;
        checksum_ = 0;
    }
}

void File::Flush()
{
    if (handle_)
        fflush((FILE*)handle_);
}

bool File::IsOpen() const
{
#ifdef __ANDROID__
    return handle_ != 0 || assetHandle_ != 0;
#else
    return handle_ != nullptr;
#endif
}

bool File::OpenInternal(const String& fileName, FileMode mode, bool fromPackage)
{
    Close();

    compressed_ = false;
    readSyncNeeded_ = false;
    writeSyncNeeded_ = false;

    auto* fileSystem = GetSubsystem<FileSystem>();
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
            name_ = fileName;
            mode_ = mode;
            position_ = 0;
            if (!fromPackage)
            {
                size_ = SDL_RWsize(assetHandle_);
                offset_ = 0;
            }
            checksum_ = 0;
            return true;
        }
    }
#endif

#ifdef _WIN32
    handle_ = _wfopen(GetWideNativePath(fileName).CString(), openMode[mode]);
#elif defined(__APPLE__)
    handle_ = fopen(GetNativePath(fileName).CString(), openMode[mode]);
#else
    handle_ = fopen64(GetNativePath(fileName).CString(), openMode[mode]);
#endif

    // If file did not exist in readwrite mode, retry with write-update mode
    if (mode == FILE_READWRITE && !handle_)
    {
#ifdef _WIN32
        handle_ = _wfopen(GetWideNativePath(fileName).CString(), openMode[mode + 1]);
#elif defined(__APPLE__)
        handle_ = fopen(GetNativePath(fileName).CString(), openMode[mode + 1]);
#else
        handle_ = fopen64(GetNativePath(fileName).CString(), openMode[mode + 1]);
#endif
    }

    if (!handle_)
    {
        URHO3D_LOGERRORF("Could not open file %s", fileName.CString());
        return false;
    }

    if (!fromPackage)
    {
        FSeek64((FILE*)handle_, 0, SEEK_END);
        i64 size = FTell64((FILE*)handle_);
        FSeek64((FILE*)handle_, 0, SEEK_SET);
        if (size > M_MAX_UNSIGNED)
        {
            URHO3D_LOGERRORF("Could not open file %s which is larger than 4GB", fileName.CString());
            Close();
            size_ = 0;
            return false;
        }
        size_ = (unsigned)size;
        offset_ = 0;
    }

    name_ = fileName;
    mode_ = mode;
    position_ = 0;
    checksum_ = 0;

    return true;
}

bool File::ReadInternal(void* dest, i32 size)
{
    assert(size >= 0);

#ifdef __ANDROID__
    if (assetHandle_)
    {
        return SDL_RWread(assetHandle_, dest, size, 1) == 1;
    }
    else
#endif
        return fread(dest, size, 1, (FILE*)handle_) == 1;
}

void File::SeekInternal(i64 newPosition)
{
    assert(newPosition >= 0);

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
    {
        FSeek64((FILE*)handle_, newPosition, SEEK_SET);
    }
}

}
