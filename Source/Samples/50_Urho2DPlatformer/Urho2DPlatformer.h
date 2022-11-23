// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"
#include "Utilities2D/Sample2D.h"

class Character2D;
class Sample2D;

/// 2D platformer example.
/// This sample demonstrates:
///    - Creating an orthogonal 2D scene from tile map file
///    - Displaying the scene using the Renderer subsystem
///    - Handling keyboard to move a character and zoom 2D camera
///    - Generating physics shapes from the tmx file's objects
///    - Mixing physics and translations to move the character
///    - Using Box2D Contact listeners to handle the gameplay
///    - Displaying debug geometry for physics and tile map
/// Note that this sample uses some functions from Sample2D utility class.
class Urho2DPlatformer : public Sample
{
    URHO3D_OBJECT(Urho2DPlatformer, Sample);

public:
    /// Construct.
    explicit Urho2DPlatformer(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;
    /// Setup before engine initialization. Modifies the engine parameters.
    void Setup() override;

private:
    /// Construct the scene content.
    void CreateScene();
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the logic post update event.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the post render update event.
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the end rendering event.
    void HandleSceneRendered(StringHash eventType, VariantMap& eventData);
    /// Handle the contact begin event (Box2D contact listener).
    void HandleCollisionBegin(StringHash eventType, VariantMap& eventData);
    /// Handle the contact end event (Box2D contact listener).
    void HandleCollisionEnd(StringHash eventType, VariantMap& eventData);
    /// Handle reloading the scene.
    void ReloadScene(bool reInit);
    /// Handle 'PLAY' button released event.
    void HandlePlayButton(StringHash eventType, VariantMap& eventData);

    /// The controllable character component.
    WeakPtr<Character2D> character2D_;
    /// Flag for drawing debug geometry.
    bool drawDebug_{};
    /// Scaling factor based on tiles' aspect ratio.
    float moveSpeedScale_{};

    /// Sample2D utility object.
    SharedPtr<Sample2D> sample2D_;
};
