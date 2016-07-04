//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../IceWeaselMods/IceWeasel.h"
#include "../IceWeaselMods/GravityProbe.h"
#include "../Scene/Node.h"


namespace Urho3D
{

// ----------------------------------------------------------------------------
GravityProbe::GravityProbe(Context* context) :
    Component(context),
    forceFactor_(1.0f)
{
}

// ----------------------------------------------------------------------------
GravityProbe::~GravityProbe()
{
}

// ----------------------------------------------------------------------------
void GravityProbe::RegisterObject(Context* context)
{
    context->RegisterFactory<GravityProbe>(ICEWEASELMODS_CATEGORY);
}

// ----------------------------------------------------------------------------
void GravityProbe::SetPosition(Vector3 position)
{
    node_->SetWorldPosition(position);
}

// ----------------------------------------------------------------------------
Vector3 GravityProbe::GetPosition() const
{
    return node_->GetWorldPosition();
}

// ----------------------------------------------------------------------------
void GravityProbe::SetDirection(Vector3 direction)
{
    node_->SetWorldDirection(direction);
}

// ----------------------------------------------------------------------------
Vector3 GravityProbe::GetDirection() const
{
    return node_->GetWorldDirection();
}

// ----------------------------------------------------------------------------
void GravityProbe::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    // Collect data for drawing an arrow
    float scale = forceFactor_ * 3.0f;
    Vector3 direction = GetDirection() * scale;
    Matrix3x4 transform = node_->GetWorldTransform();
    Vector3 startPosition = node_->GetWorldPosition();

    // Draw base of arrow
    Vector3 endPosition = startPosition + direction;
    debug->AddLine(startPosition, endPosition, Color::BLUE, depthTest);

    // Draw two lines at tip
    startPosition = transform * Vector3(-scale*.2, 0, -scale*.2) + direction;
    debug->AddLine(startPosition, endPosition, Color::BLUE, depthTest);
    startPosition = transform * Vector3(scale*.2, 0, -scale*.2) + direction;
    debug->AddLine(startPosition, endPosition, Color::BLUE, depthTest);
}

} // namespace Urho3D
