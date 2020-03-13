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
#ifdef URHO3D_PROFILING
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
