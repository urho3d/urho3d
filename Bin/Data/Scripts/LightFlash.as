#include "Scripts/GameObject.as"

class LightFlash : GameObject
{
    LightFlash()
    {
    }

    void Create(const Vector3&in position, const Quaternion&in rotation)
    {
        node.position = position;
        node.rotation = rotation;

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

        if (duration >= 0)
        {
            duration -= timeStep;
            if (duration <= 0)
                node.Remove();
        }
    }
}