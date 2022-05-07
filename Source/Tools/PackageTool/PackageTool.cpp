// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <Urho3D/Core/Context.h>
#include <Urho3D/Container/ArrayPtr.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/IO/File.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/PackageFile.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <LZ4/lz4.h>
#include <LZ4/lz4hc.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

static const unsigned COMPRESSED_BLOCK_SIZE = 32768;

struct FileEntry
{
    String name_;
    unsigned offset_{};
    unsigned size_{};
    unsigned checksum_{};
};

SharedPtr<Context> context_(new Context());
SharedPtr<FileSystem> fileSystem_(new FileSystem(context_));
String basePath_;
Vector<FileEntry> entries_;
unsigned checksum_ = 0;
bool compress_ = false;
bool quiet_ = false;
unsigned blockSize_ = COMPRESSED_BLOCK_SIZE;

String ignoreExtensions_[] = {
    ".bak",
    ".rule",
    ""
};

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);
void Pack(const Vector<String>& arguments);
void Unpack(const Vector<String>& arguments);
void ProcessFile(const String& fileName, const String& rootDir);
void WritePackageFile(const String& fileName, const String& rootDir);
void WriteHeader(File& dest);

int main(int argc, char** argv)
{
    Vector<String> arguments;

    #ifdef WIN32
    arguments = ParseArguments(GetCommandLineW());
    #else
    arguments = ParseArguments(argc, argv);
    #endif

    Run(arguments);
    return 0;
}

static const String USAGE_STR = 
    "Usage:\n"
    "1) Packing: PackageTool -p<options> <input directory name> <output package name> [base path]\n"
    "   Options:\n"
    "     q - enable quiet mode\n"
    "     c - enable LZ4 compression\n"
    "   Base path is an optional prefix that will be added to the file entries.\n"
    "   Example: PackageTool -pqc CoreData CoreData.pak\n"
    "2) Unpacking: PackageTool -u<options> <input package name> <output directory name>\n"
    "   Options:\n"
    "     q - enable quiet mode\n"
    "   Example: PackageTool -uq CoreData.pak CoreData\n"
    "3) Print info: PackageTool -<mode> <package name>\n"
    "   Modes:\n"
    "     i - print package file information\n"
    "     l - print file names (including their paths) contained in the package\n"
    "     L - similar to l but also output compression ratio (compressed package file only)\n"
    "   Example: PackageTool -i CoreData.pak";

void Pack(const Vector<String>& arguments)
{
    if (arguments.Size() != 3 && arguments.Size() != 4)
        ErrorExit(USAGE_STR);

    const String& mode = arguments[0]; // Starts with -p

    for (unsigned i = 2; i < mode.Length(); ++i)
    {
        if (mode[i] == 'q')
            quiet_ = true;
        else if (mode[i] == 'c')
            compress_ = true;
        else
            ErrorExit("Unrecognized option");
    }

    const String& dirName = arguments[1];
    const String& packageName = arguments[2];
    
    if (arguments.Size() == 4)
        basePath_ = arguments[3];

    if (!quiet_)
        PrintLine("Scanning directory " + dirName + " for files");

    // Get the file list recursively
    Vector<String> fileNames;
    fileSystem_->ScanDir(fileNames, dirName, "*.*", SCAN_FILES, true);
    if (!fileNames.Size())
        ErrorExit("No files found");

    // Check for extensions to ignore
    for (unsigned i = fileNames.Size() - 1; i < fileNames.Size(); --i)
    {
        String extension = GetExtension(fileNames[i]);
        for (unsigned j = 0; ignoreExtensions_[j].Length(); ++j)
        {
            if (extension == ignoreExtensions_[j])
            {
                fileNames.Erase(fileNames.Begin() + i);
                break;
            }
        }
    }

    for (unsigned i = 0; i < fileNames.Size(); ++i)
        ProcessFile(fileNames[i], dirName);

    WritePackageFile(packageName, dirName);
}

void Unpack(const Vector<String>& arguments)
{
    if (arguments.Size() != 3)
        ErrorExit(USAGE_STR);

    const String& mode = arguments[0]; // Starts with -u

    for (unsigned i = 2; i < mode.Length(); ++i)
    {
        if (mode[i] == 'q')
            quiet_ = true;
        else
            ErrorExit("Unrecognized option");
    }

    const String& packageName = arguments[1];
    const String& dirName = arguments[2];

    SharedPtr<PackageFile> packageFile(new PackageFile(context_, packageName));

    char buffer[1024];

    const HashMap<String, PackageEntry>& entries = packageFile->GetEntries();
    for (HashMap<String, PackageEntry>::ConstIterator i = entries.Begin(); i != entries.End();)
    {
        HashMap<String, PackageEntry>::ConstIterator current = i++;
        String outFilePath(dirName + "/" + current->first_);
        unsigned pos = outFilePath.FindLast('/');
        if (pos == String::NPOS)
            ErrorExit("pos == String::NPOS");

        fileSystem_->CreateDir(outFilePath.Substring(0, pos));

        File packedFile(context_, packageFile, current->first_);
        if (!packedFile.IsOpen())
            ErrorExit("packedFile open failed " + current->first_);

        File outFile(context_, outFilePath, FILE_WRITE);
        if (!outFile.IsOpen())
            ErrorExit("outFile open failed " + current->first_);

        if (!quiet_)
            PrintLine("Write file: " + outFilePath);

        unsigned numRead, numWrite;
        
        while (true)
        {
            numRead = packedFile.Read(buffer, sizeof(buffer));
            if (!numRead)
            {
                packedFile.Close();
                outFile.Close();
                break;
            }

            numWrite = outFile.Write(buffer, numRead);
            if (numWrite != numRead)
                ErrorExit("numWrite != numRead");
        }
    }

    if (!quiet_)
        PrintLine("Done");
}

void PrintInfo(const Vector<String>& arguments)
{
    if (arguments.Size() != 2)
        ErrorExit(USAGE_STR);

    const String& packageName = arguments[1];
    SharedPtr<PackageFile> packageFile(new PackageFile(context_, packageName));
    bool outputCompressionRatio = false;

    switch (arguments[0][1])
    {
    case 'i':
        PrintLine("Number of files: " + String(packageFile->GetNumFiles()));
        PrintLine("File data size: " + String(packageFile->GetTotalDataSize()));
        PrintLine("Package size: " + String(packageFile->GetTotalSize()));
        PrintLine("Checksum: " + String(packageFile->GetChecksum()));
        PrintLine("Compressed: " + String(packageFile->IsCompressed() ? "yes" : "no"));
        break;
    case 'L':
        if (!packageFile->IsCompressed())
            ErrorExit("Invalid output option: -L is applicable for compressed package file only");
        outputCompressionRatio = true;
        [[fallthrough]];
    case 'l':
        {
            const HashMap<String, PackageEntry>& entries = packageFile->GetEntries();
            for (HashMap<String, PackageEntry>::ConstIterator i = entries.Begin(); i != entries.End();)
            {
                HashMap<String, PackageEntry>::ConstIterator current = i++;
                String fileEntry(current->first_);
                if (outputCompressionRatio)
                {
                    unsigned compressedSize =
                        (i == entries.End() ? packageFile->GetTotalSize() - sizeof(unsigned) : i->second_.offset_) -
                        current->second_.offset_;
                    fileEntry.AppendWithFormat("\tin: %u\tout: %u\tratio: %f", current->second_.size_, compressedSize,
                        compressedSize ? 1.f * current->second_.size_ / compressedSize : 0.f);
                }
                PrintLine(fileEntry);
            }
        }
        break;
    default:
        ErrorExit("Unrecognized output option");
    }
}

void Run(const Vector<String>& arguments)
{
    if (arguments.Size() < 2)
        ErrorExit(USAGE_STR);

    const String& mode = arguments[0];
    if (mode.Length() < 2 || mode[0] != '-')
        ErrorExit(USAGE_STR);

    if (mode[1] == 'p')
        Pack(arguments);
    else if (mode[1] == 'u')
        Unpack(arguments);
    else if (mode[1] == 'i' || mode[1] == 'l' || mode[1] == 'L')
        PrintInfo(arguments);
    else
        ErrorExit(USAGE_STR);
}

void ProcessFile(const String& fileName, const String& rootDir)
{
    String fullPath = rootDir + "/" + fileName;
    File file(context_);
    if (!file.Open(fullPath))
        ErrorExit("Could not open file " + fileName);
    if (!file.GetSize())
        return;

    FileEntry newEntry;
    newEntry.name_ = fileName;
    newEntry.offset_ = 0; // Offset not yet known
    newEntry.size_ = file.GetSize();
    newEntry.checksum_ = 0; // Will be calculated later
    entries_.Push(newEntry);
}

void WritePackageFile(const String& fileName, const String& rootDir)
{
    if (!quiet_)
        PrintLine("Writing package");

    File dest(context_);
    if (!dest.Open(fileName, FILE_WRITE))
        ErrorExit("Could not open output file " + fileName);

    // Write ID, number of files & placeholder for checksum
    WriteHeader(dest);

    for (unsigned i = 0; i < entries_.Size(); ++i)
    {
        // Write entry (correct offset is still unknown, will be filled in later)
        dest.WriteString(basePath_ + entries_[i].name_);
        dest.WriteUInt(entries_[i].offset_);
        dest.WriteUInt(entries_[i].size_);
        dest.WriteUInt(entries_[i].checksum_);
    }

    unsigned totalDataSize = 0;
    unsigned lastOffset;

    // Write file data, calculate checksums & correct offsets
    for (unsigned i = 0; i < entries_.Size(); ++i)
    {
        lastOffset = entries_[i].offset_ = dest.GetSize();
        String fileFullPath = rootDir + "/" + entries_[i].name_;

        File srcFile(context_, fileFullPath);
        if (!srcFile.IsOpen())
            ErrorExit("Could not open file " + fileFullPath);

        unsigned dataSize = entries_[i].size_;
        totalDataSize += dataSize;
        SharedArrayPtr<unsigned char> buffer(new unsigned char[dataSize]);

        if (srcFile.Read(&buffer[0], dataSize) != dataSize)
            ErrorExit("Could not read file " + fileFullPath);
        srcFile.Close();

        for (unsigned j = 0; j < dataSize; ++j)
        {
            checksum_ = SDBMHash(checksum_, buffer[j]);
            entries_[i].checksum_ = SDBMHash(entries_[i].checksum_, buffer[j]);
        }

        if (!compress_)
        {
            if (!quiet_)
                PrintLine(entries_[i].name_ + " size " + String(dataSize));
            dest.Write(&buffer[0], entries_[i].size_);
        }
        else // Compress 
        {
            SharedArrayPtr<unsigned char> compressBuffer(new unsigned char[LZ4_compressBound(blockSize_)]);

            unsigned pos = 0;

            while (pos < dataSize)
            {
                unsigned unpackedSize = blockSize_;
                if (pos + unpackedSize > dataSize)
                    unpackedSize = dataSize - pos;

                auto packedSize = (unsigned)LZ4_compress_HC((const char*)&buffer[pos], (char*)compressBuffer.Get(), unpackedSize, LZ4_compressBound(unpackedSize), 0);
                if (!packedSize)
                    ErrorExit("LZ4 compression failed for file " + entries_[i].name_ + " at offset " + String(pos));

                dest.WriteUShort((unsigned short)unpackedSize);
                dest.WriteUShort((unsigned short)packedSize);
                dest.Write(compressBuffer.Get(), packedSize);

                pos += unpackedSize;
            }

            if (!quiet_)
            {
                unsigned totalPackedBytes = dest.GetSize() - lastOffset;
                String fileEntry(entries_[i].name_);
                fileEntry.AppendWithFormat("\tin: %u\tout: %u\tratio: %f", dataSize, totalPackedBytes,
                    totalPackedBytes ? 1.f * dataSize / totalPackedBytes : 0.f);
                PrintLine(fileEntry);
            }
        }
    }

    // Write package size to the end of file to allow finding it linked to an executable file
    unsigned currentSize = dest.GetSize();
    dest.WriteUInt(currentSize + sizeof(unsigned));

    // Write header again with correct offsets & checksums
    dest.Seek(0);
    WriteHeader(dest);

    for (unsigned i = 0; i < entries_.Size(); ++i)
    {
        dest.WriteString(basePath_ + entries_[i].name_);
        dest.WriteUInt(entries_[i].offset_);
        dest.WriteUInt(entries_[i].size_);
        dest.WriteUInt(entries_[i].checksum_);
    }

    if (!quiet_)
    {
        PrintLine("Number of files: " + String(entries_.Size()));
        PrintLine("File data size: " + String(totalDataSize));
        PrintLine("Package size: " + String(dest.GetSize()));
        PrintLine("Checksum: " + String(checksum_));
        PrintLine("Compressed: " + String(compress_ ? "yes" : "no"));
    }
}

void WriteHeader(File& dest)
{
    if (!compress_)
        dest.WriteFileID("UPAK");
    else
        dest.WriteFileID("ULZ4");
    dest.WriteUInt(entries_.Size());
    dest.WriteUInt(checksum_);
}
