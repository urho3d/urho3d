//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"
#include "Context.h"
#include "XMLElement.h"
#include "Zone.h"

static const float DEFAULT_FOGSTART = 250.0f;
static const float DEFAULT_FOGEND = 1000.0f;
static const Color DEFAULT_FOG_COLOR(0.0f, 0.0f, 0.0f);
static const Color DEFAULT_AMBIENT_COLOR(0.1f, 0.1f, 0.1f);

OBJECTTYPESTATIC(Zone);

Zone::Zone(Context* context) :
    Drawable(context),
    ambientColor_(DEFAULT_AMBIENT_COLOR),
    fogColor_(DEFAULT_FOG_COLOR),
    fogStart_(DEFAULT_FOGSTART),
    fogEnd_(DEFAULT_FOGEND),
    priority_(0),
    override_(false)
{
    drawableFlags_ =  DRAWABLE_ZONE;
}

Zone::~Zone()
{
}

void Zone::RegisterObject(Context* context)
{
    context->RegisterFactory<Zone>();
    
    ATTRIBUTE(Zone, VAR_VECTOR3, "Bounding Box Min", boundingBox_.min_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(Zone, VAR_VECTOR3, "Bounding Box Max", boundingBox_.max_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(Zone, VAR_COLOR, "Ambient Color", ambientColor_, DEFAULT_AMBIENT_COLOR, AM_DEFAULT);
    ATTRIBUTE(Zone, VAR_COLOR, "Fog Color", fogColor_, DEFAULT_FOG_COLOR, AM_DEFAULT);
    ATTRIBUTE(Zone, VAR_FLOAT, "Fog Start", fogStart_, DEFAULT_FOGSTART, AM_DEFAULT);
    ATTRIBUTE(Zone, VAR_FLOAT, "Fog End", fogEnd_, DEFAULT_FOGEND, AM_DEFAULT);
    ATTRIBUTE(Zone, VAR_BOOL, "Is Visible", visible_, true, AM_DEFAULT);
    ATTRIBUTE(Zone, VAR_BOOL, "Override Mode", override_, 0, AM_DEFAULT);
    ATTRIBUTE(Zone, VAR_INT, "Priority", priority_, 0, AM_DEFAULT);
    ATTRIBUTE(Zone, VAR_INT, "View Mask", viewMask_, DEFAULT_VIEWMASK, AM_DEFAULT);
    ATTRIBUTE(Zone, VAR_INT, "Light Mask", lightMask_, DEFAULT_LIGHTMASK, AM_DEFAULT);
}

void Zone::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Serializable::OnSetAttribute(attr, src);
    
    // If bounding box changes, dirty the drawable as applicable
    switch (attr.offset_)
    {
    case offsetof(Zone, boundingBox_.min_):
    case offsetof(Zone, boundingBox_.max_):
        OnMarkedDirty(node_);
        break;
    }
}

void Zone::SetBoundingBox(const BoundingBox& box)
{
    boundingBox_ = box;
    OnMarkedDirty(node_);
}

void Zone::SetAmbientColor(const Color& color)
{
    ambientColor_ = Color(color, 1.0f);
}

void Zone::SetFogColor(const Color& color)
{
    fogColor_ = Color(color, 1.0f);
}

void Zone::SetFogStart(float start)
{
    if (start < 0.0f)
        start = 0.0f;
    
    fogStart_ = start;
}

void Zone::SetFogEnd(float end)
{
    if (end < 0.0f)
        end = 0.0f;
    
    fogEnd_ = end;
}

void Zone::SetPriority(int priority)
{
    priority_ = priority;
}

bool Zone::IsInside(const Vector3& point)
{
    // Use an oriented bounding box test
    Matrix3x4 inverse(GetWorldTransform().Inverse());
    Vector3 localPoint(inverse * point);
    return boundingBox_.IsInside(localPoint) != OUTSIDE;
}

void Zone::OnWorldBoundingBoxUpdate()
{
    worldBoundingBox_ = boundingBox_.Transformed(GetWorldTransform());
}
