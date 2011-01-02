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
#include "PositionalChannel.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "Sound.h"
#include "StringUtils.h"
#include "XMLElement.h"

#include "DebugNew.h"

static const float DEFAULT_NEARDISTANCE = 0.0f;
static const float DEFAULT_FARDISTANCE = 100.0f;
static const float DEFAULT_ROLLOFF = 2.0f;

static const std::string typeNames[] =
{
    "master",
    "effect",
    "music",
    "voice"
};

PositionalChannel::PositionalChannel(Audio* audio, const std::string& name) :
    Channel(audio),
    Node(NODE_POSITIONALCHANNEL, name),
    mNearDistance(DEFAULT_NEARDISTANCE),
    mFarDistance(DEFAULT_FARDISTANCE),
    mRolloffFactor(DEFAULT_ROLLOFF),
    mAutoRemoveTimer(0.0f),
    mAutoRemove(false)
{
    // Start from zero volume until attenuation properly calculated
    mAttenuation = 0.0f;
}

void PositionalChannel::save(Serializer& dest)
{
    // Write node properties
    Node::save(dest);
    
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
    
    // Write positional audio properties
    dest.writeFloat(mNearDistance);
    dest.writeFloat(mFarDistance);
    dest.writeFloat(mRolloffFactor);
}

void PositionalChannel::load(Deserializer& source, ResourceCache* cache)
{
    // Read node properties
    Node::load(source, cache);
    
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
    
    // Read positional audio properties
    mNearDistance = source.readFloat();
    mFarDistance = source.readFloat();
    mRolloffFactor = source.readFloat();
}

void PositionalChannel::saveXML(XMLElement& dest)
{
    // Write node properties
    Node::saveXML(dest);
    
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
    
    // Write positional audio properties
    XMLElement rolloffElem = dest.createChildElement("rolloff");
    rolloffElem.setFloat("neardist", mNearDistance);
    rolloffElem.setFloat("fardist", mFarDistance);
    rolloffElem.setFloat("factor", mRolloffFactor);
}

void PositionalChannel::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read node properties
    Node::loadXML(source, cache);
    
    // Read channel properties
    XMLElement channelElem = source.getChildElement("channel");
    mChannelType = (ChannelType)getIndexFromStringList(channelElem.getStringLower("type"), typeNames, 4, 1);
    mFrequency = channelElem.getFloat("frequency");
    mGain = channelElem.getFloat("gain");
    mAttenuation = channelElem.getFloat("attenuation");
    mPanning = channelElem.getFloat("panning");
    mAutoRemove = channelElem.getBool("autoremove");
    
    // Read currently playing sound (if any)
    XMLElement soundElem = source.getChildElement("sound", false);
    if (soundElem.notNull())
    {
        Sound* sound = cache->getResource<Sound>(soundElem.getString("name"));
        unsigned offset = soundElem.getInt("offset");
        
        calculateAttenuation();
        play(sound);
        setPlayPosition(sound->getStart() + offset);
    }
    
    // Read positional audio properties
    XMLElement rolloffElem = source.getChildElement("rolloff");
    mNearDistance = rolloffElem.getFloat("neardist");
    mFarDistance = rolloffElem.getFloat("fardist");
    mRolloffFactor = rolloffElem.getFloat("factor");
}

bool PositionalChannel::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Write Node properties and see if there were any changes
    bool prevBits = Node::writeNetUpdate(dest, destRevision, baseRevision, info);
    
    Sound* sound = getSound();
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    checkUByte((unsigned char)mChannelType, (unsigned char)CHANNEL_EFFECT, baseRevision, bits, 1);
    checkFloat(mFrequency, baseRevision, bits, 2);
    checkUByte((unsigned char)(mGain * 255.0f), 255, baseRevision, bits, 4);
    // Attenuation and panning will be re-calculated according to relative position
    checkStringHash(getResourceHash(sound), StringHash(), baseRevision, bits, 8);
    checkVLE((unsigned)mNearDistance, (unsigned)DEFAULT_NEARDISTANCE, baseRevision, bits, 16);
    checkVLE((unsigned)mFarDistance, (unsigned)DEFAULT_FARDISTANCE, baseRevision, bits, 16);
    checkUByte((unsigned char)(mRolloffFactor * 16.0f), (unsigned char)(DEFAULT_ROLLOFF * 16.0f), baseRevision, bits, 32);
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeUByteDelta((unsigned char)mChannelType, dest, destRevision, bits & 1);
    writeFloatDelta(mFrequency, dest, destRevision, bits & 2);
    writeUByteDelta((unsigned char)(mGain * 255.0f), dest, destRevision, bits & 4);
    writeStringHashDelta(getResourceHash(sound), dest, destRevision, bits & 8);
    writeVLEDelta((unsigned)mNearDistance, dest, destRevision, bits & 16);
    writeVLEDelta((unsigned)mFarDistance, dest, destRevision, bits & 16);
    writeUByteDelta((unsigned char)(mRolloffFactor * 16.0f), dest, destRevision, bits & 32);
    
    return prevBits || (bits != 0);
}

void PositionalChannel::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    Node::readNetUpdate(source, cache, info);
    
    StringHash soundHash;
    unsigned char bits = source.readUByte();
    if (bits & 1)
        mChannelType = (ChannelType)source.readUByte();
    if (bits & 2)
        mFrequency = source.readFloat();
    if (bits & 4)
        mGain = source.readUByte() / 255.0f;
    if (bits & 8)
        soundHash = source.readStringHash();
    if (bits & 16)
    {
        mNearDistance = (float)source.readVLE();
        mFarDistance = (float)source.readVLE();
    }
    if (bits & 32)
        mRolloffFactor = source.readUByte() / 16.0f;;
    
    // Trigger sound only if not yet playing (we might get multiple copies of the same update)
    if ((soundHash) && (!isPlaying()))
    {
        Sound* sound = cache->getResource<Sound>(soundHash);
        calculateAttenuation();
        play(sound);
    }
}

void PositionalChannel::update(float timeStep)
{
    if (!mAudio)
        return;
    
    Channel::update(timeStep);
    calculateAttenuation();
    
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

void PositionalChannel::setDistanceAttenuation(float nearDistance, float farDistance, float rolloffFactor)
{
    mNearDistance = max(nearDistance, 0.0f);
    mFarDistance = max(farDistance, 0.0f);
    mRolloffFactor = max(rolloffFactor, CHANNEL_MIN_ROLLOFF);
}

void PositionalChannel::setFarDistance(float distance)
{
    mFarDistance = max(distance, 0.0f);
}

void PositionalChannel::setNearDistance(float distance)
{
    mNearDistance = max(distance, 0.0f);
}

void PositionalChannel::setRolloffFactor(float factor)
{
    mRolloffFactor = max(factor, CHANNEL_MIN_ROLLOFF);
}

void PositionalChannel::setAutoRemove(bool enable)
{
    mAutoRemove = enable;
}

void PositionalChannel::calculateAttenuation()
{
    if (!mAudio)
        return;
    
    float interval = mFarDistance - mNearDistance;
    if (interval > 0.0f)
    {
        Vector3 relativePos(mAudio->getListenerRotation().getInverse() * (getWorldPosition() - mAudio->getListenerPosition()));
        float distance = clamp(relativePos.getLength() - mNearDistance, 0.0f, interval);
        
        mAttenuation = powf(1.0f - distance / interval, mRolloffFactor);
        mPanning = relativePos.getNormalized().mX;
    }
}
