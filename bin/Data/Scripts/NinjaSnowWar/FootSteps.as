class FootSteps : ScriptObject
{
    void Start()
    {
        // Subscribe to animation triggers, which are sent by the AnimatedModel's node (same as our node)
        SubscribeToEvent(node, "AnimationTrigger", "HandleAnimationTrigger");
    }

    void HandleAnimationTrigger(StringHash eventType, VariantMap& eventData)
    {
        AnimatedModel@ model = node.GetComponent("AnimatedModel");
        AnimationState@ state = model.animationStates[eventData["Name"].GetString()];
        if (state is null)
            return;

        // If the animation is blended with sufficient weight, instantiate a local particle effect for the footstep.
        // The trigger data (string) tells the bone scenenode to use. Note: called on both client and server
        if (state.weight > 0.5f)
        {
            Node@ bone = node.GetChild(eventData["Data"].GetString(), true);
            if (bone !is null)
                SpawnParticleEffect(bone.worldPosition, "Particle/SnowExplosionFade.xml", 1, LOCAL);
        }
    }
}