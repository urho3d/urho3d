// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "AppState_Benchmark03.h"
#include "AppStateManager.h"
#include "Benchmark03_MoleculeLogic.h"

#include <Urho3D/Core/Context.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

AppState_Benchmark03::AppState_Benchmark03(Context* context)
    : AppState_Base(context)
{
    name_ = "Molecules";

    // This constructor is called once when the application runs, so we can register here
    context->RegisterFactory<Benchmark03_MoleculeLogic>();

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    SharedPtr<Material> material0 = MakeShared<Material>(context_);
    material0->SetName("Molecule0");
    material0->SetShaderParameter("MatDiffColor", Vector4(0, 1, 1, 1));
    material0->SetShaderParameter("MatSpecColor", Vector4(1, 1, 1, 100));
    cache->AddManualResource(material0);

    SharedPtr<Material> material1 = material0->Clone("Molecule1");
    material1->SetShaderParameter("MatDiffColor", Vector4(0, 1, 0, 1));
    cache->AddManualResource(material1);

    SharedPtr<Material> material2 = material0->Clone("Molecule2");
    material2->SetShaderParameter("MatDiffColor", Vector4(0, 0, 1, 1));
    cache->AddManualResource(material2);

    SharedPtr<Material> material3 = material0->Clone("Molecule3");
    material3->SetShaderParameter("MatDiffColor", Vector4(1, 0.5f, 0, 1));
    cache->AddManualResource(material3);

    SharedPtr<Material> material4 = material0->Clone("Molecule4");
    material4->SetShaderParameter("MatDiffColor", Vector4(1, 0, 0, 1));
    cache->AddManualResource(material4);

    SharedPtr<Material> material5 = material0->Clone("Molecule5");
    material5->SetShaderParameter("MatDiffColor", Vector4(1, 0, 1, 1));
    cache->AddManualResource(material5);

    SharedPtr<Material> material6 = material0->Clone("Molecule6");
    material6->SetShaderParameter("MatDiffColor", Vector4(1, 1, 0, 1));
    cache->AddManualResource(material6);
}

void AppState_Benchmark03::OnEnter()
{
    assert(!scene_);
    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();

    Node* zoneNode = scene_->CreateChild();
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.f, 1000.f));
    zone->SetAmbientColor(Color(0.5f, 0.5f, 0.5f));
    zone->SetFogColor(Color(0.3f, 0.6f, 0.9f));
    zone->SetFogStart(10000.f);
    zone->SetFogEnd(10000.f);

    Node* lightNode = scene_->CreateChild();
    lightNode->SetRotation(Quaternion(45.f, 45.f, 0.f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);

    Node* cameraNode = scene_->CreateChild("Camera");
    cameraNode->SetPosition(Vector3(0.f, 0.f, -10.f));
    Camera* camera = cameraNode->CreateComponent<Camera>();
    camera->SetOrthographic(true);

    constexpr int NUM_MOLECULES = 280;

    for (int i = 0; i < NUM_MOLECULES; ++i)
        CreateMolecule({Random(-10.f, 10.f), Random(-6.f, 6.f)}, Random(7));

    GetSubsystem<Input>()->SetMouseVisible(false);
    SetupViewport();
    SubscribeToEvent(scene_, E_SCENEUPDATE, URHO3D_HANDLER(AppState_Benchmark03, HandleSceneUpdate));
    fpsCounter_.Clear();
}

void AppState_Benchmark03::OnLeave()
{
    DestroyViewport();
    scene_ = nullptr;
}

void AppState_Benchmark03::CreateMolecule(const Vector2& pos, i32 type)
{
    assert(type >= 0 && type <= 6);

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    Node* node = scene_->CreateChild();
    node->SetPosition2D(pos);
    
    StaticModel* obj = node->CreateComponent<StaticModel>();
    obj->SetModel(cache->GetResource<Model>("Models/Sphere.mdl"));
    obj->SetMaterial(cache->GetResource<Material>("Molecule" + String(type)));

    Benchmark03_MoleculeLogic* logic = node->CreateComponent<Benchmark03_MoleculeLogic>();
    logic->SetParameters(type);
}

void AppState_Benchmark03::HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData[SceneUpdate::P_TIMESTEP].GetFloat();

    fpsCounter_.Update(timeStep);
    UpdateCurrentFpsElement();

    if (GetSubsystem<Input>()->GetKeyDown(KEY_ESCAPE))
    {
        GetSubsystem<AppStateManager>()->SetRequiredAppStateId(APPSTATEID_MAINSCREEN);
        return;
    }

    if (fpsCounter_.GetTotalTime() >= 30.f)
        GetSubsystem<AppStateManager>()->SetRequiredAppStateId(APPSTATEID_RESULTSCREEN);
}
