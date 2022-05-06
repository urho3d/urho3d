// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Profiler.h"
#include "../IO/File.h"
#include "../IO/Log.h"
#include "../Resource/Resource.h"
#include "../Resource/XMLElement.h"

namespace Urho3D
{

Resource::Resource(Context* context) :
    Object(context),
    memoryUse_(0),
    asyncLoadState_(ASYNC_DONE)
{
}

bool Resource::Load(Deserializer& source)
{
    // Because BeginLoad() / EndLoad() can be called from worker threads, where profiling would be a no-op,
    // create a type name -based profile block here
#ifdef URHO3D_TRACY_PROFILING
    URHO3D_PROFILE_COLOR(Load, URHO3D_PROFILE_RESOURCE_COLOR);

    String profileBlockName("Load" + GetTypeName());
    URHO3D_PROFILE_STR(profileBlockName.CString(), profileBlockName.Length());
#elif defined(URHO3D_PROFILING)
    String profileBlockName("Load" + GetTypeName());

    auto* profiler = GetSubsystem<Profiler>();
    if (profiler)
        profiler->BeginBlock(profileBlockName.CString());
#endif

    // If we are loading synchronously in a non-main thread, behave as if async loading (for example use
    // GetTempResource() instead of GetResource() to load resource dependencies)
    SetAsyncLoadState(Thread::IsMainThread() ? ASYNC_DONE : ASYNC_LOADING);
    bool success = BeginLoad(source);
    if (success)
        success &= EndLoad();
    SetAsyncLoadState(ASYNC_DONE);

#ifdef URHO3D_PROFILING
    if (profiler)
        profiler->EndBlock();
#endif

    return success;
}

bool Resource::BeginLoad(Deserializer& source)
{
    // This always needs to be overridden by subclasses
    return false;
}

bool Resource::EndLoad()
{
    // If no GPU upload step is necessary, no override is necessary
    return true;
}

bool Resource::Save(Serializer& dest) const
{
    URHO3D_LOGERROR("Save not supported for " + GetTypeName());
    return false;
}

bool Resource::LoadFile(const String& fileName)
{
    File file(context_);
    return file.Open(fileName, FILE_READ) && Load(file);
}

bool Resource::SaveFile(const String& fileName) const
{
    File file(context_);
    return file.Open(fileName, FILE_WRITE) && Save(file);
}

void Resource::SetName(const String& name)
{
    name_ = name;
    nameHash_ = name;
}

void Resource::SetMemoryUse(unsigned size)
{
    memoryUse_ = size;
}

void Resource::ResetUseTimer()
{
    useTimer_.Reset();
}

void Resource::SetAsyncLoadState(AsyncLoadState newState)
{
    asyncLoadState_ = newState;
}

unsigned Resource::GetUseTimer()
{
    // If more references than the resource cache, return always 0 & reset the timer
    if (Refs() > 1)
    {
        useTimer_.Reset();
        return 0;
    }
    else
        return useTimer_.GetMSec(false);
}

void ResourceWithMetadata::AddMetadata(const String& name, const Variant& value)
{
    bool exists;
    metadata_.Insert(MakePair(StringHash(name), value), exists);
    if (!exists)
        metadataKeys_.Push(name);
}

void ResourceWithMetadata::RemoveMetadata(const String& name)
{
    metadata_.Erase(name);
    metadataKeys_.Remove(name);
}

void ResourceWithMetadata::RemoveAllMetadata()
{
    metadata_.Clear();
    metadataKeys_.Clear();
}

const Urho3D::Variant& ResourceWithMetadata::GetMetadata(const String& name) const
{
    const Variant* value = metadata_[name];
    return value ? *value : Variant::EMPTY;
}

bool ResourceWithMetadata::HasMetadata() const
{
    return !metadata_.Empty();
}

void ResourceWithMetadata::LoadMetadataFromXML(const XMLElement& source)
{
    for (XMLElement elem = source.GetChild("metadata"); elem; elem = elem.GetNext("metadata"))
        AddMetadata(elem.GetAttribute("name"), elem.GetVariant());
}

void ResourceWithMetadata::LoadMetadataFromJSON(const JSONArray& array)
{
    for (unsigned i = 0; i < array.Size(); i++)
    {
        const JSONValue& value = array.At(i);
        AddMetadata(value.Get("name").GetString(), value.GetVariant());
    }
}

void ResourceWithMetadata::SaveMetadataToXML(XMLElement& destination) const
{
    for (unsigned i = 0; i < metadataKeys_.Size(); ++i)
    {
        XMLElement elem = destination.CreateChild("metadata");
        elem.SetString("name", metadataKeys_[i]);
        elem.SetVariant(GetMetadata(metadataKeys_[i]));
    }
}

void ResourceWithMetadata::CopyMetadata(const ResourceWithMetadata& source)
{
    metadata_ = source.metadata_;
    metadataKeys_ = source.metadataKeys_;
}

}
