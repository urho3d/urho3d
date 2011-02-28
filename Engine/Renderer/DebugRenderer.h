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

#ifndef RENDERER_DEBUGRENDERER_H
#define RENDERER_DEBUGRENDERER_H

#include "Color.h"
#include "EventListener.h"
#include "Matrix4.h"
#include "SceneExtension.h"
#include "SharedPtr.h"

#include <vector>

class BoundingBox;
class Camera;
class Frustum;
class GeometryNode;
class Light;
class Matrix4x3;
class Pipeline;
class Skeleton;

//! Debug rendering line
struct DebugLine
{
    //! Construct as undefined
    DebugLine()
    {
    }
    
    //! Construct with start and end positions and color
    DebugLine(const Vector3& start, const Vector3& end, unsigned color) :
        mStart(start),
        mEnd(end),
        mColor(color)
    {
    }
    
    //! Start position
    Vector3 mStart;
    //! End position
    Vector3 mEnd;
    //! Color
    unsigned mColor;
};

//! Debug geometry renderer
class DebugRenderer : public SceneExtension, public EventListener
{
    DEFINE_TYPE(DebugRenderer);
    
public:
    //! Construct
    DebugRenderer();
    
    //! Add a line
    void addLine(const Vector3& start, const Vector3& end, const Color& color, bool depthTest = true);
    //! Add a bounding box
    void addBoundingBox(const BoundingBox& box, const Color& color, bool depthTest = true);
    //! Add a bounding box with transform
    void addBoundingBox(const BoundingBox& box, const Matrix4x3& transform, const Color& color, bool depthTest = true);
    //! Add a frustum
    void addFrustum(const Frustum& frustum, const Color& color, bool depthTest = true);
    //! Add a skeleton
    void addSkeleton(const Skeleton& skeleton, const Color& color, bool depthTest = true);
    //! Render all debug lines from a specific camera. The viewport and rendertarget should be set before
    void render(Pipeline* pipeline, Camera* camera);
    
private:
    //! Handle end of frame. Clear debug geometry
    void handleEndFrame(StringHash eventType, VariantMap& eventData);
    
    //! Lines rendered with depth test
    std::vector<DebugLine> mLines;
    //! Lines rendered without depth test
    std::vector<DebugLine> mNoDepthLines;
};

#endif // RENDERR_DEBUGGEOMETRY_H
