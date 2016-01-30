//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Container/HashMap.h"
#include "../Container/HashSet.h"
#include "../Core/Mutex.h"
#include "../Container/Ptr.h"
#include "../Container/RefCounted.h"
#include "../Core/Thread.h"
#include "../Math/StringHash.h"

namespace Urho3D
{

class Resource;
class ResourceCache;

/// Queue item for background loading of a resource.
struct BackgroundLoadItem
{
    /// Resource.
    SharedPtr<Resource> resource_;
    /// Resources depended on for loading.
    HashSet<Pair<StringHash, StringHash> > dependencies_;
    /// Resources that depend on this resource's loading.
    HashSet<Pair<StringHash, StringHash> > dependents_;
    /// Whether to send failure event.
    bool sendEventOnFailure_;
};

/// Background loader of resources. Owned by the ResourceCache.
class BackgroundLoader : public RefCounted, public Thread
{
public:
    /// Construct.
    BackgroundLoader(ResourceCache* owner);

    /// Destruct. Forcibly clear the load queue.
    ~BackgroundLoader();

    /// Resource background loading loop.
    virtual void ThreadFunction();

    /// Queue loading of a resource. The name must be sanitated to ensure consistent format. Return true if queued (not a duplicate and resource was a known type).
    bool QueueResource(StringHash type, const String& name, bool sendEventOnFailure, Resource* caller);
    /// Wait and finish possible loading of a resource when being requested from the cache.
    void WaitForResource(StringHash type, StringHash nameHash);
    /// Process resources that are ready to finish.
    void FinishResources(int maxMs);

    /// Return amount of resources in the load queue.
    unsigned GetNumQueuedResources() const;

private:
    /// Finish one background loaded resource.
    void FinishBackgroundLoading(BackgroundLoadItem& item);

    /// Resource cache.
    ResourceCache* owner_;
    /// Mutex for thread-safe access to the background load queue.
    mutable Mutex backgroundLoadMutex_;
    /// Resources that are queued for background loading.
    HashMap<Pair<StringHash, StringHash>, BackgroundLoadItem> backgroundLoadQueue_;
};

}
