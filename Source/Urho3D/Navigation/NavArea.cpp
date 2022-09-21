// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../IO/Log.h"
#include "../Navigation/NavArea.h"
#include "../Scene/Node.h"

namespace Urho3D
{

static const unsigned MAX_NAV_AREA_ID = 255;
static const Vector3 DEFAULT_BOUNDING_BOX_MIN(-10.0f, -10.0f, -10.0f);
static const Vector3 DEFAULT_BOUNDING_BOX_MAX(10.0f, 10.0f, 10.0f);
static const unsigned DEFAULT_AREA_ID = 0;

extern const char* NAVIGATION_CATEGORY;

NavArea::NavArea(Context* context) :
    Component(context),
    areaID_(DEFAULT_AREA_ID),
    boundingBox_(DEFAULT_BOUNDING_BOX_MIN, DEFAULT_BOUNDING_BOX_MAX)
{
}

NavArea::~NavArea() = default;

void NavArea::RegisterObject(Context* context)
{
    context->RegisterFactory<NavArea>(NAVIGATION_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(Component);
    URHO3D_ATTRIBUTE("Bounding Box Min", boundingBox_.min_, DEFAULT_BOUNDING_BOX_MIN, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Bounding Box Max", boundingBox_.max_, DEFAULT_BOUNDING_BOX_MAX, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Area ID", GetAreaID, SetAreaID, unsigned, DEFAULT_AREA_ID, AM_DEFAULT);
}

void NavArea::SetAreaID(unsigned newID)
{
    if (newID > MAX_NAV_AREA_ID)
        URHO3D_LOGERRORF("NavArea Area ID %u exceeds maximum value of %u", newID, MAX_NAV_AREA_ID);
    areaID_ = (unsigned char)newID;
    MarkNetworkUpdate();
}

BoundingBox NavArea::GetWorldBoundingBox() const
{
    Matrix3x4 mat;
    mat.SetTranslation(node_->GetWorldPosition());
    return boundingBox_.Transformed(mat);
}

void NavArea::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && IsEnabledEffective())
    {
        Matrix3x4 mat;
        mat.SetTranslation(node_->GetWorldPosition());
        debug->AddBoundingBox(boundingBox_, mat, Color::GREEN, depthTest);
        debug->AddBoundingBox(boundingBox_, mat, Color(0.0f, 1.0f, 0.0f, 0.15f), true, true);
    }
}

}
