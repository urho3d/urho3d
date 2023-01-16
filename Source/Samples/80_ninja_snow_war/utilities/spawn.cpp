// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include "spawn.h"

#include "../foot_steps.h"
#include "../game_object.h"
#include "../light_flash.h"
#include "../ninja.h"
#include "../potion.h"
#include "../snow_crate.h"
#include "../snowball.h"

namespace Urho3D
{

Node* SpawnObject(Scene* scene, const Vector3& position, const Quaternion& rotation, const String& className)
{
    ResourceCache* cache = scene->GetSubsystem<ResourceCache>();
    XMLFile* xml = cache->GetResource<XMLFile>("native_objects/" + className + ".xml");
    Node* ret =  scene->InstantiateXML(xml->GetRoot(), position, rotation);

    // В AS-версии игры XML-файлы содержат компонеты ScriprInstance. В папке native_objects они вырезаны,
    // взамен нужно добавить C++-версии компонентов. Эти компоненты создаются только на сервере и не реплицируются на клиенте
    if (className == "ninja")
    {
        ret->CreateComponent<Ninja>(LOCAL);
        Node* node = ret->GetChild(0); // Дочерняя нода с анимированной моделью
        node->CreateComponent<FootSteps>(LOCAL);
    }
    else if (className == "snowball")
    {
        ret->CreateComponent<Snowball>(LOCAL);
    }
    else if (className == "light_flash")
    {
        ret->CreateComponent<LightFlash>(LOCAL);
    }
    else if (className == "potion")
    {
        ret->CreateComponent<Potion>(LOCAL);
    }
    else if (className == "snow_crate")
    {
        ret->CreateComponent<SnowCrate>(LOCAL);
    }

    return ret;
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
