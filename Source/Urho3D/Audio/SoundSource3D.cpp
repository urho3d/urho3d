// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    URHO3D_ATTRIBUTE("Near Distance", nearDistance_, DEFAULT_NEARDISTANCE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Far Distance", farDistance_, DEFAULT_FARDISTANCE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Inner Angle", innerAngle_, DEFAULT_ANGLE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Outer Angle", outerAngle_, DEFAULT_ANGLE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Rolloff Factor", rolloffFactor_, DEFAULT_ROLLOFF, AM_DEFAULT);
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
        const Quaternion rotation = worldRotation * Quaternion(Vector3::UP, Vector3::FORWARD);
        debug->AddSphereSector(Sphere(worldPosition, nearDistance_), rotation, innerAngle_, false, INNER_COLOR, depthTest);
        debug->AddSphereSector(Sphere(worldPosition, nearDistance_), rotation, outerAngle_, false, OUTER_COLOR, depthTest);
        debug->AddSphereSector(Sphere(worldPosition, farDistance_), rotation, innerAngle_, true, INNER_COLOR, depthTest);
        debug->AddSphereSector(Sphere(worldPosition, farDistance_), rotation, outerAngle_, true, OUTER_COLOR, depthTest);
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
