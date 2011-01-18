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

#include "Precompiled.h"
#include "Audio.h"
#include "Entity.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "Sound.h"
#include "StereoChannel.h"
#include "StringUtils.h"
#include "XMLElement.h"

#include "DebugNew.h"

static const std::string typeNames[] =
{
    "master",
    "effect",
    "music",
    "voice"
};

StereoChannel::StereoChannel(Audio* audio, const std::string& name) :
    Channel(audio),
    Component(name),
    mAutoRemoveTimer(0.0f),
    mAutoRemove(false)
{
}

void StereoChannel::save(Serializer& dest)
{
    // Read Component properties
    Component::save(dest);
    
    // Write channel properties
    dest.writeUByte((unsigned char)mChannelType);
    dest.writeFloat(mFrequency);
    dest.writeFloat(mGain);
    dest.writeFloat(mAttenuation);
    dest.writeFloat(mPanning);
    dest.writeBool(mAutoRemove);
    
    // Write currently playing sound and its offset (if any)
    Sound* sound = getSound();
    dest.writeStringHash(getResourceHash(sound));
    if (sound)
        dest.writeUInt((unsigned)(getPlayPosition() - sound->getStart()));
}

void StereoChannel::load(Deserializer& source, ResourceCache* cache)
{
    // Read Component properties
    Component::load(source, cache);
    
    // Read channel properties
    mChannelType = (ChannelType)source.readUByte();
    mFrequency = source.readFloat();
    mGain = source.readFloat();
    mAttenuation = source.readFloat();
    mPanning = source.readFloat();
    mAutoRemove = source.readBool();
    
    // Read currently playing sound (if any)
    StringHash soundHash = source.readStringHash();
    if (soundHash)
    {
        Sound* sound = cache->getResource<Sound>(soundHash);
        unsigned offset = source.readUInt();
        
        play(sound);
        setPlayPosition(sound->getStart() + offset);
    }
}

void StereoChannel::saveXML(XMLElement& dest)
{
    // Write Component properties
    Component::saveXML(dest);
    
    // Write channel properties
    XMLElement channelElem = dest.createChildElement("channel");
    channelElem.setString("type", typeNames[mChannelType]);
    channelElem.setFloat("frequency", mFrequency);
    channelElem.setFloat("gain", mGain);
    channelElem.setFloat("attenuation", mAttenuation);
    channelElem.setFloat("panning", mPanning);
    channelElem.setBool("autoremove", mAutoRemove);
    
    // Write currently playing sound and its offset (if any)
    Sound* sound = getSound();
    if (sound)
    {
        XMLElement soundElem = dest.createChildElement("sound");
        soundElem.setString("name", getResourceName(sound));
        soundElem.setInt("offset", (unsigned)(getPlayPosition() - sound->getStart()));
    }
}

void StereoChannel::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read Component properties
    Component::loadXML(source, cache);
    
    // Read channel properties
    XMLElement channelElem = source.getChildElement("channel");
    mChannelType = (ChannelType)getIndexFromStringList(channelElem.getStringLower("type"), typeNames, 4, 1);
    mFrequency = channelElem.getFloat("frequency");
    mGain = channelElem.getFloat("gain");
    mAttenuation = channelElem.getFloat("attenuation");
    mPanning = channelElem.getFloat("panning");
    mAutoRemove = channelElem.getBool("autoremove");
    
    // Read currently playing sound (if any)
    XMLElement soundElem = source.getChildElement("sound");
    if (soundElem)
    {
        Sound* sound = cache->getResource<Sound>(soundElem.getString("name"));
        unsigned offset = soundElem.getInt("offset");
        
        play(sound);
        setPlayPosition(sound->getStart() + offset);
    }
}

bool StereoChannel::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    Sound* sound = getSound();
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    checkUByte((unsigned char)mChannelType, (unsigned char)CHANNEL_EFFECT, baseRevision, bits, 1);
    checkFloat(mFrequency, baseRevision, bits, 2);
    checkFloat(mGain, 1.0f, baseRevision, bits, 4);
    checkFloat(mAttenuation, 1.0f, baseRevision, bits, 8);
    checkFloat(mPanning, 0.0f, baseRevision, bits, 16);
    checkStringHash(getResourceHash(sound), StringHash(), baseRevision, bits, 32);
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeUByteDelta((unsigned char)mChannelType, dest, destRevision, bits & 1);
    writeFloatDelta(mFrequency, dest, destRevision, bits & 2);
    writeFloatDelta(mGain, dest, destRevision, bits & 4);
    writeFloatDelta(mAttenuation, dest, destRevision, bits & 8);
    writeFloatDelta(mPanning, dest, destRevision, bits & 16);
    writeStringHashDelta(getResourceHash(sound), dest, destRevision, bits & 32);
    
    return bits != 0;
}

void StereoChannel::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    StringHash soundHash;
    unsigned char bits = source.readUByte();
    if (bits & 1)
        mChannelType = (ChannelType)source.readUByte();
    if (bits & 2)
        mFrequency = source.readFloat();
    if (bits & 4)
        mGain = source.readFloat();
    if (bits & 8)
        mAttenuation = source.readFloat();
    if (bits & 16)
        mPanning = source.readFloat();
    if (bits & 32)
        soundHash = source.readStringHash();
    
    // Trigger sound only if not yet playing (we might get multiple copies of the same update)
    if ((soundHash) && (!isPlaying()))
    {
        Sound* sound = cache->getResource<Sound>(soundHash);
        play(sound);
    }
}

void StereoChannel::update(float timeStep)
{
    if (!mAudio)
        return;
    
    Channel::update(timeStep);
    
    // Check automatic remove. Never do autoremove for client proxy components, because this could lead in exceptions
    // as the server could still be sending updates to a removed component
    if ((mAutoRemove) && (!isProxy()) && (mEntity))
    {
        if (!isPlaying())
        {
            mAutoRemoveTimer += timeStep;
            if (mAutoRemoveTimer > CHANNEL_AUTOREMOVE_DELAY)
            {
                mEntity->removeComponent(this);
                return;
            }
        }
        else
            mAutoRemoveTimer = 0.0f;
    }
}

void StereoChannel::setAutoRemove(bool enable)
{
    mAutoRemove = enable;
}
