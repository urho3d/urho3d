#pragma once


namespace Urho3D
{

class GravityPoint
{
public:
    GravityPoint() {}
    GravityPoint(const Vector3& vertex, const Vector3& direction, float forceFactor) :
        position_(vertex),
        direction_(direction),
        forceFactor_(forceFactor)
    {}

    Vector3 position_;
    Vector3 direction_;
    float forceFactor_;
};

} // namespace Urho3D
