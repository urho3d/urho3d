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
#include "Log.h"
#include "PackageFile.h"
#include "ResourceCache.h"
#include "ResourceFactory.h"
#include "StringUtils.h"

#include "DebugNew.h"

static ResourceCache* instance = 0;

ResourceCache::ResourceCache()
{
    if (instance)
        EXCEPTION("Resource cache already exists");
    
    LOGINFO("Resource cache created");
    
    instance = this;
}

ResourceCache::~ResourceCache()
{
    // At this point factories may be the only thing keeping subsystems alive; remove resources before factories so that
    // resources can be released cleanly
    mResourceGroups.clear();
    mFactories.clear();
    
    LOGINFO("Resource cache shut down");
    
    if (instance == this)
        instance = 0;
}

void ResourceCache::addResourceFactory(ResourceFactory* factory)
{
    if (!factory)
        return;
    
    mFactories.push_back(SharedPtr<ResourceFactory>(factory));
}

void ResourceCache::addResourcePath(const std::string& path)
{
    checkDirectoryAccess(path);
    
    std::string fixedPath = fixPath(path);
    mResourcePaths.push_back(fixedPath);
    
    // Scan the path for files recursively and add their hash-to-name mappings
    std::vector<std::string> fileNames = scanDirectory(fixedPath, "*.*", true);
    for (unsigned i = 0; i < fileNames.size(); ++i)
        registerHash(fileNames[i]);
    
    LOGINFO("Added resource path " + path);
}

void ResourceCache::addPackageFile(PackageFile* package, bool addAsFirst)
{
    if (!package)
        return;
    
    if (addAsFirst)
        mPackages.insert(mPackages.begin(), SharedPtr<PackageFile>(package));
    else
        mPackages.push_back(SharedPtr<PackageFile>(package));
    
    // Scan the package for files and add their hash-to-name mappings
    const std::map<std::string, PackageEntry>& entries = package->getEntries();
    for (std::map<std::string, PackageEntry>::const_iterator i = entries.begin(); i != entries.end(); ++i)
        registerHash(i->first);
    
    LOGINFO("Added resource package " + package->getName());
}

bool ResourceCache::addManualResource(Resource* resource)
{
    if (!resource)
    {
        LOGERROR("Null manual resource");
        return false;
    }
    
    if (resource->getName().empty())
    {
        LOGERROR("Manual resource with empty name, can not add");
        return false;
    }
    
    resource->resetUseTimer();
    mResourceGroups[resource->getType()].mResources[resource->getNameHash()] = resource;
    updateResourceGroup(resource->getType());
    return true;
}

void ResourceCache::removeResourcePath(const std::string& path)
{
    for (std::vector<std::string>::iterator i = mResourcePaths.begin(); i != mResourcePaths.end();)
    {
        if (i->find(path) == 0)
            i = mResourcePaths.erase(i);
        else
            ++i;
    }
}

void ResourceCache::removePackageFile(PackageFile* package, bool releaseResources, bool forceRelease)
{
    for (std::vector<SharedPtr<PackageFile> >::iterator i = mPackages.begin(); i != mPackages.end(); ++i)
    {
        if ((*i) == package)
        {
            if (releaseResources)
                releasePackageResources(*i, forceRelease);
            mPackages.erase(i);
            return;
        }
    }
}

void ResourceCache::removePackageFile(const std::string& fileName, bool releaseResources, bool forceRelease)
{
    for (std::vector<SharedPtr<PackageFile> >::iterator i = mPackages.begin(); i != mPackages.end(); ++i)
    {
        if ((*i)->getName() == fileName)
        {
            if (releaseResources)
                releasePackageResources(*i, forceRelease);
            mPackages.erase(i);
            return;
        }
    }
}

void ResourceCache::releaseResource(ShortStringHash type, const std::string& name, bool force)
{
    releaseResource(type, StringHash(name), force);
}

void ResourceCache::releaseResource(ShortStringHash type, StringHash nameHash, bool force)
{
    const SharedPtr<Resource>& existingRes = findResource(type, nameHash);
    if (!existingRes)
        return;
    
    // If other references exist, do not release, unless forced
    if ((existingRes.getRefCount() == 1) || (force))
    {
        mResourceGroups[type].mResources.erase(nameHash);
        updateResourceGroup(type);
    }
}

void ResourceCache::releaseResources(ShortStringHash type, bool force)
{
    bool released = false;
    
    for (std::map<ShortStringHash, ResourceGroup>::iterator i = mResourceGroups.begin();
        i != mResourceGroups.end(); ++i)
    {
        if (i->first == type)
        {
            for (std::map<StringHash, SharedPtr<Resource> >::iterator j = i->second.mResources.begin();
                j != i->second.mResources.end();)
            {
                std::map<StringHash, SharedPtr<Resource> >::iterator current = j;
                ++j;
                // If other references exist, do not release, unless forced
                if ((current->second.getRefCount() == 1) || (force))
                {
                    i->second.mResources.erase(current);
                    released = true;
                }
            }
        }
    }
    
    if (released)
        updateResourceGroup(type);
}

void ResourceCache::releaseResources(ShortStringHash type, const std::string& partialName, bool force)
{
    std::string partialNameLower = toLower(partialName);
    bool released = false;
    
    for (std::map<ShortStringHash, ResourceGroup>::iterator i = mResourceGroups.begin();
        i != mResourceGroups.end(); ++i)
    {
        if (i->first == type)
        {
            for (std::map<StringHash, SharedPtr<Resource> >::iterator j = i->second.mResources.begin();
                j != i->second.mResources.end();)
            {
                std::map<StringHash, SharedPtr<Resource> >::iterator current = j;
                ++j;
                if (current->second->getName().find(partialNameLower) != std::string::npos)
                {
                    // If other references exist, do not release, unless forced
                    if ((current->second.getRefCount() == 1) || (force))
                    {
                        i->second.mResources.erase(current);
                        released = true;
                    }
                }
            }
        }
    }
    
    if (released)
        updateResourceGroup(type);
}

void ResourceCache::reloadResource(Resource* resource)
{
    if (!resource)
        return;
    
    SharedPtr<File> file = getFile(resource->getName());
    resource->load(*(file.getPtr()), this);
    resource->resetUseTimer();
    updateResourceGroup(resource->getType());
}

void ResourceCache::setMemoryBudget(ShortStringHash type, unsigned budget)
{
    mResourceGroups[type].mMemoryBudget = budget;
}

SharedPtr<File> ResourceCache::getFile(const std::string& name)
{
    // Check first the packages
    for (unsigned i = 0; i < mPackages.size(); ++i)
    {
        if (mPackages[i]->exists(name))
        {
            const PackageEntry& entry = mPackages[i]->getEntry(name);
            return SharedPtr<File>(new File(name, &mPackages[i]->getFile(), entry));
        }
    }
    
    // Then the filesystem
    for (unsigned i = 0; i < mResourcePaths.size(); ++i)
    {
        if (fileExists(mResourcePaths[i] + name))
        {
            // Construct the file first with full path, then rename it to not contain the resource path,
            // so that the file's name can be used in further getFile() calls (for example over the network)
            SharedPtr<File> file(new File(mResourcePaths[i] + name));
            file->setName(name);
            return file;
        }
    }
    
    EXCEPTION("Could not find resource " + name);
}

Resource* ResourceCache::getResource(ShortStringHash type, const std::string& name)
{
    // Add the name to the hash map, so if this is an unknown resource, the error will not be unintelligible
    registerHash(name);
    
    return getResource(type, StringHash(name));
}

Resource* ResourceCache::getResource(ShortStringHash type, StringHash nameHash)
{
    // Special case: null hash is allowed to return null pointer to simplify resource loading code
    if (!nameHash)
        return 0;
    
    const SharedPtr<Resource>& existing = findResource(type, nameHash);
    if (existing)
        return existing;
    
    SharedPtr<Resource> resource;
    std::string name = hashToString(nameHash);
    
    for (unsigned i = 0; i < mFactories.size(); ++i)
    {
        resource = mFactories[i]->createResource(type, name);
        if (resource)
            break;
    }
    
    if (!resource)
        EXCEPTION("Could not load unknown resource type " + toString(type));
    
    LOGDEBUG("Loading resource " + name);
    
    // Attempt to load the resource
    SharedPtr<File> file = getFile(name);
    resource->load(*(file.getPtr()), this);
    resource->resetUseTimer();
    
    // Store to cache
    mResourceGroups[type].mResources[nameHash] = resource;
    updateResourceGroup(type);
    
    return mResourceGroups[type].mResources[nameHash];
}

std::vector<Resource*> ResourceCache::getResources(ShortStringHash type)
{
    std::vector<Resource*> ret;
    
    std::map<ShortStringHash, ResourceGroup>::const_iterator i = mResourceGroups.find(type);
    if (i != mResourceGroups.end())
    {
        for (std::map<StringHash, SharedPtr<Resource> >::const_iterator j = i->second.mResources.begin();
            j != i->second.mResources.end(); ++j)
            ret.push_back(j->second);
    }
    
    return ret;
}

bool ResourceCache::exists(const std::string& name) const
{
    for (unsigned i = 0; i < mPackages.size(); ++i)
    {
        if (mPackages[i]->exists(name))
            return true;
    }
    
    for (unsigned i = 0; i < mResourcePaths.size(); ++i)
    {
        if (fileExists(mResourcePaths[i] + name))
            return true;
    }
    
    return false;
}

bool ResourceCache::exists(StringHash nameHash) const
{
    std::string name = hashToString(nameHash);
    return exists(name);
}

unsigned ResourceCache::getMemoryBudget(ShortStringHash type) const
{
    std::map<ShortStringHash, ResourceGroup>::const_iterator i = mResourceGroups.find(type);
    if (i != mResourceGroups.end())
        return i->second.mMemoryBudget;
    else
        return 0;
}

unsigned ResourceCache::getMemoryUse(ShortStringHash type) const
{
    std::map<ShortStringHash, ResourceGroup>::const_iterator i = mResourceGroups.find(type);
    if (i != mResourceGroups.end())
        return i->second.mMemoryUse;
    else
        return 0;
}

unsigned ResourceCache::getTotalMemoryUse() const
{
    unsigned total = 0;
    for (std::map<ShortStringHash, ResourceGroup>::const_iterator i = mResourceGroups.begin(); i != mResourceGroups.end(); ++i)
        total += i->second.mMemoryUse;
    return total;
}

const SharedPtr<Resource>& ResourceCache::findResource(ShortStringHash type, StringHash nameHash)
{
    static const SharedPtr<Resource> noResource;
    
    std::map<ShortStringHash, ResourceGroup>::iterator i = mResourceGroups.find(type);
    if (i == mResourceGroups.end())
        return noResource;
    std::map<StringHash, SharedPtr<Resource> >::iterator j = i->second.mResources.find(nameHash);
    if (j == i->second.mResources.end())
        return noResource;
    
    return j->second;
}

void ResourceCache::releasePackageResources(PackageFile* package, bool force)
{
    std::set<ShortStringHash> affectedGroups;
    
    const std::map<std::string, PackageEntry>& entries = package->getEntries();
    for (std::map<std::string, PackageEntry>::const_iterator i = entries.begin(); i != entries.end(); ++i)
    {
        StringHash nameHash(i->first);
        
        // We do not know the actual resource type, so search all type containers
        for (std::map<ShortStringHash, ResourceGroup>::iterator j = mResourceGroups.begin();
            j != mResourceGroups.end(); ++j)
        {
            std::map<StringHash, SharedPtr<Resource> >::iterator k = j->second.mResources.find(nameHash);
            if (k != j->second.mResources.end())
            {
                // If other references exist, do not release, unless forced
                if ((k->second.getRefCount() == 1) || (force))
                {
                    j->second.mResources.erase(k);
                    affectedGroups.insert(j->first);
                }
                break;
            }
        }
    }
    
    for (std::set<ShortStringHash>::iterator i = affectedGroups.begin(); i != affectedGroups.end(); ++i)
        updateResourceGroup(*i);
}

void ResourceCache::updateResourceGroup(ShortStringHash type)
{
    std::map<ShortStringHash, ResourceGroup>::iterator i = mResourceGroups.find(type);
    if (i == mResourceGroups.end())
        return;
    
    for (;;)
    {
        unsigned totalSize = 0;
        unsigned oldestTimer = 0;
        std::map<StringHash, SharedPtr<Resource> >::iterator oldestResource = i->second.mResources.end();
        
        for (std::map<StringHash, SharedPtr<Resource> >::iterator j = i->second.mResources.begin();
            j != i->second.mResources.end(); ++j)
        {
            totalSize += j->second->getMemoryUse();
            unsigned useTimer = j->second->getUseTimer();
            if (useTimer > oldestTimer)
            {
                oldestTimer = useTimer;
                oldestResource = j;
            }
        }
        
        i->second.mMemoryUse = totalSize;
        
        // If memory budget defined and is exceeded, remove the oldest resource and loop again
        // (resources in use always return a zero timer and can not be removed)
        if ((i->second.mMemoryBudget) && (i->second.mMemoryUse > i->second.mMemoryBudget) &&
            (oldestResource != i->second.mResources.end()))
        {
            LOGDEBUG("Resource group " + oldestResource->second->getTypeName() + " over memory budget, releasing resource " +
                oldestResource->second->getName());
            i->second.mResources.erase(oldestResource);
        }
        else
            break;
    }
}

ResourceCache* getResourceCache()
{
    return instance;
}
