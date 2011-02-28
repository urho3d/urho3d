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
#include "Hash.h"
#include "Log.h"
#include "PackageFile.h"
#include "StringUtils.h"

#include <direct.h>
#include <windows.h>

#include "DebugNew.h"

static std::set<std::string> allowedDirectories;

void scanDirectoryInternal(std::vector<std::string>& result, std::string path, const std::string& startPath, const std::string& filter, unsigned flags, bool recursive);

File::File(const std::string& fileName, FileMode mode) :
    mHandle(0),
    mFileName(fileName),
    mMode(mode),
    mOffset(0),
    mChecksum(0)
{
    static const char* openMode[] =
    {
        "rb",
        "wb",
        "w+b"
    };
    
    if (!checkDirectoryAccess(getPath(mFileName)))
        EXCEPTION("Access denied to " + fileName);
    
    mHandle = fopen(getOSPath(mFileName).c_str(), openMode[mMode]);
    if (!mHandle)
        EXCEPTION("Could not open file " + fileName);
    
    fseek(mHandle, 0, SEEK_END);
    mSize = ftell(mHandle);
    fseek(mHandle, 0, SEEK_SET);
}

File::File(const PackageFile& package, const std::string& fileName) :
    mHandle(0),
    mFileName(fileName),
    mMode(FILE_READ)
{
    const PackageEntry& entry = package.getEntry(fileName);
    mOffset = entry.mOffset;
    mSize = entry.mSize;
    mChecksum = entry.mChecksum;
    
    mHandle = fopen(getOSPath(package.getName()).c_str(), "rb");
    if (!mHandle)
        EXCEPTION("Could not open package file " + fileName);
    fseek(mHandle, mOffset, SEEK_SET);
}

File::~File()
{
    close();
}

void File::read(void* dest, unsigned size)
{
    if (!size)
        return;
    
    if (mMode == FILE_WRITE)
        SAFE_EXCEPTION("File not opened for reading");
    
    if (size + mPosition > mSize)
        SAFE_EXCEPTION("Attempted to read past file end");
    
    if (!mHandle)
        SAFE_EXCEPTION("File not open");
    
    size_t ret = fread(dest, size, 1, mHandle);
    if (ret != 1)
    {
        // Return to the position where the read began
        fseek(mHandle, mPosition + mOffset, SEEK_SET);
        SAFE_EXCEPTION("Error while reading from file");
    }
    
    mPosition += size;
}

unsigned File::seek(unsigned position)
{
    if (position > mSize)
        position = mSize;
    
    if (!mHandle)
        SAFE_EXCEPTION_RET("File not open", 0);
        
    fseek(mHandle, position + mOffset, SEEK_SET);
    
    mPosition = position;
    return mPosition;
}

void File::write(const void* data, unsigned size)
{
    if (!size)
        return;
    
    if (mMode == FILE_READ)
        SAFE_EXCEPTION("File not opened for writing");
    
    if (!mHandle)
        SAFE_EXCEPTION("File not open");
    
    if (fwrite(data, size, 1, mHandle) != 1)
    {
        // Return to the position where the write began
        fseek(mHandle, mPosition + mOffset, SEEK_SET);
        SAFE_EXCEPTION("Error while writing to file");
    }
    
    mPosition += size;
    if (mPosition > mSize)
        mSize = mPosition;
}

void File::close()
{
    if (mHandle)
    {
        fclose(mHandle);
        mHandle = 0;
    }
}

void File::setName(const std::string& name)
{
    mFileName = name;
}

unsigned File::getChecksum()
{
    if ((mOffset) || (mChecksum))
        return mChecksum;
    
    unsigned oldPos = mPosition;
    mChecksum = 0;
    
    seek(0);
    while (!isEof())
        updateHash(mChecksum, readUByte());
    
    seek(oldPos);
    return mChecksum;
}

bool fileExists(const std::string& fileName)
{
    if (!checkDirectoryAccess(getPath(fileName)))
        return false;
    
    std::string fixedName = getOSPath(unfixPath(fileName), true);
    DWORD attributes = GetFileAttributes(fixedName.c_str());
    if ((attributes == INVALID_FILE_ATTRIBUTES) || (attributes & FILE_ATTRIBUTE_DIRECTORY))
        return false;
    
    return true;
}

bool directoryExists(const std::string& pathName)
{
    if (!checkDirectoryAccess(pathName))
        return false;
    
    std::string fixedName = getOSPath(unfixPath(pathName), true);
    DWORD attributes = GetFileAttributes(fixedName.c_str());
    if ((attributes == INVALID_FILE_ATTRIBUTES) || (!(attributes & FILE_ATTRIBUTE_DIRECTORY)))
        return false;
    
    return true;
}

void scanDirectory(std::vector<std::string>& result, const std::string& pathName, const std::string& filter, unsigned flags, bool recursive)
{
    result.clear();
    
    if (!checkDirectoryAccess(pathName))
        LOGERROR("Access denied to " + pathName);
    else
    {
        std::string initialPath = fixPath(pathName);
        scanDirectoryInternal(result, initialPath, initialPath, filter, flags, recursive);
    }
}

std::string getCurrentDirectory()
{
    char path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, path);
    return fixPath(std::string(path));
}

bool setCurrentDirectory(const std::string& pathName)
{
    if (!checkDirectoryAccess(pathName))
    {
        LOGERROR("Access denied to " + pathName);
        return false;
    }
    if (SetCurrentDirectory(getOSPath(pathName, true).c_str()) == FALSE)
    {
        LOGERROR("Failed to change directory to " + pathName);
        return false;
    }
    return true;
}

bool createDirectory(const std::string& pathName)
{
    if (!checkDirectoryAccess(pathName))
    {
        LOGERROR("Access denied to " + pathName);
        return false;
    }
    
    bool success = (CreateDirectory(getOSPath(pathName, true).c_str(), 0) == TRUE) || (GetLastError() == ERROR_ALREADY_EXISTS);
    if (success)
        LOGDEBUG("Created directory " + pathName);
    else
        LOGERROR("Failed to create directory " + pathName);
    
    return success;
}


void registerDirectory(const std::string& pathName)
{
    if (pathName.empty())
        return;
    
    allowedDirectories.insert(fixPath(pathName));
}

bool checkDirectoryAccess(const std::string& pathName)
{
    std::string fixedPath = fixPath(pathName);
    
    // If no allowed directories defined, succeed always
    if (allowedDirectories.empty())
        return true;
    
    // If there is any attempt to go to a parent directory, disallow
    if (fixedPath.find("..") != std::string::npos)
        return false;
    
    // Check if the path is a partial match of any of the allowed directories
    for (std::set<std::string>::const_iterator i = allowedDirectories.begin(); i != allowedDirectories.end(); ++i)
    {
        if (fixedPath.find(*i) == 0)
            return true;
    }
    
    // Not found, so disallow
    return false;
}

void splitPath(const std::string& fullPath, std::string& pathName, std::string& fileName, std::string& extension, bool lowerCaseExtension)
{
    std::string fullPathCopy = replace(fullPath, '\\', '/');
    
    size_t extPos = fullPathCopy.rfind('.');
    if (extPos != std::string::npos)
    {
        extension = fullPathCopy.substr(extPos);
        fullPathCopy = fullPathCopy.substr(0, extPos);
    }
    else
        extension = "";
    
    size_t pathPos = fullPathCopy.rfind('/');
    if (pathPos != std::string::npos)
    {
        fileName = fullPathCopy.substr(pathPos + 1);
        pathName = fullPathCopy.substr(0, pathPos + 1);
    }
    else
    {
        fileName = fullPathCopy;
        pathName = "";
    }
    
    if (lowerCaseExtension)
        extension = toLower(extension);
}

std::string getPath(const std::string& fullPath)
{
    std::string path, file, extension;
    splitPath(fullPath, path, file, extension);
    return path;
}

std::string getFileName(const std::string& fullPath)
{
    std::string path, file, extension;
    splitPath(fullPath, path, file, extension);
    return file;
}

std::string getExtension(const std::string& fullPath, bool lowerCaseExtension)
{
    std::string path, file, extension;
    splitPath(fullPath, path, file, extension, lowerCaseExtension);
    return extension;
}

std::string getFileNameAndExtension(const std::string& fileName, bool lowerCaseExtension)
{
    std::string path, file, extension;
    splitPath(fileName, path, file, extension, lowerCaseExtension);
    return file + extension;
}

std::string fixPath(const std::string& path)
{
    std::string ret;
    
    if (!path.empty())
    {
        ret = path;
        char last = path[path.length() - 1];
        if ((last != '/') && (last != '\\'))
            ret += '/';
    }
    
    return replace(ret, '\\', '/');
}

std::string unfixPath(const std::string& path)
{
    if (!path.empty())
    {
        char last = path[path.length() - 1];
        if ((last == '/') || (last == '\\'))
            return path.substr(0, path.length() - 1);
    }
    
    return path;
}

std::string getOSPath(const std::string& pathName, bool forNativeApi)
{
    // On MSVC, replace slash always with backslash. On MinGW only if going to do Win32 native calls
#ifdef _MSC_VER
    forNativeApi = true;
#endif
    
    if (forNativeApi)
        return replace(pathName, '/', '\\');
    else
        return pathName;
}

void scanDirectoryInternal(std::vector<std::string>& result, std::string path, const std::string& startPath, const std::string& filter, unsigned flags, bool recursive)
{
    path = fixPath(path);
    std::string pathAndFilter = getOSPath(path + filter, true);
    std::string deltaPath;
    if (path.length() > startPath.length())
        deltaPath = path.substr(startPath.length());
    
    WIN32_FIND_DATA info;
    HANDLE handle = FindFirstFile(pathAndFilter.c_str(), &info);
    if (handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            std::string fileName((const char*)&info.cFileName[0]);
            if (!fileName.empty())
            {
                if ((info.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && (!(flags & SCAN_HIDDEN)))
                    continue;
                if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (flags & SCAN_DIRECTORIES)
                        result.push_back(path + fileName);
                    if ((recursive) && (fileName != ".") && (fileName != ".."))
                        scanDirectoryInternal(result, path + fileName, startPath, filter, flags, recursive);
                }
                else if (flags & SCAN_FILES)
                    result.push_back(deltaPath + fileName);
            }
        } 
        while (FindNextFile(handle, &info));
        
        FindClose(handle);
    }
}
