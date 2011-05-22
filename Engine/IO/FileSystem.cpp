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

#include <cstdio>
#include <direct.h>
#include <process.h>
#include <Windows.h>
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


bool FileSystem::SetCurrentDir(const String& pathName)
{
    if (!CheckAccess(pathName))
    {
        LOGERROR("Access denied to " + pathName);
        return false;
    }
    if (SetCurrentDirectory(GetNativePath(pathName, true).CString()) == FALSE)
    {
        LOGERROR("Failed to change directory to " + pathName);
        return false;
    }
    return true;
}

bool FileSystem::CreateDir(const String& pathName)
{
    if (!CheckAccess(pathName))
    {
        LOGERROR("Access denied to " + pathName);
        return false;
    }
    
    bool success = (CreateDirectory(GetNativePath(RemoveTrailingSlash(pathName), true).CString(), 0) == TRUE) ||
        (GetLastError() == ERROR_ALREADY_EXISTS);
    if (success)
        LOGDEBUG("Created directory " + pathName);
    else
        LOGERROR("Failed to create directory " + pathName);
    
    return success;
}

int FileSystem::SystemCommand(const String& commandLine)
{
    if (allowedPaths_.Empty())
        return system(commandLine.CString());
    else
    {
        LOGERROR("Executing an external command is not allowed");
        return -1;
    }
}

int FileSystem::SystemRun(const String& fileName, const Vector<String>& arguments)
{
    if (allowedPaths_.Empty())
    {
        String fixedFileName = GetNativePath(fileName, true);
        
        PODVector<const char*> argPtrs;
        argPtrs.Push(fixedFileName.CString());
        for (unsigned i = 0; i < arguments.Size(); ++i)
            argPtrs.Push(arguments[i].CString());
        argPtrs.Push(0);
        
        return _spawnv(_P_WAIT, fixedFileName.CString(), &argPtrs[0]);
    }
    else
    {
        LOGERROR("Executing an external command is not allowed");
        return -1;
    }
}

bool FileSystem::SystemOpen(const String& fileName, const String& mode)
{
    if (allowedPaths_.Empty())
    {
        if ((!FileExists(fileName)) && (!DirExists(fileName)))
        {
            LOGERROR("File or directory " + fileName + " not found");
            return false;
        }
        
        bool success = (int)ShellExecute(0, !mode.Empty() ? (char*)mode.CString() : 0,
            (char*)GetNativePath(fileName, true).CString(), 0, 0, SW_SHOW) > 32;
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

bool FileSystem::Copy(const String& srcFileName, const String& destFileName)
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

bool FileSystem::Rename(const String& srcFileName, const String& destFileName)
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
    
    return rename(GetNativePath(srcFileName).CString(), GetNativePath(destFileName).CString()) == 0;
}

bool FileSystem::Delete(const String& fileName)
{
    if (!CheckAccess(GetPath(fileName)))
    {
        LOGERROR("Access denied to " + fileName);
        return false;
    }
    
    return remove(GetNativePath(fileName).CString()) == 0;
}


String FileSystem::GetCurrentDir()
{
    char path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, path);
    return AddTrailingSlash(String(path));
}

bool FileSystem::CheckAccess(const String& pathName)
{
    String fixedPath = AddTrailingSlash(pathName);
    
    // If no allowed directories defined, succeed always
    if (allowedPaths_.Empty())
        return true;
    
    // If there is any attempt to go to a parent directory, disallow
    if (fixedPath.Find("..") != String::NPOS)
        return false;
    
    // Check if the path is a partial match of any of the allowed directories
    for (Set<String>::ConstIterator i = allowedPaths_.Begin(); i != allowedPaths_.End(); ++i)
    {
        if (fixedPath.Find(*i) == 0)
            return true;
    }
    
    // Not found, so disallow
    return false;
}

bool FileSystem::FileExists(const String& fileName)
{
    if (!CheckAccess(GetPath(fileName)))
        return false;
    
    String fixedName = GetNativePath(RemoveTrailingSlash(fileName), true);
    DWORD attributes = GetFileAttributes(fixedName.CString());
    if ((attributes == INVALID_FILE_ATTRIBUTES) || (attributes & FILE_ATTRIBUTE_DIRECTORY))
        return false;
    
    return true;
}

bool FileSystem::DirExists(const String& pathName)
{
    if (!CheckAccess(pathName))
        return false;
    
    String fixedName = GetNativePath(RemoveTrailingSlash(pathName), true);
    DWORD attributes = GetFileAttributes(fixedName.CString());
    if ((attributes == INVALID_FILE_ATTRIBUTES) || (!(attributes & FILE_ATTRIBUTE_DIRECTORY)))
        return false;
    
    return true;
}

void FileSystem::ScanDir(Vector<String>& result, const String& pathName, const String& filter, unsigned flags, bool recursive)
{
    result.Clear();
    
    if (CheckAccess(pathName))
    {
        String initialPath = AddTrailingSlash(pathName);
        ScanDirInternal(result, initialPath, initialPath, filter, flags, recursive);
    }
}

String FileSystem::GetProgramDir()
{
    char exeName[MAX_PATH];
    exeName[0] = 0;
    GetModuleFileName(0, exeName, MAX_PATH);
    return GetPath(String(exeName));
}

String FileSystem::GetUserDocumentsDir()
{
    char pathName[MAX_PATH];
    pathName[0] = 0;
    SHGetSpecialFolderPath(0, pathName, CSIDL_PERSONAL, 0);
    return AddTrailingSlash(String(pathName));
}

String FileSystem::GetSystemFontDir()
{
    char pathName[MAX_PATH];
    if (!ExpandEnvironmentStrings("%WinDir%", pathName, MAX_PATH))
        return String();
    return AddTrailingSlash(String(pathName)) + "Fonts";
}

void FileSystem::RegisterPath(const String& pathName)
{
    if (pathName.Empty())
        return;
    
    allowedPaths_.Insert(AddTrailingSlash(pathName));
}

void FileSystem::ScanDirInternal(Vector<String>& result, String path, const String& startPath,
    const String& filter, unsigned flags, bool recursive)
{
    path = AddTrailingSlash(path);
    String pathAndFilter = GetNativePath(path + filter, true);
    String deltaPath;
    if (path.Length() > startPath.Length())
        deltaPath = path.Substring(startPath.Length());
    
    WIN32_FIND_DATA info;
    HANDLE handle = FindFirstFile(pathAndFilter.CString(), &info);
    if (handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            String fileName((const char*)&info.cFileName[0]);
            if (!fileName.Empty())
            {
                if ((info.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && (!(flags & SCAN_HIDDEN)))
                    continue;
                if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (flags & SCAN_DIRS)
                        result.Push(deltaPath + fileName);
                    if ((recursive) && (fileName != ".") && (fileName != ".."))
                        ScanDirInternal(result, path + fileName, startPath, filter, flags, recursive);
                }
                else if (flags & SCAN_FILES)
                    result.Push(deltaPath + fileName);
            }
        } 
        while (FindNextFile(handle, &info));
        
        FindClose(handle);
    }
}

void SplitPath(const String& fullPath, String& pathName, String& fileName, String& extension)
{
    String fullPathCopy = GetInternalPath(fullPath);
    
    unsigned extPos = fullPathCopy.FindLast('.');
    if (extPos != String::NPOS)
    {
        extension = fullPathCopy.Substring(extPos).ToLower();
        fullPathCopy = fullPathCopy.Substring(0, extPos);
    }
    else
        extension.Clear();
    
    unsigned pathPos = fullPathCopy.FindLast('/');
    if (pathPos != String::NPOS)
    {
        fileName = fullPathCopy.Substring(pathPos + 1);
        pathName = fullPathCopy.Substring(0, pathPos + 1);
    }
    else
    {
        fileName = fullPathCopy;
        pathName.Clear();
    }
}

String GetPath(const String& fullPath)
{
    String path, file, extension;
    SplitPath(fullPath, path, file, extension);
    return path;
}

String GetFileName(const String& fullPath)
{
    String path, file, extension;
    SplitPath(fullPath, path, file, extension);
    return file;
}

String GetExtension(const String& fullPath)
{
    String path, file, extension;
    SplitPath(fullPath, path, file, extension);
    return extension;
}

String GetFileNameAndExtension(const String& fileName)
{
    String path, file, extension;
    SplitPath(fileName, path, file, extension);
    return file + extension;
}

String AddTrailingSlash(const String& pathName)
{
    String ret = pathName;
    ret.Replace('\\', '/');
    if ((!ret.Empty()) && (ret.Back() != '/'))
        ret += '/';
    
    return ret;
}

String RemoveTrailingSlash(const String& pathName)
{
    String ret = pathName;
    ret.Replace('\\', '/');
    if ((!ret.Empty()) && (ret.Back() == '/'))
        ret.Resize(ret.Length() - 1);
    
    return ret;
}

String GetParentPath(const String& path)
{
    unsigned pos = RemoveTrailingSlash(path).FindLast('/');
    if (pos != String::NPOS)
        return path.Substring(0, pos + 1);
    else
        return path;
}

String GetInternalPath(const String& pathName)
{
    String ret = pathName;
    ret.Replace('\\', '/');
    
    return ret;
}

String GetNativePath(const String& pathName, bool forNativeApi)
{
    // On MSVC, replace slash always with backslash. On MinGW only if going to do Win32 native calls
#ifdef _MSC_VER
    forNativeApi = true;
#endif
    
    if (forNativeApi)
    {
        String ret = pathName;
        ret.Replace('/', '\\');
        return ret;
    }
    else
        return pathName;
}
