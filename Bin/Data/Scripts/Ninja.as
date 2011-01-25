class Ninja
{
    void start()
    {
        subscribeToEvent("Create", "handleCreate");
    }

    void handleCreate(StringHash eventType, VariantMap& eventData)
    {
        Vector3 pos = eventData["Pos"].getVector3();
        Quaternion rot = eventData["Rot"].getQuaternion();

        // Create model
        AnimatedModel@ model = entity.createComponent("AnimatedModel");
        model.setModel(cache.getResource("Model", "Models/Ninja.mdl"));
        model.setMaterial(cache.getResource("Material", "Materials/Ninja.xml"));
        model.setDrawDistance(15000);
        model.setCastShadows(true);

        // Create animation controller
        AnimationController@ controller = entity.createComponent("AnimationController");
        controller.setAnimatedModel(model);

        // Create body
        RigidBody@ body = entity.createComponent("RigidBody");
        body.setPosition(pos);
        body.setRotation(rot);
        body.setMode(PHYS_DYNAMIC);
        body.setMass(80);
        body.setFriction(0.5);
        body.setCollisionShape(cache.getResource("CollisionShape", "Physics/Ninja.xml"));
        body.setCollisionGroup(1);
        body.setCollisionMask(3);
        body.setAngularMaxVelocity(0);
        body.addChild(model);
        model.setPosition(Vector3(0, -90, 0));
    }
}