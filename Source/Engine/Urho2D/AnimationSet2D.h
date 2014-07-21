//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "Resource.h"

namespace Urho3D
{

class Animation2D;
class Sprite2D;
class XMLElement;

/// Spriter animation set, it includes one or more animations, for more information please refer to http://www.brashmonkey.com/spriter.htm.
class URHO3D_API AnimationSet2D : public Resource
{
    OBJECT(AnimationSet2D);

public:
    /// Construct.
    AnimationSet2D(Context* context);
    /// Destruct.
    virtual ~AnimationSet2D();
    /// Register object factory. 
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);

    /// Get number of animations.
    unsigned GetNumAnimations() const;
    /// Return animation by index.
    Animation2D* GetAnimation(unsigned index) const;
    /// Return animation by name.
    Animation2D* GetAnimation(const String& name) const;

private:
    /// Load folders.
    bool LoadFolders(const XMLElement& rootElem);
    /// Return sprite by folder id and file id.
    Sprite2D* GetSprite(unsigned folderId, unsigned fileId) const;
    /// Load animation.
    bool LoadAnimation(const XMLElement& animationElem);

    /// Sprites.
    HashMap<unsigned, SharedPtr<Sprite2D> > sprites_;
    /// Animations.
    Vector<SharedPtr<Animation2D> > animations_;
};

}

