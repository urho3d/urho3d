// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

// class SoundStream | File: ../Audio/SoundStream.h
void CollectMembers_SoundStream(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

    // virtual unsigned SoundStream::GetData(signed char* dest, unsigned numBytes) = 0
    // Error: type "signed char*" can not automatically bind

}

// class Audio | File: ../Audio/Audio.h
void CollectMembers_Audio(MemberCollection& members)
{
    CollectMembers_Object(members);

    // void Audio::MixOutput(void* dest, unsigned samples)
    // Error: type "void*" can not automatically bind

}

// class BufferedSoundStream | File: ../Audio/BufferedSoundStream.h
void CollectMembers_BufferedSoundStream(MemberCollection& members)
{
    CollectMembers_SoundStream(members);

    Remove(members.methods_, "virtual unsigned SoundStream::GetData(signed char* dest, unsigned numBytes) = 0");

    // void BufferedSoundStream::AddData(const SharedArrayPtr<signed char>& data, unsigned numBytes)
    // Error: type "const SharedArrayPtr<signed char>&" can not automatically bind
    // void BufferedSoundStream::AddData(const SharedArrayPtr<signed short>& data, unsigned numBytes)
    // Error: type "const SharedArrayPtr<signed short>&" can not automatically bind
    // void BufferedSoundStream::AddData(void* data, unsigned numBytes)
    // Error: type "void*" can not automatically bind

}

// class OggVorbisSoundStream | File: ../Audio/OggVorbisSoundStream.h
void CollectMembers_OggVorbisSoundStream(MemberCollection& members)
{
    CollectMembers_SoundStream(members);

    Remove(members.methods_, "virtual bool SoundStream::Seek(unsigned sample_number)");
    Remove(members.methods_, "virtual unsigned SoundStream::GetData(signed char* dest, unsigned numBytes) = 0");

}

// class Sound | File: ../Audio/Sound.h
void CollectMembers_Sound(MemberCollection& members)
{
    CollectMembers_ResourceWithMetadata(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");

    // SharedArrayPtr<signed char> Sound::GetData() const
    // Error: type "SharedArrayPtr<signed char>" can not automatically bind
    // signed char* Sound::GetEnd() const
    // Error: type "signed char*" can not automatically bind
    // signed char* Sound::GetRepeat() const
    // Error: type "signed char*" can not automatically bind
    // signed char* Sound::GetStart() const
    // Error: type "signed char*" can not automatically bind
    // void Sound::SetData(const void* data, unsigned dataSize)
    // Error: type "const void*" can not automatically bind

    // static void Sound::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class SoundListener | File: ../Audio/SoundListener.h
void CollectMembers_SoundListener(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class SoundSource | File: ../Audio/SoundSource.h
void CollectMembers_SoundSource(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // volatile signed char* SoundSource::GetPlayPosition() const
    // Error: type "signed char*" can not automatically bind
    // void SoundSource::Mix(int* dest, unsigned samples, int mixRate, bool stereo, bool interpolation)
    // Error: type "int*" can not automatically bind
    // void SoundSource::SetPlayPosition(signed char* pos)
    // Error: type "signed char*" can not automatically bind

}

// class SoundSource3D | File: ../Audio/SoundSource3D.h
void CollectMembers_SoundSource3D(MemberCollection& members)
{
    CollectMembers_SoundSource(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");
    Remove(members.methods_, "virtual void SoundSource::Update(float timeStep)");

    Remove(members.staticMethods_, "static void SoundSource::RegisterObject(Context* context)");

}

} // namespace Urho3D
