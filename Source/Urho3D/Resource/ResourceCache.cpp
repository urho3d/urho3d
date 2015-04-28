//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Resource/BackgroundLoader.h"
#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../IO/FileSystem.h"
#include "../IO/FileWatcher.h"
#include "../Resource/Image.h"
#include "../Resource/JSONFile.h"
#include "../IO/Log.h"
#include "../IO/PackageFile.h"
#include "../Resource/PListFile.h"
#include "../Core/Profiler.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/ResourceEvents.h"
#include "../Core/WorkQueue.h"
#include "../Resource/XMLFile.h"

#include "../DebugNew.h"

namespace Urho3D
{

static const char* checkDirs[] = {
    "Fonts",
    "Materials",
    "Models",
    "Music",
    "Objects",
    "Particle",
    "PostProcess",
    "RenderPaths",
    "Scenes",
    "Scripts",
    "Sounds",
    "Shaders",
    "Techniques",
    "Textures",
    "UI",
    0
};

static const SharedPtr<Resource> noResource;

ResourceCache::ResourceCache(Context* context) :
    Object(context),
    autoReloadResources_(false),
    returnFailedResources_(false),
    searchPackagesFirst_(true),
    finishBackgroundResourcesMs_(5)
{
    // Register Resource library object factories
    RegisterResourceLibrary(context_);
    
    // Create resource background loader. Its thread will start on the first background request
    backgroundLoader_ = new BackgroundLoader(this);
    
    // Subscribe BeginFrame for handling directory watchers and background loaded resource finalization
    SubscribeToEvent(E_BEGINFRAME, HANDLER(ResourceCache, HandleBeginFrame));
}

ResourceCache::~ResourceCache()
{
    // Shut down the background loader first
    backgroundLoader_.Reset();
}

bool ResourceCache::AddResourceDir(const String& pathName, unsigned priority)
{
    MutexLock lock(resourceMutex_);
    
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (!fileSystem || !fileSystem->DirExists(pathName))
    {
        LOGERROR("Could not open directory " + pathName);
        return false;
    }
    
    // Convert path to absolute
    String fixedPath = SanitateResourceDirName(pathName);
    
    // Check that the same path does not already exist
    for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
    {
        if (!resourceDirs_[i].Compare(fixedPath, false))
            return true;
    }
    
    if (priority < resourceDirs_.Size())
        resourceDirs_.Insert(priority, fixedPath);
    else
        resourceDirs_.Push(fixedPath);
    
    // If resource auto-reloading active, create a file watcher for the directory
    if (autoReloadResources_)
    {
        SharedPtr<FileWatcher> watcher(new FileWatcher(context_));
        watcher->StartWatching(fixedPath, true);
        fileWatchers_.Push(watcher);
    }
    
    LOGINFO("Added resource path " + fixedPath);
    return true;
}

bool ResourceCache::AddPackageFile(PackageFile* package, unsigned priority)
{
    MutexLock lock(resourceMutex_);
    
    // Do not add packages that failed to load
    if (!package || !package->GetNumFiles())
        return false;
    
    if (priority < packages_.Size())
        packages_.Insert(priority, SharedPtr<PackageFile>(package));
    else
        packages_.Push(SharedPtr<PackageFile>(package));
    
    LOGINFO("Added resource package " + package->GetName());
    return true;
}

bool ResourceCache::AddPackageFile(const String& fileName, unsigned priority)
{
    SharedPtr<PackageFile> package(new PackageFile(context_));
    return package->Open(fileName) && AddPackageFile(package);
}

bool ResourceCache::AddManualResource(Resource* resource)
{
    if (!resource)
    {
        LOGERROR("Null manual resource");
        return false;
    }
    
    const String& name = resource->GetName();
    if (name.Empty())
    {
        LOGERROR("Manual resource with empty name, can not add");
        return false;
    }
    
    resource->ResetUseTimer();
    resourceGroups_[resource->GetType()].resources_[resource->GetNameHash()] = resource;
    UpdateResourceGroup(resource->GetType());
    return true;
}

void ResourceCache::RemoveResourceDir(const String& pathName)
{
    MutexLock lock(resourceMutex_);
    
    String fixedPath = SanitateResourceDirName(pathName);
    
    for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
    {
        if (!resourceDirs_[i].Compare(fixedPath, false))
        {
            resourceDirs_.Erase(i);
            // Remove the filewatcher with the matching path
            for (unsigned j = 0; j < fileWatchers_.Size(); ++j)
            {
                if (!fileWatchers_[j]->GetPath().Compare(fixedPath, false))
                {
                    fileWatchers_.Erase(j);
                    break;
                }
            }
            LOGINFO("Removed resource path " + fixedPath);
            return;
        }
    }
}

void ResourceCache::RemovePackageFile(PackageFile* package, bool releaseResources, bool forceRelease)
{
    MutexLock lock(resourceMutex_);
    
    for (Vector<SharedPtr<PackageFile> >::Iterator i = packages_.Begin(); i != packages_.End(); ++i)
    {
        if (*i == package)
        {
            if (releaseResources)
                ReleasePackageResources(*i, forceRelease);
            LOGINFO("Removed resource package " + (*i)->GetName());
            packages_.Erase(i);
            return;
        }
    }
}

void ResourceCache::RemovePackageFile(const String& fileName, bool releaseResources, bool forceRelease)
{
    MutexLock lock(resourceMutex_);

    // Compare the name and extension only, not the path
    String fileNameNoPath = GetFileNameAndExtension(fileName);
    
    for (Vector<SharedPtr<PackageFile> >::Iterator i = packages_.Begin(); i != packages_.End(); ++i)
    {
        if (!GetFileNameAndExtension((*i)->GetName()).Compare(fileNameNoPath, false))
        {
            if (releaseResources)
                ReleasePackageResources(*i, forceRelease);
            LOGINFO("Removed resource package " + (*i)->GetName());
            packages_.Erase(i);
            return;
        }
    }
}

void ResourceCache::ReleaseResource(StringHash type, const String& name, bool force)
{
    StringHash nameHash(name);
    const SharedPtr<Resource>& existingRes = FindResource(type, nameHash);
    if (!existingRes)
        return;
    
    // If other references exist, do not release, unless forced
    if ((existingRes.Refs() == 1 && existingRes.WeakRefs() == 0) || force)
    {
        resourceGroups_[type].resources_.Erase(nameHash);
        UpdateResourceGroup(type);
    }
}

void ResourceCache::ReleaseResources(StringHash type, bool force)
{
    bool released = false;
    
    HashMap<StringHash, ResourceGroup>::Iterator i = resourceGroups_.Find(type);
    if (i != resourceGroups_.End())
    {
        for (HashMap<StringHash, SharedPtr<Resource> >::Iterator j = i->second_.resources_.Begin();
            j != i->second_.resources_.End();)
        {
            HashMap<StringHash, SharedPtr<Resource> >::Iterator current = j++;
            // If other references exist, do not release, unless forced
            if ((current->second_.Refs() == 1 && current->second_.WeakRefs() == 0) || force)
            {
                i->second_.resources_.Erase(current);
                released = true;
            }
        }
    }
    
    if (released)
        UpdateResourceGroup(type);
}

void ResourceCache::ReleaseResources(StringHash type, const String& partialName, bool force)
{
    bool released = false;
    
    HashMap<StringHash, ResourceGroup>::Iterator i = resourceGroups_.Find(type);
    if (i != resourceGroups_.End())
    {
        for (HashMap<StringHash, SharedPtr<Resource> >::Iterator j = i->second_.resources_.Begin();
            j != i->second_.resources_.End();)
        {
            HashMap<StringHash, SharedPtr<Resource> >::Iterator current = j++;
            if (current->second_->GetName().Contains(partialName))
            {
                // If other references exist, do not release, unless forced
                if ((current->second_.Refs() == 1 && current->second_.WeakRefs() == 0) || force)
                {
                    i->second_.resources_.Erase(current);
                    released = true;
                }
            }
        }
    }
    
    if (released)
        UpdateResourceGroup(type);
}

void ResourceCache::ReleaseResources(const String& partialName, bool force)
{
    // Some resources refer to others, like materials to textures. Release twice to ensure these get released.
    // This is not necessary if forcing release
    unsigned repeat = force ? 1 : 2;
    
    while (repeat--)
    {
        for (HashMap<StringHash, ResourceGroup>::Iterator i = resourceGroups_.Begin(); i != resourceGroups_.End(); ++i)
        {
            bool released = false;
            
            for (HashMap<StringHash, SharedPtr<Resource> >::Iterator j = i->second_.resources_.Begin();
                j != i->second_.resources_.End();)
            {
                HashMap<StringHash, SharedPtr<Resource> >::Iterator current = j++;
                if (current->second_->GetName().Contains(partialName))
                {
                    // If other references exist, do not release, unless forced
                    if ((current->second_.Refs() == 1 && current->second_.WeakRefs() == 0) || force)
                    {
                        i->second_.resources_.Erase(current);
                        released = true;
                    }
                }
            }
            if (released)
                UpdateResourceGroup(i->first_);
        }
    }
}

void ResourceCache::ReleaseAllResources(bool force)
{
    unsigned repeat = force ? 1 : 2;
    
    while (repeat--)
    {
        for (HashMap<StringHash, ResourceGroup>::Iterator i = resourceGroups_.Begin();
            i != resourceGroups_.End(); ++i)
        {
            bool released = false;
            
            for (HashMap<StringHash, SharedPtr<Resource> >::Iterator j = i->second_.resources_.Begin();
                j != i->second_.resources_.End();)
            {
                HashMap<StringHash, SharedPtr<Resource> >::Iterator current = j++;
                // If other references exist, do not release, unless forced
                if ((current->second_.Refs() == 1 && current->second_.WeakRefs() == 0) || force)
                {
                    i->second_.resources_.Erase(current);
                    released = true;
                }
            }
            if (released)
                UpdateResourceGroup(i->first_);
        }
    }
}

bool ResourceCache::ReloadResource(Resource* resource)
{
    if (!resource)
        return false;
    
    resource->SendEvent(E_RELOADSTARTED);
    
    bool success = false;
    SharedPtr<File> file = GetFile(resource->GetName());
    if (file)
        success = resource->Load(*(file.Get()));
    
    if (success)
    {
        resource->ResetUseTimer();
        UpdateResourceGroup(resource->GetType());
        resource->SendEvent(E_RELOADFINISHED);
        return true;
    }
    
    // If reloading failed, do not remove the resource from cache, to allow for a new live edit to
    // attempt loading again
    resource->SendEvent(E_RELOADFAILED);
    return false;
}

void ResourceCache::ReloadResourceWithDependencies(const String& fileName)
{
    StringHash fileNameHash(fileName);
    // If the filename is a resource we keep track of, reload it
    const SharedPtr<Resource>& resource = FindResource(fileNameHash);
    if (resource)
    {
        LOGDEBUG("Reloading changed resource " + fileName);
        ReloadResource(resource);
    }
    // Always perform dependency resource check for resource loaded from XML file as it could be used in inheritance
    if (!resource || GetExtension(resource->GetName()) == ".xml")
    {
        // Check if this is a dependency resource, reload dependents
        HashMap<StringHash, HashSet<StringHash> >::ConstIterator j = dependentResources_.Find(fileNameHash);
        if (j != dependentResources_.End())
        {
            // Reloading a resource may modify the dependency tracking structure. Therefore collect the
            // resources we need to reload first
            Vector<SharedPtr<Resource> > dependents;
            dependents.Reserve(j->second_.Size());
            
            for (HashSet<StringHash>::ConstIterator k = j->second_.Begin(); k != j->second_.End(); ++k)
            {
                const SharedPtr<Resource>& dependent = FindResource(*k);
                if (dependent)
                    dependents.Push(dependent);
            }
            
            for (unsigned k = 0; k < dependents.Size(); ++k)
            {
                LOGDEBUG("Reloading resource " + dependents[k]->GetName() + " depending on " + fileName);
                ReloadResource(dependents[k]);
            }
        }
    }
}

void ResourceCache::SetMemoryBudget(StringHash type, unsigned budget)
{
    resourceGroups_[type].memoryBudget_ = budget;
}

void ResourceCache::SetAutoReloadResources(bool enable)
{
    if (enable != autoReloadResources_)
    {
        if (enable)
        {
            for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
            {
                SharedPtr<FileWatcher> watcher(new FileWatcher(context_));
                watcher->StartWatching(resourceDirs_[i], true);
                fileWatchers_.Push(watcher);
            }
        }
        else
            fileWatchers_.Clear();
        
        autoReloadResources_ = enable;
    }
}

void ResourceCache::SetReturnFailedResources(bool enable)
{
    returnFailedResources_ = enable;
}

SharedPtr<File> ResourceCache::GetFile(const String& nameIn, bool sendEventOnFailure)
{
    MutexLock lock(resourceMutex_);
    
    String name = SanitateResourceName(nameIn);
    if (resourceRouter_)
        resourceRouter_->Route(name, RESOURCE_GETFILE);
    
    if (name.Length())
    {
        File* file = 0;

        if (searchPackagesFirst_)
        {
            file = SearchPackages(name);
            if (!file)
                file = SearchResourceDirs(name);
        }
        else
        {
            file = SearchResourceDirs(name);
            if (!file)
                file = SearchPackages(name);
        }
        
        if (file)
            return SharedPtr<File>(file);
    }
    
    if (sendEventOnFailure)
    {
        if (resourceRouter_ && name.Empty() && !nameIn.Empty())
            LOGERROR("Resource request " + nameIn + " was blocked");
        else
            LOGERROR("Could not find resource " + name);

        if (Thread::IsMainThread())
        {
            using namespace ResourceNotFound;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_RESOURCENAME] = name.Length() ? name : nameIn;
            SendEvent(E_RESOURCENOTFOUND, eventData);
        }
    }

    return SharedPtr<File>();
}

Resource* ResourceCache::GetResource(StringHash type, const String& nameIn, bool sendEventOnFailure)
{
    String name = SanitateResourceName(nameIn);
    
    if (!Thread::IsMainThread())
    {
        LOGERROR("Attempted to get resource " + name + " from outside the main thread");
        return 0;
    }
    
    // If empty name, return null pointer immediately
    if (name.Empty())
        return 0;
    
    StringHash nameHash(name);

    // Check if the resource is being background loaded but is now needed immediately
    backgroundLoader_->WaitForResource(type, nameHash);

    const SharedPtr<Resource>& existing = FindResource(type, nameHash);
    if (existing)
        return existing;
    
    SharedPtr<Resource> resource;
    // Make sure the pointer is non-null and is a Resource subclass
    resource = DynamicCast<Resource>(context_->CreateObject(type));
    if (!resource)
    {
        LOGERROR("Could not load unknown resource type " + String(type));

        if (sendEventOnFailure)
        {
            using namespace UnknownResourceType;
            
            VariantMap& eventData = GetEventDataMap();
            eventData[P_RESOURCETYPE] = type;
            SendEvent(E_UNKNOWNRESOURCETYPE, eventData);
        }
        
        return 0;
    }
    
    // Attempt to load the resource
    SharedPtr<File> file = GetFile(name, sendEventOnFailure);
    if (!file)
        return 0;   // Error is already logged

    LOGDEBUG("Loading resource " + name);
    resource->SetName(name);

    if (!resource->Load(*(file.Get())))
    {
        // Error should already been logged by corresponding resource descendant class
        if (sendEventOnFailure)
        {
            using namespace LoadFailed;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_RESOURCENAME] = name;
            SendEvent(E_LOADFAILED, eventData);
        }
        
        if (!returnFailedResources_)
            return 0;
    }
    
    // Store to cache
    resource->ResetUseTimer();
    resourceGroups_[type].resources_[nameHash] = resource;
    UpdateResourceGroup(type);
    
    return resource;
}

bool ResourceCache::BackgroundLoadResource(StringHash type, const String& nameIn, bool sendEventOnFailure, Resource* caller)
{
    // If empty name, fail immediately
    String name = SanitateResourceName(nameIn);
    if (name.Empty())
        return false;
    
    // First check if already exists as a loaded resource
    StringHash nameHash(name);
    if (FindResource(type, nameHash) != noResource)
        return false;
    
    return backgroundLoader_->QueueResource(type, name, sendEventOnFailure, caller);
}

SharedPtr<Resource> ResourceCache::GetTempResource(StringHash type, const String& nameIn, bool sendEventOnFailure)
{
    String name = SanitateResourceName(nameIn);
    
    // If empty name, return null pointer immediately
    if (name.Empty())
        return SharedPtr<Resource>();
    
    SharedPtr<Resource> resource;
    // Make sure the pointer is non-null and is a Resource subclass
    resource = DynamicCast<Resource>(context_->CreateObject(type));
    if (!resource)
    {
        LOGERROR("Could not load unknown resource type " + String(type));

        if (sendEventOnFailure)
        {
            using namespace UnknownResourceType;
            
            VariantMap& eventData = GetEventDataMap();
            eventData[P_RESOURCETYPE] = type;
            SendEvent(E_UNKNOWNRESOURCETYPE, eventData);
        }
        
        return SharedPtr<Resource>();
    }
    
    // Attempt to load the resource
    SharedPtr<File> file = GetFile(name, sendEventOnFailure);
    if (!file)
        return SharedPtr<Resource>();  // Error is already logged

    LOGDEBUG("Loading temporary resource " + name);
    resource->SetName(file->GetName());

    if (!resource->Load(*(file.Get())))
    {
        // Error should already been logged by corresponding resource descendant class
        if (sendEventOnFailure)
        {
            using namespace LoadFailed;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_RESOURCENAME] = name;
            SendEvent(E_LOADFAILED, eventData);
        }
        
        return SharedPtr<Resource>();
    }
    
    return resource;
}

unsigned ResourceCache::GetNumBackgroundLoadResources() const
{
    return backgroundLoader_->GetNumQueuedResources();
}

void ResourceCache::GetResources(PODVector<Resource*>& result, StringHash type) const
{
    result.Clear();
    HashMap<StringHash, ResourceGroup>::ConstIterator i = resourceGroups_.Find(type);
    if (i != resourceGroups_.End())
    {
        for (HashMap<StringHash, SharedPtr<Resource> >::ConstIterator j = i->second_.resources_.Begin();
            j != i->second_.resources_.End(); ++j)
            result.Push(j->second_);
    }
}

bool ResourceCache::Exists(const String& nameIn) const
{
    MutexLock lock(resourceMutex_);
    
    String name = SanitateResourceName(nameIn);
    if (resourceRouter_)
        resourceRouter_->Route(name, RESOURCE_CHECKEXISTS);
    
    if (name.Empty())
        return false;
    
    for (unsigned i = 0; i < packages_.Size(); ++i)
    {
        if (packages_[i]->Exists(name))
            return true;
    }
    
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
    {
        if (fileSystem->FileExists(resourceDirs_[i] + name))
            return true;
    }
    
    // Fallback using absolute path
    if (fileSystem->FileExists(name))
        return true;

    return false;
}

unsigned ResourceCache::GetMemoryBudget(StringHash type) const
{
    HashMap<StringHash, ResourceGroup>::ConstIterator i = resourceGroups_.Find(type);
    if (i != resourceGroups_.End())
        return i->second_.memoryBudget_;
    else
        return 0;
}

unsigned ResourceCache::GetMemoryUse(StringHash type) const
{
    HashMap<StringHash, ResourceGroup>::ConstIterator i = resourceGroups_.Find(type);
    if (i != resourceGroups_.End())
        return i->second_.memoryUse_;
    else
        return 0;
}

unsigned ResourceCache::GetTotalMemoryUse() const
{
    unsigned total = 0;
    for (HashMap<StringHash, ResourceGroup>::ConstIterator i = resourceGroups_.Begin(); i != resourceGroups_.End(); ++i)
        total += i->second_.memoryUse_;
    return total;
}

String ResourceCache::GetResourceFileName(const String& name) const
{
    MutexLock lock(resourceMutex_);
    
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
    {
        if (fileSystem->FileExists(resourceDirs_[i] + name))
            return resourceDirs_[i] + name;
    }
    
    return String();
}

String ResourceCache::GetPreferredResourceDir(const String& path) const
{
    String fixedPath = AddTrailingSlash(path);
    
    bool pathHasKnownDirs = false;
    bool parentHasKnownDirs = false;
    
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    
    for (unsigned i = 0; checkDirs[i] != 0; ++i)
    {
        if (fileSystem->DirExists(fixedPath + checkDirs[i]))
        {
            pathHasKnownDirs = true;
            break;
        }
    }
    if (!pathHasKnownDirs)
    {
        String parentPath = GetParentPath(fixedPath);
        for (unsigned i = 0; checkDirs[i] != 0; ++i)
        {
            if (fileSystem->DirExists(parentPath + checkDirs[i]))
            {
                parentHasKnownDirs = true;
                break;
            }
        }
        // If path does not have known subdirectories, but the parent path has, use the parent instead
        if (parentHasKnownDirs)
            fixedPath = parentPath;
    }
    
    return fixedPath;
}

String ResourceCache::SanitateResourceName(const String& nameIn) const
{
    // Sanitate unsupported constructs from the resource name
    String name = GetInternalPath(nameIn);
    name.Replace("../", "");
    name.Replace("./", "");

    // If the path refers to one of the resource directories, normalize the resource name
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (resourceDirs_.Size())
    {
        String namePath = GetPath(name);
        String exePath = fileSystem->GetProgramDir();
        for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
        {
            String relativeResourcePath = resourceDirs_[i];
            if (relativeResourcePath.StartsWith(exePath))
                relativeResourcePath = relativeResourcePath.Substring(exePath.Length());
            
            if (namePath.StartsWith(resourceDirs_[i], false))
                namePath = namePath.Substring(resourceDirs_[i].Length());
            else if (namePath.StartsWith(relativeResourcePath, false))
                namePath = namePath.Substring(relativeResourcePath.Length());
        }

        name = namePath + GetFileNameAndExtension(name);
    }

    return name.Trimmed();
}

String ResourceCache::SanitateResourceDirName(const String& nameIn) const
{
    String fixedPath = AddTrailingSlash(nameIn);
    if (!IsAbsolutePath(fixedPath))
        fixedPath = GetSubsystem<FileSystem>()->GetCurrentDir() + fixedPath;
    
    // Sanitate away /./ construct
    fixedPath.Replace("/./", "/");
    
    return fixedPath.Trimmed();
}

void ResourceCache::StoreResourceDependency(Resource* resource, const String& dependency)
{
    // If resource reloading is not on, do not create the dependency data structure (saves memory)
    if (!resource || !autoReloadResources_)
        return;
    
    MutexLock lock(resourceMutex_);
    
    StringHash nameHash(resource->GetName());
    HashSet<StringHash>& dependents = dependentResources_[dependency];
    dependents.Insert(nameHash);
}

void ResourceCache::ResetDependencies(Resource* resource)
{
    if (!resource || !autoReloadResources_)
        return;
    
    MutexLock lock(resourceMutex_);
    
    StringHash nameHash(resource->GetName());
    
    for (HashMap<StringHash, HashSet<StringHash> >::Iterator i = dependentResources_.Begin(); i !=
        dependentResources_.End();)
    {
        HashSet<StringHash>& dependents = i->second_;
        dependents.Erase(nameHash);
        if (dependents.Empty())
            i = dependentResources_.Erase(i);
        else
            ++i;
    }
}

const SharedPtr<Resource>& ResourceCache::FindResource(StringHash type, StringHash nameHash)
{
    MutexLock lock(resourceMutex_);

    HashMap<StringHash, ResourceGroup>::Iterator i = resourceGroups_.Find(type);
    if (i == resourceGroups_.End())
        return noResource;
    HashMap<StringHash, SharedPtr<Resource> >::Iterator j = i->second_.resources_.Find(nameHash);
    if (j == i->second_.resources_.End())
        return noResource;
    
    return j->second_;
}

const SharedPtr<Resource>& ResourceCache::FindResource(StringHash nameHash)
{
    MutexLock lock(resourceMutex_);

    for (HashMap<StringHash, ResourceGroup>::Iterator i = resourceGroups_.Begin(); i != resourceGroups_.End(); ++i)
    {
        HashMap<StringHash, SharedPtr<Resource> >::Iterator j = i->second_.resources_.Find(nameHash);
        if (j != i->second_.resources_.End())
            return j->second_;
    }
    
    return noResource;
}

void ResourceCache::ReleasePackageResources(PackageFile* package, bool force)
{
    HashSet<StringHash> affectedGroups;
    
    const HashMap<String, PackageEntry>& entries = package->GetEntries();
    for (HashMap<String, PackageEntry>::ConstIterator i = entries.Begin(); i != entries.End(); ++i)
    {
        StringHash nameHash(i->first_);
        
        // We do not know the actual resource type, so search all type containers
        for (HashMap<StringHash, ResourceGroup>::Iterator j = resourceGroups_.Begin();
            j != resourceGroups_.End(); ++j)
        {
            HashMap<StringHash, SharedPtr<Resource> >::Iterator k = j->second_.resources_.Find(nameHash);
            if (k != j->second_.resources_.End())
            {
                // If other references exist, do not release, unless forced
                if ((k->second_.Refs() == 1 && k->second_.WeakRefs() == 0) || force)
                {
                    j->second_.resources_.Erase(k);
                    affectedGroups.Insert(j->first_);
                }
                break;
            }
        }
    }
    
    for (HashSet<StringHash>::Iterator i = affectedGroups.Begin(); i != affectedGroups.End(); ++i)
        UpdateResourceGroup(*i);
}

void ResourceCache::UpdateResourceGroup(StringHash type)
{
    HashMap<StringHash, ResourceGroup>::Iterator i = resourceGroups_.Find(type);
    if (i == resourceGroups_.End())
        return;
    
    for (;;)
    {
        unsigned totalSize = 0;
        unsigned oldestTimer = 0;
        HashMap<StringHash, SharedPtr<Resource> >::Iterator oldestResource = i->second_.resources_.End();
        
        for (HashMap<StringHash, SharedPtr<Resource> >::Iterator j = i->second_.resources_.Begin();
            j != i->second_.resources_.End(); ++j)
        {
            totalSize += j->second_->GetMemoryUse();
            unsigned useTimer = j->second_->GetUseTimer();
            if (useTimer > oldestTimer)
            {
                oldestTimer = useTimer;
                oldestResource = j;
            }
        }
        
        i->second_.memoryUse_ = totalSize;
        
        // If memory budget defined and is exceeded, remove the oldest resource and loop again
        // (resources in use always return a zero timer and can not be removed)
        if (i->second_.memoryBudget_ && i->second_.memoryUse_ > i->second_.memoryBudget_ &&
            oldestResource != i->second_.resources_.End())
        {
            LOGDEBUG("Resource group " + oldestResource->second_->GetTypeName() + " over memory budget, releasing resource " +
                oldestResource->second_->GetName());
            i->second_.resources_.Erase(oldestResource);
        }
        else
            break;
    }
}

void ResourceCache::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    for (unsigned i = 0; i < fileWatchers_.Size(); ++i)
    {
        String fileName;
        while (fileWatchers_[i]->GetNextChange(fileName))
        {
            ReloadResourceWithDependencies(fileName);

            // Finally send a general file changed event even if the file was not a tracked resource
            using namespace FileChanged;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_FILENAME] = fileWatchers_[i]->GetPath() + fileName;
            eventData[P_RESOURCENAME] = fileName;
            SendEvent(E_FILECHANGED, eventData);
        }
    }
    
    // Check for background loaded resources that can be finished
    {
        PROFILE(FinishBackgroundResources);
        backgroundLoader_->FinishResources(finishBackgroundResourcesMs_);
    }
}

File* ResourceCache::SearchResourceDirs(const String& nameIn)
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
    {
        if (fileSystem->FileExists(resourceDirs_[i] + nameIn))
        {
            // Construct the file first with full path, then rename it to not contain the resource path,
            // so that the file's name can be used in further GetFile() calls (for example over the network)
            File* file(new File(context_, resourceDirs_[i] + nameIn));
            file->SetName(nameIn);
            return file;
        }
    }

    // Fallback using absolute path
    if (fileSystem->FileExists(nameIn))
        return new File(context_, nameIn);

    return 0;
}

File* ResourceCache::SearchPackages(const String& nameIn)
{
    for (unsigned i = 0; i < packages_.Size(); ++i)
    {
        if (packages_[i]->Exists(nameIn))
            return new File(context_, packages_[i], nameIn);
    }

    return 0;
}

void RegisterResourceLibrary(Context* context)
{
    Image::RegisterObject(context);
    JSONFile::RegisterObject(context);
    PListFile::RegisterObject(context);
    XMLFile::RegisterObject(context);
}

}
