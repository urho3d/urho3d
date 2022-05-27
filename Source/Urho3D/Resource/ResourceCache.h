// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../Container/HashSet.h"
#include "../Core/Mutex.h"
#include "../IO/File.h"
#include "../Resource/Resource.h"

namespace Urho3D
{

class BackgroundLoader;
class FileWatcher;
class PackageFile;

/// Sets to priority so that a package or file is pushed to the end of the vector.
static const unsigned PRIORITY_LAST = 0xffffffff;

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
    unsigned long long memoryBudget_;
    /// Current memory use.
    unsigned long long memoryUse_;
    /// Resources.
    HashMap<StringHash, SharedPtr<Resource>> resources_;
};

/// Resource request types.
enum ResourceRequest
{
    RESOURCE_CHECKEXISTS = 0,
    RESOURCE_GETFILE = 1
};

/// Optional resource request processor. Can deny requests, re-route resource file names, or perform other processing per request.
/// @nobindtemp
class URHO3D_API ResourceRouter : public Object
{
public:
    /// Construct.
    explicit ResourceRouter(Context* context) :
        Object(context)
    {
    }

    /// Process the resource request and optionally modify the resource name string. Empty name string means the resource is not found or not allowed.
    virtual void Route(String& name, ResourceRequest requestType) = 0;
};

/// %Resource cache subsystem. Loads resources on demand and stores them for later access.
class URHO3D_API ResourceCache : public Object
{
    URHO3D_OBJECT(ResourceCache, Object);

public:
    /// Construct.
    explicit ResourceCache(Context* context);
    /// Destruct. Free all resources.
    ~ResourceCache() override;

    /// Add a resource load directory. Optional priority parameter which will control search order.
    bool AddResourceDir(const String& pathName, unsigned priority = PRIORITY_LAST);
    /// Add a package file for loading resources from. Optional priority parameter which will control search order.
    bool AddPackageFile(PackageFile* package, unsigned priority = PRIORITY_LAST);
    /// Add a package file for loading resources from by name. Optional priority parameter which will control search order.
    bool AddPackageFile(const String& fileName, unsigned priority = PRIORITY_LAST);
    /// Add a manually created resource. Must be uniquely named within its type.
    bool AddManualResource(Resource* resource);
    /// Remove a resource load directory.
    void RemoveResourceDir(const String& pathName);
    /// Remove a package file. Optionally release the resources loaded from it.
    void RemovePackageFile(PackageFile* package, bool releaseResources = true, bool forceRelease = false);
    /// Remove a package file by name. Optionally release the resources loaded from it.
    void RemovePackageFile(const String& fileName, bool releaseResources = true, bool forceRelease = false);
    /// Release a resource by name.
    void ReleaseResource(StringHash type, const String& name, bool force = false);
    /// Release all resources of a specific type.
    void ReleaseResources(StringHash type, bool force = false);
    /// Release resources of a specific type and partial name.
    void ReleaseResources(StringHash type, const String& partialName, bool force = false);
    /// Release resources of all types by partial name.
    void ReleaseResources(const String& partialName, bool force = false);
    /// Release all resources. When called with the force flag false, releases all currently unused resources.
    void ReleaseAllResources(bool force = false);
    /// Reload a resource. Return true on success. The resource will not be removed from the cache in case of failure.
    bool ReloadResource(Resource* resource);
    /// Reload a resource based on filename. Causes also reload of dependent resources if necessary.
    void ReloadResourceWithDependencies(const String& fileName);
    /// Set memory budget for a specific resource type, default 0 is unlimited.
    /// @property
    void SetMemoryBudget(StringHash type, unsigned long long budget);
    /// Enable or disable automatic reloading of resources as files are modified. Default false.
    /// @property
    void SetAutoReloadResources(bool enable);
    /// Enable or disable returning resources that failed to load. Default false. This may be useful in editing to not lose resource ref attributes.
    /// @property
    void SetReturnFailedResources(bool enable) { returnFailedResources_ = enable; }

    /// Define whether when getting resources should check package files or directories first. True for packages, false for directories.
    /// @property
    void SetSearchPackagesFirst(bool value) { searchPackagesFirst_ = value; }

    /// Set how many milliseconds maximum per frame to spend on finishing background loaded resources.
    /// @property
    void SetFinishBackgroundResourcesMs(int ms) { finishBackgroundResourcesMs_ = Max(ms, 1); }

    /// Add a resource router object. By default there is none, so the routing process is skipped.
    void AddResourceRouter(ResourceRouter* router, bool addAsFirst = false);
    /// Remove a resource router object.
    void RemoveResourceRouter(ResourceRouter* router);

    /// Open and return a file from the resource load paths or from inside a package file. If not found, use a fallback search with absolute path. Return null if fails. Can be called from outside the main thread.
    SharedPtr<File> GetFile(const String& name, bool sendEventOnFailure = true);
    /// Return a resource by type and name. Load if not loaded yet. Return null if not found or if fails, unless SetReturnFailedResources(true) has been called. Can be called only from the main thread.
    Resource* GetResource(StringHash type, const String& name, bool sendEventOnFailure = true);
    /// Load a resource without storing it in the resource cache. Return null if not found or if fails. Can be called from outside the main thread if the resource itself is safe to load completely (it does not possess for example GPU data).
    SharedPtr<Resource> GetTempResource(StringHash type, const String& name, bool sendEventOnFailure = true);
    /// Background load a resource. An event will be sent when complete. Return true if successfully stored to the load queue, false if eg. already exists. Can be called from outside the main thread.
    bool BackgroundLoadResource(StringHash type, const String& name, bool sendEventOnFailure = true, Resource* caller = nullptr);
    /// Return number of pending background-loaded resources.
    /// @property
    unsigned GetNumBackgroundLoadResources() const;
    /// Return all loaded resources of a specific type.
    void GetResources(PODVector<Resource*>& result, StringHash type) const;
    /// Return an already loaded resource of specific type & name, or null if not found. Will not load if does not exist.
    Resource* GetExistingResource(StringHash type, const String& name);

    /// Return all loaded resources.
    const HashMap<StringHash, ResourceGroup>& GetAllResources() const { return resourceGroups_; }

    /// Return added resource load directories.
    /// @property
    const Vector<String>& GetResourceDirs() const { return resourceDirs_; }

    /// Return added package files.
    /// @property
    const Vector<SharedPtr<PackageFile>>& GetPackageFiles() const { return packages_; }

    /// Template version of returning a resource by name.
    template <class T> T* GetResource(const String& name, bool sendEventOnFailure = true);
    /// Template version of returning an existing resource by name.
    template <class T> T* GetExistingResource(const String& name);
    /// Template version of loading a resource without storing it to the cache.
    template <class T> SharedPtr<T> GetTempResource(const String& name, bool sendEventOnFailure = true);
    /// Template version of releasing a resource by name.
    template <class T> void ReleaseResource(const String& name, bool force = false);
    /// Template version of queueing a resource background load.
    template <class T> bool BackgroundLoadResource(const String& name, bool sendEventOnFailure = true, Resource* caller = nullptr);
    /// Template version of returning loaded resources of a specific type.
    template <class T> void GetResources(PODVector<T*>& result) const;
    /// Return whether a file exists in the resource directories or package files. Does not check manually added in-memory resources.
    bool Exists(const String& name) const;
    /// Return memory budget for a resource type.
    /// @property
    unsigned long long GetMemoryBudget(StringHash type) const;
    /// Return total memory use for a resource type.
    /// @property
    unsigned long long GetMemoryUse(StringHash type) const;
    /// Return total memory use for all resources.
    /// @property
    unsigned long long GetTotalMemoryUse() const;
    /// Return full absolute file name of resource if possible, or empty if not found.
    String GetResourceFileName(const String& name) const;

    /// Return whether automatic resource reloading is enabled.
    /// @property
    bool GetAutoReloadResources() const { return autoReloadResources_; }

    /// Return whether resources that failed to load are returned.
    /// @property
    bool GetReturnFailedResources() const { return returnFailedResources_; }

    /// Return whether when getting resources should check package files or directories first.
    /// @property
    bool GetSearchPackagesFirst() const { return searchPackagesFirst_; }

    /// Return how many milliseconds maximum to spend on finishing background loaded resources.
    /// @property
    int GetFinishBackgroundResourcesMs() const { return finishBackgroundResourcesMs_; }

    /// Return a resource router by index.
    ResourceRouter* GetResourceRouter(unsigned index) const;

    /// Return either the path itself or its parent, based on which of them has recognized resource subdirectories.
    String GetPreferredResourceDir(const String& path) const;
    /// Remove unsupported constructs from the resource name to prevent ambiguity, and normalize absolute filename to resource path relative if possible.
    String SanitateResourceName(const String& name) const;
    /// Remove unnecessary constructs from a resource directory name and ensure it to be an absolute path.
    String SanitateResourceDirName(const String& name) const;
    /// Store a dependency for a resource. If a dependency file changes, the resource will be reloaded.
    void StoreResourceDependency(Resource* resource, const String& dependency);
    /// Reset dependencies for a resource.
    void ResetDependencies(Resource* resource);

    /// Returns a formatted string containing the memory actively used.
    String PrintMemoryUsage() const;

private:
    /// Find a resource.
    const SharedPtr<Resource>& FindResource(StringHash type, StringHash nameHash);
    /// Find a resource by name only. Searches all type groups.
    const SharedPtr<Resource>& FindResource(StringHash nameHash);
    /// Release resources loaded from a package file.
    void ReleasePackageResources(PackageFile* package, bool force = false);
    /// Update a resource group. Recalculate memory use and release resources if over memory budget.
    void UpdateResourceGroup(StringHash type);
    /// Handle begin frame event. Automatic resource reloads and the finalization of background loaded resources are processed here.
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    /// Search FileSystem for file.
    File* SearchResourceDirs(const String& name);
    /// Search resource packages for file.
    File* SearchPackages(const String& name);

    /// Mutex for thread-safe access to the resource directories, resource packages and resource dependencies.
    mutable Mutex resourceMutex_;
    /// Resources by type.
    HashMap<StringHash, ResourceGroup> resourceGroups_;
    /// Resource load directories.
    Vector<String> resourceDirs_;
    /// File watchers for resource directories, if automatic reloading enabled.
    Vector<SharedPtr<FileWatcher>> fileWatchers_;
    /// Package files.
    Vector<SharedPtr<PackageFile>> packages_;
    /// Dependent resources. Only used with automatic reload to eg. trigger reload of a cube texture when any of its faces change.
    HashMap<StringHash, HashSet<StringHash>> dependentResources_;
    /// Resource background loader.
    SharedPtr<BackgroundLoader> backgroundLoader_;
    /// Resource routers.
    Vector<SharedPtr<ResourceRouter>> resourceRouters_;
    /// Automatic resource reloading flag.
    bool autoReloadResources_;
    /// Return failed resources flag.
    bool returnFailedResources_;
    /// Search priority flag.
    bool searchPackagesFirst_;
    /// Resource routing flag to prevent endless recursion.
    mutable bool isRouting_;
    /// How many milliseconds maximum per frame to spend on finishing background loaded resources.
    int finishBackgroundResourcesMs_;
};

template <class T> T* ResourceCache::GetExistingResource(const String& name)
{
    StringHash type = T::GetTypeStatic();
    return static_cast<T*>(GetExistingResource(type, name));
}

template <class T> T* ResourceCache::GetResource(const String& name, bool sendEventOnFailure)
{
    StringHash type = T::GetTypeStatic();
    return static_cast<T*>(GetResource(type, name, sendEventOnFailure));
}

template <class T> void ResourceCache::ReleaseResource(const String& name, bool force)
{
    StringHash type = T::GetTypeStatic();
    ReleaseResource(type, name, force);
}

template <class T> SharedPtr<T> ResourceCache::GetTempResource(const String& name, bool sendEventOnFailure)
{
    StringHash type = T::GetTypeStatic();
    return StaticCast<T>(GetTempResource(type, name, sendEventOnFailure));
}

template <class T> bool ResourceCache::BackgroundLoadResource(const String& name, bool sendEventOnFailure, Resource* caller)
{
    StringHash type = T::GetTypeStatic();
    return BackgroundLoadResource(type, name, sendEventOnFailure, caller);
}

template <class T> void ResourceCache::GetResources(PODVector<T*>& result) const
{
    auto& resources = reinterpret_cast<PODVector<Resource*>&>(result);
    StringHash type = T::GetTypeStatic();
    GetResources(resources, type);

    // Perform conversion of the returned pointers
    for (unsigned i = 0; i < result.Size(); ++i)
    {
        Resource* resource = resources[i];
        result[i] = static_cast<T*>(resource);
    }
}

/// Register Resource library subsystems and objects.
/// @nobind
void URHO3D_API RegisterResourceLibrary(Context* context);

}
