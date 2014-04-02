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

class AttributeAnimation;

/// Object animation class.
class URHO3D_API ObjectAnimation : public Resource
{
    OBJECT(ObjectAnimation );

public:
    /// Construct.
    ObjectAnimation(Context* context);
    /// Destruct.
    virtual ~ObjectAnimation();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load from XML data. Return true if successful.
    bool LoadXML(const XMLElement& source);
    /// Save as XML data. Return true if successful.
    bool SaveXML(XMLElement& dest) const;

    /// Add attribute animation.
    void AddAttributeAnimation(const String& name, AttributeAnimation* attributeAnimation);
    /// Remove attribute animation.
    void RemoveAttributeAnimation(const String& name);
    /// Remove attribute animation.
    void RemoveAttributeAnimation(AttributeAnimation* attributeAnimation);

    /// Return attribute animation by name.
    AttributeAnimation* GetAttributeAnimation(const String& name) const;
    /// Return all attribute animations.
    const HashMap<String, SharedPtr<AttributeAnimation> >& GetAttributeAnimations() const { return attributeAnimations_; }

private:
    /// Name to attribute animation mapping.
    HashMap<String, SharedPtr<AttributeAnimation> > attributeAnimations_;
};

}
