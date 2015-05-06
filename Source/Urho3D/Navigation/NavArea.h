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

#pragma once

#include "../Scene/Component.h"
#include "../Math/BoundingBox.h"

namespace Urho3D
{
    class URHO3D_API NavArea : public Component
    {
        OBJECT(NavArea);

    public:
        /// Construct
        NavArea(Context*);
        /// Destruct
        virtual ~NavArea();
        /// Register object factory and attributes
        static void RegisterObject(Context*);

        /// Render debug geometry for the bounds
        virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

        /// Gets the area id for this volume
        unsigned GetAreaType() const { return areaType_; }
        /// Sets the area id for this volume
        void SetAreaType(unsigned);

        /// Gets the bounding box of this navigation area, in local space
        BoundingBox GetBounds() const { return boundingBox_; }
        /// Sets the bounding box of this area, in local space
        void SetBounds(const BoundingBox& bnds) { boundingBox_ = bnds; }

        /// Gets the bounds of this navigation area in world space
        BoundingBox GetTransformedBounds() const;

    private:
        /// Bounds of area to mark
        BoundingBox boundingBox_;
        /// Flags to assign to the marked area of the navigation map
        unsigned flags_;
        /// Area identifier to assign to the marked area
        unsigned areaType_;
    };
}