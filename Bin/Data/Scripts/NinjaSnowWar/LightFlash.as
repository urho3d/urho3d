#include "Scripts/NinjaSnowWar/GameObject.as"

class LightFlash : GameObject
{
    LightFlash()
    {
    }

    void Start()
    {
        // If components already exist, we are probably (re)executing this after deserialization.
        // Do not create duplicate components in that case
        if (node.HasComponent("Light"))
            return;

        Light@ light = node.CreateComponent("Light");
        light.lightType = LIGHT_POINT;
        light.range = 500.0;
        light.color = Color(2.0, 2.0, 2.0);
        light.castShadows = true;
        light.shadowResolution = 0.25;
        light.rampTexture = cache.GetResource("Texture2D", "Textures/RampWide.png");
        duration = 0.1;
    }

    void FixedUpdate(float timeStep)
    {
        Light@ light = node.GetComponent("Light");
        light.color = light.color * Max(1.0 - timeStep * 10.0, 0.0);

        // Call superclass to handle lifetime
        GameObject::FixedUpdate(timeStep);
    }
}