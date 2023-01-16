// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include "foot_steps.h"
#include "utilities/spawn.h"

namespace Urho3D
{

void FootSteps::RegisterObject(Context* context)
{
    context->RegisterFactory<FootSteps>();
}

FootSteps::FootSteps(Context* context)
    : LogicComponent(context)
{
}

void FootSteps::Start()
{
    // Subscribe to animation triggers, which are sent by the AnimatedModel's node (same as our node)
    SubscribeToEvent(node_, E_ANIMATIONTRIGGER, URHO3D_HANDLER(FootSteps, HandleAnimationTrigger));
}

void FootSteps::HandleAnimationTrigger(StringHash eventType, VariantMap& eventData)
{
    using namespace AnimationTrigger;

    AnimatedModel* model = node_->GetComponent<AnimatedModel>();
    AnimationState* state = model->GetAnimationState(eventData[P_NAME].GetString());
    
    if (!state)
        return;

    // If the animation is blended with sufficient weight, instantiate a local particle effect for the footstep.
    // The trigger data (string) tells the bone scenenode to use. Note: called on both client and server
    if (state->GetWeight() > 0.5f)
    {
        Node* bone = node_->GetChild(eventData[P_DATA].GetString(), true);
        if (bone)
            SpawnParticleEffect(bone->GetScene(), bone->GetWorldPosition(), "Particle/SnowExplosionFade.xml", 1, LOCAL);
    }
}

} // namespace Urho3D
