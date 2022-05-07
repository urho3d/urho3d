// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../Core/Object.h"
#include "../Core/Timer.h"
#include "../Resource/JSONValue.h"

namespace Urho3D
{

class Deserializer;
class Serializer;
class XMLElement;

/// Asynchronous loading state of a resource.
enum AsyncLoadState
{
    /// No async operation in progress.
    ASYNC_DONE = 0,
    /// Queued for asynchronous loading.
    ASYNC_QUEUED = 1,
    /// In progress of calling BeginLoad() in a worker thread.
    ASYNC_LOADING = 2,
    /// BeginLoad() succeeded. EndLoad() can be called in the main thread.
    ASYNC_SUCCESS = 3,
    /// BeginLoad() failed.
    ASYNC_FAIL = 4
};

/// Base class for resources.
/// @templateversion
class URHO3D_API Resource : public Object
{
    URHO3D_OBJECT(Resource, Object);

public:
    /// Construct.
    explicit Resource(Context* context);

    /// Load resource synchronously. Call both BeginLoad() & EndLoad() and return true if both succeeded.
    bool Load(Deserializer& source);
    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    virtual bool EndLoad();
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest) const;

    /// Load resource from file.
    /// @alias{Load}
    bool LoadFile(const String& fileName);
    /// Save resource to file.
    /// @alias{Save}
    virtual bool SaveFile(const String& fileName) const;

    /// Set name.
    /// @property
    void SetName(const String& name);
    /// Set memory use in bytes, possibly approximate.
    void SetMemoryUse(unsigned size);
    /// Reset last used timer.
    void ResetUseTimer();
    /// Set the asynchronous loading state. Called by ResourceCache. Resources in the middle of asynchronous loading are not normally returned to user.
    void SetAsyncLoadState(AsyncLoadState newState);

    /// Return name.
    /// @property
    const String& GetName() const { return name_; }

    /// Return name hash.
    StringHash GetNameHash() const { return nameHash_; }

    /// Return memory use in bytes, possibly approximate.
    /// @property
    unsigned GetMemoryUse() const { return memoryUse_; }

    /// Return time since last use in milliseconds. If referred to elsewhere than in the resource cache, returns always zero.
    /// @property
    unsigned GetUseTimer();

    /// Return the asynchronous loading state.
    AsyncLoadState GetAsyncLoadState() const { return asyncLoadState_; }

private:
    /// Name.
    String name_;
    /// Name hash.
    StringHash nameHash_;
    /// Last used timer.
    Timer useTimer_;
    /// Memory use in bytes.
    unsigned memoryUse_;
    /// Asynchronous loading state.
    AsyncLoadState asyncLoadState_;
};

/// Base class for resources that support arbitrary metadata stored. Metadata serialization shall be implemented in derived classes.
class URHO3D_API ResourceWithMetadata : public Resource
{
    URHO3D_OBJECT(ResourceWithMetadata, Resource);

public:
    /// Construct.
    explicit ResourceWithMetadata(Context* context) : Resource(context) {}

    /// Add new metadata variable or overwrite old value.
    /// @property{set_metadata}
    void AddMetadata(const String& name, const Variant& value);
    /// Remove metadata variable.
    void RemoveMetadata(const String& name);
    /// Remove all metadata variables.
    void RemoveAllMetadata();
    /// Return metadata variable.
    /// @property
    const Variant& GetMetadata(const String& name) const;
    /// Return whether the resource has metadata.
    /// @property
    bool HasMetadata() const;

protected:
    /// Load metadata from <metadata> children of XML element.
    void LoadMetadataFromXML(const XMLElement& source);
    /// Load metadata from JSON array.
    void LoadMetadataFromJSON(const JSONArray& array);
    /// Save as <metadata> children of XML element.
    void SaveMetadataToXML(XMLElement& destination) const;
    /// Copy metadata from another resource.
    void CopyMetadata(const ResourceWithMetadata& source);

private:
    /// Animation metadata variables.
    VariantMap metadata_;
    /// Animation metadata keys.
    StringVector metadataKeys_;
};

inline const String& GetResourceName(Resource* resource)
{
    return resource ? resource->GetName() : String::EMPTY;
}

inline StringHash GetResourceType(Resource* resource, StringHash defaultType)
{
    return resource ? resource->GetType() : defaultType;
}

inline ResourceRef GetResourceRef(Resource* resource, StringHash defaultType)
{
    return ResourceRef(GetResourceType(resource, defaultType), GetResourceName(resource));
}

template <class T> Vector<String> GetResourceNames(const Vector<SharedPtr<T> >& resources)
{
    Vector<String> ret(resources.Size());
    for (unsigned i = 0; i < resources.Size(); ++i)
        ret[i] = GetResourceName(resources[i]);

    return ret;
}

template <class T> ResourceRefList GetResourceRefList(const Vector<SharedPtr<T> >& resources)
{
    return ResourceRefList(T::GetTypeStatic(), GetResourceNames(resources));
}

}
