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

#pragma once

#include "File.h"
#include "HashSet.h"
#include "Resource.h"

namespace Urho3D
{

class FileWatcher;
class PackageFile;

/// Container of resources with specific type.
struct ResourceGroup
{
    /// Construct with defaults.
    ResourceGroup() :
        memoryBudget_(0),
        memoryUse_(0)
    {
    }
    
    /// Memory budget.
    unsigned memoryBudget_;
    /// Current memory use.
    unsigned memoryUse_;
    /// Resources.
    HashMap<StringHash, SharedPtr<Resource> > resources_;
};

/// %Resource cache subsystem. Loads resources on demand and stores them for later access.
class URHO3D_API ResourceCache : public Object
{
    OBJECT(ResourceCache);
    
public:
    /// Construct.
    ResourceCache(Context* context);
    /// Destruct. Free all resources.
    virtual ~ResourceCache();
    
    /// Add a resource load directory.
    bool AddResourceDir(const String& pathName);
    /// Add a package file for loading resources from.
    void AddPackageFile(PackageFile* package, bool addAsFirst = false);
    /// Add a manually created resource. Must be uniquely named.
    bool AddManualResource(Resource* resource);
    /// Remove a resource load directory.
    void RemoveResourceDir(const String& pathName);
    /// Remove a package file. Optionally release the resources loaded from it.
    void RemovePackageFile(PackageFile* package, bool releaseResources = true, bool forceRelease = false);
    /// Remove a package file by name. Optionally release the resources loaded from it.
    void RemovePackageFile(const String& fileName, bool releaseResources = true, bool forceRelease = false);
    /// Release a resource by name.
    void ReleaseResource(ShortStringHash type, const String& name, bool force = false);
    /// Release all resources of a specific type.
    void ReleaseResources(ShortStringHash type, bool force = false);
    /// Release resources of a specific type and partial name.
    void ReleaseResources(ShortStringHash type, const String& partialName, bool force = false);
    /// Release resources of all types by partial name.
    void ReleaseResources(const String& partialName, bool force = false);
    /// Release all resources. When called with the force flag false, releases all currently unused resources.
    void ReleaseAllResources(bool force = false);
    /// Reload a resource. Return false and release it if fails.
    bool ReloadResource(Resource* resource);
    /// Set memory budget for a specific resource type, default 0 is unlimited.
    void SetMemoryBudget(ShortStringHash type, unsigned budget);
    /// Enable or disable automatic reloading of resources as files are modified.
    void SetAutoReloadResources(bool enable);
    
    /// Open and return a file from the resource load paths or from inside a package file. If not found, use a fallback search with absolute path. Return null if fails.
    SharedPtr<File> GetFile(const String& name);
    /// Return a resource by type and name. Load if not loaded yet. Return null if fails.
    Resource* GetResource(ShortStringHash type, const String& name);
    /// Return a resource by type and name. Load if not loaded yet. Return null if fails.
    Resource* GetResource(ShortStringHash type, const char* name);
    /// Return all loaded resources of a specific type.
    void GetResources(PODVector<Resource*>& result, ShortStringHash type) const;
    /// Return all loaded resources.
    const HashMap<ShortStringHash, ResourceGroup>& GetAllResources() const { return resourceGroups_; }
    /// Return added resource load directories.
    const Vector<String>& GetResourceDirs() const { return resourceDirs_; }
    /// Return added package files.
    const Vector<SharedPtr<PackageFile> >& GetPackageFiles() const { return packages_; }
    /// Template version of returning a resource by name.
    template <class T> T* GetResource(const String& name);
    /// Template version of returning a resource by name.
    template <class T> T* GetResource(const char* name);
    /// Template version of returning loaded resources of a specific type.
    template <class T> void GetResources(PODVector<T*>& result) const;
    /// Return whether a file exists by name.
    bool Exists(const String& name) const;
    /// Return memory budget for a resource type.
    unsigned GetMemoryBudget(ShortStringHash type) const;
    /// Return total memory use for a resource type.
    unsigned GetMemoryUse(ShortStringHash type) const;
    /// Return total memory use for all resources.
    unsigned GetTotalMemoryUse() const;
    /// Return full absolute file name of resource if possible.
    String GetResourceFileName(const String& name) const;
    /// Return whether automatic resource reloading is enabled.
    bool GetAutoReloadResources() const { return autoReloadResources_; }
    
    /// Return either the path itself or its parent, based on which of them has recognized resource subdirectories.
    String GetPreferredResourceDir(const String& path) const;
    /// Remove unsupported constructs from the resource name to prevent ambiguity, and normalize absolute filename to resource path relative if possible.
    String SanitateResourceName(const String& name) const;
    /// Store a dependency for a resource. If a dependency file changes, the resource will be reloaded.
    void StoreResourceDependency(Resource* resource, const String& dependency);
    /// Reset dependencies for a resource.
    void ResetDependencies(Resource* resource);
    
private:
    /// Find a resource.
    const SharedPtr<Resource>& FindResource(ShortStringHash type, StringHash nameHash);
    /// Find a resource by name only. Searches all type groups.
    const SharedPtr<Resource>& FindResource(StringHash nameHash);
    /// Release resources loaded from a package file.
    void ReleasePackageResources(PackageFile* package, bool force = false);
    /// Update a resource group. Recalculate memory use and release resources if over memory budget.
    void UpdateResourceGroup(ShortStringHash type);
    /// Handle begin frame event. Automatic resource reloads are processed here.
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    
    /// Resources by type.
    HashMap<ShortStringHash, ResourceGroup> resourceGroups_;
    /// Resource load directories.
    Vector<String> resourceDirs_;
    /// File watchers for resource directories, if automatic reloading enabled.
    Vector<SharedPtr<FileWatcher> > fileWatchers_;
    /// Package files.
    Vector<SharedPtr<PackageFile> > packages_;
    /// Dependent resources.
    HashMap<StringHash, HashSet<StringHash> > dependentResources_;
    /// Automatic resource reloading flag.
    bool autoReloadResources_;
};

template <class T> T* ResourceCache::GetResource(const String& name)
{
    ShortStringHash type = T::GetTypeStatic();
    return static_cast<T*>(GetResource(type, name));
}

template <class T> T* ResourceCache::GetResource(const char* name)
{
    ShortStringHash type = T::GetTypeStatic();
    return static_cast<T*>(GetResource(type, name));
}

template <class T> void ResourceCache::GetResources(PODVector<T*>& result) const
{
    PODVector<Resource*>& resources = reinterpret_cast<PODVector<Resource*>&>(result);
    ShortStringHash type = T::GetTypeStatic();
    GetResources(resources, type);
    
    // Perform conversion of the returned pointers
    for (unsigned i = 0; i < result.Size(); ++i)
    {
        Resource* resource = resources[i];
        result[i] = static_cast<T*>(resource);
    }
}

/// Register Resource library subsystems and objects.
void URHO3D_API RegisterResourceLibrary(Context* context);

}
