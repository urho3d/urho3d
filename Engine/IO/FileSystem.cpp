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
#include "Context.h"
#include "File.h"
#include "FileSystem.h"
#include "Log.h"
#include "SharedArrayPtr.h"
#include "StringUtils.h"

#include <direct.h>
#include <process.h>
#include <windows.h>
#include <shellapi.h>

// Enable SHGetSpecialFolderPath on MinGW
#ifndef _MSC_VER
#define _WIN32_IE 0x0400
#endif
#include <shlobj.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(FileSystem);

FileSystem::FileSystem(Context* context) :
    Object(context)
{
}

FileSystem::~FileSystem()
{
}


bool FileSystem::SetCurrentDir(const std::string& pathName)
{
    if (!CheckAccess(pathName))
    {
        LOGERROR("Access denied to " + pathName);
        return false;
    }
    if (SetCurrentDirectory(GetNativePath(pathName, true).c_str()) == FALSE)
    {
        LOGERROR("Failed to change directory to " + pathName);
        return false;
    }
    return true;
}

bool FileSystem::CreateDir(const std::string& pathName)
{
    if (!CheckAccess(pathName))
    {
        LOGERROR("Access denied to " + pathName);
        return false;
    }
    
    bool success = (CreateDirectory(GetNativePath(RemoveTrailingSlash(pathName), true).c_str(), 0) == TRUE) || (GetLastError() == ERROR_ALREADY_EXISTS);
    if (success)
        LOGDEBUG("Created directory " + pathName);
    else
        LOGERROR("Failed to create directory " + pathName);
    
    return success;
}

int FileSystem::SystemCommand(const std::string& commandLine)
{
    if (allowedPaths_.empty())
        return system(commandLine.c_str());
    else
    {
        LOGERROR("Executing an external command is not allowed");
        return -1;
    }
}

int FileSystem::SystemRun(const std::string& fileName, const std::vector<std::string>& arguments)
{
    if (allowedPaths_.empty())
    {
        std::string fixedFileName = GetNativePath(fileName, true);
        
        std::vector<const char*> argPtrs;
        argPtrs.push_back(fixedFileName.c_str());
        for (unsigned i = 0; i < arguments.size(); ++i)
            argPtrs.push_back(arguments[i].c_str());
        argPtrs.push_back(0);
        
        return _spawnv(_P_WAIT, fixedFileName.c_str(), &argPtrs[0]);
    }
    else
    {
        LOGERROR("Executing an external command is not allowed");
        return -1;
    }
}

bool FileSystem::SystemOpen(const std::string& fileName, const std::string& mode)
{
    if (allowedPaths_.empty())
    {
        if ((!FileExists(fileName)) && (!DirExists(fileName)))
        {
            LOGERROR("File or directory " + fileName + " not found");
            return false;
        }
        
        bool success = (int)ShellExecute(0, !mode.empty() ? (char*)mode.c_str() : 0, (char*)GetNativePath(fileName, true).c_str(), 0, 0, SW_SHOW) > 32;
        if (!success)
            LOGERROR("Failed to open " + fileName + " externally");
        return success;
    }
    else
    {
        LOGERROR("Opening a file externally is not allowed");
        return false;
    }
}

bool FileSystem::Copy(const std::string& srcFileName, const std::string& destFileName)
{
    if (!CheckAccess(GetPath(srcFileName)))
    {
        LOGERROR("Access denied to " + srcFileName);
        return false;
    }
    if (!CheckAccess(GetPath(destFileName)))
    {
        LOGERROR("Access denied to " + destFileName);
        return false;
    }
    
    SharedPtr<File> srcFile(new File(context_, srcFileName, FILE_READ));
    SharedPtr<File> destFile(new File(context_, destFileName, FILE_WRITE));
    if ((!srcFile->IsOpen()) || (!destFile->IsOpen()))
        return false;
    
    unsigned fileSize = srcFile->GetSize();
    
    SharedArrayPtr<unsigned char> buffer(new unsigned char[fileSize]);
    unsigned bytesRead = srcFile->Read(buffer.GetPtr(), fileSize);
    unsigned bytesWritten = destFile->Write(buffer.GetPtr(), fileSize);
    
    return (bytesRead == fileSize) && (bytesWritten == fileSize);
}

bool FileSystem::Rename(const std::string& srcFileName, const std::string& destFileName)
{
    if (!CheckAccess(GetPath(srcFileName)))
    {
        LOGERROR("Access denied to " + srcFileName);
        return false;
    }
    if (!CheckAccess(GetPath(destFileName)))
    {
        LOGERROR("Access denied to " + destFileName);
        return false;
    }
    
    return rename(GetNativePath(srcFileName).c_str(), GetNativePath(destFileName).c_str()) == 0;
}

bool FileSystem::Delete(const std::string& fileName)
{
    if (!CheckAccess(GetPath(fileName)))
    {
        LOGERROR("Access denied to " + fileName);
        return false;
    }
    
    return remove(GetNativePath(fileName).c_str()) == 0;
}


std::string FileSystem::GetCurrentDir()
{
    char path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, path);
    return AddTrailingSlash(std::string(path));
}

bool FileSystem::CheckAccess(const std::string& pathName)
{
    std::string fixedPath = AddTrailingSlash(pathName);
    
    // If no allowed directories defined, succeed always
    if (allowedPaths_.empty())
        return true;
    
    // If there is any attempt to go to a parent directory, disallow
    if (fixedPath.find("..") != std::string::npos)
        return false;
    
    // Check if the path is a partial match of any of the allowed directories
    for (std::set<std::string>::const_iterator i = allowedPaths_.begin(); i != allowedPaths_.end(); ++i)
    {
        if (fixedPath.find(*i) == 0)
            return true;
    }
    
    // Not found, so disallow
    return false;
}

bool FileSystem::FileExists(const std::string& fileName)
{
    if (!CheckAccess(GetPath(fileName)))
        return false;
    
    std::string fixedName = GetNativePath(RemoveTrailingSlash(fileName), true);
    DWORD attributes = GetFileAttributes(fixedName.c_str());
    if ((attributes == INVALID_FILE_ATTRIBUTES) || (attributes & FILE_ATTRIBUTE_DIRECTORY))
        return false;
    
    return true;
}

bool FileSystem::DirExists(const std::string& pathName)
{
    if (!CheckAccess(pathName))
        return false;
    
    std::string fixedName = GetNativePath(RemoveTrailingSlash(pathName), true);
    DWORD attributes = GetFileAttributes(fixedName.c_str());
    if ((attributes == INVALID_FILE_ATTRIBUTES) || (!(attributes & FILE_ATTRIBUTE_DIRECTORY)))
        return false;
    
    return true;
}

void FileSystem::ScanDir(std::vector<std::string>& result, const std::string& pathName, const std::string& filter, unsigned flags, bool recursive)
{
    result.clear();
    
    if (CheckAccess(pathName))
    {
        std::string initialPath = AddTrailingSlash(pathName);
        ScanDirInternal(result, initialPath, initialPath, filter, flags, recursive);
    }
}

std::string FileSystem::GetProgramDir()
{
    char exeName[MAX_PATH];
    exeName[0] = 0;
    GetModuleFileName(0, exeName, MAX_PATH);
    return GetPath(std::string(exeName));
}

std::string FileSystem::GetUserDocumentsDir()
{
    char pathName[MAX_PATH];
    pathName[0] = 0;
    SHGetSpecialFolderPath(0, pathName, CSIDL_PERSONAL, 0);
    return AddTrailingSlash(std::string(pathName));
}

std::string FileSystem::GetSystemFontDir()
{
    char pathName[MAX_PATH];
    if (!ExpandEnvironmentStrings("%WinDir%", pathName, MAX_PATH))
        return std::string();
    return AddTrailingSlash(std::string(pathName)) + "Fonts";
}

void FileSystem::RegisterPath(const std::string& pathName)
{
    if (pathName.empty())
        return;
    
    allowedPaths_.insert(AddTrailingSlash(pathName));
}

void FileSystem::ScanDirInternal(std::vector<std::string>& result, std::string path, const std::string& startPath,
    const std::string& filter, unsigned flags, bool recursive)
{
    path = AddTrailingSlash(path);
    std::string pathAndFilter = GetNativePath(path + filter, true);
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
                    if (flags & SCAN_DIRS)
                        result.push_back(deltaPath + fileName);
                    if ((recursive) && (fileName != ".") && (fileName != ".."))
                        ScanDirInternal(result, path + fileName, startPath, filter, flags, recursive);
                }
                else if (flags & SCAN_FILES)
                    result.push_back(deltaPath + fileName);
            }
        } 
        while (FindNextFile(handle, &info));
        
        FindClose(handle);
    }
}

void SplitPath(const std::string& fullPath, std::string& pathName, std::string& fileName, std::string& extension)
{
    std::string fullPathCopy = Replace(fullPath, '\\', '/');
    
    size_t extPos = fullPathCopy.rfind('.');
    if (extPos != std::string::npos)
    {
        extension = ToLower(fullPathCopy.substr(extPos));
        fullPathCopy = fullPathCopy.substr(0, extPos);
    }
    else
        extension.clear();
    
    size_t pathPos = fullPathCopy.rfind('/');
    if (pathPos != std::string::npos)
    {
        fileName = fullPathCopy.substr(pathPos + 1);
        pathName = fullPathCopy.substr(0, pathPos + 1);
    }
    else
    {
        fileName = fullPathCopy;
        pathName.clear();
    }
}

std::string GetPath(const std::string& fullPath)
{
    std::string path, file, extension;
    SplitPath(fullPath, path, file, extension);
    return path;
}

std::string GetFileName(const std::string& fullPath)
{
    std::string path, file, extension;
    SplitPath(fullPath, path, file, extension);
    return file;
}

std::string GetExtension(const std::string& fullPath)
{
    std::string path, file, extension;
    SplitPath(fullPath, path, file, extension);
    return extension;
}

std::string GetFileNameAndExtension(const std::string& fileName)
{
    std::string path, file, extension;
    SplitPath(fileName, path, file, extension);
    return file + extension;
}

std::string AddTrailingSlash(const std::string& path)
{
    std::string ret;
    
    if (!path.empty())
    {
        ret = path;
        char last = path[path.length() - 1];
        if ((last != '/') && (last != '\\'))
            ret += '/';
    }
    
    return Replace(ret, '\\', '/');
}

std::string RemoveTrailingSlash(const std::string& path)
{
    if (!path.empty())
    {
        char last = path[path.length() - 1];
        if ((last == '/') || (last == '\\'))
            return path.substr(0, path.length() - 1);
    }
    
    return path;
}

std::string GetParentPath(const std::string& path)
{
    unsigned pos = RemoveTrailingSlash(path).rfind('/');
    if (pos != std::string::npos)
        return path.substr(0, pos + 1);
    else
        return path;
}

std::string GetNativePath(const std::string& pathName, bool forNativeApi)
{
    // On MSVC, replace slash always with backslash. On MinGW only if going to do Win32 native calls
#ifdef _MSC_VER
    forNativeApi = true;
#endif
    
    if (forNativeApi)
        return Replace(pathName, '/', '\\');
    else
        return pathName;
}
