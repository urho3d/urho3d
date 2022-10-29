// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Base/Utils.h"
#include "../Container/Sort.h"
#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/Animation.h"
#include "../IO/Deserializer.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/Serializer.h"
#include "../Resource/JSONFile.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLFile.h"

#include "../DebugNew.h"

namespace Urho3D
{

inline bool CompareTriggers(AnimationTriggerPoint& lhs, AnimationTriggerPoint& rhs)
{
    return lhs.time_ < rhs.time_;
}

inline bool CompareKeyFrames(AnimationKeyFrame& lhs, AnimationKeyFrame& rhs)
{
    return lhs.time_ < rhs.time_;
}

void AnimationTrack::SetKeyFrame(i32 index, const AnimationKeyFrame& keyFrame)
{
    assert(index >= 0);

    if (index < keyFrames_.Size())
    {
        keyFrames_[index] = keyFrame;
        Urho3D::Sort(keyFrames_.Begin(), keyFrames_.End(), CompareKeyFrames);
    }
    else if (index == keyFrames_.Size())
        AddKeyFrame(keyFrame);
}

void AnimationTrack::AddKeyFrame(const AnimationKeyFrame& keyFrame)
{
    bool needSort = keyFrames_.Size() ? keyFrames_.Back().time_ > keyFrame.time_ : false;
    keyFrames_.Push(keyFrame);
    if (needSort)
        Urho3D::Sort(keyFrames_.Begin(), keyFrames_.End(), CompareKeyFrames);
}

void AnimationTrack::InsertKeyFrame(i32 index, const AnimationKeyFrame& keyFrame)
{
    assert(index >= 0);
    keyFrames_.Insert(index, keyFrame);
    Urho3D::Sort(keyFrames_.Begin(), keyFrames_.End(), CompareKeyFrames);
}

void AnimationTrack::RemoveKeyFrame(i32 index)
{
    assert(index >= 0);
    keyFrames_.Erase(index);
}

void AnimationTrack::RemoveAllKeyFrames()
{
    keyFrames_.Clear();
}

AnimationKeyFrame* AnimationTrack::GetKeyFrame(i32 index)
{
    assert(index >= 0);
    return index < keyFrames_.Size() ? &keyFrames_[index] : nullptr;
}

bool AnimationTrack::GetKeyFrameIndex(float time, i32& index) const
{
    if (keyFrames_.Empty())
        return false;

    if (time < 0.0f)
        time = 0.0f;

    if (index >= keyFrames_.Size())
        index = keyFrames_.Size() - 1;

    // Check for being too far ahead
    while (index && time < keyFrames_[index].time_)
        --index;

    // Check for being too far behind
    while (index < keyFrames_.Size() - 1 && time >= keyFrames_[index + 1].time_)
        ++index;

    return true;
}

Animation::Animation(Context* context) :
    ResourceWithMetadata(context),
    length_(0.f)
{
}

Animation::~Animation() = default;

void Animation::RegisterObject(Context* context)
{
    context->RegisterFactory<Animation>();
}

bool Animation::BeginLoad(Deserializer& source)
{
    unsigned memoryUse = sizeof(Animation);

    // Check ID
    if (source.ReadFileID() != "UANI")
    {
        URHO3D_LOGERROR(source.GetName() + " is not a valid animation file");
        return false;
    }

    // Read name and length
    animationName_ = source.ReadString();
    animationNameHash_ = animationName_;
    length_ = source.ReadFloat();
    tracks_.Clear();

    unsigned tracks = source.ReadU32();
    memoryUse += tracks * sizeof(AnimationTrack);

    // Read tracks
    for (unsigned i = 0; i < tracks; ++i)
    {
        AnimationTrack* newTrack = CreateTrack(source.ReadString());
        newTrack->channelMask_ = AnimationChannels(source.ReadU8());

        unsigned keyFrames = source.ReadU32();
        newTrack->keyFrames_.Resize(keyFrames);
        memoryUse += keyFrames * sizeof(AnimationKeyFrame);

        // Read keyframes of the track
        for (unsigned j = 0; j < keyFrames; ++j)
        {
            AnimationKeyFrame& newKeyFrame = newTrack->keyFrames_[j];
            newKeyFrame.time_ = source.ReadFloat();
            if (!!(newTrack->channelMask_ & AnimationChannels::Position))
                newKeyFrame.position_ = source.ReadVector3();
            if (!!(newTrack->channelMask_ & AnimationChannels::Rotation))
                newKeyFrame.rotation_ = source.ReadQuaternion();
            if (!!(newTrack->channelMask_ & AnimationChannels::Scale))
                newKeyFrame.scale_ = source.ReadVector3();
        }
    }

    // Optionally read triggers from an XML file
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    String xmlName = ReplaceExtension(GetName(), ".xml");

    SharedPtr<XMLFile> file(cache->GetTempResource<XMLFile>(xmlName, false));
    if (file)
    {
        XMLElement rootElem = file->GetRoot();
        for (XMLElement triggerElem = rootElem.GetChild("trigger"); triggerElem; triggerElem = triggerElem.GetNext("trigger"))
        {
            if (triggerElem.HasAttribute("normalizedtime"))
                AddTrigger(triggerElem.GetFloat("normalizedtime"), true, triggerElem.GetVariant());
            else if (triggerElem.HasAttribute("time"))
                AddTrigger(triggerElem.GetFloat("time"), false, triggerElem.GetVariant());
        }

        LoadMetadataFromXML(rootElem);

        memoryUse += triggers_.Size() * sizeof(AnimationTriggerPoint);
        SetMemoryUse(memoryUse);
        return true;
    }

    // Optionally read triggers from a JSON file
    String jsonName = ReplaceExtension(GetName(), ".json");

    SharedPtr<JSONFile> jsonFile(cache->GetTempResource<JSONFile>(jsonName, false));
    if (jsonFile)
    {
        const JSONValue& rootVal = jsonFile->GetRoot();
        const JSONArray& triggerArray = rootVal.Get("triggers").GetArray();

        for (const JSONValue& triggerValue : triggerArray)
        {
            JSONValue normalizedTimeValue = triggerValue.Get("normalizedTime");
            if (!normalizedTimeValue.IsNull())
                AddTrigger(normalizedTimeValue.GetFloat(), true, triggerValue.GetVariant());
            else
            {
                JSONValue timeVal = triggerValue.Get("time");
                if (!timeVal.IsNull())
                    AddTrigger(timeVal.GetFloat(), false, triggerValue.GetVariant());
            }
        }

        const JSONArray& metadataArray = rootVal.Get("metadata").GetArray();
        LoadMetadataFromJSON(metadataArray);

        memoryUse += triggers_.Size() * sizeof(AnimationTriggerPoint);
        SetMemoryUse(memoryUse);
        return true;
    }

    SetMemoryUse(memoryUse);
    return true;
}

bool Animation::Save(Serializer& dest) const
{
    // Write ID, name and length
    dest.WriteFileID("UANI");
    dest.WriteString(animationName_);
    dest.WriteFloat(length_);

    // Write tracks
    dest.WriteU32(tracks_.Size());
    for (HashMap<StringHash, AnimationTrack>::ConstIterator i = tracks_.Begin(); i != tracks_.End(); ++i)
    {
        const AnimationTrack& track = i->second_;
        dest.WriteString(track.name_);
        dest.WriteU8(ToU8(track.channelMask_));
        dest.WriteU32(track.keyFrames_.Size());

        // Write keyframes of the track
        for (const AnimationKeyFrame& keyFrame : track.keyFrames_)
        {
            dest.WriteFloat(keyFrame.time_);
            if (!!(track.channelMask_ & AnimationChannels::Position))
                dest.WriteVector3(keyFrame.position_);
            if (!!(track.channelMask_ & AnimationChannels::Rotation))
                dest.WriteQuaternion(keyFrame.rotation_);
            if (!!(track.channelMask_ & AnimationChannels::Scale))
                dest.WriteVector3(keyFrame.scale_);
        }
    }

    // If triggers have been defined, write an XML file for them
    if (!triggers_.Empty() || HasMetadata())
    {
        File* destFile = dynamic_cast<File*>(&dest);
        if (destFile)
        {
            String xmlName = ReplaceExtension(destFile->GetName(), ".xml");

            SharedPtr<XMLFile> xml(new XMLFile(context_));
            XMLElement rootElem = xml->CreateRoot("animation");

            for (const AnimationTriggerPoint& trigger : triggers_)
            {
                XMLElement triggerElem = rootElem.CreateChild("trigger");
                triggerElem.SetFloat("time", trigger.time_);
                triggerElem.SetVariant(trigger.data_);
            }

            SaveMetadataToXML(rootElem);

            File xmlFile(context_, xmlName, FILE_WRITE);
            xml->Save(xmlFile);
        }
        else
            URHO3D_LOGWARNING("Can not save animation trigger data when not saving into a file");
    }

    return true;
}

void Animation::SetAnimationName(const String& name)
{
    animationName_ = name;
    animationNameHash_ = StringHash(name);
}

void Animation::SetLength(float length)
{
    length_ = Max(length, 0.0f);
}

AnimationTrack* Animation::CreateTrack(const String& name)
{
    /// \todo When tracks / keyframes are created dynamically, memory use is not updated
    StringHash nameHash(name);
    AnimationTrack* oldTrack = GetTrack(nameHash);
    if (oldTrack)
        return oldTrack;

    AnimationTrack& newTrack = tracks_[nameHash];
    newTrack.name_ = name;
    newTrack.nameHash_ = nameHash;
    return &newTrack;
}

bool Animation::RemoveTrack(const String& name)
{
    HashMap<StringHash, AnimationTrack>::Iterator i = tracks_.Find(StringHash(name));
    if (i != tracks_.End())
    {
        tracks_.Erase(i);
        return true;
    }
    else
        return false;
}

void Animation::RemoveAllTracks()
{
    tracks_.Clear();
}

void Animation::SetTrigger(i32 index, const AnimationTriggerPoint& trigger)
{
    assert(index >= 0);

    if (index == triggers_.Size())
        AddTrigger(trigger);
    else if (index < triggers_.Size())
    {
        triggers_[index] = trigger;
        Sort(triggers_.Begin(), triggers_.End(), CompareTriggers);
    }
}

void Animation::AddTrigger(const AnimationTriggerPoint& trigger)
{
    triggers_.Push(trigger);
    Sort(triggers_.Begin(), triggers_.End(), CompareTriggers);
}

void Animation::AddTrigger(float time, bool timeIsNormalized, const Variant& data)
{
    AnimationTriggerPoint newTrigger;
    newTrigger.time_ = timeIsNormalized ? time * length_ : time;
    newTrigger.data_ = data;
    triggers_.Push(newTrigger);

    Sort(triggers_.Begin(), triggers_.End(), CompareTriggers);
}

void Animation::RemoveTrigger(i32 index)
{
    assert(index >= 0);

    if (index < triggers_.Size())
        triggers_.Erase(index);
}

void Animation::RemoveAllTriggers()
{
    triggers_.Clear();
}

void Animation::SetNumTriggers(i32 num)
{
    assert(num >= 0);
    triggers_.Resize(num);
}

SharedPtr<Animation> Animation::Clone(const String& cloneName) const
{
    SharedPtr<Animation> ret(new Animation(context_));

    ret->SetName(cloneName);
    ret->SetAnimationName(animationName_);
    ret->length_ = length_;
    ret->tracks_ = tracks_;
    ret->triggers_ = triggers_;
    ret->CopyMetadata(*this);
    ret->SetMemoryUse(GetMemoryUse());

    return ret;
}

AnimationTrack* Animation::GetTrack(i32 index)
{
    assert(index >= 0);

    if (index >= GetNumTracks())
        return nullptr;

    int j = 0;
    for(HashMap<StringHash, AnimationTrack>::Iterator i = tracks_.Begin(); i != tracks_.End(); ++i)
    {
        if (j == index)
            return &i->second_;

        ++j;
    }

    return nullptr;
}

AnimationTrack* Animation::GetTrack(const String& name)
{
    HashMap<StringHash, AnimationTrack>::Iterator i = tracks_.Find(StringHash(name));
    return i != tracks_.End() ? &i->second_ : nullptr;
}

AnimationTrack* Animation::GetTrack(StringHash nameHash)
{
    HashMap<StringHash, AnimationTrack>::Iterator i = tracks_.Find(nameHash);
    return i != tracks_.End() ? &i->second_ : nullptr;
}

AnimationTriggerPoint* Animation::GetTrigger(i32 index)
{
    assert(index >= 0);
    return index < triggers_.Size() ? &triggers_[index] : nullptr;
}

}
