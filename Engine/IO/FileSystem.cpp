//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "ArrayPtr.h"
#include "Context.h"
#include "File.h"
#include "FileSystem.h"
#include "Log.h"

#include <cstdio>
#include <cstring>

#ifdef WIN32
#ifndef _MSC_VER
#define _WIN32_IE 0x400
#endif
#include <windows.h>
#include <shellapi.h>
#include <direct.h>
#include <shlobj.h>
#else
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define MAX_PATH 256
#endif

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

#ifdef ANDROID
extern "C" const char* SDL_Android_GetFilesDir();
#endif
#ifdef IOS
extern "C" const char* SDL_IOS_GetResourceDir();
#endif

#include "DebugNew.h"

namespace Urho3D
{

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
    #ifdef WIN32
    if (SetCurrentDirectoryW(GetWideNativePath(pathName).CString()) == FALSE)
    {
        LOGERROR("Failed to change directory to " + pathName);
        return false;
    }
    #else
    if (chdir(GetNativePath(pathName).CString()) != 0)
    {
        LOGERROR("Failed to change directory to " + pathName);
        return false;
    }
    #endif

    return true;
}

bool FileSystem::CreateDir(const String& pathName)
{
    if (!CheckAccess(pathName))
    {
        LOGERROR("Access denied to " + pathName);
        return false;
    }

    #ifdef WIN32
    bool success = (CreateDirectoryW(GetWideNativePath(RemoveTrailingSlash(pathName)).CString(), 0) == TRUE) ||
        (GetLastError() == ERROR_ALREADY_EXISTS);
    #else
    bool success = mkdir(GetNativePath(RemoveTrailingSlash(pathName)).CString(), S_IRWXU) == 0 || errno == EEXIST;
    #endif

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
        String fixedFileName = GetNativePath(fileName);

        #ifdef WIN32
        // Add .exe extension if no extension defined
        if (GetExtension(fixedFileName).Empty())
            fixedFileName += ".exe";

        // If executable is not found, try cwd-relative path as a fallback
        if (!FileExists(fixedFileName))
            fixedFileName = GetNativePath(GetCurrentDir() + GetFileNameAndExtension(fixedFileName));

        String commandLine = "\"" + fixedFileName + "\"";
        for (unsigned i = 0; i < arguments.Size(); ++i)
            commandLine += " " + arguments[i];

        STARTUPINFOW startupInfo;
        PROCESS_INFORMATION processInfo;
        memset(&startupInfo, 0, sizeof startupInfo);
        memset(&processInfo, 0, sizeof processInfo);

        WString commandLineW(commandLine);
        if (!CreateProcessW(NULL, (wchar_t*)commandLineW.CString(), 0, 0, 0, CREATE_NO_WINDOW, 0, 0, &startupInfo, &processInfo))
        {
            LOGERROR("Failed to execute command " + commandLine);
            return -1;
        }

        WaitForSingleObject(processInfo.hProcess, INFINITE);
        DWORD exitCode;
        GetExitCodeProcess(processInfo.hProcess, &exitCode);

        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);

        return exitCode;
        #else
        // If executable is not found, try cwd-relative path as a fallback
        if (!FileExists(fixedFileName))
            fixedFileName = GetNativePath(GetCurrentDir() + GetFileNameAndExtension(fixedFileName));
        
        pid_t pid = fork();
        if (!pid)
        {
            PODVector<const char*> argPtrs;
            argPtrs.Push(fixedFileName.CString());
            for (unsigned i = 0; i < arguments.Size(); ++i)
                argPtrs.Push(arguments[i].CString());
            argPtrs.Push(0);

            execvp(argPtrs[0], (char**)&argPtrs[0]);
            return -1; // Return -1 if we could not spawn the process
        }
        else if (pid > 0)
        {
            int exitCode;
            wait(&exitCode);
            return exitCode;
        }
        else
        {
            LOGERROR("Failed to fork");
            return -1;
        }
        #endif
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
        if (!FileExists(fileName) && !DirExists(fileName))
        {
            LOGERROR("File or directory " + fileName + " not found");
            return false;
        }

        #ifdef WIN32
        bool success = (int)ShellExecuteW(0, !mode.Empty() ? WString(mode).CString() : 0,
            GetWideNativePath(fileName).CString(), 0, 0, SW_SHOW) > 32;
        #else
        Vector<String> arguments;
        arguments.Push(fileName);
        bool success = SystemRun(
        #if defined(__APPLE__)
                "/usr/bin/open",
        #else
                "/usr/bin/xdg-open",
        #endif
                arguments) == 0;
        #endif
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
    if (!srcFile->IsOpen() || !destFile->IsOpen())
        return false;

    unsigned fileSize = srcFile->GetSize();
    SharedArrayPtr<unsigned char> buffer(new unsigned char[fileSize]);

    unsigned bytesRead = srcFile->Read(buffer.Get(), fileSize);
    unsigned bytesWritten = destFile->Write(buffer.Get(), fileSize);
    return bytesRead == fileSize && bytesWritten == fileSize;
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

    #ifdef WIN32
    return MoveFileW(GetWideNativePath(srcFileName).CString(), GetWideNativePath(destFileName).CString()) != 0;
    #else
    return rename(GetNativePath(srcFileName).CString(), GetNativePath(destFileName).CString()) == 0;
    #endif
}

bool FileSystem::Delete(const String& fileName)
{
    if (!CheckAccess(GetPath(fileName)))
    {
        LOGERROR("Access denied to " + fileName);
        return false;
    }

    #ifdef WIN32
    return DeleteFileW(GetWideNativePath(fileName).CString()) != 0;
    #else
    return remove(GetNativePath(fileName).CString()) == 0;
    #endif
}

String FileSystem::GetCurrentDir() const
{
    #ifdef WIN32
    wchar_t path[MAX_PATH];
    path[0] = 0;
    GetCurrentDirectoryW(MAX_PATH, path);
    return AddTrailingSlash(String(path));
    #else
    char path[MAX_PATH];
    path[0] = 0;
    getcwd(path, MAX_PATH);
    return AddTrailingSlash(String(path));
    #endif
}

bool FileSystem::CheckAccess(const String& pathName) const
{
    String fixedPath = AddTrailingSlash(pathName);

    // If no allowed directories defined, succeed always
    if (allowedPaths_.Empty())
        return true;

    // If there is any attempt to go to a parent directory, disallow
    if (fixedPath.Contains(".."))
        return false;

    // Check if the path is a partial match of any of the allowed directories
    for (HashSet<String>::ConstIterator i = allowedPaths_.Begin(); i != allowedPaths_.End(); ++i)
    {
        if (fixedPath.Find(*i) == 0)
            return true;
    }

    // Not found, so disallow
    return false;
}

unsigned FileSystem::GetLastModifiedTime(const String& fileName) const
{
    if (fileName.Empty() || !CheckAccess(fileName))
        return 0;

    #ifdef WIN32
    WIN32_FILE_ATTRIBUTE_DATA fileAttrData;
    memset(&fileAttrData, 0, sizeof fileAttrData);
    if (GetFileAttributesExW(WString(fileName).CString(), GetFileExInfoStandard, &fileAttrData))
    {
        ULARGE_INTEGER ull;
        ull.LowPart = fileAttrData.ftLastWriteTime.dwLowDateTime;
        ull.HighPart = fileAttrData.ftLastWriteTime.dwHighDateTime;
        return (unsigned)(ull.QuadPart / 10000000ULL - 11644473600ULL);
    }
    else
        return 0;
    #else
    struct stat st;
    if (!stat(fileName.CString(), &st))
        return (unsigned)st.st_mtime;
    else
        return 0;
    #endif
}

bool FileSystem::FileExists(const String& fileName) const
{
    if (!CheckAccess(GetPath(fileName)))
        return false;

    String fixedName = GetNativePath(RemoveTrailingSlash(fileName));

    #ifdef ANDROID
    if (fixedName.StartsWith("/apk/"))
    {
        SDL_RWops* rwOps = SDL_RWFromFile(fileName.Substring(5).CString(), "rb");
        if (rwOps)
        {
            SDL_RWclose(rwOps);
            return true;
        }
        else
            return false;
    }
    #endif

    #ifdef WIN32
    DWORD attributes = GetFileAttributesW(WString(fixedName).CString());
    if (attributes == INVALID_FILE_ATTRIBUTES || attributes & FILE_ATTRIBUTE_DIRECTORY)
        return false;
    #else
    struct stat st;
    if (stat(fixedName.CString(), &st) || st.st_mode & S_IFDIR)
        return false;
    #endif

    return true;
}

bool FileSystem::DirExists(const String& pathName) const
{
    if (!CheckAccess(pathName))
        return false;

    #ifndef WIN32
    // Always return true for the root directory
    if (pathName == "/")
	return true;
    #endif

    String fixedName = GetNativePath(RemoveTrailingSlash(pathName));

    #ifdef ANDROID
    /// \todo Actually check for existence, now true is always returned for directories within the APK
    if (fixedName.StartsWith("/apk/"))
        return true;
    #endif

    #ifdef WIN32
    DWORD attributes = GetFileAttributesW(WString(fixedName).CString());
    if (attributes == INVALID_FILE_ATTRIBUTES || !(attributes & FILE_ATTRIBUTE_DIRECTORY))
        return false;
    #else
    struct stat st;
    if (stat(fixedName.CString(), &st) || !(st.st_mode & S_IFDIR))
        return false;
    #endif

    return true;
}

void FileSystem::ScanDir(Vector<String>& result, const String& pathName, const String& filter, unsigned flags, bool recursive) const
{
    result.Clear();

    if (CheckAccess(pathName))
    {
        String initialPath = AddTrailingSlash(pathName);
        ScanDirInternal(result, initialPath, initialPath, filter, flags, recursive);
    }
}

String FileSystem::GetProgramDir() const
{
    #if defined(ANDROID)
    // This is an internal directory specifier pointing to the assets in the .apk
    // Files from this directory will be opened using special handling
    return "/apk/";
    #elif defined(IOS)
    return AddTrailingSlash(SDL_IOS_GetResourceDir());
    #elif defined(WIN32)
    wchar_t exeName[MAX_PATH];
    exeName[0] = 0;
    GetModuleFileNameW(0, exeName, MAX_PATH);
    return GetPath(String(exeName));
    #elif defined(__APPLE__)
    char exeName[MAX_PATH];
    memset(exeName, 0, MAX_PATH);
    unsigned size = MAX_PATH;
    _NSGetExecutablePath(exeName, &size);
    return GetPath(String(exeName));
    #elif defined(__linux__)
    char exeName[MAX_PATH];
    memset(exeName, 0, MAX_PATH);
    pid_t pid = getpid();
    String link = "/proc/" + String(pid) + "/exe";
    readlink(link.CString(), exeName, MAX_PATH);
    return GetPath(String(exeName));
    #else
    return String();
    #endif
}

String FileSystem::GetUserDocumentsDir() const
{
    #if defined(ANDROID)
    return AddTrailingSlash(SDL_Android_GetFilesDir());
    #elif defined(IOS)
    return AddTrailingSlash(SDL_IOS_GetResourceDir());
    #elif defined(WIN32)
    wchar_t pathName[MAX_PATH];
    pathName[0] = 0;
    SHGetSpecialFolderPathW(0, pathName, CSIDL_PERSONAL, 0);
    return AddTrailingSlash(String(pathName));
    #else
    char pathName[MAX_PATH];
    pathName[0] = 0;
    strcpy(pathName, getenv("HOME"));
    return AddTrailingSlash(String(pathName));
    #endif
}

void FileSystem::RegisterPath(const String& pathName)
{
    if (pathName.Empty())
        return;

    allowedPaths_.Insert(AddTrailingSlash(pathName));
}

void FileSystem::ScanDirInternal(Vector<String>& result, String path, const String& startPath,
    const String& filter, unsigned flags, bool recursive) const
{
    path = AddTrailingSlash(path);
    String deltaPath;
    if (path.Length() > startPath.Length())
        deltaPath = path.Substring(startPath.Length());

    String filterExtension = filter.Substring(filter.Find('.'));
    if (filterExtension.Contains('*'))
        filterExtension.Clear();

    #ifdef WIN32
    WIN32_FIND_DATAW info;
    HANDLE handle = FindFirstFileW(WString(path + "*").CString(), &info);
    if (handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            String fileName(info.cFileName);
            if (!fileName.Empty())
            {
                if (info.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN && !(flags & SCAN_HIDDEN))
                    continue;
                if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (flags & SCAN_DIRS)
                        result.Push(deltaPath + fileName);
                    if (recursive && fileName != "." && fileName != "..")
                        ScanDirInternal(result, path + fileName, startPath, filter, flags, recursive);
                }
                else if (flags & SCAN_FILES)
                {
                    if (filterExtension.Empty() || fileName.EndsWith(filterExtension))
                        result.Push(deltaPath + fileName);
                }
            }
        }
        while (FindNextFileW(handle, &info));

        FindClose(handle);
    }
    #else
    DIR *dir;
    struct dirent *de;
    struct stat st;
    dir = opendir(GetNativePath(path).CString());
    if (dir)
    {
        while ((de = readdir(dir)))
        {
            /// \todo Filename may be unnormalized Unicode on Mac OS X. Re-normalize as necessary
            String fileName(de->d_name);
            bool normalEntry = fileName != "." && fileName != "..";
            if (normalEntry && !(flags & SCAN_HIDDEN) && fileName.StartsWith("."))
                continue;
            String pathAndName = path + fileName;
            if (!stat(pathAndName.CString(), &st))
            {
                if (st.st_mode & S_IFDIR)
                {
                    if (flags & SCAN_DIRS)
                        result.Push(deltaPath + fileName);
                    if (recursive && normalEntry)
                        ScanDirInternal(result, path + fileName, startPath, filter, flags, recursive);
                }
                else if (flags & SCAN_FILES)
                {
                    if (filterExtension.Empty() || fileName.EndsWith(filterExtension))
                        result.Push(deltaPath + fileName);
                }
            }
        }
        closedir(dir);
    }
    #endif
}

void SplitPath(const String& fullPath, String& pathName, String& fileName, String& extension)
{
    String fullPathCopy = GetInternalPath(fullPath);

    unsigned extPos = fullPathCopy.FindLast('.');
    unsigned pathPos = fullPathCopy.FindLast('/');

    if (extPos != String::NPOS && (pathPos == String::NPOS || extPos > pathPos))
    {
        extension = fullPathCopy.Substring(extPos).ToLower();
        fullPathCopy = fullPathCopy.Substring(0, extPos);
    }
    else
        extension.Clear();

    pathPos = fullPathCopy.FindLast('/');
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

String ReplaceExtension(const String& fullPath, const String& newExtension)
{
    String path, file, extension;
    SplitPath(fullPath, path, file, extension);
    return path + file + newExtension;
}

String AddTrailingSlash(const String& pathName)
{
    String ret = pathName;
    ret.Replace('\\', '/');
    if (!ret.Empty() && ret.Back() != '/')
        ret += '/';
    return ret;
}

String RemoveTrailingSlash(const String& pathName)
{
    String ret = pathName;
    ret.Replace('\\', '/');
    if (!ret.Empty() && ret.Back() == '/')
        ret.Resize(ret.Length() - 1);
    return ret;
}

String GetParentPath(const String& path)
{
    unsigned pos = RemoveTrailingSlash(path).FindLast('/');
    if (pos != String::NPOS)
        return path.Substring(0, pos + 1);
    else
        return String();
}

String GetInternalPath(const String& pathName)
{
    return pathName.Replaced('\\', '/');
}

String GetNativePath(const String& pathName)
{
#ifdef WIN32
    return pathName.Replaced('/', '\\');
#else
    return pathName;
#endif
}

WString GetWideNativePath(const String& pathName)
{
#ifdef WIN32
    return WString(pathName.Replaced('/', '\\'));
#else
    return WString(pathName);
#endif
}

}
