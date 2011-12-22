#include "Scripts/NinjaSnowWar/GameObject.as"

class LightFlash : GameObject
{
    LightFlash()
    {
    }

    void FixedUpdate(float timeStep)
    {
        Light@ light = node.GetComponent("Light");
        light.color = light.color * Max(1.0 - timeStep * 10.0, 0.0);

        // Call superclass to handle lifetime
        GameObject::FixedUpdate(timeStep);
    }
}