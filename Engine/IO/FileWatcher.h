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

#pragma once

#include "List.h"
#include "Mutex.h"
#include "Object.h"
#include "Thread.h"

/// Watches a directory and its subdirectories for files being modified
class FileWatcher : public Object, public Thread
{
    OBJECT(FileWatcher);
    
public:
    /// Construct.
    FileWatcher(Context* context);
    /// Destruct.
    virtual ~FileWatcher();
    
    /// Directory watching loop.
    virtual void ThreadFunction();
    
    /// Start watching a directory. Return true if successful.
    bool StartWatching(const String& pathName, bool watchSubDirs);
    /// Stop watching the directory.
    void StopWatching();
    /// Return a file change (true if was found, false if not.)
    bool GetNextChange(String& dest);
    
    /// Return the path being watched, or empty if not watching.
    const String& GetPath() const { return path_; }
    
private:
    /// The path being watched.
    String path_;
    /// Buffered file changes.
    List<String> changes_;
    /// Mutex for the change buffer.
    Mutex changesMutex_;
    /// Watch subdirectories flag.
    bool watchSubDirs_;
    
    // Directory handle for the path being watched
    void* dirHandle_;
};
