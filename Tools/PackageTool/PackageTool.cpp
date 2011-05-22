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

#include "Context.h"
#include "File.h"
#include "FileSystem.h"
#include "ProcessUtils.h"
#include "SharedArrayPtr.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <Windows.h>

#include "DebugNew.h"

struct FileEntry
{
    String name_;
    unsigned offset_;
    unsigned size_;
    unsigned checksum_;
};

SharedPtr<Context> context_(new Context());
SharedPtr<FileSystem> fileSystem_(new FileSystem(context_));
String basePath_;
Vector<FileEntry> entries_;
unsigned checksum_ = 0;

String ignoreExtensions_[] = {
    ".bak",
    ".rule",
    ""
};

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);
void ProcessFile(const String& fileName, const String& rootDir);
void WritePackageFile(const String& fileName, const String& rootDir);

int main(int argc, char** argv)
{
    Vector<String> arguments;
    
    for (int i = 1; i < argc; ++i)
        arguments.Push(String(argv[i]));
    
    Run(arguments);
    return 0;
}

void Run(const Vector<String>& arguments)
{
    if (arguments.Size() < 2)
        ErrorExit("Usage: PackageTool <directory to process> <package name> [basepath]\n");
    
    const String& dirName = arguments[0];
    const String& packageName = arguments[1];
    if (arguments.Size() > 2)
        basePath_ = AddTrailingSlash(arguments[2]);
    
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
    PrintLine("Writing package");
    
    File dest(context_);
    if (!dest.Open(fileName, FILE_WRITE))
        ErrorExit("Could not open output file " + fileName);
    
    // Write ID, number of files & placeholder for checksum
    dest.WriteID("UPAK");
    dest.WriteUInt(entries_.Size());
    dest.WriteUInt(checksum_);
    
    for (unsigned i = 0; i < entries_.Size(); ++i)
    {
        // Write entry (correct offset is still unknown, will be filled in later)
        dest.WriteString(entries_[i].name_);
        dest.WriteUInt(entries_[i].offset_);
        dest.WriteUInt(entries_[i].size_);
        dest.WriteUInt(entries_[i].checksum_);
    }
    
    // Write file data, calculate checksums & correct offsets
    for (unsigned i = 0; i < entries_.Size(); ++i)
    {
        entries_[i].offset_ = dest.GetSize();
        String fileFullPath = rootDir + "/" + entries_[i].name_;
        
        File srcFile(context_, fileFullPath);
        if (!srcFile.IsOpen())
            ErrorExit("Could not open file " + fileFullPath);
        
        unsigned dataSize = entries_[i].size_;
        SharedArrayPtr<unsigned char> buffer(new unsigned char[dataSize]);
        
        if (srcFile.Read(&buffer[0], dataSize) != dataSize)
            ErrorExit("Could not read file " + fileFullPath);
        srcFile.Close();
        
        for (unsigned j = 0; j < dataSize; ++j)
        {
            checksum_ = SDBMHash(checksum_, buffer[j]);
            entries_[i].checksum_ = SDBMHash(entries_[i].checksum_, buffer[j]);
        }
        
        dest.Write(&buffer[0], entries_[i].size_);
    }
    
    // Write header again with correct offsets & checksums
    dest.Seek(0);
    dest.WriteID("UPAK");
    dest.WriteUInt(entries_.Size());
    dest.WriteUInt(checksum_);
    
    for (unsigned i = 0; i < entries_.Size(); ++i)
    {
        dest.WriteString(entries_[i].name_);
        dest.WriteUInt(entries_[i].offset_);
        dest.WriteUInt(entries_[i].size_);
        dest.WriteUInt(entries_[i].checksum_);
    }
    
    PrintLine("Package total size " + String(dest.GetSize()) + " bytes");
}
