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
#include "PositionalChannel.h"
#include "RegisterTemplates.h"
#include "Song.h"
#include "Sound.h"
#include "StereoChannel.h"
#include "VectorBuffer.h"

static void registerAudio(asIScriptEngine* engine)
{
    engine->RegisterEnum("ChannelType");
    engine->RegisterEnumValue("ChannelType", "CHANNEL_MASTER", CHANNEL_MASTER);
    engine->RegisterEnumValue("ChannelType", "CHANNEL_EFFECT", CHANNEL_EFFECT);
    engine->RegisterEnumValue("ChannelType", "CHANNEL_MUSIC", CHANNEL_MUSIC);
    engine->RegisterEnumValue("ChannelType", "CHANNEL_VOICE", CHANNEL_VOICE);
    
    engine->RegisterObjectType("Audio", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Audio", asBEHAVE_ADDREF, "void f()", asMETHOD(Audio, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Audio", asBEHAVE_RELEASE, "void f()", asMETHOD(Audio, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool setMode(int, int, bool, bool, bool)", asMETHOD(Audio, setMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool play()", asMETHOD(Audio, play), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void stop()", asMETHOD(Audio, stop), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void setMasterGain(ChannelType, float)", asMETHOD(Audio, setMasterGain), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void setListenerPosition(const Vector3& in)", asMETHOD(Audio, setListenerPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void setListenerRotation(const Quaternion& in)", asMETHOD(Audio, setListenerRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void setListenerTransform(const Vector3& in, const Quaternion& in)", asMETHOD(Audio, setListenerTransform), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "uint getBufferSamples() const", asMETHOD(Audio, getBufferSamples), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "uint getBufferSize() const", asMETHOD(Audio, getBufferSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "uint getSampleSize() const", asMETHOD(Audio, getSampleSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "int getMixRate() const", asMETHOD(Audio, getMixRate), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool isSixteenBit() const", asMETHOD(Audio, isSixteenBit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool isStereo() const", asMETHOD(Audio, isStereo), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool isInterpolated() const", asMETHOD(Audio, isInterpolated), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool isPlaying() const", asMETHOD(Audio, isPlaying), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool hasBuffer() const", asMETHOD(Audio, hasBuffer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "float getMasterGain(ChannelType) const", asMETHOD(Audio, getMasterGain), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "const Vector3& getListenerPosition() const", asMETHOD(Audio, getListenerPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "const Quaternion& getListenerRotation() const", asMETHOD(Audio, getListenerRotation), asCALL_THISCALL);
    
    engine->RegisterGlobalFunction("Audio@+ getAudio()", asFUNCTION(getAudio), asCALL_CDECL);
    engine->RegisterGlobalFunction("Audio@+ get_audio()", asFUNCTION(getAudio), asCALL_CDECL);
}

static Sound* ConstructSound(const std::string& name)
{
    return new Sound(name);
}

static void SoundSetData(const VectorBuffer& buffer, Sound* ptr)
{
    if (!buffer.getSize())
        return;
    
    // If the sound is playing, stop it
    Audio* audio = getAudio();
    if (audio)
        audio->stopSound(ptr);
    
    ptr->setData(buffer.getData(), buffer.getSize());
}

static void registerSound(asIScriptEngine* engine)
{
    registerResource<Sound>(engine, "Sound");
    engine->RegisterObjectBehaviour("Sound", asBEHAVE_FACTORY, "Sound@+ f(const string& in)", asFUNCTION(ConstructSound), asCALL_CDECL);
    engine->RegisterObjectMethod("Sound", "void setData(const VectorBuffer& in)", asFUNCTION(SoundSetData), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Sound", "void setFormat(uint, bool, bool)", asMETHOD(Sound, setFormat), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void setOneshot()", asMETHOD(Sound, setOneshot), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void setLooped()", asMETHOD(Sound, setLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void setLoop(uint, uint)", asMETHOD(Sound, setLoop), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "float getLength() const", asMETHOD(Sound, getLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "float getFrequency() const", asMETHOD(Sound, getFrequency), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "uint getIntFrequency() const", asMETHOD(Sound, getIntFrequency), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool isLooped() const", asMETHOD(Sound, isLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool isSixteenBit() const", asMETHOD(Sound, isSixteenBit), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool isStereo() const", asMETHOD(Sound, isStereo), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool isCompressed() const", asMETHOD(Sound, isCompressed), asCALL_THISCALL);
    registerRefCasts<Resource, Sound>(engine, "Resource", "Sound");
}

static void registerSong(asIScriptEngine* engine)
{
    registerResource<Song>(engine, "Song");
    engine->RegisterObjectMethod("Song", "void play(uint)", asMETHOD(Song, play), asCALL_THISCALL);
    engine->RegisterObjectMethod("Song", "void stop()", asMETHOD(Song, stop), asCALL_THISCALL);
    engine->RegisterObjectMethod("Song", "void setGain(float)", asMETHOD(Song, setGain), asCALL_THISCALL);
    engine->RegisterObjectMethod("Song", "void fade(float, float)", asMETHOD(Song, fade), asCALL_THISCALL);
    engine->RegisterObjectMethod("Song", "uint getPosition() const", asMETHOD(Song, getPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("Song", "uint getBpmTempo() const", asMETHOD(Song, getBpmTempo), asCALL_THISCALL);
    engine->RegisterObjectMethod("Song", "float getGain() const", asMETHOD(Song, getGain), asCALL_THISCALL);
    engine->RegisterObjectMethod("Song", "float getFader() const", asMETHOD(Song, getFader), asCALL_THISCALL);
    engine->RegisterObjectMethod("Song", "bool isPlaying() const", asMETHOD(Song, isPlaying), asCALL_THISCALL);
    registerRefCasts<Resource, Song>(engine, "Resource", "Song");
}

static void registerChannels(asIScriptEngine* engine)
{
    registerComponent<StereoChannel>(engine, "StereoChannel");
    registerChannel<StereoChannel>(engine, "StereoChannel");
    engine->RegisterObjectMethod("StereoChannel", "void setAttenuation(float)", asMETHODPR(StereoChannel, setAttenuation, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StereoChannel", "void setAutoRemove(bool)", asMETHODPR(StereoChannel, setAutoRemove, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StereoChannel", "bool getAutoRemove() const", asMETHODPR(StereoChannel, getAutoRemove, () const, bool), asCALL_THISCALL);
    registerRefCasts<Component, StereoChannel>(engine, "Component", "StereoChannel");
    
    registerNode<PositionalChannel>(engine, "PositionalChannel");
    registerChannel<PositionalChannel>(engine, "PositionalChannel");
    engine->RegisterObjectMethod("PositionalChannel", "void setDistanceAttenuation(float, float, float)", asMETHOD(PositionalChannel, setDistanceAttenuation), asCALL_THISCALL);
    engine->RegisterObjectMethod("PositionalChannel", "void setNearDistance(float)", asMETHOD(PositionalChannel, setNearDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("PositionalChannel", "void setFarDistance(float)", asMETHOD(PositionalChannel, setFarDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("PositionalChannel", "void setRolloffFactor(float)", asMETHOD(PositionalChannel, setRolloffFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("PositionalChannel", "void setAutoRemove(bool)", asMETHODPR(PositionalChannel, setAutoRemove, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("PositionalChannel", "bool getNearDistance() const", asMETHOD(PositionalChannel, getNearDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("PositionalChannel", "bool getFarDistance() const", asMETHOD(PositionalChannel, getFarDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("PositionalChannel", "bool getRolloffFactor() const", asMETHOD(PositionalChannel, getRolloffFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("PositionalChannel", "bool getAutoRemove() const", asMETHODPR(PositionalChannel, getAutoRemove, () const, bool), asCALL_THISCALL);
    registerRefCasts<Component, PositionalChannel>(engine, "Component", "PositionalChannel");
    registerRefCasts<Node, PositionalChannel>(engine, "Node", "PositionalChannel");
}

void registerAudioLibrary(asIScriptEngine* engine)
{
    registerAudio(engine);
    registerSound(engine);
    registerSong(engine);
    registerChannels(engine);
}
