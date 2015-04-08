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

#include "../Resource/Resource.h"

namespace Urho3D
{

class Animation2D;
class Sprite2D;
class XMLElement;
class XMLFile;

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
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    virtual bool EndLoad();

    /// Get number of animations.
    unsigned GetNumAnimations() const;
    /// Return animation by index.
    Animation2D* GetAnimation(unsigned index) const;
    /// Return animation by name.
    Animation2D* GetAnimation(const String& name) const;

private:
    /// Return sprite by hash.
    Sprite2D* GetSprite(const StringHash& hash) const;
    /// Begin load scml.
    bool BeginLoadSpriter(Deserializer &source);
    /// Finish load scml.
    bool EndLoadSpriter();
    /// Load spriter folders.
    bool LoadSpriterFolders(const XMLElement& rootElem);
    /// Load spriter animation.
    bool LoadSpriterAnimation(const XMLElement& animationElem);

    /// Sprites.
    HashMap<StringHash, SharedPtr<Sprite2D> > sprites_;
    /// Animations.
    Vector<SharedPtr<Animation2D> > animations_;
    /// Spriter file.
    SharedPtr<XMLFile> spriterFile_;
};

}

