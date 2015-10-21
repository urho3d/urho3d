//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Precompiled.h"

#include "../Audio/Audio.h"
#include "../Audio/Sound.h"
#include "../Audio/SoundListener.h"
#include "../Audio/SoundSource3D.h"
#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../Scene/Node.h"

namespace Urho3D
{

static const float DEFAULT_NEARDISTANCE = 0.0f;
static const float DEFAULT_FARDISTANCE = 100.0f;
static const float DEFAULT_ROLLOFF = 2.0f;
static const float DEFAULT_ANGLE = 360.0f;
static const float MIN_ROLLOFF = 0.1f;
static const Color INNER_COLOR(1.0f, 0.5f, 1.0f);
static const Color OUTER_COLOR(1.0f, 0.0f, 1.0f);

extern const char* AUDIO_CATEGORY;

static Vector3 PointOnSphere(float radius, float theta, float phi)
{
    // Zero angles point toward positive Z axis
    phi += 90.0f;

    return Vector3(
        radius * Sin(theta) * Sin(phi),
        radius * Cos(phi),
        radius * Cos(theta) * Sin(phi)
    );
}

static void DrawDebugArc(const Vector3& worldPosition, const Quaternion& worldRotation, float angle, float distance, bool drawLines,
    const Color& color, DebugRenderer* debug, bool depthTest)
{
    if (angle <= 0.f)
        return;
    else if (angle >= 360.0f)
    {
        debug->AddSphere(Sphere(worldPosition, distance), color, depthTest);
        return;
    }

    unsigned uintColor = color.ToUInt();
    float halfAngle = 0.5f * angle;

    if (drawLines)
    {
        debug->AddLine(worldPosition, worldPosition + worldRotation * PointOnSphere(distance, halfAngle, halfAngle),
            uintColor);
        debug->AddLine(worldPosition, worldPosition + worldRotation * PointOnSphere(distance, -halfAngle, halfAngle),
            uintColor);
        debug->AddLine(worldPosition, worldPosition + worldRotation * PointOnSphere(distance, halfAngle, -halfAngle),
            uintColor);
        debug->AddLine(worldPosition, worldPosition + worldRotation * PointOnSphere(distance, -halfAngle, -halfAngle),
            uintColor);
    }

    const float step = 0.5f;

    for (float x = -1.0f; x < 1.0f; x += step)
    {
        debug->AddLine(worldPosition + worldRotation * PointOnSphere(distance, x * halfAngle, halfAngle),
            worldPosition + worldRotation * PointOnSphere(distance, (x + step) * halfAngle, halfAngle),
            uintColor);
        debug->AddLine(worldPosition + worldRotation * PointOnSphere(distance, x * halfAngle, -halfAngle),
            worldPosition + worldRotation * PointOnSphere(distance, (x + step) * halfAngle, -halfAngle),
            uintColor);
        debug->AddLine(worldPosition + worldRotation * PointOnSphere(distance, halfAngle, x * halfAngle),
            worldPosition + worldRotation * PointOnSphere(distance, halfAngle, (x + step) * halfAngle),
            uintColor);
        debug->AddLine(worldPosition + worldRotation * PointOnSphere(distance, -halfAngle, x * halfAngle),
            worldPosition + worldRotation * PointOnSphere(distance, -halfAngle, (x + step) * halfAngle),
            uintColor);
    }
}

SoundSource3D::SoundSource3D(Context* context) :
    SoundSource(context),
    nearDistance_(DEFAULT_NEARDISTANCE),
    farDistance_(DEFAULT_FARDISTANCE),
    innerAngle_(DEFAULT_ANGLE),
    outerAngle_(DEFAULT_ANGLE),
    rolloffFactor_(DEFAULT_ROLLOFF)
{
    // Start from zero volume until attenuation properly calculated
    attenuation_ = 0.0f;
}

void SoundSource3D::RegisterObject(Context* context)
{
    context->RegisterFactory<SoundSource3D>(AUDIO_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(SoundSource);
    // Remove Attenuation and Panning as attribute as they are constantly being updated
    URHO3D_REMOVE_ATTRIBUTE("Attenuation");
    URHO3D_REMOVE_ATTRIBUTE("Panning");
    URHO3D_ATTRIBUTE("Near Distance", float, nearDistance_, DEFAULT_NEARDISTANCE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Far Distance", float, farDistance_, DEFAULT_FARDISTANCE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Inner Angle", float, innerAngle_, DEFAULT_ANGLE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Outer Angle", float, outerAngle_, DEFAULT_ANGLE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Rolloff Factor", float, rolloffFactor_, DEFAULT_ROLLOFF, AM_DEFAULT);
}

void SoundSource3D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (!debug || !node_ || !IsEnabledEffective())
        return;

    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    Vector3 worldPosition = worldTransform.Translation();
    Quaternion worldRotation = worldTransform.Rotation();

    // Draw cones for directional sounds, or spheres for non-directional
    if (innerAngle_ < DEFAULT_ANGLE && outerAngle_ > 0.0f)
    {
        DrawDebugArc(worldPosition, worldRotation, innerAngle_, nearDistance_, false, INNER_COLOR, debug, depthTest);
        DrawDebugArc(worldPosition, worldRotation, outerAngle_, nearDistance_, false, OUTER_COLOR, debug, depthTest);
        DrawDebugArc(worldPosition, worldRotation, innerAngle_, farDistance_, true, INNER_COLOR, debug, depthTest);
        DrawDebugArc(worldPosition, worldRotation, outerAngle_, farDistance_, true, OUTER_COLOR, debug, depthTest);
    }
    else
    {
        debug->AddSphere(Sphere(worldPosition, nearDistance_), INNER_COLOR, depthTest);
        debug->AddSphere(Sphere(worldPosition, farDistance_), OUTER_COLOR, depthTest);
    }
}

void SoundSource3D::Update(float timeStep)
{
    CalculateAttenuation();
    SoundSource::Update(timeStep);
}

void SoundSource3D::SetDistanceAttenuation(float nearDistance, float farDistance, float rolloffFactor)
{
    nearDistance_ = Max(nearDistance, 0.0f);
    farDistance_ = Max(farDistance, 0.0f);
    rolloffFactor_ = Max(rolloffFactor, MIN_ROLLOFF);
    MarkNetworkUpdate();
}

void SoundSource3D::SetAngleAttenuation(float innerAngle, float outerAngle)
{
    innerAngle_ = Clamp(innerAngle, 0.0f, DEFAULT_ANGLE);
    outerAngle_ = Clamp(outerAngle, 0.0f, DEFAULT_ANGLE);
    MarkNetworkUpdate();
}

void SoundSource3D::SetFarDistance(float distance)
{
    farDistance_ = Max(distance, 0.0f);
    MarkNetworkUpdate();
}

void SoundSource3D::SetNearDistance(float distance)
{
    nearDistance_ = Max(distance, 0.0f);
    MarkNetworkUpdate();
}

void SoundSource3D::SetInnerAngle(float angle)
{
    innerAngle_ = Clamp(angle, 0.0f, DEFAULT_ANGLE);
    MarkNetworkUpdate();
}

void SoundSource3D::SetOuterAngle(float angle)
{
    outerAngle_ = Clamp(angle, 0.0f, DEFAULT_ANGLE);
    MarkNetworkUpdate();
}

void SoundSource3D::SetRolloffFactor(float factor)
{
    rolloffFactor_ = Max(factor, MIN_ROLLOFF);
    MarkNetworkUpdate();
}

void SoundSource3D::CalculateAttenuation()
{
    if (!audio_)
        return;

    float interval = farDistance_ - nearDistance_;
    if (node_)
    {
        SoundListener* listener = audio_->GetListener();

        // Listener must either be sceneless or in the same scene, else attenuate sound to silence
        if (listener && listener->IsEnabledEffective() && (!listener->GetScene() || listener->GetScene() == GetScene()))
        {
            Node* listenerNode = listener->GetNode();
            Vector3 relativePos
                (listenerNode->GetWorldRotation().Inverse() * (node_->GetWorldPosition() - listenerNode->GetWorldPosition()));
            float distance = relativePos.Length();

            // Distance attenuation
            if (interval > 0.0f)
                attenuation_ = powf(1.0f - Clamp(distance - nearDistance_, 0.0f, interval) / interval, rolloffFactor_);
            else
                attenuation_ = distance <= nearDistance_ ? 1.0f : 0.0f;

            // Panning
            panning_ = relativePos.Normalized().x_;

            // Angle attenuation
            if (innerAngle_ < DEFAULT_ANGLE && outerAngle_ > 0.0f)
            {
                Vector3 listenerRelativePos
                    (node_->GetWorldRotation().Inverse() * (listenerNode->GetWorldPosition() - node_->GetWorldPosition()));
                float listenerDot = Vector3::FORWARD.DotProduct(listenerRelativePos.Normalized());
                float listenerAngle = acosf(listenerDot) * M_RADTODEG * 2.0f;
                float angleInterval = Max(outerAngle_ - innerAngle_, 0.0f);
                float angleAttenuation = 1.0f;

                if (angleInterval > 0.0f)
                {
                    if (listenerAngle > innerAngle_)
                    {
                        angleAttenuation = powf(1.0f - Clamp(listenerAngle - innerAngle_, 0.0f, angleInterval) / angleInterval,
                            rolloffFactor_);
                    }
                }
                else
                    angleAttenuation = listenerAngle <= innerAngle_ ? 1.0f : 0.0f;

                attenuation_ *= angleAttenuation;
            }
        }
        else
            attenuation_ = 0.0f;
    }
    else
        attenuation_ = 0.0f;
}

}
