//
// Created by arnislielturks on 18.6.11.
//

#pragma once

#include <Urho3D/Input/Controls.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Network/Connection.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>

using namespace Urho3D;

// Control bits we define
static const unsigned CTRL_FORWARD = 1;
static const unsigned CTRL_BACK = 2;
static const unsigned CTRL_LEFT = 4;
static const unsigned CTRL_RIGHT = 8;
static const unsigned CTRL_JUMP = 16;

class Peer: public Object {

    URHO3D_OBJECT(Peer, Object);

public:
    /// Construct.
    explicit Peer(Context* context);

    ~Peer();

    /// Register object factory and attributes.
    static void RegisterObject(Context* context);

    /// Handle physics world update. Called by LogicComponent base class.
    void HandlePhysicsPrestep(StringHash eventType, VariantMap& eventData);

    void Create(Connection* connection);

    void SetScene(Scene* scene);

    void SetConnection(Connection* connection);

    const WeakPtr<Connection> GetConnection() const { return connection_; }

    void SetNode(Node* node);

    const Node* GetNode() const { return node_; };

    void DestroyNode();

private:
    /// Movement controls. Assigned by the main program each physics update step.
    Controls controls_;

    SharedPtr<Node> node_;

    WeakPtr<Connection> connection_;

    WeakPtr<Scene> scene_;

    Timer updateTimer_;
};


