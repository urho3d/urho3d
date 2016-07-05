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

#pragma once

#include "../Scene/Component.h"


namespace Urho3D
{

class Context;


class URHO3D_API GravityVector : public Component
{
    URHO3D_OBJECT(GravityVector, Component)

public:

    /*!
     * @brief Constructs a new gravity probe.
     */
    GravityVector(Context* context);

    /*!
     * @brief Destructs the gravity probe.
     */
    virtual ~GravityVector();

    /*!
     * @brief Registers this class as an object factory.
     */
    static void RegisterObject(Context* context);

    /*!
     * @brief Sets the world position of the gravity probe.
     * @param[in] position World location as Vector3.
     */
    void SetPosition(Vector3 position);

    /*!
     * @brief Gets the world position of the gravity probe.
     */
    Vector3 GetPosition() const;

    /*!
     * @brief Sets in which world direction gravity should be applied to
     * objects.
     * @param[in] direction A directional Vector3 in world space. It will be
     * normalized internally..
     */
    void SetDirection(Vector3 direction);

    /*!
     * @brief Returns the normalized direction of the node.
     * @return A normalized Vector3.
     */
    Vector3 GetDirection() const;

    /*!
     * @brief The global gravity is multiplied by this factor. The default
     * value is 1.0.
     * @param[in] factor Multiplication factor to apply to this probe.
     */
    void SetForceFactor(float factor)
            { forceFactor_ = factor; }

    /*!
     * @brief Gets the probe's force factor. This is multiplied with the global
     * gravity setting to calculate the final gravitational force. Defaults to
     * 1.0.
     */
    float GetForceFactor() const
            { return forceFactor_; }

protected:
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

private:
    float forceFactor_;
};

} // namespace Urho3D
