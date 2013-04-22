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

#include "Object.h"
#include "Timer.h"

namespace Urho3D
{

class Deserializer;
class Serializer;

/// Base class for resources.
class Resource : public Object
{
    OBJECT(Resource);
    
public:
    /// Construct.
    Resource(Context* context);
    
    /// Load resource. Return true if successful.
    virtual bool Load(Deserializer& source);
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest) const;
    
    /// Set name.
    void SetName(const String& name);
    /// Set memory use in bytes, possibly approximate.
    void SetMemoryUse(unsigned size);
    /// Reset last used timer.
    void ResetUseTimer();
    
    /// Return name.
    const String& GetName() const { return name_; }
    /// Return name hash.
    StringHash GetNameHash() const { return nameHash_; }
    /// Return memory use in bytes, possibly approximate.
    unsigned GetMemoryUse() const { return memoryUse_; }
    /// Return time since last use in milliseconds. If referred to elsewhere than in the resource cache, returns always zero.
    unsigned GetUseTimer();
    
private:
    /// Name.
    String name_;
    /// Name hash.
    StringHash nameHash_;
    /// Last used timer.
    Timer useTimer_;
    /// Memory use in bytes.
    unsigned memoryUse_;
};

inline StringHash GetResourceHash(Resource* resource)
{
    return resource ? resource->GetNameHash() : StringHash();
}

inline String GetResourceName(Resource* resource)
{
    return resource ? resource->GetName() : String();
}

inline ShortStringHash GetResourceType(Resource* resource, ShortStringHash defaultType)
{
    return resource ? resource->GetType() : defaultType;
}

inline ResourceRef GetResourceRef(Resource* resource, ShortStringHash defaultType)
{
    return ResourceRef(GetResourceType(resource, defaultType), GetResourceHash(resource));
}

template <class T> Vector<StringHash> GetResourceHashes(const Vector<SharedPtr<T> >& resources)
{
    Vector<StringHash> ret(resources.Size());
    for (unsigned i = 0; i < resources.Size(); ++i)
        ret[i] = GetResourceHash(resources[i]);
    
    return ret;
}

template <class T> ResourceRefList GetResourceRefList(const Vector<SharedPtr<T> >& resources)
{
    return ResourceRefList(T::GetTypeStatic(), GetResourceHashes(resources));
}

}
