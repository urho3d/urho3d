//
// Copyright (c) 2014-2015, THUNDERBEAST GAMES LLC All rights reserved
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

#pragma once

#include "../Graphics/Texture2D.h"
#include "../Urho2D/Drawable2D.h"
#include "../Urho2D/PhysicsWorld2D.h"
#include "../Math/Vector2.h"
#include "../Scene/Component.h"

namespace Urho3D
{

class Light2DGroup;

enum LightType2D
{
    LIGHT2D_DIRECTIONAL,
    LIGHT2D_POINT,
};

struct Light2DRay
{
    float cos_;
    float sin_;

    Vector2 start_;
    Vector2 end_;
    // where along ray there was a collision if any
    float fraction_;
};

class URHO3D_API Light2D : public Component
{
    URHO3D_OBJECT(Light2D, Component);

public:
    /// Construct.
    Light2D(Context* context);
    /// Destruct.
    virtual ~Light2D();
    /// Register object factory
    static void RegisterObject(Context* context);

    void SetLightGroupID(int id) { lightgroupID_ = id; }
    int GetLightGroupID() const { return lightgroupID_; }

    const Color& GetColor() const { return color_; }
    void SetColor(const Color& color) { color_ = color; }

    void AddVertices(Vector<Vertex2D> &vertices);

    virtual void UpdateVertices() {}

    void SetNumRays(int numRays);
    int GetNumRays() const { return (int) rays_.Size(); }

    virtual void OnSetEnabled();

    LightType2D GetLightType() { return lightType_; }

    bool GetCastShadows() const { return castShadows_; }
    void SetCastShadows(bool castShadows) { castShadows_ = castShadows; }

    bool GetSoftShadows() const { return softShadows_; }
    void SetSoftShadows(bool softShadows) { softShadows_ = softShadows; }

    float GetSoftShadowLength() const { return softShadowLength_; }
    void SetSoftShadowLength(float softShadowLength) { softShadowLength_ = softShadowLength; }

    bool GetBacktrace() const { return backtrace_; }
    void SetBacktrace(bool backtrace) { backtrace_ = backtrace; }

protected:

    void OnSceneSet(Scene* scene);

    void CastRays();

    int lightgroupID_;
    WeakPtr<Light2DGroup> lightgroup_;

    Color color_;
    bool castShadows_;
    bool softShadows_;
    bool backtrace_;
    float softShadowLength_;
    PODVector<Light2DRay> rays_;
    bool raysInitialized_;
    Vector<Vertex2D> vertices_;
    LightType2D lightType_;
};


class URHO3D_API DirectionalLight2D : public Light2D
{
    URHO3D_OBJECT(DirectionalLight2D, Light2D);

public:
    /// Construct.
    DirectionalLight2D(Context* context);
    /// Destruct.
    virtual ~DirectionalLight2D();
    /// Register object factory
    static void RegisterObject(Context* context);

    virtual void UpdateVertices();

    float GetDirection() const { return direction_; }
    void SetDirection(float direction) { direction_ = direction; }


protected:

    float direction_;

};


class URHO3D_API PositionalLight2D : public Light2D
{
    URHO3D_OBJECT(PositionalLight2D, Light2D);

public:
    /// Construct.
    PositionalLight2D(Context* context);
    /// Destruct.
    virtual ~PositionalLight2D();
    /// Register object factory
    static void RegisterObject(Context* context);

    virtual void UpdateVertices();

protected:

};


class URHO3D_API PointLight2D : public PositionalLight2D
{
    URHO3D_OBJECT(PointLight2D, PositionalLight2D);

public:
    /// Construct.
    PointLight2D(Context* context);
    /// Destruct.
    virtual ~PointLight2D();

    /// Register object factory
    static void RegisterObject(Context* context);

    virtual void UpdateVertices();

    void SetRadius(float radius) { radius_ = radius; }
    float GetRadius() const { return radius_; }

protected:

    float radius_;


};

class URHO3D_API Light2DGroup : public Drawable2D
{
    URHO3D_OBJECT(Light2DGroup, Drawable2D);

public:
    /// Construct.
    Light2DGroup(Context* context);
    /// Destruct.
    virtual ~Light2DGroup();
    /// Register object factory. drawable2d must be registered first.
    static void RegisterObject(Context* context);

    PhysicsWorld2D* GetPhysicsWorld() { return physicsWorld_; }

    void AddLight2D(Light2D* light);
    void RemoveLight2D(Light2D* light);

    Vector<WeakPtr<Light2D> >& GetLights() { return lights_; }

    void SetDirty() { /*verticesDirty_ = true;*/ }

    void SetAmbientColor(const Color& color);
    const Color& GetAmbientColor() { return ambientColor_; }

    void SetLightGroupID(int id) { lightgroupID_ = id; }
    int GetLightGroupID() const { return lightgroupID_; }

    const BoundingBox& GetFrustumBox() const { return frustumBoundingBox_; }

protected:

    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate();

    void OnSceneSet(Scene* scene);

    /// Handle draw order changed.
    virtual void OnDrawOrderChanged();
    /// Update source batches.
    virtual void UpdateSourceBatches();

private:

    void HandleBeginRendering(StringHash eventType, VariantMap& eventData);
    void HandleBeginViewUpdate(StringHash eventType, VariantMap& eventData);
    void CreateLight2DMaterial();

    int lightgroupID_;
    Color ambientColor_;

    Vector<WeakPtr<Light2D> > lights_;

    SharedPtr<Material> shadow2DMaterial_;
    SharedPtr<Material> light2DMaterial_;

    WeakPtr<PhysicsWorld2D> physicsWorld_;

    /// Frustum for current frame.
    const Frustum* frustum_;
    /// Frustum bounding box for current frame.
    BoundingBox frustumBoundingBox_;

};

}
