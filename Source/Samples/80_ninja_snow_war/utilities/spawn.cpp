// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include "spawn.h"

#include "../game_object.h"

namespace Urho3D
{

Node* SpawnObject(Scene* scene, const Vector3& position, const Quaternion& rotation, const String& className)
{
    ResourceCache* cache = scene->GetSubsystem<ResourceCache>();
    XMLFile* xml = cache->GetResource<XMLFile>("native_objects/" + className + ".xml");
    return scene->InstantiateXML(xml->GetRoot(), position, rotation);
}

Node* SpawnParticleEffect(Scene* scene, const Vector3& position, const String& effectName, float duration, CreateMode mode)
{
    ResourceCache* cache = scene->GetSubsystem<ResourceCache>();

    Node* newNode = scene->CreateChild("Effect", mode);
    newNode->SetPosition(position);

    // Create the particle emitter
    ParticleEmitter* emitter = newNode->CreateComponent<ParticleEmitter>();
    emitter->SetEffect(cache->GetResource<ParticleEffect>(effectName));

    // Create a GameObject for managing the effect lifetime. This is always local, so for server-controlled effects it
    // exists only on the server
    GameObject* object = newNode->CreateComponent<GameObject>(LOCAL);
    object->duration = duration;

    return newNode;
}

Node* SpawnSound(Scene* scene, const Vector3& position, const String& soundName, float duration)
{
    ResourceCache* cache = scene->GetSubsystem<ResourceCache>();

    Node* newNode = scene->CreateChild();
    newNode->SetPosition(position);

    // Create the sound source
    SoundSource3D* source = newNode->CreateComponent<SoundSource3D>();
    Sound* sound = cache->GetResource<Sound>(soundName);
    source->SetDistanceAttenuation(200.0f, 5000.0f, 1.0f);
    source->Play(sound);

    // Create a GameObject for managing the sound lifetime
    GameObject* object = newNode->CreateComponent<GameObject>(LOCAL);
    object->duration = duration;

    return newNode;
}

} // namespace Urho3D
