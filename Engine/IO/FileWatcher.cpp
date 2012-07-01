//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "File.h"
#include "FileSystem.h"
#include "FileWatcher.h"
#include "Log.h"

#ifdef WIN32
#include <windows.h>

static const unsigned BUFFERSIZE = 4096;
#endif

OBJECTTYPESTATIC(FileWatcher);

FileWatcher::FileWatcher(Context* context) :
    Object(context),
    fileSystem_(GetSubsystem<FileSystem>()),
    watchSubDirs_(false)
{
}

FileWatcher::~FileWatcher()
{
    StopWatching();
}

bool FileWatcher::StartWatching(const String& pathName, bool watchSubDirs)
{
    if (!fileSystem_)
    {
        LOGERROR("No FileSystem, can not start watching");
        return false;
    }
    
    // Stop any previous watching
    StopWatching();
    
#if defined(WIN32) && defined(ENABLE_FILEWATCHER)
    String nativePath = GetNativePath(RemoveTrailingSlash(pathName));
    
    dirHandle_ = (void*)CreateFileW(
        WString(nativePath).CString(),
        FILE_LIST_DIRECTORY,
        FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
        0,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        0);
    
    if (dirHandle_ != INVALID_HANDLE_VALUE)
    {
        path_ = AddTrailingSlash(pathName);
        watchSubDirs_ = watchSubDirs;
        Start();
        
        LOGDEBUG("Started watching path " + pathName);
        return true;
    }
    else
    {
        LOGERROR("Failed to start watching path " + pathName);
        return false;
    }
#else
    /// \todo Implement on Unix-like systems
    LOGERROR("FileWatcher not implemented, can not start watching path " + pathName);
    return false;
#endif
}

void FileWatcher::StopWatching()
{
    if (handle_)
    {
        shouldRun_ = false;
        
        // Create and delete a dummy file to make sure the watcher loop terminates
        String dummyFileName = path_ + "dummy.tmp";
        File file(context_, dummyFileName, FILE_WRITE);
        file.Close();
        if (fileSystem_)
            fileSystem_->Delete(dummyFileName);
        
        Stop();
        
        #ifdef WIN32
        CloseHandle((HANDLE)dirHandle_);
        #endif
        
        LOGDEBUG("Stopped watching path " + path_);
        path_.Clear();
    }
}

void FileWatcher::ThreadFunction()
{
#if defined(WIN32) && defined(ENABLE_FILEWATCHER)
    unsigned char buffer[BUFFERSIZE];
    DWORD bytesFilled = 0;
    
    while (shouldRun_)
    {
        if (ReadDirectoryChangesW((HANDLE)dirHandle_,
            buffer,
            BUFFERSIZE,
            watchSubDirs_,
            FILE_NOTIFY_CHANGE_FILE_NAME |
            FILE_NOTIFY_CHANGE_LAST_WRITE,
            &bytesFilled,
            0,
            0))
        {
            unsigned offset = 0;
            
            while (offset < bytesFilled)
            {
                FILE_NOTIFY_INFORMATION* record = (FILE_NOTIFY_INFORMATION*)&buffer[offset];
                
                if (record->Action == FILE_ACTION_MODIFIED) // Modify
                {
                    String fileName;
                    const wchar_t* src = record->FileName;
                    const wchar_t* end = src + record->FileNameLength / 2;
                    while (src < end)
                        fileName.AppendUTF8(String::DecodeUTF16(src));
                    
                    fileName = GetInternalPath(fileName);
                    
                    {
                        MutexLock lock(changesMutex_);
                        // If we have 2 unprocessed modifies in a row into the same file, only record the first
                        if (changes_.Empty() || changes_.Back() != fileName)
                            changes_.Push(fileName);
                    }
                }
                
                if (!record->NextEntryOffset)
                    break;
                else
                    offset += record->NextEntryOffset;
            }
        }
    }
#endif
}

bool FileWatcher::GetNextChange(String& dest)
{
    MutexLock lock(changesMutex_);
    
    if (changes_.Empty())
        return false;
    else
    {
        dest = changes_.Front();
        changes_.Erase(changes_.Begin());
        return true;
    }
}
