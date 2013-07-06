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
#include "Context.h"
#include "CoreEvents.h"
#include "FileSystem.h"
#include "FileWatcher.h"
#include "Image.h"
#include "Log.h"
#include "PackageFile.h"
#include "ResourceCache.h"
#include "ResourceEvents.h"
#include "XMLFile.h"

#include "DebugNew.h"

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
    autoReloadResources_(false)
{
    // Register Resource library object factories
    RegisterResourceLibrary(context_);
}

ResourceCache::~ResourceCache()
{
}

bool ResourceCache::AddResourceDir(const String& pathName)
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (!fileSystem || !fileSystem->DirExists(pathName))
    {
        LOGERROR("Could not open directory " + pathName);
        return false;
    }
    
    String fixedPath = AddTrailingSlash(pathName);
    
    // Check that the same path does not already exist
    for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
    {
        if (!resourceDirs_[i].Compare(fixedPath, false))
            return true;
    }
    
    resourceDirs_.Push(fixedPath);
    
    // Scan the path for files recursively and add their hash-to-name mappings
    Vector<String> fileNames;
    fileSystem->ScanDir(fileNames, fixedPath, "*.*", SCAN_FILES, true);
    for (unsigned i = 0; i < fileNames.Size(); ++i)
        StoreNameHash(fileNames[i]);
    
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

void ResourceCache::AddPackageFile(PackageFile* package, bool addAsFirst)
{
    // Do not add packages that failed to load
    if (!package || !package->GetNumFiles())
        return;
    
    if (addAsFirst)
        packages_.Insert(packages_.Begin(), SharedPtr<PackageFile>(package));
    else
        packages_.Push(SharedPtr<PackageFile>(package));
    
    // Scan the package for files and add their hash-to-name mappings
    const HashMap<String, PackageEntry>& entries = package->GetEntries();
    for (HashMap<String, PackageEntry>::ConstIterator i = entries.Begin(); i != entries.End(); ++i)
        StoreNameHash(i->first_);
    
    LOGINFO("Added resource package " + package->GetName());
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
    
    StoreNameHash(name);
    resource->ResetUseTimer();
    resourceGroups_[resource->GetType()].resources_[resource->GetNameHash()] = resource;
    UpdateResourceGroup(resource->GetType());
    return true;
}

void ResourceCache::RemoveResourceDir(const String& path)
{
    String fixedPath = AddTrailingSlash(path);
    for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
    {
        if (!resourceDirs_[i].Compare(path, false))
        {
            resourceDirs_.Erase(i);
            if (fileWatchers_.Size() > i)
                fileWatchers_.Erase(i);
            LOGINFO("Removed resource path " + fixedPath);
            return;
        }
    }
}

void ResourceCache::RemovePackageFile(PackageFile* package, bool releaseResources, bool forceRelease)
{
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

void ResourceCache::ReleaseResource(ShortStringHash type, const String& name, bool force)
{
    ReleaseResource(type, StringHash(name), force);
}

void ResourceCache::ReleaseResource(ShortStringHash type, StringHash nameHash, bool force)
{
    const SharedPtr<Resource>& existingRes = FindResource(type, nameHash);
    if (!existingRes)
        return;
    
    // If other references exist, do not release, unless forced
    if (existingRes.Refs() == 1 || force)
    {
        resourceGroups_[type].resources_.Erase(nameHash);
        UpdateResourceGroup(type);
    }
}

void ResourceCache::ReleaseResources(ShortStringHash type, bool force)
{
    bool released = false;
    
    HashMap<ShortStringHash, ResourceGroup>::Iterator i = resourceGroups_.Find(type);
    if (i != resourceGroups_.End())
    {
        for (HashMap<StringHash, SharedPtr<Resource> >::Iterator j = i->second_.resources_.Begin();
            j != i->second_.resources_.End();)
        {
            HashMap<StringHash, SharedPtr<Resource> >::Iterator current = j++;
            // If other references exist, do not release, unless forced
            if (current->second_.Refs() == 1 || force)
            {
                i->second_.resources_.Erase(current);
                released = true;
            }
        }
    }
    
    if (released)
        UpdateResourceGroup(type);
}

void ResourceCache::ReleaseResources(ShortStringHash type, const String& partialName, bool force)
{
    bool released = false;
    
    HashMap<ShortStringHash, ResourceGroup>::Iterator i = resourceGroups_.Find(type);
    if (i != resourceGroups_.End())
    {
        for (HashMap<StringHash, SharedPtr<Resource> >::Iterator j = i->second_.resources_.Begin();
            j != i->second_.resources_.End();)
        {
            HashMap<StringHash, SharedPtr<Resource> >::Iterator current = j++;
            if (current->second_->GetName().Contains(partialName))
            {
                // If other references exist, do not release, unless forced
                if (current->second_.Refs() == 1 || force)
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

void ResourceCache::ReleaseAllResources(bool force)
{
    for (HashMap<ShortStringHash, ResourceGroup>::Iterator i = resourceGroups_.Begin();
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

void ResourceCache::SetMemoryBudget(ShortStringHash type, unsigned budget)
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

            SubscribeToEvent(E_BEGINFRAME, HANDLER(ResourceCache, HandleBeginFrame));
        }
        else
        {
            UnsubscribeFromEvent(E_BEGINFRAME);
            fileWatchers_.Clear();
        }
        
        autoReloadResources_ = enable;
    }
}

SharedPtr<File> ResourceCache::GetFile(const String& nameIn)
{
    String name = SanitateResourceName(nameIn);
    
    // Check first the packages
    for (unsigned i = 0; i < packages_.Size(); ++i)
    {
        if (packages_[i]->Exists(name))
            return SharedPtr<File>(new File(context_, packages_[i], name));
    }
    
    // Then the filesystem
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem)
    {
        for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
        {
            if (fileSystem->FileExists(resourceDirs_[i] + name))
            {
                // Construct the file first with full path, then rename it to not contain the resource path,
                // so that the file's name can be used in further GetFile() calls (for example over the network)
                SharedPtr<File> file(new File(context_, resourceDirs_[i] + name));
                file->SetName(name);
                return file;
            }
        }
        
        // Fallback using absolute path
        if (fileSystem->FileExists(name))
            return SharedPtr<File>(new File(context_, name));
    }
    
    LOGERROR("Could not find resource " + name);
    return SharedPtr<File>();
}

Resource* ResourceCache::GetResource(ShortStringHash type, const String& nameIn)
{
    String name = SanitateResourceName(nameIn);
    
    // Add the name to the hash map, so if this is an unknown resource, the error will not be unintelligible
    StoreNameHash(name);
    
    return GetResource(type, StringHash(name));
}

Resource* ResourceCache::GetResource(ShortStringHash type, const char* name)
{
    return GetResource(type, String(name));
}

Resource* ResourceCache::GetResource(ShortStringHash type, StringHash nameHash)
{
    // If null hash, return null pointer immediately
    if (!nameHash)
        return 0;
    
    const SharedPtr<Resource>& existing = FindResource(type, nameHash);
    if (existing)
        return existing;
    
    SharedPtr<Resource> resource;
    const String& name = GetResourceName(nameHash);
    if (name.Empty())
    {
        LOGERROR("Could not load unknown resource " + String(nameHash));
        return 0;
    }
    
    // Make sure the pointer is non-null and is a Resource subclass
    resource = DynamicCast<Resource>(context_->CreateObject(type));
    if (!resource)
    {
        LOGERROR("Could not load unknown resource type " + String(type));
        return 0;
    }
    
    // Attempt to load the resource
    SharedPtr<File> file = GetFile(name);
    if (!file)
        return 0;
    
    LOGDEBUG("Loading resource " + name);
    resource->SetName(file->GetName());
    if (!resource->Load(*(file.Get())))
        return 0;
    
    // Store to cache
    resource->ResetUseTimer();
    resourceGroups_[type].resources_[nameHash] = resource;
    UpdateResourceGroup(type);
    
    return resource;
}

void ResourceCache::GetResources(PODVector<Resource*>& result, ShortStringHash type) const
{
    result.Clear();
    HashMap<ShortStringHash, ResourceGroup>::ConstIterator i = resourceGroups_.Find(type);
    if (i != resourceGroups_.End())
    {
        for (HashMap<StringHash, SharedPtr<Resource> >::ConstIterator j = i->second_.resources_.Begin();
            j != i->second_.resources_.End(); ++j)
            result.Push(j->second_);
    }
}

bool ResourceCache::Exists(const String& nameIn) const
{
    String name = SanitateResourceName(nameIn);
    
    for (unsigned i = 0; i < packages_.Size(); ++i)
    {
        if (packages_[i]->Exists(name))
            return true;
    }
    
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem)
    {
        for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
        {
            if (fileSystem->FileExists(resourceDirs_[i] + name))
                return true;
        }
        
        // Fallback using absolute path
        if (fileSystem->FileExists(name))
            return true;
    }
    
    return false;
}

bool ResourceCache::Exists(StringHash nameHash) const
{
    return Exists(GetResourceName(nameHash));
}

unsigned ResourceCache::GetMemoryBudget(ShortStringHash type) const
{
    HashMap<ShortStringHash, ResourceGroup>::ConstIterator i = resourceGroups_.Find(type);
    if (i != resourceGroups_.End())
        return i->second_.memoryBudget_;
    else
        return 0;
}

unsigned ResourceCache::GetMemoryUse(ShortStringHash type) const
{
    HashMap<ShortStringHash, ResourceGroup>::ConstIterator i = resourceGroups_.Find(type);
    if (i != resourceGroups_.End())
        return i->second_.memoryUse_;
    else
        return 0;
}

unsigned ResourceCache::GetTotalMemoryUse() const
{
    unsigned total = 0;
    for (HashMap<ShortStringHash, ResourceGroup>::ConstIterator i = resourceGroups_.Begin(); i != resourceGroups_.End(); ++i)
        total += i->second_.memoryUse_;
    return total;
}

const String& ResourceCache::GetResourceName(StringHash nameHash) const
{
    HashMap<StringHash, String>::ConstIterator i = hashToName_.Find(nameHash);
    if (i == hashToName_.End())
        return String::EMPTY;
    else
        return i->second_;
}

String ResourceCache::GetResourceFileName(const String& name) const
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem)
    {
        for (unsigned i = 0; i < resourceDirs_.Size(); ++i)
        {
            if (fileSystem->FileExists(resourceDirs_[i] + name))
                return resourceDirs_[i] + name;
        }
    }
    
    return String();
}

String ResourceCache::GetPreferredResourceDir(const String& path) const
{
    String fixedPath = AddTrailingSlash(path);
    
    bool pathHasKnownDirs = false;
    bool parentHasKnownDirs = false;
    
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    // If no filesystem, can not check directory existence, so just return the original path
    if (!fileSystem)
        return fixedPath;
    
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
    return name;
}

void ResourceCache::StoreNameHash(const String& name)
{
    if (name.Empty())
        return;
    
    StringHash hash(name);
    
    // If entry exists, check for difference (collision)
    HashMap<StringHash, String>::Iterator i = hashToName_.Find(hash);
    if (i != hashToName_.End())
    {
        if (i->second_.Compare(name, false))
            LOGERROR("Resource hash collision " + i->second_ + " vs " + name);
        i->second_ = name;
    }
    else
        hashToName_[hash] = name;
}

void ResourceCache::StoreResourceDependency(Resource* resource, const String& dependency)
{
    // If resource reloading is not on, do not create the dependency data structure (saves memory)
    if (!resource || !autoReloadResources_)
        return;
    
    StringHash nameHash(resource->GetName());
    HashSet<StringHash>& dependents = dependentResources_[dependency];
    dependents.Insert(nameHash);
}

void ResourceCache::ResetDependencies(Resource* resource)
{
    if (!resource || !autoReloadResources_)
        return;
    
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

const SharedPtr<Resource>& ResourceCache::FindResource(ShortStringHash type, StringHash nameHash)
{
    HashMap<ShortStringHash, ResourceGroup>::Iterator i = resourceGroups_.Find(type);
    if (i == resourceGroups_.End())
        return noResource;
    HashMap<StringHash, SharedPtr<Resource> >::Iterator j = i->second_.resources_.Find(nameHash);
    if (j == i->second_.resources_.End())
        return noResource;
    
    return j->second_;
}

const SharedPtr<Resource>& ResourceCache::FindResource(StringHash nameHash)
{
    for (HashMap<ShortStringHash, ResourceGroup>::Iterator i = resourceGroups_.Begin(); i != resourceGroups_.End(); ++i)
    {
        HashMap<StringHash, SharedPtr<Resource> >::Iterator j = i->second_.resources_.Find(nameHash);
        if (j != i->second_.resources_.End())
            return j->second_;
    }
    
    return noResource;
}

void ResourceCache::ReleasePackageResources(PackageFile* package, bool force)
{
    HashSet<ShortStringHash> affectedGroups;
    
    const HashMap<String, PackageEntry>& entries = package->GetEntries();
    for (HashMap<String, PackageEntry>::ConstIterator i = entries.Begin(); i != entries.End(); ++i)
    {
        StringHash nameHash(i->first_);
        
        // We do not know the actual resource type, so search all type containers
        for (HashMap<ShortStringHash, ResourceGroup>::Iterator j = resourceGroups_.Begin();
            j != resourceGroups_.End(); ++j)
        {
            HashMap<StringHash, SharedPtr<Resource> >::Iterator k = j->second_.resources_.Find(nameHash);
            if (k != j->second_.resources_.End())
            {
                // If other references exist, do not release, unless forced
                if (k->second_.Refs() == 1 || force)
                {
                    j->second_.resources_.Erase(k);
                    affectedGroups.Insert(j->first_);
                }
                break;
            }
        }
    }
    
    for (HashSet<ShortStringHash>::Iterator i = affectedGroups.Begin(); i != affectedGroups.End(); ++i)
        UpdateResourceGroup(*i);
}

void ResourceCache::UpdateResourceGroup(ShortStringHash type)
{
    HashMap<ShortStringHash, ResourceGroup>::Iterator i = resourceGroups_.Find(type);
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
            StringHash fileNameHash(fileName);
            // If the filename is a resource we keep track of, reload it
            const SharedPtr<Resource>& resource = FindResource(fileNameHash);
            if (resource)
            {
                LOGDEBUG("Reloading changed resource " + fileName);
                ReloadResource(resource);
            }
            else
            {
                // Check if this is a dependency resource, reload dependents
                HashMap<StringHash, HashSet<StringHash> >::ConstIterator j = dependentResources_.Find(fileNameHash);
                if (j != dependentResources_.End())
                {
                    // Reloading a resource may modify the dependency tracking structure. Therefore collect the
                    // resources we need to reload first
                    Vector<SharedPtr<Resource> > dependents;
                    
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
    }
}

void RegisterResourceLibrary(Context* context)
{
    Image::RegisterObject(context);
    XMLFile::RegisterObject(context);
}

}
