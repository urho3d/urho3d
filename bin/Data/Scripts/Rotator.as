// Rotator script object class. Script objects to be added to a scene node must implement the empty ScriptObject interface
class Rotator : ScriptObject
{
    Vector3 rotationSpeed;

    void SetRotationSpeed(const Vector3&in speed)
    {
        rotationSpeed = speed;
    }

    // Update is called during the variable timestep scene update
    void Update(float timeStep)
    {
        node.Rotate(Quaternion(rotationSpeed.x * timeStep, rotationSpeed.y * timeStep, rotationSpeed.z * timeStep));
    }
}
