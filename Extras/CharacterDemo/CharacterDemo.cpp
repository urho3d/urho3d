#include "AnimatedModel.h"
#include "AnimationController.h"
#include "Camera.h"
#include "Character.h"
#include "CharacterDemo.h"
#include "CollisionShape.h"
#include "Context.h"
#include "Controls.h"
#include "CoreEvents.h"
#include "DebugRenderer.h"
#include "Engine.h"
#include "Font.h"
#include "Input.h"
#include "Light.h"
#include "Material.h"
#include "Model.h"
#include "Octree.h"
#include "PhysicsWorld.h"
#include "ProcessUtils.h"
#include "Renderer.h"
#include "RigidBody.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "StaticModel.h"
#include "Text.h"
#include "UI.h"
#include "Zone.h"

#include "Main.h"
#include "DebugNew.h"

const float CAMERA_MIN_DIST = 1.0f;
const float CAMERA_MAX_DIST = 5.0f;

int Run()
{
    SharedPtr<Context> context(new Context());
    SharedPtr<Engine> engine(new Engine(context));
    engine->Initialize("CharacterDemo", "CharacterDemo.log", GetArguments());
    
    SharedPtr<CharacterDemo> characterDemo(new CharacterDemo(context));
    characterDemo->Start();
    while (!engine->IsExiting())
        engine->RunFrame();
    
    return 0;
}

DEFINE_MAIN(Run())

OBJECTTYPESTATIC(CharacterDemo);

CharacterDemo::CharacterDemo(Context* context) :
    Object(context),
    cache_(GetSubsystem<ResourceCache>()),
    firstPerson_(false)
{
    // Register factory for the Character component so it can be created via CreateComponent
    context_->RegisterFactory<Character>();
}

void CharacterDemo::Start()
{
    CreateScene();
    CreateCharacter();
    SubscribeToEvents();
}

void CharacterDemo::CreateScene()
{
    scene_ = new Scene(context_);
    
    // Create scene subsystem components
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<PhysicsWorld>();
    scene_->CreateComponent<DebugRenderer>();
    
    // Create camera and define viewport. Camera does not necessarily have to belong to the scene
    cameraNode_ = new Node(context_);
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    GetSubsystem<Renderer>()->SetViewport(0, new Viewport(context_, scene_, camera));
    
    // Create static scene content, same as in TestScene.as
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    
    {
        Node* lightNode = scene_->CreateChild("GlobalLight");
        lightNode->SetDirection(Vector3(0.3f, -0.5f, 0.425f));
        
        Light* light = lightNode->CreateComponent<Light>();
        light->SetLightType(LIGHT_DIRECTIONAL);
        light->SetCastShadows(true);
        light->SetShadowBias(BiasParameters(0.0001f, 0.5f));
        light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
        light->SetSpecularIntensity(0.5f);
    }

    {
        Node* objectNode = scene_->CreateChild("Floor");
        objectNode->SetPosition(Vector3(0.0f, -0.5f, 0.0f));
        objectNode->SetScale(Vector3(200.0f, 1.0f, 200.0f));
        
        StaticModel* object = objectNode->CreateComponent<StaticModel>();
        object->SetModel(cache_->GetResource<Model>("Models/Box.mdl"));
        object->SetMaterial(cache_->GetResource<Material>("Materials/Stone.xml"));
        object->SetOccluder(true);
        
        RigidBody* body = objectNode->CreateComponent<RigidBody>();
        body->SetCollisionLayer(2);
        CollisionShape* shape = objectNode->CreateComponent<CollisionShape>();
        shape->SetBox(Vector3::ONE);
    }
    
    for (unsigned i = 0; i < 50; ++i)
    {
        Node* objectNode = scene_->CreateChild("Box");
        objectNode->SetPosition(Vector3(Random() * 180.0f - 90.0f, 1.0f, Random() * 180.0f - 90.0f));
        objectNode->SetScale(2.0f);
        
        StaticModel* object = objectNode->CreateComponent<StaticModel>();
        object->SetModel(cache_->GetResource<Model>("Models/Box.mdl"));
        object->SetMaterial(cache_->GetResource<Material>("Materials/Stone.xml"));
        object->SetCastShadows(true);
        
        RigidBody* body = objectNode->CreateComponent<RigidBody>();
        body->SetCollisionLayer(2);
        CollisionShape* shape = objectNode->CreateComponent<CollisionShape>();
        shape->SetBox(Vector3::ONE);
    }
    
    for (unsigned i = 0; i < 10; ++i)
    {
        Node* objectNode = scene_->CreateChild("Box");
        objectNode->SetPosition(Vector3(Random() * 180.0f - 90.0f, 10.0f, Random() * 180.0f - 90.0f));
        objectNode->SetScale(20);
        
        StaticModel* object = objectNode->CreateComponent<StaticModel>();
        object->SetModel(cache_->GetResource<Model>("Models/Box.mdl"));
        object->SetMaterial(cache_->GetResource<Material>("Materials/Stone.xml"));
        object->SetCastShadows(true);
        object->SetOccluder(true);
        
        RigidBody* body = objectNode->CreateComponent<RigidBody>();
        body->SetCollisionLayer(2);
        CollisionShape* shape = objectNode->CreateComponent<CollisionShape>();
        shape->SetBox(Vector3::ONE);
    }

    for (unsigned i = 0; i < 50; ++i)
    {
        Node* objectNode = scene_->CreateChild("Mushroom");
        objectNode->SetPosition(Vector3(Random() * 180.0f - 90.0f, 0.0f, Random() * 180.0f - 90.0f));
        objectNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
        objectNode->SetScale(5.0f);
        
        StaticModel* object = objectNode->CreateComponent<StaticModel>();
        object->SetModel(cache_->GetResource<Model>("Models/Mushroom.mdl"));
        object->SetMaterial(cache_->GetResource<Material>("Materials/Mushroom.xml"));
        object->SetCastShadows(true);
        
        RigidBody* body = objectNode->CreateComponent<RigidBody>();
        body->SetCollisionLayer(2);
        CollisionShape* shape = objectNode->CreateComponent<CollisionShape>();
        shape->SetTriangleMesh(object->GetModel(), 0);
    }
}

void CharacterDemo::CreateCharacter()
{
    Node* objectNode = scene_->CreateChild("Jack");
    objectNode->SetPosition(Vector3(0.0f, 1.0f, 0.0f));
    
    // Create the rendering component + animation controller
    AnimatedModel* object = objectNode->CreateComponent<AnimatedModel>();
    object->SetModel(cache_->GetResource<Model>("Models/Jack.mdl"));
    object->SetMaterial(cache_->GetResource<Material>("Materials/Jack.xml"));
    object->SetCastShadows(true);
    objectNode->CreateComponent<AnimationController>();
    
    // Create rigidbody, and set non-zero mass so that the body becomes dynamic
    RigidBody* body = objectNode->CreateComponent<RigidBody>();
    body->SetCollisionLayer(1);
    body->SetMass(1.0f);
    
    // Set zero angular factor so that physics doesn't turn the character on its own.
    // Instead we will control the character yaw manually
    body->SetAngularFactor(Vector3::ZERO);
    
    // Set the rigidbody to signal collision also when in rest, so that we get ground collisions properly
    body->SetCollisionEventMode(COLLISION_ALWAYS);
    
    // Set a capsule shape for collision
    CollisionShape* shape = objectNode->CreateComponent<CollisionShape>();
    shape->SetCapsule(0.7f, 1.8f, Vector3(0.0f, 0.9f, 0.0f));
    
    // Create the character logic component, which takes care of steering the rigidbody
    // Remember it so that we can set the controls. Use a WeakPtr because the scene hierarchy already owns it
    // and keeps it alive as long as it's not removed from the hierarchy
    character_ = objectNode->CreateComponent<Character>();
}

void CharacterDemo::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, HANDLER(CharacterDemo, HandleUpdate));
    SubscribeToEvent(E_POSTUPDATE, HANDLER(CharacterDemo, HandlePostUpdate));
}

void CharacterDemo::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    Input* input = GetSubsystem<Input>();

    if (input->GetKeyDown(KEY_ESC))
        GetSubsystem<Engine>()->Exit();
    
    if (input->GetKeyPress('F'))
        firstPerson_ = !firstPerson_;
    
    if (character_)
    {
        // Get movement controls and assign them to the character logic component
        character_->controls_.Set(CTRL_UP, input->GetKeyDown('W'));
        character_->controls_.Set(CTRL_DOWN, input->GetKeyDown('S'));
        character_->controls_.Set(CTRL_LEFT, input->GetKeyDown('A'));
        character_->controls_.Set(CTRL_RIGHT, input->GetKeyDown('D'));
        character_->controls_.Set(CTRL_JUMP, input->GetKeyDown(KEY_SPACE));
        
        // Add character yaw & pitch from the mouse motion
        character_->controls_.yaw_ += (float)input->GetMouseMoveX() * YAW_SENSITIVITY;
        character_->controls_.pitch_ += (float)input->GetMouseMoveY() * YAW_SENSITIVITY;
        // Limit pitch
        character_->controls_.pitch_ = Clamp(character_->controls_.pitch_, -80.0f, 80.0f);
        
        // Set rotation already here so that it's updated every rendering frame instead of every physics frame
        character_->GetNode()->SetRotation(Quaternion(character_->controls_.yaw_, Vector3::UP));
    }
}

void CharacterDemo::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!character_)
        return;
    
    Node* characterNode = character_->GetNode();
    
    // Get camera lookat dir from character yaw + pitch
    Quaternion rot = characterNode->GetRotation();
    Quaternion dir = rot * Quaternion(character_->controls_.pitch_, Vector3::RIGHT);
    
    if (firstPerson_)
    {
        // First person camera: position to the head bone + offset slightly forward & up
        Node* headNode = characterNode->GetChild("Bip01_Head", true);
        if (headNode)
        {
            cameraNode_->SetPosition(headNode->GetWorldPosition() + rot * Vector3(0.0f, 0.15f, 0.2f));
            cameraNode_->SetRotation(dir);
        }
    }
    else
    {
        // Third person camera: position behind the character
        Vector3 aimPoint = characterNode->GetPosition() + rot * Vector3(0.0f, 1.7f, 0.0f);
        
        // Collide camera ray with static physics objects (layer bitmask 2) to ensure we see the character properly
        Vector3 rayDir = dir * Vector3::BACK;
        float rayDistance = CAMERA_MAX_DIST;
        PhysicsRaycastResult result;
        scene_->GetComponent<PhysicsWorld>()->RaycastSingle(result, Ray(aimPoint, rayDir), rayDistance, 2);
        if (result.body_)
            rayDistance = Min(rayDistance, result.distance_);
        rayDistance = Clamp(rayDistance, CAMERA_MIN_DIST, CAMERA_MAX_DIST);
        
        cameraNode_->SetPosition(aimPoint + rayDir * rayDistance);
        cameraNode_->SetRotation(dir);
    }
}
