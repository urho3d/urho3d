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
#include "FileSystem.h"
#include "Image.h"
#include "Log.h"
#include "PackageFile.h"
#include "ResourceCache.h"
#include "ResourceEvents.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include "DebugNew.h"

static const std::string checkDirs[] = {
    "Fonts",
    "Materials",
    "Models",
    "Music",
    "Particle",
    "Physics",
    "Scripts",
    "Sounds",
    "Shaders",
    "Textures",
    "UI",
    ""
};

static const std::string noName;
static const SharedPtr<Resource> noResource;

OBJECTTYPESTATIC(ResourceCache);

ResourceCache::ResourceCache(Context* context) :
    Object(context)
{
}

ResourceCache::~ResourceCache()
{
}

bool ResourceCache::AddResourcePath(const std::string& path)
{
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if ((!fileSystem) || (!fileSystem->DirExists(path)))
    {
        LOGERROR("Could not open directory " + path);
        return false;
    }
    
    std::string fixedPath = AddTrailingSlash(path);
    std::string pathLower = ToLower(fixedPath);
    
    // Check that the same path does not already exist
    for (unsigned i = 0; i < resourcePaths_.size(); ++i)
    {
        if (ToLower(resourcePaths_[i]) == pathLower)
            return true;
    }
    
    resourcePaths_.push_back(fixedPath);
    
    // Scan the path for files recursively and add their hash-to-name mappings
    std::vector<std::string> fileNames;
    fileSystem->ScanDir(fileNames, fixedPath, "*.*", SCAN_FILES, true);
    for (unsigned i = 0; i < fileNames.size(); ++i)
        StoreNameHash(fileNames[i]);
    
    LOGINFO("Added resource path " + fixedPath);
    return true;
}

void ResourceCache::AddPackageFile(PackageFile* package, bool addAsFirst)
{
    // Do not add packages that failed to load
    if ((!package) || (!package->GetNumFiles()))
        return;
    
    if (addAsFirst)
        packages_.insert(packages_.begin(), SharedPtr<PackageFile>(package));
    else
        packages_.push_back(SharedPtr<PackageFile>(package));
    
    // Scan the package for files and add their hash-to-name mappings
    const std::map<std::string, PackageEntry>& entries = package->GetEntries();
    for (std::map<std::string, PackageEntry>::const_iterator i = entries.begin(); i != entries.end(); ++i)
        StoreNameHash(i->first);
    
    LOGINFO("Added resource package " + package->GetName());
}

bool ResourceCache::AddManualResource(Resource* resource)
{
    if (!resource)
    {
        LOGERROR("Null manual resource");
        return false;
    }
    
    const std::string& name = resource->GetName();
    if (name.empty())
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

void ResourceCache::RemoveResourcePath(const std::string& path)
{
    std::string fixedPath = ToLower(AddTrailingSlash(path));
    for (std::vector<std::string>::iterator i = resourcePaths_.begin(); i != resourcePaths_.end(); ++i)
    {
        if (ToLower(*i) == fixedPath)
        {
            resourcePaths_.erase(i);
            return;
        }
    }
}

void ResourceCache::RemovePackageFile(PackageFile* package, bool ReleaseResources, bool forceRelease)
{
    for (std::vector<SharedPtr<PackageFile> >::iterator i = packages_.begin(); i != packages_.end(); ++i)
    {
        if ((*i) == package)
        {
            if (ReleaseResources)
                ReleasePackageResources(*i, forceRelease);
            packages_.erase(i);
            return;
        }
    }
}

void ResourceCache::RemovePackageFile(const std::string& fileName, bool ReleaseResources, bool forceRelease)
{
    std::string fileNameLower = ToLower(fileName);
    
    for (std::vector<SharedPtr<PackageFile> >::iterator i = packages_.begin(); i != packages_.end(); ++i)
    {
        if (ToLower((*i)->GetName()) == fileNameLower)
        {
            if (ReleaseResources)
                ReleasePackageResources(*i, forceRelease);
            packages_.erase(i);
            return;
        }
    }
}

void ResourceCache::ReleaseResource(ShortStringHash type, const std::string& name, bool force)
{
    ReleaseResource(type, StringHash(name), force);
}

void ResourceCache::ReleaseResource(ShortStringHash type, StringHash nameHash, bool force)
{
    const SharedPtr<Resource>& existingRes = FindResource(type, nameHash);
    if (!existingRes)
        return;
    
    // If other references exist, do not release, unless forced
    if ((existingRes.GetRefCount() == 1) || (force))
    {
        resourceGroups_[type].resources_.erase(nameHash);
        UpdateResourceGroup(type);
    }
}

void ResourceCache::ReleaseResources(ShortStringHash type, bool force)
{
    bool released = false;
    
    for (std::map<ShortStringHash, ResourceGroup>::iterator i = resourceGroups_.begin();
        i != resourceGroups_.end(); ++i)
    {
        if (i->first == type)
        {
            for (std::map<StringHash, SharedPtr<Resource> >::iterator j = i->second.resources_.begin();
                j != i->second.resources_.end();)
            {
                std::map<StringHash, SharedPtr<Resource> >::iterator current = j++;
                // If other references exist, do not release, unless forced
                if ((current->second.GetRefCount() == 1) || (force))
                {
                    i->second.resources_.erase(current);
                    released = true;
                }
            }
        }
    }
    
    if (released)
        UpdateResourceGroup(type);
}

void ResourceCache::ReleaseResources(ShortStringHash type, const std::string& partialName, bool force)
{
    std::string partialNameLower = ToLower(partialName);
    bool released = false;
    
    for (std::map<ShortStringHash, ResourceGroup>::iterator i = resourceGroups_.begin();
        i != resourceGroups_.end(); ++i)
    {
        if (i->first == type)
        {
            for (std::map<StringHash, SharedPtr<Resource> >::iterator j = i->second.resources_.begin();
                j != i->second.resources_.end();)
            {
                std::map<StringHash, SharedPtr<Resource> >::iterator current = j++;
                if (current->second->GetName().find(partialNameLower) != std::string::npos)
                {
                    // If other references exist, do not release, unless forced
                    if ((current->second.GetRefCount() == 1) || (force))
                    {
                        i->second.resources_.erase(current);
                        released = true;
                    }
                }
            }
        }
    }
    
    if (released)
        UpdateResourceGroup(type);
}

void ResourceCache::ReleaseAllResources(bool force)
{
    for (std::map<ShortStringHash, ResourceGroup>::iterator i = resourceGroups_.begin();
        i != resourceGroups_.end(); ++i)
    {
        bool released = false;
        
        for (std::map<StringHash, SharedPtr<Resource> >::iterator j = i->second.resources_.begin();
            j != i->second.resources_.end();)
        {
            std::map<StringHash, SharedPtr<Resource> >::iterator current = j++;
            // If other references exist, do not release, unless forced
            if ((current->second.GetRefCount() == 1) || (force))
            {
                i->second.resources_.erase(current);
                released = true;
            }
        }
        if (released)
            UpdateResourceGroup(i->first);
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
        success = resource->Load(*(file.GetPtr()));
    
    if (success)
    {
        resource->ResetUseTimer();
        UpdateResourceGroup(resource->GetType());
        resource->SendEvent(E_RELOADFINISHED);
        return true;
    }
    
    // If reloading failed, remove the resource from cache
    resource->SendEvent(E_RELOADFAILED);
    ReleaseResource(resource->GetType(), resource->GetNameHash());
    return false;
}

void ResourceCache::SetMemoryBudget(ShortStringHash type, unsigned budget)
{
    resourceGroups_[type].memoryBudget_ = budget;
}

SharedPtr<File> ResourceCache::GetFile(const std::string& name)
{
    // Check first the packages
    for (unsigned i = 0; i < packages_.size(); ++i)
    {
        if (packages_[i]->Exists(name))
            return SharedPtr<File>(new File(context_, packages_[i], name));
    }
    
    // Then the filesystem
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem)
    {
        for (unsigned i = 0; i < resourcePaths_.size(); ++i)
        {
            if (fileSystem->FileExists(resourcePaths_[i] + name))
            {
                // Construct the file first with full path, then rename it to not contain the resource path,
                // so that the file's name can be used in further GetFile() calls (for example over the network)
                SharedPtr<File> file(new File(context_, resourcePaths_[i] + name));
                file->SetName(name);
                return file;
            }
        }
    }
    
    LOGERROR("Could not find resource " + name);
    return SharedPtr<File>();
}

Resource* ResourceCache::GetResource(ShortStringHash type, const std::string& name)
{
    // Add the name to the hash map, so if this is an unknown resource, the error will not be unintelligible
    StoreNameHash(name);
    
    return GetResource(type, StringHash(name));
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
    const std::string& name = GetResourceName(nameHash);
    if (name.empty())
    {
        LOGERROR("Could not load unknown resource " + ToString(nameHash));
        return 0;
    }
    
    // Make sure the pointer is non-null and is a Resource subclass
    resource = DynamicCast<Resource>(context_->CreateObject(type));
    if (!resource)
    {
        LOGERROR("Could not load unknown resource type " + ToString(type));
        return 0;
    }
    
    // Attempt to load the resource
    SharedPtr<File> file = GetFile(name);
    if (!file)
        return 0;
    
    LOGDEBUG("Loading resource " + name);
    resource->SetName(file->GetName());
    if (!resource->Load(*(file.GetPtr())))
        return 0;
    
    // Store to cache
    resource->ResetUseTimer();
    resourceGroups_[type].resources_[nameHash] = resource;
    UpdateResourceGroup(type);
    
    return resource;
}

void ResourceCache::GetResources(std::vector<Resource*>& result, ShortStringHash type) const
{
    result.clear();
    std::map<ShortStringHash, ResourceGroup>::const_iterator i = resourceGroups_.find(type);
    if (i != resourceGroups_.end())
    {
        for (std::map<StringHash, SharedPtr<Resource> >::const_iterator j = i->second.resources_.begin();
            j != i->second.resources_.end(); ++j)
            result.push_back(j->second);
    }
}

bool ResourceCache::Exists(const std::string& name) const
{
    for (unsigned i = 0; i < packages_.size(); ++i)
    {
        if (packages_[i]->Exists(name))
            return true;
    }
    
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    if (fileSystem)
    {
        for (unsigned i = 0; i < resourcePaths_.size(); ++i)
        {
            if (fileSystem->FileExists(resourcePaths_[i] + name))
                return true;
        }
    }
    
    return false;
}

bool ResourceCache::Exists(StringHash nameHash) const
{
    return Exists(GetResourceName(nameHash));
}

unsigned ResourceCache::GetMemoryBudget(ShortStringHash type) const
{
    std::map<ShortStringHash, ResourceGroup>::const_iterator i = resourceGroups_.find(type);
    if (i != resourceGroups_.end())
        return i->second.memoryBudget_;
    else
        return 0;
}

unsigned ResourceCache::GetMemoryUse(ShortStringHash type) const
{
    std::map<ShortStringHash, ResourceGroup>::const_iterator i = resourceGroups_.find(type);
    if (i != resourceGroups_.end())
        return i->second.memoryUse_;
    else
        return 0;
}

unsigned ResourceCache::GetTotalMemoryUse() const
{
    unsigned total = 0;
    for (std::map<ShortStringHash, ResourceGroup>::const_iterator i = resourceGroups_.begin(); i != resourceGroups_.end(); ++i)
        total += i->second.memoryUse_;
    return total;
}

const std::string& ResourceCache::GetResourceName(StringHash nameHash) const
{
    std::map<StringHash, std::string>::const_iterator i = hashToName_.find(nameHash);
    if (i == hashToName_.end())
        return noName;
    else
        return i->second;
}

std::string ResourceCache::GetPreferredResourcePath(const std::string& path)
{
    std::string fixedPath = AddTrailingSlash(path);
    
    bool pathHasKnownDirs = false;
    bool parentHasKnownDirs = false;
    
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    // If no filesystem, can not check directory existence, so just return the original path
    if (!fileSystem)
        return fixedPath;
    
    for (unsigned i = 0; !checkDirs[i].empty(); ++i)
    {
        if (fileSystem->DirExists(fixedPath + checkDirs[i]))
        {
            pathHasKnownDirs = true;
            break;
        }
    }
    if (!pathHasKnownDirs)
    {
        std::string parentPath = GetParentPath(fixedPath);
        for (unsigned i = 0; !checkDirs[i].empty(); ++i)
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

const SharedPtr<Resource>& ResourceCache::FindResource(ShortStringHash type, StringHash nameHash)
{
    std::map<ShortStringHash, ResourceGroup>::iterator i = resourceGroups_.find(type);
    if (i == resourceGroups_.end())
        return noResource;
    std::map<StringHash, SharedPtr<Resource> >::iterator j = i->second.resources_.find(nameHash);
    if (j == i->second.resources_.end())
        return noResource;
    
    return j->second;
}

void ResourceCache::ReleasePackageResources(PackageFile* package, bool force)
{
    std::set<ShortStringHash> affectedGroups;
    
    const std::map<std::string, PackageEntry>& entries = package->GetEntries();
    for (std::map<std::string, PackageEntry>::const_iterator i = entries.begin(); i != entries.end(); ++i)
    {
        StringHash nameHash(i->first);
        
        // We do not know the actual resource type, so search all type containers
        for (std::map<ShortStringHash, ResourceGroup>::iterator j = resourceGroups_.begin();
            j != resourceGroups_.end(); ++j)
        {
            std::map<StringHash, SharedPtr<Resource> >::iterator k = j->second.resources_.find(nameHash);
            if (k != j->second.resources_.end())
            {
                // If other references exist, do not release, unless forced
                if ((k->second.GetRefCount() == 1) || (force))
                {
                    j->second.resources_.erase(k);
                    affectedGroups.insert(j->first);
                }
                break;
            }
        }
    }
    
    for (std::set<ShortStringHash>::iterator i = affectedGroups.begin(); i != affectedGroups.end(); ++i)
        UpdateResourceGroup(*i);
}

void ResourceCache::UpdateResourceGroup(ShortStringHash type)
{
    std::map<ShortStringHash, ResourceGroup>::iterator i = resourceGroups_.find(type);
    if (i == resourceGroups_.end())
        return;
    
    for (;;)
    {
        unsigned totalSize = 0;
        unsigned oldestTimer = 0;
        std::map<StringHash, SharedPtr<Resource> >::iterator oldestResource = i->second.resources_.end();
        
        for (std::map<StringHash, SharedPtr<Resource> >::iterator j = i->second.resources_.begin();
            j != i->second.resources_.end(); ++j)
        {
            totalSize += j->second->GetMemoryUse();
            unsigned useTimer = j->second->GetUseTimer();
            if (useTimer > oldestTimer)
            {
                oldestTimer = useTimer;
                oldestResource = j;
            }
        }
        
        i->second.memoryUse_ = totalSize;
        
        // If memory budget defined and is exceeded, remove the oldest resource and loop again
        // (resources in use always return a zero timer and can not be removed)
        if ((i->second.memoryBudget_) && (i->second.memoryUse_ > i->second.memoryBudget_) &&
            (oldestResource != i->second.resources_.end()))
        {
            LOGDEBUG("Resource group " + oldestResource->second->GetTypeNameStr() + " over memory budget, releasing resource " +
                oldestResource->second->GetName());
            i->second.resources_.erase(oldestResource);
        }
        else
            break;
    }
}

void ResourceCache::StoreNameHash(const std::string& name)
{
    if (name.empty())
        return;
    
    hashToName_[StringHash(name)] = name;
}

void RegisterResourceLibrary(Context* context)
{
    Image::RegisterObject(context);
    XMLFile::RegisterObject(context);
}
