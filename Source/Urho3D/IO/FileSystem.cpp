//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Container/ArrayPtr.h"
#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../Core/Path.h"
#include "../Core/Thread.h"
#include "../Engine/EngineEvents.h"
#include "../IO/File.h"
#include "../IO/FileSystem.h"
#include "../IO/IOEvents.h"
#include "../IO/Log.h"

#ifdef __ANDROID__
#include <SDL/SDL_rwops.h>
#endif

#ifndef MINI_URHO
#include <SDL/SDL_filesystem.h>
#endif

#include <sys/stat.h>
#include <cstdio>

#ifdef _WIN32
#ifndef _MSC_VER
#define _WIN32_IE 0x501
#endif
#include <windows.h>
#include <shellapi.h>
#include <direct.h>
#include <shlobj.h>
#include <sys/types.h>
#include <sys/utime.h>
#else
#include <dirent.h>
#include <cerrno>
#include <unistd.h>
#include <utime.h>
#include <sys/wait.h>
#define MAX_PATH 256
#endif

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

extern "C"
{
#ifdef __ANDROID__
const char* SDL_Android_GetFilesDir();
char** SDL_Android_GetFileList(const char* path, int* count);
void SDL_Android_FreeFileList(char*** array, int* count);
#elif defined(IOS) || defined(TVOS)
const char* SDL_IOS_GetResourceDir();
const char* SDL_IOS_GetDocumentsDir();
#endif
}

#include "../DebugNew.h"

namespace Urho3D
{

int DoSystemCommand(const String& commandLine, bool redirectToLog, Context* context)
{
#if defined(TVOS) || defined(IOS)
    return -1;
#else
#if !defined(__EMSCRIPTEN__) && !defined(MINI_URHO)
    if (!redirectToLog)
#endif
        return system(commandLine.CString());

#if !defined(__EMSCRIPTEN__) && !defined(MINI_URHO)
    // Get a platform-agnostic temporary file name for stderr redirection
    String stderrFilename;
    String adjustedCommandLine(commandLine);
    char* prefPath = SDL_GetPrefPath("urho3d", "temp");
    if (prefPath)
    {
        stderrFilename = String(prefPath) + "command-stderr";
        adjustedCommandLine += " 2>" + stderrFilename;
        SDL_free(prefPath);
    }

#ifdef _MSC_VER
    #define popen _popen
    #define pclose _pclose
#endif

    // Use popen/pclose to capture the stdout and stderr of the command
    FILE* file = popen(adjustedCommandLine.CString(), "r");
    if (!file)
        return -1;

    // Capture the standard output stream
    char buffer[128];
    while (!feof(file))
    {
        if (fgets(buffer, sizeof(buffer), file))
            URHO3D_LOGRAW(String(buffer));
    }
    int exitCode = pclose(file);

    // Capture the standard error stream
    if (!stderrFilename.Empty())
    {
        SharedPtr<File> errFile(new File(context, stderrFilename, FILE_READ));
        while (!errFile->IsEof())
        {
            unsigned numRead = errFile->Read(buffer, sizeof(buffer));
            if (numRead)
                Log::WriteRaw(String(buffer, numRead), true);
        }
    }

    return exitCode;
#endif
#endif
}

int DoSystemRun(const Path& fileName, const Vector<String>& arguments)
{
#ifdef TVOS
    return -1;
#else
    String fixedFileName = fileName.GetNativePathString();

#ifdef _WIN32
    // Add .exe extension if no extension defined
    if (GetExtension(fixedFileName).Empty())
        fixedFileName += ".exe";

    String commandLine = "\"" + fixedFileName + "\"";
    for (unsigned i = 0; i < arguments.Size(); ++i)
        commandLine += " " + arguments[i];

    STARTUPINFOW startupInfo;
    PROCESS_INFORMATION processInfo;
    memset(&startupInfo, 0, sizeof startupInfo);
    memset(&processInfo, 0, sizeof processInfo);

    WString commandLineW(commandLine);
    if (!CreateProcessW(nullptr, (wchar_t*)commandLineW.CString(), nullptr, nullptr, 0, CREATE_NO_WINDOW, nullptr, nullptr, &startupInfo, &processInfo))
        return -1;

    WaitForSingleObject(processInfo.hProcess, INFINITE);
    DWORD exitCode;
    GetExitCodeProcess(processInfo.hProcess, &exitCode);

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    return exitCode;
#else
    pid_t pid = fork();
    if (!pid)
    {
        PODVector<const char*> argPtrs;
        argPtrs.Push(fixedFileName.CString());
        for (unsigned i = 0; i < arguments.Size(); ++i)
            argPtrs.Push(arguments[i].CString());
        argPtrs.Push(nullptr);

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
        return -1;
#endif
#endif
}

/// Base class for async execution requests.
class AsyncExecRequest : public Thread
{
public:
    /// Construct.
    explicit AsyncExecRequest(unsigned& requestID) :
        requestID_(requestID)
    {
        // Increment ID for next request
        ++requestID;
        if (requestID == M_MAX_UNSIGNED)
            requestID = 1;
    }

    /// Return request ID.
    unsigned GetRequestID() const { return requestID_; }

    /// Return exit code. Valid when IsCompleted() is true.
    int GetExitCode() const { return exitCode_; }

    /// Return completion status.
    bool IsCompleted() const { return completed_; }

protected:
    /// Request ID.
    unsigned requestID_{};
    /// Exit code.
    int exitCode_{};
    /// Completed flag.
    volatile bool completed_{};
};

/// Async system command operation.
class AsyncSystemCommand : public AsyncExecRequest
{
public:
    /// Construct and run.
    AsyncSystemCommand(unsigned requestID, const String& commandLine) :
        AsyncExecRequest(requestID),
        commandLine_(commandLine)
    {
        Run();
    }

    /// The function to run in the thread.
    void ThreadFunction() override
    {
        exitCode_ = DoSystemCommand(commandLine_, false, nullptr);
        completed_ = true;
    }

private:
    /// Command line.
    String commandLine_;
};

/// Async system run operation.
class AsyncSystemRun : public AsyncExecRequest
{
public:
    /// Construct and run.
    AsyncSystemRun(unsigned requestID, const Path& fileName, const Vector<String>& arguments) :
        AsyncExecRequest(requestID),
        fileName_(fileName),
        arguments_(arguments)
    {
        Run();
    }

    /// The function to run in the thread.
    void ThreadFunction() override
    {
        exitCode_ = DoSystemRun(fileName_, arguments_);
        completed_ = true;
    }

private:
    /// File to run.
    Path fileName_;
    /// Command line split in arguments.
    const Vector<String>& arguments_;
};

FileSystem::FileSystem(Context* context) :
    Object(context)
{
    SubscribeToEvent(E_BEGINFRAME, URHO3D_HANDLER(FileSystem, HandleBeginFrame));

    // Subscribe to console commands
    SetExecuteConsoleCommands(true);
}

FileSystem::~FileSystem()
{
    // If any async exec items pending, delete them
    if (asyncExecQueue_.Size())
    {
        for (List<AsyncExecRequest*>::Iterator i = asyncExecQueue_.Begin(); i != asyncExecQueue_.End(); ++i)
            delete(*i);

        asyncExecQueue_.Clear();
    }
}

bool FileSystem::SetCurrentDir(const Path& pathName)
{
    if (!CheckAccess(pathName))
    {
        URHO3D_LOGERROR("Access denied to " + pathName.ToString());
        return false;
    }
#ifdef _WIN32
    if (SetCurrentDirectoryW(pathName.GetWideNativePathString().CString()) == FALSE)
    {
        URHO3D_LOGERROR("Failed to change directory to " + pathName);
        return false;
    }
#else
    if (chdir(pathName.GetNativePathString().CString()) != 0)
    {
        URHO3D_LOGERROR("Failed to change directory to " + pathName.ToString());
        return false;
    }
#endif

    return true;
}

bool FileSystem::CreateDir(Path pathName)
{
    if (!CheckAccess(pathName))
    {
        URHO3D_LOGERROR("Access denied to " + pathName.ToString());
        return false;
    }

    // Create each of the parents if necessary
    Path parentPath = pathName.GetParentPath();
    if (parentPath.ToString().Length() > 1 && !DirExists(parentPath))
    {
        if (!CreateDir(parentPath))
            return false;
    }

    pathName.RemoveTrailingSlash();

#ifdef _WIN32
    bool success = (CreateDirectoryW(pathName.GetWideNativePathString().CString(), nullptr) == TRUE) ||
        (GetLastError() == ERROR_ALREADY_EXISTS);
#else
    bool success = mkdir(pathName.GetNativePathString().CString(), S_IRWXU) == 0 || errno == EEXIST;
#endif

    if (success)
        URHO3D_LOGDEBUG("Created directory " + pathName.ToString());
    else
        URHO3D_LOGERROR("Failed to create directory " + pathName.ToString());

    return success;
}

void FileSystem::SetExecuteConsoleCommands(bool enable)
{
    if (enable == executeConsoleCommands_)
        return;

    executeConsoleCommands_ = enable;
    if (enable)
        SubscribeToEvent(E_CONSOLECOMMAND, URHO3D_HANDLER(FileSystem, HandleConsoleCommand));
    else
        UnsubscribeFromEvent(E_CONSOLECOMMAND);
}

int FileSystem::SystemCommand(const String& commandLine, bool redirectStdOutToLog)
{
    if (allowedPaths_.Empty())
        return DoSystemCommand(commandLine, redirectStdOutToLog, context_);
    else
    {
        URHO3D_LOGERROR("Executing an external command is not allowed");
        return -1;
    }
}

int FileSystem::SystemRun(const Path& fileName, const Vector<String>& arguments)
{
    if (allowedPaths_.Empty())
        return DoSystemRun(fileName, arguments);
    else
    {
        URHO3D_LOGERROR("Executing an external command is not allowed");
        return -1;
    }
}

unsigned FileSystem::SystemCommandAsync(const String& commandLine)
{
#ifdef URHO3D_THREADING
    if (allowedPaths_.Empty())
    {
        unsigned requestID = nextAsyncExecID_;
        auto* cmd = new AsyncSystemCommand(nextAsyncExecID_, commandLine);
        asyncExecQueue_.Push(cmd);
        return requestID;
    }
    else
    {
        URHO3D_LOGERROR("Executing an external command is not allowed");
        return M_MAX_UNSIGNED;
    }
#else
    URHO3D_LOGERROR("Can not execute an asynchronous command as threading is disabled");
    return M_MAX_UNSIGNED;
#endif
}

unsigned FileSystem::SystemRunAsync(const Path& fileName, const Vector<String>& arguments)
{
#ifdef URHO3D_THREADING
    if (allowedPaths_.Empty())
    {
        unsigned requestID = nextAsyncExecID_;
        auto* cmd = new AsyncSystemRun(nextAsyncExecID_, fileName, arguments);
        asyncExecQueue_.Push(cmd);
        return requestID;
    }
    else
    {
        URHO3D_LOGERROR("Executing an external command is not allowed");
        return M_MAX_UNSIGNED;
    }
#else
    URHO3D_LOGERROR("Can not run asynchronously as threading is disabled");
    return M_MAX_UNSIGNED;
#endif
}

bool FileSystem::SystemOpen(const Path& fileName, const String& mode)
{
    if (allowedPaths_.Empty())
    {
        if (!FileExists(fileName) && !DirExists(fileName))
        {
            URHO3D_LOGERROR("File or directory " + fileName.ToString() + " not found");
            return false;
        }

#ifdef _WIN32
        bool success = (size_t)ShellExecuteW(nullptr, !mode.Empty() ? WString(mode).CString() : nullptr,
            fileName.GetWideNativePathString().CString(), nullptr, nullptr, SW_SHOW) > 32;
#else
        Vector<String> arguments;
        arguments.Push(fileName.ToString());
        bool success = SystemRun(
#if defined(__APPLE__)
            "/usr/bin/open",
#else
            "/usr/bin/xdg-open",
#endif
            arguments) == 0;
#endif
        if (!success)
            URHO3D_LOGERROR("Failed to open " + fileName.ToString() + " externally");
        return success;
    }
    else
    {
        URHO3D_LOGERROR("Opening a file externally is not allowed");
        return false;
    }
}

bool FileSystem::Copy(const Path& srcFileName, const Path& destFileName)
{
    if (!CheckAccess(srcFileName.GetDirectoryPath()))
    {
        URHO3D_LOGERROR("Access denied to " + srcFileName.ToString());
        return false;
    }
    if (!CheckAccess(destFileName.GetDirectoryPath()))
    {
        URHO3D_LOGERROR("Access denied to " + destFileName.ToString());
        return false;
    }

    SharedPtr<File> srcFile(new File(context_, srcFileName, FILE_READ));
    if (!srcFile->IsOpen())
        return false;
    SharedPtr<File> destFile(new File(context_, destFileName, FILE_WRITE));
    if (!destFile->IsOpen())
        return false;

    unsigned fileSize = srcFile->GetSize();
    SharedArrayPtr<unsigned char> buffer(new unsigned char[fileSize]);

    unsigned bytesRead = srcFile->Read(buffer.Get(), fileSize);
    unsigned bytesWritten = destFile->Write(buffer.Get(), fileSize);
    return bytesRead == fileSize && bytesWritten == fileSize;
}

bool FileSystem::Rename(const Path& srcFileName, const Path& destFileName)
{
    if (!CheckAccess(srcFileName.GetDirectoryPath()))
    {
        URHO3D_LOGERROR("Access denied to " + srcFileName.ToString());
        return false;
    }
    if (!CheckAccess(destFileName.GetDirectoryPath()))
    {
        URHO3D_LOGERROR("Access denied to " + destFileName.ToString());
        return false;
    }

#ifdef _WIN32
    return MoveFileW(srcFileName.GetWideNativePathString().CString(), destFileName.GetWideNativePathString().CString()) != 0;
#else
    return rename(srcFileName.GetNativePathString().CString(), destFileName.GetNativePathString().CString()) == 0;
#endif
}

bool FileSystem::Delete(const Path& fileName)
{
    if (!CheckAccess(fileName.GetDirectoryPath()))
    {
        URHO3D_LOGERROR("Access denied to " + fileName.ToString());
        return false;
    }

#ifdef _WIN32
    return DeleteFileW(fileName.GetWideNativePathString().CString()) != 0;
#else
    return remove(fileName.GetNativePathString().CString()) == 0;
#endif
}

Path FileSystem::GetCurrentDir() const
{
#ifdef _WIN32
    wchar_t path[MAX_PATH];
    path[0] = 0;
    GetCurrentDirectoryW(MAX_PATH, path);
#else
    char path[MAX_PATH];
    path[0] = 0;
    getcwd(path, MAX_PATH);
#endif

    Path ret(path);
    ret.AddTrailingSlash();
    return ret;
}

bool FileSystem::CheckAccess(Path pathName) const
{
    // By not using a const Path& we can avoid having to duplicate the path anyway to add the slash
    pathName.AddTrailingSlash();

    // Resolving the path will move the .. to the front so our check will be more complete
    pathName.ResolveRelativeTo(Path::EMPTY);

    // If no allowed directories defined, succeed always
    if (allowedPaths_.Empty())
        return true;

    // If there is any attempt to go to a parent directory, disallow
    if (pathName.IsRequestingParentDirectory())
        return false;

    // Check if the path is a partial match of any of the allowed directories
    for (auto i = allowedPaths_.Begin(); i != allowedPaths_.End(); ++i)
    {
        if (GLOBMatches(*i,pathName))
            return true;
    }

    // Not found, so disallow
    return false;
}

unsigned FileSystem::GetLastModifiedTime(const Path& fileName) const
{
    if (fileName.Empty() || !CheckAccess(fileName))
        return 0;

#ifdef _WIN32
    struct _stat st;
    if (!_stat(fileName.ToString().CString(), &st))
        return (unsigned)st.st_mtime;
    else
        return 0;
#else
    struct stat st{};
    if (!stat(fileName.ToString().CString(), &st))
        return (unsigned)st.st_mtime;
    else
        return 0;
#endif
}

bool FileSystem::FileExists(const Path& fileName) const
{
    if (fileName.Empty())
        return false;

    if (!CheckAccess(fileName.GetDirectoryPath()))
        return false;

#ifdef __ANDROID__
    if (URHO3D_IS_ASSET(fileName.ToString()))
    {
        SDL_RWops* rwOps = SDL_RWFromFile(URHO3D_ASSET(fileName.ToString()), "rb");
        if (rwOps)
        {
            SDL_RWclose(rwOps);
            return true;
        }
        else
            return false;
    }
#endif

    String fixedName = fileName.WithoutTrailingSlash().GetNativePathString();

#ifdef _WIN32
    DWORD attributes = GetFileAttributesW(WString(fixedName).CString());
    if (attributes == INVALID_FILE_ATTRIBUTES || attributes & FILE_ATTRIBUTE_DIRECTORY)
        return false;
#else
    struct stat st{};
    if (stat(fixedName.CString(), &st) || st.st_mode & S_IFDIR)
        return false;
#endif

    return true;
}

bool FileSystem::DirExists(const Path& pathName) const
{
    if (!CheckAccess(pathName))
        return false;

#ifndef _WIN32
    // Always return true for the root directory
    if (pathName.ToString() == "/")
        return true;
#endif

    String fixedName = pathName.WithoutTrailingSlash().GetNativePathString();

#ifdef __ANDROID__
    if (URHO3D_IS_ASSET(fixedName))
    {
        // Split the pathname into two components: the longest parent directory path and the last name component
        String assetPath(URHO3D_ASSET((fixedName + "/")));
        String parentPath;
        unsigned pos = assetPath.FindLast('/', assetPath.Length() - 2);
        if (pos != String::NPOS)
        {
            parentPath = assetPath.Substring(0, pos);
            assetPath = assetPath.Substring(pos + 1);
        }
        assetPath.Resize(assetPath.Length() - 1);

        bool exist = false;
        int count;
        char** list = SDL_Android_GetFileList(parentPath.CString(), &count);
        for (int i = 0; i < count; ++i)
        {
            exist = assetPath == list[i];
            if (exist)
                break;
        }
        SDL_Android_FreeFileList(&list, &count);
        return exist;
    }
#endif

#ifdef _WIN32
    DWORD attributes = GetFileAttributesW(WString(fixedName).CString());
    if (attributes == INVALID_FILE_ATTRIBUTES || !(attributes & FILE_ATTRIBUTE_DIRECTORY))
        return false;
#else
    struct stat st{};
    if (stat(fixedName.CString(), &st) || !(st.st_mode & S_IFDIR))
        return false;
#endif

    return true;
}

void FileSystem::ScanDir(Vector<Path>& result, Path pathName, const String& filter, unsigned flags, bool recursive) const
{
    result.Clear();

    if (CheckAccess(pathName))
    {
        pathName.AddTrailingSlash();
        ScanDirInternal(result, pathName, pathName, filter, flags, recursive);
    }
}

Path FileSystem::GetProgramDir() const
{
#if defined(__ANDROID__)
    // This is an internal directory specifier pointing to the assets in the .apk
    // Files from this directory will be opened using special handling
    return APK;
#elif defined(IOS) || defined(TVOS)
    return AddTrailingSlash(SDL_IOS_GetResourceDir());
#elif defined(_WIN32)
    wchar_t exeName[MAX_PATH];
    exeName[0] = 0;
    GetModuleFileNameW(nullptr, exeName, MAX_PATH);
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
    return GetCurrentDir();
#endif
}

Path FileSystem::GetUserDocumentsDir() const
{
#if defined(__ANDROID__)
    Path path{SDL_Android_GetFilesDir()};
    path.AddTrailingSlash();
    return path;
#elif defined(IOS) || defined(TVOS)
    Path path{SDL_IOS_GetDocumentsDir()};
    path.AddTrailingSlash();
    return path;
#elif defined(_WIN32)
    wchar_t pathName[MAX_PATH];
    pathName[0] = 0;
    SHGetSpecialFolderPathW(nullptr, pathName, CSIDL_PERSONAL, 0);
    Path path{pathName};
    path.AddTrailingSlash();
    return path;
#else
    char pathName[MAX_PATH];
    pathName[0] = 0;
    strcpy(pathName, getenv("HOME"));
    Path path{pathName};
    path.AddTrailingSlash();
    return path;
#endif
}

Path FileSystem::GetAppPreferencesDir(const String& org, const String& app) const
{
#ifndef MINI_URHO
    char* prefPath = SDL_GetPrefPath(org.CString(), app.CString());
    if (prefPath)
    {
        Path dir(prefPath);
        SDL_free(prefPath);
        return dir;
    }
    else
#endif
        URHO3D_LOGWARNING("Could not get application preferences directory");

    return {};
}

void FileSystem::RegisterPath(const Path& pathName, bool partialMatch)
{
    if (pathName.Empty())
        return;

    // Partial match enables the "Old" behavior where the path just had to match part of the registered path.
    if (partialMatch)
    {
        Path match = pathName.WithTrailingSlash();
        if (!match.ToString().StartsWith("**"))
            match = "**" + match;
        if (!match.ToString().EndsWith("**"))
            match += "**";
        allowedPaths_.Insert(match);
    }
    else
        allowedPaths_.Insert(pathName);
}

bool FileSystem::SetLastModifiedTime(const Path& fileName, unsigned newTime)
{
    if (fileName.Empty() || !CheckAccess(fileName))
        return false;

#ifdef _WIN32
    struct _stat oldTime;
    struct _utimbuf newTimes;
    if (_stat(fileName.ToString().CString(), &oldTime) != 0)
        return false;
    newTimes.actime = oldTime.st_atime;
    newTimes.modtime = newTime;
    return _utime(fileName.ToString().CString(), &newTimes) == 0;
#else
    struct stat oldTime{};
    struct utimbuf newTimes{};
    if (stat(fileName.ToString().CString(), &oldTime) != 0)
        return false;
    newTimes.actime = oldTime.st_atime;
    newTimes.modtime = newTime;
    return utime(fileName.ToString().CString(), &newTimes) == 0;
#endif
}

void FileSystem::ScanDirInternal(Vector<Path>& result, Path path, const Path& startPath,
    const String& filter, unsigned flags, bool recursive) const
{
    path.AddTrailingSlash();
    String deltaPath;
    if (path.Length() > startPath.Length())
        deltaPath = path.ToString().Substring(startPath.Length());

    String filterExtension = filter.Substring(filter.FindLast('.'));
    if (filterExtension.Contains('*'))
        filterExtension.Clear();

#ifdef __ANDROID__
    if (URHO3D_IS_ASSET(path))
    {
        String assetPath(URHO3D_ASSET(path));
        assetPath.Resize(assetPath.Length() - 1);       // AssetManager.list() does not like trailing slash
        int count;
        char** list = SDL_Android_GetFileList(assetPath.CString(), &count);
        for (int i = 0; i < count; ++i)
        {
            String fileName(list[i]);
            if (!(flags & SCAN_HIDDEN) && fileName.StartsWith("."))
                continue;

#ifdef ASSET_DIR_INDICATOR
            // Patch the directory name back after retrieving the directory flag
            bool isDirectory = fileName.EndsWith(ASSET_DIR_INDICATOR);
            if (isDirectory)
            {
                fileName.Resize(fileName.Length() - sizeof(ASSET_DIR_INDICATOR) / sizeof(char) + 1);
                if (flags & SCAN_DIRS)
                    result.Push(deltaPath + fileName);
                if (recursive)
                    ScanDirInternal(result, path + fileName, startPath, filter, flags, recursive);
            }
            else if (flags & SCAN_FILES)
#endif
            {
                if (filterExtension.Empty() || fileName.EndsWith(filterExtension))
                    result.Push(deltaPath + fileName);
            }
        }
        SDL_Android_FreeFileList(&list, &count);
        return;
    }
#endif
#ifdef _WIN32
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
    DIR* dir;
    struct dirent* de;
    struct stat st{};
    dir = opendir(path.GetNativePathString().CString());
    if (dir)
    {
        while ((de = readdir(dir)))
        {
            /// \todo Filename may be unnormalized Unicode on Mac OS X. Re-normalize as necessary
            String fileName(de->d_name);
            bool normalEntry = fileName != "." && fileName != "..";
            if (normalEntry && !(flags & SCAN_HIDDEN) && fileName.StartsWith("."))
                continue;
            Path pathAndName = path + fileName;
            if (!stat(pathAndName.GetNativePathString().CString(), &st))
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

void FileSystem::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    // Go through the execution queue and post + remove completed requests
    for (List<AsyncExecRequest*>::Iterator i = asyncExecQueue_.Begin(); i != asyncExecQueue_.End();)
    {
        AsyncExecRequest* request = *i;
        if (request->IsCompleted())
        {
            using namespace AsyncExecFinished;

            VariantMap& newEventData = GetEventDataMap();
            newEventData[P_REQUESTID] = request->GetRequestID();
            newEventData[P_EXITCODE] = request->GetExitCode();
            SendEvent(E_ASYNCEXECFINISHED, newEventData);

            delete request;
            i = asyncExecQueue_.Erase(i);
        }
        else
            ++i;
    }
}

void FileSystem::HandleConsoleCommand(StringHash eventType, VariantMap& eventData)
{
    using namespace ConsoleCommand;
    if (eventData[P_ID].GetString() == GetTypeName())
        SystemCommand(eventData[P_COMMAND].GetString(), true);
}

void SplitPath(const String& fullPath, String& pathName, String& fileName, String& extension, bool lowercaseExtension)
{
    String fullPathCopy = GetInternalPath(fullPath);

    unsigned extPos = fullPathCopy.FindLast('.');
    unsigned pathPos = fullPathCopy.FindLast('/');

    if (extPos != String::NPOS && (pathPos == String::NPOS || extPos > pathPos))
    {
        extension = fullPathCopy.Substring(extPos);
        if (lowercaseExtension)
            extension = extension.ToLower();
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

String GetExtension(const String& fullPath, bool lowercaseExtension)
{
    String path, file, extension;
    SplitPath(fullPath, path, file, extension, lowercaseExtension);
    return extension;
}

String GetFileNameAndExtension(const String& fileName, bool lowercaseExtension)
{
    String path, file, extension;
    SplitPath(fileName, path, file, extension, lowercaseExtension);
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
    String ret = pathName.Trimmed();
    ret.Replace('\\', '/');
    if (!ret.Empty() && ret.Back() != '/')
        ret += '/';
    return ret;
}

String RemoveTrailingSlash(const String& pathName)
{
    String ret = pathName.Trimmed();
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
#ifdef _WIN32
    return pathName.Replaced('/', '\\');
#else
    return pathName;
#endif
}

WString GetWideNativePath(const String& pathName)
{
#ifdef _WIN32
    return WString(pathName.Replaced('/', '\\'));
#else
    return WString(pathName);
#endif
}

bool IsAbsolutePath(const String& pathName)
{
    if (pathName.Empty())
        return false;

    String path = GetInternalPath(pathName);

    if (path[0] == '/')
        return true;

#ifdef _WIN32
    if (path.Length() > 1 && IsAlpha(path[0]) && path[1] == ':')
        return true;
#endif

    return false;
}

Path FileSystem::GetTemporaryDir() const
{
#if defined(_WIN32)
#if defined(MINI_URHO)
    return getenv("TMP");
#else
    wchar_t pathName[MAX_PATH];
    pathName[0] = 0;
    GetTempPathW(SDL_arraysize(pathName), pathName);
    Path ret(pathName);
    ret.AddTrailingSlash();
    return ret;
#endif
#else
    if (char* pathName = getenv("TMPDIR"))
    {
        Path ret(pathName);
        ret.AddTrailingSlash();
        return ret;
    }
#ifdef P_tmpdir
    return Path(P_tmpdir).WithTrailingSlash();
#else
    return "/tmp/";
#endif
#endif
}

}
