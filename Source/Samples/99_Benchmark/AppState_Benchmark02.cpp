// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "AppState_Benchmark02.h"
#include "AppStateManager.h"
#include "Benchmark02_WomanMover.h"

#include <Urho3D/Core/Context.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/Animation.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/AnimationState.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Scene/SplinePath.h>

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

AppState_Benchmark02::AppState_Benchmark02(Context* context)
    : AppState_Base(context)
{
    name_ = "Orcs & Humans";

    // This constructor is called once when the application runs, so we can register here
    context->RegisterFactory<Benchmark02_WomanMover>();
}

void AppState_Benchmark02::OnEnter()
{
    assert(!scene_);
    LoadSceneXml("99_Benchmark/Scenes/Benchmark02.xml");

    Vector3 castlePos = scene_->GetChild("Castle")->GetPosition();
    BoundingBox castleTop(castlePos - Vector3(7.f, 0.f, 7.f), castlePos + Vector3(7.f, 0.f, 7.f));

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    Vector<Node*> womans;
    scene_->GetChildrenWithTag(womans, "woman");
    for (Node* woman : womans)
    {
        Benchmark02_WomanMover* mover = woman->CreateComponent<Benchmark02_WomanMover>();
        mover->SetParameters(2.f, 100.f, castleTop);

        AnimatedModel* modelObject = woman->GetComponent<AnimatedModel>();
        Animation* walkAnimation = cache->GetResource<Animation>("Models/Kachujin/Kachujin_Walk.ani");
        AnimationState* state = modelObject->AddAnimationState(walkAnimation);
        if (state)
        {
            state->SetWeight(1.0f);
            state->SetLooped(true);
            state->SetTime(Random(walkAnimation->GetLength()));
        }
    }

    Vector<Node*> mutants;
    scene_->GetChildrenWithTag(mutants, "mutant");
    for (Node* mutant : mutants)
    {
        AnimationController* animCtrl = mutant->CreateComponent<AnimationController>();
        animCtrl->PlayExclusive("Models/Mutant/Mutant_Idle0.ani", 0, true, 0.f);
        animCtrl->SetTime("Models/Mutant/Mutant_Idle0.ani", Random(animCtrl->GetLength("Models/Mutant/Mutant_Idle0.ani")));
    }

    Node* mutantGeneral = scene_->GetChild("MutantGeneral");
    AnimationController* generalAnimCtrl = mutantGeneral->CreateComponent<AnimationController>();
    generalAnimCtrl->PlayExclusive("Models/Mutant/Mutant_Idle1.ani", 0, true, 0.f);
    generalAnimCtrl->SetTime("Models/Mutant/Mutant_Idle1.ani", Random(generalAnimCtrl->GetLength("Models/Mutant/Mutant_Idle1.ani")));

    Node* cameraNode = scene_->GetChild("Camera");
    
    Node* cameraPath = scene_->GetChild("CameraPath");
    SplinePath* cameraSplinePath = cameraPath->CreateComponent<SplinePath>();
    cameraSplinePath->SetControlledNode(cameraNode);
    for (Node* child : cameraPath->GetChildren())
        cameraSplinePath->AddControlPoint(child);
    cameraSplinePath->SetSpeed(2.f);
    cameraSplinePath->SetInterpolationMode(InterpolationMode::CATMULL_ROM_FULL_CURVE);

    Node* cameraTargetNode = scene_->CreateChild("CameraTarget");
    Node* cameraTargetPath = scene_->GetChild("CameraTargetPath");
    SplinePath* cameraTargetSplinePath = cameraPath->CreateComponent<SplinePath>();
    cameraTargetSplinePath->SetControlledNode(cameraTargetNode);
    for (Node* child : cameraPath->GetChildren())
        cameraTargetSplinePath->AddControlPoint(child);
    cameraTargetSplinePath->SetSpeed(2.f);
    cameraTargetSplinePath->SetInterpolationMode(InterpolationMode::CATMULL_ROM_FULL_CURVE);

    GetSubsystem<Input>()->SetMouseVisible(false);
    SetupViewport();
    SubscribeToEvent(scene_, E_SCENEUPDATE, URHO3D_HANDLER(AppState_Benchmark02, HandleSceneUpdate));
    fpsCounter_.Clear();
}

void AppState_Benchmark02::OnLeave()
{
    DestroyViewport();
    scene_ = nullptr;
}

void AppState_Benchmark02::HandleSceneUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData[SceneUpdate::P_TIMESTEP].GetFloat();

    fpsCounter_.Update(timeStep);
    UpdateCurrentFpsElement();

    if (GetSubsystem<Input>()->GetKeyDown(KEY_ESCAPE))
    {
        GetSubsystem<AppStateManager>()->SetRequiredAppStateId(APPSTATEID_MAINSCREEN);
        return;
    }

    Node* cameraPath = scene_->GetChild("CameraPath");
    SplinePath* cameraSplinePath = cameraPath->GetComponent<SplinePath>();
    cameraSplinePath->Move(timeStep);

    Node* cameraTargetPath = scene_->GetChild("CameraTargetPath");
    SplinePath* cameraTargetSplinePath = cameraPath->GetComponent<SplinePath>();
    cameraTargetSplinePath->Move(timeStep);

    Node* cameraTargetNode = scene_->GetChild("CameraTarget");
    Node* cameraNode = scene_->GetChild("Camera");
    cameraNode->LookAt(cameraTargetNode->GetPosition());

    if (cameraSplinePath->IsFinished())
        GetSubsystem<AppStateManager>()->SetRequiredAppStateId(APPSTATEID_RESULTSCREEN);
}
