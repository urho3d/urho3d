//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "../Graphics/Animation.h"
#include "../Core/Context.h"
#include "../IO/Deserializer.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Core/Profiler.h"
#include "../Resource/ResourceCache.h"
#include "../IO/Serializer.h"
#include "../Resource/XMLFile.h"

#include "../DebugNew.h"

namespace Urho3D
{

inline bool CompareTriggers(AnimationTriggerPoint& lhs, AnimationTriggerPoint& rhs)
{
    return lhs.time_ < rhs.time_;
}

void AnimationTrack::GetKeyFrameIndex(float time, unsigned& index) const
{
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
}

Animation::Animation(Context* context) :
    Resource(context),
    length_(0.f)
{
}

Animation::~Animation()
{
}

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
        LOGERROR(source.GetName() + " is not a valid animation file");
        return false;
    }
    
    // Read name and length
    animationName_ = source.ReadString();
    animationNameHash_ = animationName_;
    length_ = source.ReadFloat();
    tracks_.Clear();
    
    unsigned tracks = source.ReadUInt();
    tracks_.Resize(tracks);
    memoryUse += tracks * sizeof(AnimationTrack);
    
    // Read tracks
    for (unsigned i = 0; i < tracks; ++i)
    {
        AnimationTrack& newTrack = tracks_[i];
        newTrack.name_ = source.ReadString();
        newTrack.nameHash_ = newTrack.name_;
        newTrack.channelMask_ = source.ReadUByte();
        
        unsigned keyFrames = source.ReadUInt();
        newTrack.keyFrames_.Resize(keyFrames);
        memoryUse += keyFrames * sizeof(AnimationKeyFrame);
        
        // Read keyframes of the track
        for (unsigned j = 0; j < keyFrames; ++j)
        {
            AnimationKeyFrame& newKeyFrame = newTrack.keyFrames_[j];
            newKeyFrame.time_ = source.ReadFloat();
            if (newTrack.channelMask_ & CHANNEL_POSITION)
                newKeyFrame.position_ = source.ReadVector3();
            if (newTrack.channelMask_ & CHANNEL_ROTATION)
                newKeyFrame.rotation_ = source.ReadQuaternion();
            if (newTrack.channelMask_ & CHANNEL_SCALE)
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
        XMLElement triggerElem = rootElem.GetChild("trigger");
        while (triggerElem)
        {
            if (triggerElem.HasAttribute("normalizedtime"))
                AddTrigger(triggerElem.GetFloat("normalizedtime"), true, triggerElem.GetVariant());
            else if (triggerElem.HasAttribute("time"))
                AddTrigger(triggerElem.GetFloat("time"), false, triggerElem.GetVariant());
            
            triggerElem = triggerElem.GetNext("trigger");
        }

        memoryUse += triggers_.Size() * sizeof(AnimationTriggerPoint);
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
    dest.WriteUInt(tracks_.Size());
    for (unsigned i = 0; i < tracks_.Size(); ++i)
    {
        const AnimationTrack& track = tracks_[i];
        dest.WriteString(track.name_);
        dest.WriteUByte(track.channelMask_);
        dest.WriteUInt(track.keyFrames_.Size());
        
        // Write keyframes of the track
        for (unsigned j = 0; j < track.keyFrames_.Size(); ++j)
        {
            const AnimationKeyFrame& keyFrame = track.keyFrames_[j];
            dest.WriteFloat(keyFrame.time_);
            if (track.channelMask_ & CHANNEL_POSITION)
                dest.WriteVector3(keyFrame.position_);
            if (track.channelMask_ & CHANNEL_ROTATION)
                dest.WriteQuaternion(keyFrame.rotation_);
            if (track.channelMask_ & CHANNEL_SCALE)
                dest.WriteVector3(keyFrame.scale_);
        }
    }
    
    // If triggers have been defined, write an XML file for them
    if (triggers_.Size())
    {
        File* destFile = dynamic_cast<File*>(&dest);
        if (destFile)
        {
            String xmlName = ReplaceExtension(destFile->GetName(), ".xml");
            
            SharedPtr<XMLFile> xml(new XMLFile(context_));
            XMLElement rootElem = xml->CreateRoot("animation");
            
            for (unsigned i = 0; i < triggers_.Size(); ++i)
            {
                XMLElement triggerElem = rootElem.CreateChild("trigger");
                triggerElem.SetFloat("time", triggers_[i].time_);
                triggerElem.SetVariant(triggers_[i].data_);
            }
            
            File xmlFile(context_, xmlName, FILE_WRITE);
            xml->Save(xmlFile);
        }
        else
            LOGWARNING("Can not save animation trigger data when not saving into a file");
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

void Animation::SetTracks(const Vector<AnimationTrack>& tracks)
{
    tracks_ = tracks;
}

void Animation::AddTrigger(float time, bool timeIsNormalized, const Variant& data)
{
    AnimationTriggerPoint newTrigger;
    newTrigger.time_ = timeIsNormalized ? time * length_ : time;
    newTrigger.data_ = data;
    triggers_.Push(newTrigger);
    
    Sort(triggers_.Begin(), triggers_.End(), CompareTriggers);
}

void Animation::RemoveTrigger(unsigned index)
{
    if (index < triggers_.Size())
        triggers_.Erase(index);
}

void Animation::RemoveAllTriggers()
{
    triggers_.Clear();
}

void Animation::SetNumTriggers(unsigned num)
{
    triggers_.Resize(num);
}

const AnimationTrack* Animation::GetTrack(unsigned index) const
{
    return index < tracks_.Size() ? &tracks_[index] : 0;
}

const AnimationTrack* Animation::GetTrack(const String& name) const
{
    for (Vector<AnimationTrack>::ConstIterator i = tracks_.Begin(); i != tracks_.End(); ++i)
    {
        if (i->name_ == name)
            return &(*i);
    }
    
    return 0;
}

const AnimationTrack* Animation::GetTrack(StringHash nameHash) const
{
    for (Vector<AnimationTrack>::ConstIterator i = tracks_.Begin(); i != tracks_.End(); ++i)
    {
        if (i->nameHash_ == nameHash)
            return &(*i);
    }
    
    return 0;
}

}
