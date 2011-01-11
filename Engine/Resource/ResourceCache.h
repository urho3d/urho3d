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

#ifndef RESOURCE_RESOURCECACHE_H
#define RESOURCE_RESOURCECACHE_H

#include "File.h"
#include "Resource.h"
#include "SharedPtr.h"

#include <map>
#include <string>
#include <vector>

class PackageFile;
class ResourceFactory;

//! A container of resources with specific type
struct ResourceGroup
{
    //! Construct with defaults
    ResourceGroup() :
        mMemoryBudget(0),
        mMemoryUse(0)
    {
    }
    
    //! Memory budget
    unsigned mMemoryBudget;
    //! Current memory use
    unsigned mMemoryUse;
    //! Resources
    std::map<StringHash, SharedPtr<Resource> > mResources;
};

//! Loads resources when requested and holds them for later access
class ResourceCache : public RefCounted
{
public:
    //! Construct
    ResourceCache();
    //! Destruct. Free all resources
    virtual ~ResourceCache();
    
    //! Add a resource factory
    void addResourceFactory(ResourceFactory* factory);
    //! Add a resource load path
    void addResourcePath(const std::string& path);
    //! Add a package file for loading resources from
    void addPackageFile(PackageFile* package, bool addAsFirst = false);
    //! Add a manually created resource. Must be uniquely named
    bool addManualResource(Resource* resource);
    //! Remove a resource load path
    void removeResourcePath(const std::string& path);
    //! Remove a package file. Optionally release the resources loaded from it
    void removePackageFile(PackageFile* package, bool releaseResources = true, bool forceRelease = false);
    //! Remove a package file by name. Optionally release the resources loaded from it
    void removePackageFile(const std::string& fileName, bool releaseResources = true, bool forceRelease = false);
    //! Release a resource by name
    void releaseResource(ShortStringHash type, const std::string& name, bool force = false);
    //! Release a resource by name hash
    void releaseResource(ShortStringHash type, StringHash nameHash, bool force = false); 
    //! Release all resources of a specific type
    void releaseResources(ShortStringHash type, bool force = false);
    //! Release resources of a specific type and partial name
    void releaseResources(ShortStringHash type, const std::string& partialName, bool force = false);
    //! Reload a resource
    void reloadResource(Resource* resource);
    //! Set memory budget for a specific resource type, default 0 is unlimited
    void setMemoryBudget(ShortStringHash type, unsigned budget);
    
    //! Open and return a file from either the resource load paths or from inside a package file. Throw an exception if fails
    SharedPtr<File> getFile(const std::string& name);
    //! Return a resource by type and name. Load if not loaded yet. Throw an exception if fails
    Resource* getResource(ShortStringHash type, const std::string& name);
    //! Return a resource by type and name hash. Load if not loaded yet. Throw an exception if fails
    Resource* getResource(ShortStringHash type, StringHash nameHash);
    //! Return all resources of a specific type
    std::vector<Resource*> getResources(ShortStringHash type);
    //! Return all resources
    const std::map<ShortStringHash, ResourceGroup>& getAllResources() const { return mResourceGroups; }
    //! Return added resource load paths
    const std::vector<std::string>& getResourcePaths() const { return mResourcePaths; }
    //! Return added package files
    const std::vector<SharedPtr<PackageFile> >& getPackageFiles() const { return mPackages; }
    //! Template version of returning a resource by name
    template <class T> T* getResource(const std::string& name);
    //! Template version of returning a resource by name hash
    template <class T> T* getResource(StringHash nameHash);
    //! Template version of returning resources of a specific type
    template <class T> std::vector<T*> getResources();
    //! Return whether a file exists by name
    bool exists(const std::string& name) const;
    //! Return whether a file exists by name hash
    bool exists(StringHash nameHash) const;
    //! Return memory budget for a resource type
    unsigned getMemoryBudget(ShortStringHash type) const;
    //! Return total memory use for a resource type
    unsigned getMemoryUse(ShortStringHash type) const;
    //! Return total memory use for all resources
    unsigned getTotalMemoryUse() const;
    
private:
    //! Find a resource
    const SharedPtr<Resource>& findResource(ShortStringHash type, StringHash nameHash);
    //! Release resources loaded from a package file
    void releasePackageResources(PackageFile* package, bool force = false);
    //! Update a resource group. Recalculate memory use and release resources if over memory budget
    void updateResourceGroup(ShortStringHash type);
    
    //! Resources by type
    std::map<ShortStringHash, ResourceGroup> mResourceGroups;
    //! Resource factories
    std::vector<SharedPtr<ResourceFactory> > mFactories;
    //! Resource load paths
    std::vector<std::string> mResourcePaths;
    //! Package files
    std::vector<SharedPtr<PackageFile> > mPackages;
};

template <class T> T* ResourceCache::getResource(const std::string& name)
{
    ShortStringHash type = T::getTypeStatic();
    return static_cast<T*>(getResource(type, name));
}

template <class T> T* ResourceCache::getResource(StringHash nameHash)
{
    ShortStringHash type = T::getTypeStatic();
    return static_cast<T*>(getResource(type, nameHash));
}

template <class T> std::vector<T*> ResourceCache::getResources()
{
    ShortStringHash type = T::getTypeStatic();
    std::vector<Resource*> resources = getResources(type);
    std::vector<T*> ret;
    
    for (std::vector<Resource*>::const_iterator i = resources.begin(); i != resources.end(); ++i)
        ret.push_back(static_cast<T*>(*i));
    
    return ret;
}

//! Return ResourceCache instance
ResourceCache* getResourceCache();

#endif // RESOURCE_RESOURCECACHE_H
