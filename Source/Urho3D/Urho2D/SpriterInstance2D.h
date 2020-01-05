//
// Copyright (c) 2008-2020 the Urho3D project.
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

/// \file

#pragma once

#include "../Urho2D/SpriterData2D.h"

namespace Urho3D
{

class Component;

namespace Spriter
{

/// Loop Mode.
enum LoopMode
{
    Default = 0,
    ForceLooped,
    ForceClamped,
};

/// Spriter instance.
class SpriterInstance
{
public:
    /// Constructor with spriter data.
    SpriterInstance(Component* owner, SpriterData* spriteData);
    /// Destructor.
    ~SpriterInstance();

    /// Set current entity.
    bool SetEntity(int index);
    /// Set current entity.
    bool SetEntity(const String& entityName);
    /// Set current animation.
    bool SetAnimation(int index, LoopMode loopMode = Default);
    /// Set current animation.
    bool SetAnimation(const String& animationName, LoopMode loopMode = Default);
    /// Set root spatial info.
    void setSpatialInfo(const SpatialInfo& spatialInfo);
    /// Set root spatial info.
    void setSpatialInfo(float x, float y, float angle, float scaleX, float scaleY);
    /// Update animation.
    void Update(float deltaTime);

    /// Return current entity.
    Entity* GetEntity() const { return entity_; }
    /// Return current animation.
    Animation* GetAnimation() const { return animation_; }
    /// Return root spatial info.
    const SpatialInfo& GetSpatialInfo() const { return spatialInfo_; }
    /// Return animation result timeline keys.
    const PODVector<SpatialTimelineKey*>& GetTimelineKeys() const { return timelineKeys_; }

private:
    /// Handle set entity.
    void OnSetEntity(Entity* entity);
    /// Handle set animation.
    void OnSetAnimation(Animation* animation, LoopMode loopMode = Default);
    /// Update mainline key.
    void UpdateMainlineKey();
    /// Update timeline keys.
    void UpdateTimelineKeys();
    /// Get timeline key by ref.
    TimelineKey* GetTimelineKey(Ref* ref) const;
    /// Clear mainline key and timeline keys.
    void Clear();

    /// Parent component.
    Component* owner_{};
    /// Spriter data.
    SpriterData* spriterData_{};
    /// Current entity.
    Entity* entity_{};
    /// Current animation.
    Animation* animation_{};
    /// Looping.
    bool looping_{};
    /// Root spatial info.
    SpatialInfo spatialInfo_;
    /// Current time.
    float currentTime_{};
    /// Current mainline key.
    MainlineKey* mainlineKey_{};
    /// Current timeline keys.
    PODVector<SpatialTimelineKey*> timelineKeys_;
};

}

}
