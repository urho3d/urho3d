#include "../../Scene/Node.h"
#include "../Defines.h"

extern "C"
{

URHO3D_API Component* Node_CreateComponent(Node* nativeInstance, StringHash type, CreateMode mode = REPLICATED, unsigned id = 0)
{
    return nativeInstance->CreateComponent(type, mode, id);
}

URHO3D_API Node* Node_CreateChild(Node* nativeInstance, const char* name = "", CreateMode mode = REPLICATED, unsigned id = 0, bool temporary = false)
{
    return nativeInstance->CreateChild(name, mode, id, temporary);
}

URHO3D_API void Node_SetScale(Node* nativeInstance, Vector3& scale)
{
    nativeInstance->SetScale(scale);
}

URHO3D_API void Node_SetDirection(Node* nativeInstance, Vector3& direction)
{
    nativeInstance->SetDirection(direction);
}

URHO3D_API void Node_SetPosition(Node* nativeInstance, Vector3& position)
{
    nativeInstance->SetPosition(position);
}

}
