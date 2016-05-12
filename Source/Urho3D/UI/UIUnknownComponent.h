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

#include "../UI/UIComponent.h"

namespace Urho3D
{

/// Placeholder for allowing unregistered ui components to be loaded & saved along with elements.
class URHO3D_API UIUnknownComponent : public UIComponent
{
public:
    /// Construct.
    UIUnknownComponent(Context* context);

    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Return type of the stored component.
    virtual StringHash GetType() const { return typeHash_; }

    /// Return type name of the stored component.
    virtual const String& GetTypeName() const { return typeName_; }

    /// Return attribute descriptions, or null if none defined.
    virtual const Vector<AttributeInfo>* GetAttributes() const { return &xmlAttributeInfos_; }

    /// Load from XML data. Return true if successful.
    virtual bool LoadXML(const XMLElement& source, bool setInstanceDefault = false);
    /// Save as XML data. Return true if successful.
    virtual bool SaveXML(XMLElement& dest) const;

    /// Initialize the type name. Called by element when loading.
    void SetTypeName(const String& typeName);
    /// Initialize the type hash only when type name not known. Called by Node when loading.
    void SetType(StringHash typeHash);

    /// Return the XML format attributes.
    const Vector<String>& GetXMLAttributes() const { return xmlAttributes_; }

    /// Return static type.
    static Urho3D::StringHash GetTypeStatic()
    {
        static const StringHash typeStatic("UIUnknownComponent");
        return typeStatic;
    }

    /// Return static type name.
    static const Urho3D::String& GetTypeNameStatic()
    {
        static const String typeNameStatic("UIUnknownComponent");
        return typeNameStatic;
    }

private:
    /// Type of stored component.
    StringHash typeHash_;
    /// Type name of the stored component.
    String typeName_;
    /// XML format attribute infos.
    Vector<AttributeInfo> xmlAttributeInfos_;
    /// XML format attribute data (as strings).
    Vector<String> xmlAttributes_;
};

}
