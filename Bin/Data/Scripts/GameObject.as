interface GameObject
{
    void create(const Vector3&in position, const Quaternion&in rotation);
    void setControls(const Controls&in newControls);
}
