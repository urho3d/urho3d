// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// Return true when the running OS has the specified version number or later.
bool CheckMinimalVersion(int major, int minor);

/// Return true when individual file watcher is supported by the running Mac OS X.
bool IsFileWatcherSupported();

/// Create and start the file watcher.
void* CreateFileWatcher(const char* pathname, bool watchSubDirs);

/// Stop and release the file watcher.
void CloseFileWatcher(void* watcher);

/// Read changes queued by the file watcher.
const char* ReadFileWatcher(void* watcher);
