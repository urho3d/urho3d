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

#include "Exception.h"
#include "File.h"
#include "Hash.h"
#include "SharedArrayPtr.h"
#include "StringUtils.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "DebugNew.h"

int main(int argc, char** argv);
void run(const std::vector<std::string>& arguments);
void processFile(const std::string& fileName, const std::string& rootDir);
void writePackageFile(const std::string& fileName, const std::string& rootDir);
void errorExit(const std::string& error);

struct FileEntry
{
    std::string mName;
    unsigned mOffset;
    unsigned mSize;
    unsigned mChecksum;
};

std::string gBasePath;
std::vector<FileEntry> gEntries;
unsigned gChecksum = 0;

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    
    for (int i = 1; i < argc; ++i)
        arguments.push_back(std::string(argv[i]));
    
    try
    {
        run(arguments);
    }
    catch (Exception& e)
    {
        std::cout << e.whatStr() << std::endl;
        return 1;
    }
    
    return 0;
}

void run(const std::vector<std::string>& arguments)
{
    if (arguments.size() < 2)
        errorExit("Usage: PackageTool <directory to process> <package name> [basepath]");
    
    const std::string& dirName = arguments[0];
    const std::string& packageName = arguments[1];
    if (arguments.size() > 2)
        gBasePath = fixPath(arguments[2]);
    
   // Get the file list recursively
    std::vector<std::string> fileNames;
    scanDirectory(fileNames, dirName, "*.*", SCAN_FILES, true);
    if (!fileNames.size())
        errorExit("No files found");
    for (unsigned i = 0; i < fileNames.size(); ++i)
        processFile(fileNames[i], dirName);
    
    writePackageFile(packageName, dirName);
}

void processFile(const std::string& fileName, const std::string& rootDir)
{
    std::string fullPath = rootDir + "/" + fileName;
    File file(fullPath);
    if (!file.getSize())
        return;
    
    FileEntry newEntry;
    newEntry.mName = fileName;
    newEntry.mOffset = 0; // Offset not yet known
    newEntry.mSize = file.getSize();
    newEntry.mChecksum = 0; // Will be calculated later
    gEntries.push_back(newEntry);
}

void writePackageFile(const std::string& fileName, const std::string& rootDir)
{
    std::cout << "Writing package" << std::endl;
    
    File dest(fileName, FILE_WRITE);
    
    // Write number of files & placeholder for checksum
    dest.writeUInt(gEntries.size());
    dest.writeUInt(gChecksum);
    
    for (unsigned i = 0; i < gEntries.size(); ++i)
    {
        // Write entry (correct offset is still unknown, will be filled in later)
        dest.writeString(gEntries[i].mName);
        dest.writeUInt(gEntries[i].mOffset);
        dest.writeUInt(gEntries[i].mSize);
        dest.writeUInt(gEntries[i].mChecksum);
    }
    
    // Write file data, calculate checksums & correct offsets
    for (unsigned i = 0; i < gEntries.size(); ++i)
    {
        gEntries[i].mOffset = dest.getSize();
        std::string fileFullPath = getOSPath(rootDir + "/" + gEntries[i].mName);
        FILE* handle = fopen(fileFullPath.c_str(), "rb");
        if (!handle)
            errorExit("Could not open file " + fileFullPath);
        SharedArrayPtr<unsigned char> buffer(new unsigned char[gEntries[i].mSize]);
        if (fread(&buffer[0], gEntries[i].mSize, 1, handle) != 1)
            errorExit("Could not read file " + fileFullPath);
        
        for (unsigned j = 0; j < gEntries[i].mSize; ++j)
        {
            updateHash(gChecksum, buffer[j]);
            updateHash(gEntries[i].mChecksum, buffer[j]);
        }
        
        fclose(handle);
        dest.write(&buffer[0], gEntries[i].mSize);
    }
    
    // Write header again with correct offsets & checksums
    dest.seek(0);
    dest.writeUInt(gEntries.size());
    dest.writeUInt(gChecksum);
    
    for (unsigned i = 0; i < gEntries.size(); ++i)
    {
        dest.writeString(gEntries[i].mName);
        dest.writeUInt(gEntries[i].mOffset);
        dest.writeUInt(gEntries[i].mSize);
        dest.writeUInt(gEntries[i].mChecksum);
    }
    
    std::cout << "Package total size " << dest.getSize() << " bytes" << std::endl;
}

void errorExit(const std::string& error)
{
    throw Exception(error);
}
