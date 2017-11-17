#include "../../Engine/Engine.h"

// TODO: REMOVE
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"
#include "../../Engine/DebugHud.h"

using namespace Urho3D;

extern "C"
{

URHO3D_API DebugHud* Engine_CreateDebugHud(Engine* nativeInstance)
{
    //return nativeInstance->CreateDebugHud();

    // JUST FOR TEST
    ResourceCache* cache = nativeInstance->GetSubsystem<ResourceCache>();
    XMLFile* xmlFile = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");

    DebugHud* debugHud = nativeInstance->CreateDebugHud();
    debugHud->SetDefaultStyle(xmlFile);

    return debugHud;
}

}
