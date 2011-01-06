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

#ifndef RESOURCE_RESOURCE_H
#define RESOURCE_RESOURCE_H

#include "HashedType.h"
#include "Timer.h"

class Deserializer;
class ResourceCache;
class Serializer;

//! Base class for resources
class Resource : public HashedType
{
public:
    //! Construct with name
    Resource(const std::string& name);
    
    //! Load resource. Throw exception on error
    virtual void load(Deserializer& source, ResourceCache* cache = 0) = 0;
    //! Save resource. Throw exception if not supported or on error
    virtual void save(Serializer& dest);
    
    //! Set memory use in bytes, possibly approximate
    void setMemoryUse(unsigned size);
    //! Reset last used timer
    void resetUseTimer();
    
    //! Return name
    const std::string& getName() const { return mName; }
    //! Return name hash
    StringHash getNameHash() const { return mNameHash; }
    //! Return memory use in bytes, possibly approximate
    unsigned getMemoryUse() const { return mMemoryUse; }
    //! Return time since last use in milliseconds. If referred to elsewhere than in the resource cache, returns always zero
    unsigned getUseTimer();
    
private:
    //! Name
    std::string mName;
    //! Name hash
    StringHash mNameHash;
    //! Last used timer
    Timer mUseTimer;
    //! Memory use in bytes
    unsigned mMemoryUse;
};

inline StringHash getResourceHash(Resource* resource)
{
    if (resource)
        return resource->getNameHash();
    else
        return StringHash();
}

inline std::string getResourceName(Resource* resource)
{
    if (resource)
        return resource->getName();
    else
        return std::string();
}

#endif // RESOURCE_RESOURCE_H
