#include "StateMachine.h"
#include "../Precompiled.h"

#include "../Container/Sort.h"
#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/Animation.h"
#include "../IO/Deserializer.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/Serializer.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLFile.h"
#include "../Resource/JSONFile.h"

#include "../DebugNew.h"


namespace Urho3D
{

StateMachine::StateMachine(Context* context)
:ResourceWithMetadata(context)
{}

StateMachine::~StateMachine()
{

}

void StateMachine::RegisterObject(Context* context)
{
    context->RegisterFactory<StateMachine>();
}

bool StateMachine::BeginLoad(Deserializer& source) 
{
    return true;
}

bool StateMachine::Save(Serializer& dest) const 
{
    return true;
}

}
