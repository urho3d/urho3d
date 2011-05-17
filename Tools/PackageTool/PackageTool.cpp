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
#include "StringUtils.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
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
std::vector<FileEntry> entries_;
unsigned checksum_ = 0;

String ignoreExtensions_[] = {
    ".bak",
    ".rule",
    ""
};

int main(int argc, char** argv);
void Run(const std::vector<String>& arguments);
void ProcessFile(const String& fileName, const String& rootDir);
void WritePackageFile(const String& fileName, const String& rootDir);

int main(int argc, char** argv)
{
    std::vector<String> arguments;
    
    for (int i = 1; i < argc; ++i)
        arguments.push_back(String(argv[i]));
    
    Run(arguments);
    return 0;
}

void Run(const std::vector<String>& arguments)
{
    if (arguments.size() < 2)
        ErrorExit("Usage: PackageTool <directory to process> <package name> [basepath]\n");
    
    const String& dirName = arguments[0];
    const String& packageName = arguments[1];
    if (arguments.size() > 2)
        basePath_ = AddTrailingSlash(arguments[2]);
    
   // Get the file list recursively
    std::vector<String> fileNames;
    fileSystem_->ScanDir(fileNames, dirName, "*.*", SCAN_FILES, true);
    if (!fileNames.size())
        ErrorExit("No files found");
    
    // Check for extensions to ignore
    for (unsigned i = fileNames.size() - 1; i < fileNames.size(); --i)
    {
        String extension = GetExtension(fileNames[i]);
        for (unsigned j = 0; ignoreExtensions_[j].Length(); ++j)
        {
            if (extension == ignoreExtensions_[j])
            {
                fileNames.erase(fileNames.begin() + i);
                break;
            }
        }
    }
    
    for (unsigned i = 0; i < fileNames.size(); ++i)
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
    newEntry.checksum_ = 0; // Will be Calculated later
    entries_.push_back(newEntry);
}

void WritePackageFile(const String& fileName, const String& rootDir)
{
    PrintLine("Writing package");
    
    File dest(context_);
    if (!dest.Open(fileName, FILE_WRITE))
        ErrorExit("Could not open output file " + fileName);
    
    // Write ID, number of files & placeholder for checksum
    dest.WriteID("UPAK");
    dest.WriteUInt(entries_.size());
    dest.WriteUInt(checksum_);
    
    for (unsigned i = 0; i < entries_.size(); ++i)
    {
        // Write entry (correct offset is still unknown, will be filled in later)
        dest.WriteString(entries_[i].name_);
        dest.WriteUInt(entries_[i].offset_);
        dest.WriteUInt(entries_[i].size_);
        dest.WriteUInt(entries_[i].checksum_);
    }
    
    // Write file data, Calculate checksums & correct offsets
    for (unsigned i = 0; i < entries_.size(); ++i)
    {
        entries_[i].offset_ = dest.GetSize();
        String fileFullPath = GetNativePath(rootDir + "/" + entries_[i].name_);
        FILE* handle = fopen(fileFullPath.CString(), "rb");
        if (!handle)
            ErrorExit("Could not open file " + fileFullPath);
        SharedArrayPtr<unsigned char> buffer(new unsigned char[entries_[i].size_]);
        if (fread(&buffer[0], entries_[i].size_, 1, handle) != 1)
            ErrorExit("Could not read file " + fileFullPath);
        
        for (unsigned j = 0; j < entries_[i].size_; ++j)
        {
            checksum_ = SDBMHash(checksum_, buffer[j]);
            entries_[i].checksum_ = SDBMHash(entries_[i].checksum_, buffer[j]);
        }
        
        fclose(handle);
        dest.Write(&buffer[0], entries_[i].size_);
    }
    
    // Write header again with correct offsets & checksums
    dest.Seek(0);
    dest.WriteID("UPAK");
    dest.WriteUInt(entries_.size());
    dest.WriteUInt(checksum_);
    
    for (unsigned i = 0; i < entries_.size(); ++i)
    {
        dest.WriteString(entries_[i].name_);
        dest.WriteUInt(entries_[i].offset_);
        dest.WriteUInt(entries_[i].size_);
        dest.WriteUInt(entries_[i].checksum_);
    }
    
    PrintLine("Package total size " + ToString(dest.GetSize()) + " bytes");
}
