#pragma once

#include "Object.h"

using namespace Urho3D;

namespace Urho3D
{
    class Node;
    class ResourceCache;
    class Scene;
}

class Character;

class CharacterDemo : public Object
{
    OBJECT(CharacterDemo);

public:
    /// Construct.
    CharacterDemo(Context* context);
    
    /// Initialize.
    void Start();
    
private:
    /// Create static scene content.
    void CreateScene();
    /// Create controllable character.
    void CreateCharacter();
    /// Subscribe to necessary events.
    void SubscribeToEvents();
    /// Handle application update. Set controls to character & check global keys.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle application post-update. Update camera position after character has moved.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Scene.
    SharedPtr<Scene> scene_;
    /// Resource cache subsystem, stored here for convenience.
    SharedPtr<ResourceCache> cache_;
    /// Camera scene node.
    SharedPtr<Node> cameraNode_;
    /// The controllable character.
    WeakPtr<Character> character_;
    /// First person camera flag.
    bool firstPerson_;
};
