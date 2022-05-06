// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#ifdef URHO3D_THREADING

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../IO/Log.h"
#include "../Resource/BackgroundLoader.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/ResourceEvents.h"

#include "../DebugNew.h"

namespace Urho3D
{

BackgroundLoader::BackgroundLoader(ResourceCache* owner) :
    owner_(owner)
{
}

BackgroundLoader::~BackgroundLoader()
{
    MutexLock lock(backgroundLoadMutex_);

    backgroundLoadQueue_.Clear();
}

void BackgroundLoader::ThreadFunction()
{
    URHO3D_PROFILE_THREAD("BackgroundLoader Thread");

    while (shouldRun_)
    {
        backgroundLoadMutex_.Acquire();

        // Search for a queued resource that has not been loaded yet
        HashMap<Pair<StringHash, StringHash>, BackgroundLoadItem>::Iterator i = backgroundLoadQueue_.Begin();
        while (i != backgroundLoadQueue_.End())
        {
            if (i->second_.resource_->GetAsyncLoadState() == ASYNC_QUEUED)
                break;
            else
                ++i;
        }

        if (i == backgroundLoadQueue_.End())
        {
            // No resources to load found
            backgroundLoadMutex_.Release();
            Time::Sleep(5);
        }
        else
        {
            BackgroundLoadItem& item = i->second_;
            Resource* resource = item.resource_;
            // We can be sure that the item is not removed from the queue as long as it is in the
            // "queued" or "loading" state
            backgroundLoadMutex_.Release();

            bool success = false;
            SharedPtr<File> file = owner_->GetFile(resource->GetName(), item.sendEventOnFailure_);
            if (file)
            {
                resource->SetAsyncLoadState(ASYNC_LOADING);
                success = resource->BeginLoad(*file);
            }

            // Process dependencies now
            // Need to lock the queue again when manipulating other entries
            Pair<StringHash, StringHash> key = MakePair(resource->GetType(), resource->GetNameHash());
            backgroundLoadMutex_.Acquire();
            if (item.dependents_.Size())
            {
                for (HashSet<Pair<StringHash, StringHash> >::Iterator i = item.dependents_.Begin();
                     i != item.dependents_.End(); ++i)
                {
                    HashMap<Pair<StringHash, StringHash>, BackgroundLoadItem>::Iterator j = backgroundLoadQueue_.Find(*i);
                    if (j != backgroundLoadQueue_.End())
                        j->second_.dependencies_.Erase(key);
                }

                item.dependents_.Clear();
            }

            resource->SetAsyncLoadState(success ? ASYNC_SUCCESS : ASYNC_FAIL);
            backgroundLoadMutex_.Release();
        }
    }
}

bool BackgroundLoader::QueueResource(StringHash type, const String& name, bool sendEventOnFailure, Resource* caller)
{
    StringHash nameHash(name);
    Pair<StringHash, StringHash> key = MakePair(type, nameHash);

    MutexLock lock(backgroundLoadMutex_);

    // Check if already exists in the queue
    if (backgroundLoadQueue_.Find(key) != backgroundLoadQueue_.End())
        return false;

    BackgroundLoadItem& item = backgroundLoadQueue_[key];
    item.sendEventOnFailure_ = sendEventOnFailure;

    // Make sure the pointer is non-null and is a Resource subclass
    item.resource_ = DynamicCast<Resource>(owner_->GetContext()->CreateObject(type));
    if (!item.resource_)
    {
        URHO3D_LOGERROR("Could not load unknown resource type " + String(type));

        if (sendEventOnFailure && Thread::IsMainThread())
        {
            using namespace UnknownResourceType;

            VariantMap& eventData = owner_->GetEventDataMap();
            eventData[P_RESOURCETYPE] = type;
            owner_->SendEvent(E_UNKNOWNRESOURCETYPE, eventData);
        }

        backgroundLoadQueue_.Erase(key);
        return false;
    }

    URHO3D_LOGDEBUG("Background loading resource " + name);

    item.resource_->SetName(name);
    item.resource_->SetAsyncLoadState(ASYNC_QUEUED);

    // If this is a resource calling for the background load of more resources, mark the dependency as necessary
    if (caller)
    {
        Pair<StringHash, StringHash> callerKey = MakePair(caller->GetType(), caller->GetNameHash());
        HashMap<Pair<StringHash, StringHash>, BackgroundLoadItem>::Iterator j = backgroundLoadQueue_.Find(callerKey);
        if (j != backgroundLoadQueue_.End())
        {
            BackgroundLoadItem& callerItem = j->second_;
            item.dependents_.Insert(callerKey);
            callerItem.dependencies_.Insert(key);
        }
        else
            URHO3D_LOGWARNING("Resource " + caller->GetName() +
                       " requested for a background loaded resource but was not in the background load queue");
    }

    // Start the background loader thread now
    if (!IsStarted())
        Run();

    return true;
}

void BackgroundLoader::WaitForResource(StringHash type, StringHash nameHash)
{
    backgroundLoadMutex_.Acquire();

    // Check if the resource in question is being background loaded
    Pair<StringHash, StringHash> key = MakePair(type, nameHash);
    HashMap<Pair<StringHash, StringHash>, BackgroundLoadItem>::Iterator i = backgroundLoadQueue_.Find(key);
    if (i != backgroundLoadQueue_.End())
    {
        backgroundLoadMutex_.Release();

        {
            Resource* resource = i->second_.resource_;
            HiresTimer waitTimer;
            bool didWait = false;

            for (;;)
            {
                unsigned numDeps = i->second_.dependencies_.Size();
                AsyncLoadState state = resource->GetAsyncLoadState();
                if (numDeps > 0 || state == ASYNC_QUEUED || state == ASYNC_LOADING)
                {
                    didWait = true;
                    Time::Sleep(1);
                }
                else
                    break;
            }

            if (didWait)
                URHO3D_LOGDEBUG("Waited " + String(waitTimer.GetUSec(false) / 1000) + " ms for background loaded resource " +
                         resource->GetName());
        }

        // This may take a long time and may potentially wait on other resources, so it is important we do not hold the mutex during this
        FinishBackgroundLoading(i->second_);

        backgroundLoadMutex_.Acquire();
        backgroundLoadQueue_.Erase(i);
        backgroundLoadMutex_.Release();
    }
    else
        backgroundLoadMutex_.Release();
}

void BackgroundLoader::FinishResources(int maxMs)
{
    if (IsStarted())
    {
        HiresTimer timer;

        backgroundLoadMutex_.Acquire();

        for (HashMap<Pair<StringHash, StringHash>, BackgroundLoadItem>::Iterator i = backgroundLoadQueue_.Begin();
             i != backgroundLoadQueue_.End();)
        {
            Resource* resource = i->second_.resource_;
            unsigned numDeps = i->second_.dependencies_.Size();
            AsyncLoadState state = resource->GetAsyncLoadState();
            if (numDeps > 0 || state == ASYNC_QUEUED || state == ASYNC_LOADING)
                ++i;
            else
            {
                // Finishing a resource may need it to wait for other resources to load, in which case we can not
                // hold on to the mutex
                backgroundLoadMutex_.Release();
                FinishBackgroundLoading(i->second_);
                backgroundLoadMutex_.Acquire();
                i = backgroundLoadQueue_.Erase(i);
            }

            // Break when the time limit passed so that we keep sufficient FPS
            if (timer.GetUSec(false) >= maxMs * 1000LL)
                break;
        }

        backgroundLoadMutex_.Release();
    }
}

unsigned BackgroundLoader::GetNumQueuedResources() const
{
    MutexLock lock(backgroundLoadMutex_);
    return backgroundLoadQueue_.Size();
}

void BackgroundLoader::FinishBackgroundLoading(BackgroundLoadItem& item)
{
    Resource* resource = item.resource_;

    bool success = resource->GetAsyncLoadState() == ASYNC_SUCCESS;
    // If BeginLoad() phase was successful, call EndLoad() and get the final success/failure result
    if (success)
    {
#ifdef URHO3D_TRACY_PROFILING
        URHO3D_PROFILE_COLOR(FinishBackgroundLoading, URHO3D_PROFILE_RESOURCE_COLOR);

        String profileBlockName("Finish" + resource->GetTypeName());
        URHO3D_PROFILE_STR(profileBlockName.CString(), profileBlockName.Length());
#elif defined(URHO3D_PROFILING)
        String profileBlockName("Finish" + resource->GetTypeName());

        auto* profiler = owner_->GetSubsystem<Profiler>();
        if (profiler)
            profiler->BeginBlock(profileBlockName.CString());
#endif

        URHO3D_LOGDEBUG("Finishing background loaded resource " + resource->GetName());
        success = resource->EndLoad();

#ifdef URHO3D_PROFILING
        if (profiler)
            profiler->EndBlock();
#endif
    }
    resource->SetAsyncLoadState(ASYNC_DONE);

    if (!success && item.sendEventOnFailure_)
    {
        using namespace LoadFailed;

        VariantMap& eventData = owner_->GetEventDataMap();
        eventData[P_RESOURCENAME] = resource->GetName();
        owner_->SendEvent(E_LOADFAILED, eventData);
    }

    // Store to the cache just before sending the event; use same mechanism as for manual resources
    if (success || owner_->GetReturnFailedResources())
        owner_->AddManualResource(resource);

    // Send event, either success or failure
    {
        using namespace ResourceBackgroundLoaded;

        VariantMap& eventData = owner_->GetEventDataMap();
        eventData[P_RESOURCENAME] = resource->GetName();
        eventData[P_SUCCESS] = success;
        eventData[P_RESOURCE] = resource;
        owner_->SendEvent(E_RESOURCEBACKGROUNDLOADED, eventData);
    }
}

}

#endif
