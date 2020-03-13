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

#import <Foundation/Foundation.h>
#import <CoreServices/CoreServices.h>

#include "../IO/MacFileWatcher.h"

static void CallbackFunction(ConstFSEventStreamRef streamRef, void* clientCallBackInfo, size_t numEvents, void* eventPaths, const FSEventStreamEventFlags eventFlags[], const FSEventStreamEventId eventIds[]);

@interface MacFileWatcher : NSObject
{
    NSString* pathName_;
    bool watchSubDirs_;
    FSEventStreamRef streamRef_;
    NSMutableString* changes_;
}

@property (nonatomic, retain) NSString* pathName;
@property (nonatomic, assign) bool watchSubDirs;
@property (nonatomic, retain) NSMutableString* changes;

- (MacFileWatcher*)initWithPathName:(const char*)pathName recursive:(bool)watchSubDirs;
- (const char*)readChanges;
- (void)addChange:(NSString*)fileName;

@end

@implementation MacFileWatcher

@synthesize pathName=pathName_;
@synthesize watchSubDirs=watchSubDirs_;
@synthesize changes=changes_;

- (MacFileWatcher*)initWithPathName:(const char*)pathName recursive:(bool)watchSubDirs
{
    self = [super init];
    if (self)
    {
        self.pathName = [[[NSString stringWithUTF8String:pathName] stringByResolvingSymlinksInPath] stringByAppendingString:@"/"];
        self.watchSubDirs = watchSubDirs;
        self.changes = [NSMutableString stringWithString:@""];

        CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)&pathName_, 1, NULL);
        FSEventStreamContext context = {0, self, NULL, NULL, NULL};
        CFAbsoluteTime latency = 0.1;   // in seconds
        streamRef_ = FSEventStreamCreate(NULL, &CallbackFunction, &context, pathsToWatch, kFSEventStreamEventIdSinceNow, latency, kFSEventStreamCreateFlagUseCFTypes | kFSEventStreamCreateFlagFileEvents);
        CFRelease(pathsToWatch);

        if (streamRef_)
        {
            FSEventStreamScheduleWithRunLoop(streamRef_, CFRunLoopGetMain(), kCFRunLoopDefaultMode);
            if (!FSEventStreamStart(streamRef_))
            {
                [self release];
                return nil;
            }
        }

    }
    return self;
}

- (void)dealloc
{
    FSEventStreamStop(streamRef_);
    FSEventStreamInvalidate(streamRef_);
    FSEventStreamRelease(streamRef_);
    streamRef_ = NULL;
    
    self.changes = nil;
    self.pathName = nil;
    [super dealloc];
}

- (const char*)readChanges
{
    @synchronized(changes_)
    {
        const char* changes = [changes_ UTF8String];
        [changes_ setString:@""];
        return changes;
    }
}

- (void)addChange:(NSString*)fileName
{
    @synchronized(changes_)
    {
        // Use character with ASCII code 1 as separator character
        [changes_ appendFormat:@"%@%c", fileName, 1];
    }
}

@end

static void CallbackFunction(ConstFSEventStreamRef streamRef, void* clientCallBackInfo, size_t numEvents, void* eventPaths, const FSEventStreamEventFlags eventFlags[], const FSEventStreamEventId eventIds[])
{
    MacFileWatcher* watcher = (MacFileWatcher*)clientCallBackInfo;
    NSArray* paths = eventPaths;
    int index = -1;
    for (NSString* fileName in paths)
    {
        ++index;
        if (![fileName length])
            continue;
        if ([[fileName lastPathComponent] isEqualToString:@".DS_Store"])
            continue;
        if ([fileName hasPrefix:watcher.pathName])
            fileName = [fileName substringFromIndex:[watcher.pathName length]];
        
        // Skip if event path is a sub dir and watch sub dirs is not requested
        if (!watcher.watchSubDirs && [fileName rangeOfString:@"/"].location != NSNotFound)
            continue;

        FSEventStreamEventFlags flags = eventFlags[index];
        if (flags & kFSEventStreamEventFlagItemIsFile && (
            flags & kFSEventStreamEventFlagItemCreated || flags & kFSEventStreamEventFlagItemModified ||
            flags & kFSEventStreamEventFlagItemRenamed || flags & kFSEventStreamEventFlagItemRemoved))
        {
            [watcher addChange:fileName];
        }
    }
}

bool CheckMinimalVersion(int major, int minor)
{
    NSString* plistPath = @"/System/Library/CoreServices/SystemVersion.plist";
    NSDictionary* pListDict = [[[NSDictionary alloc] initWithContentsOfFile:plistPath] autorelease];
    NSString* productVersion = [pListDict valueForKey:@"ProductVersion"];
    NSArray* parts = [productVersion componentsSeparatedByString: @"."];
    if ([[parts objectAtIndex:0] integerValue] < major)
        return false;
    if ([[parts objectAtIndex:1] integerValue] < minor)
        return false;
    return true;
}

bool IsFileWatcherSupported()
{
    // The FS Event API only supports individual file watching in 10.7 (Lion) or later 
    return CheckMinimalVersion(10, 7);
}

void* CreateFileWatcher(const char* pathName, bool watchSubDirs)
{
    // Do not autorelease as the caller has no way to retain it
    return [[MacFileWatcher alloc] initWithPathName:pathName recursive:watchSubDirs];
}

void CloseFileWatcher(void* watcher)
{
    // Release the object now
    [(MacFileWatcher*)watcher release];
}

const char* ReadFileWatcher(void* watcher)
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    const char* result = [(MacFileWatcher*)watcher readChanges];
    [pool release];
    pool = nil;
    return result;
}
