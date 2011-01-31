#include "Scripts/GameObject.as"

class LightFlash : GameObject
{
    LightFlash()
    {
    }
    
    void create(const Vector3&in position, const Quaternion&in rotation)
    {
        Light@ light = entity.createComponent("Light");
        light.setLightType(LIGHT_POINT);
        light.setRange(500.0);
        light.setColor(Color(2.0, 2.0, 2.0));
        light.setCastShadows(true);
        light.setShadowResolution(0.25);
        light.setRampTexture(cache.getResource("Texture2D", "Textures/RampWide.png"));
        light.setPosition(position);
        duration = 0.1;
    }

    void updateFixed(float timeStep)
    {
        Light@ light = entity.getComponent("Light");
        light.setColor(light.getColor() * max(1.0 - timeStep * 10.0, 0.0));

        if (duration > 0)
        {
            duration -= timeStep;
            if (duration <= 0)
                scene.removeEntity(entity);
        }
    }
}