#include "Scripts/NinjaSnowWar/GameObject.as"

class LightFlash : GameObject
{
    LightFlash()
    {
        duration = 2.0;
    }

    void FixedUpdate(float timeStep)
    {
        Light@ light = node.GetComponent("Light");
        light.brightness = light.brightness * Max(1.0 - timeStep * 10.0, 0.0);

        // Call superclass to handle lifetime
        GameObject::FixedUpdate(timeStep);
    }
}