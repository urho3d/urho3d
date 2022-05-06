// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Scene/Component.h"

namespace Urho3D
{

/// Placeholder for allowing unregistered components to be loaded & saved along with scenes.
class URHO3D_API UnknownComponent : public Component
{
public:
    /// Construct.
    explicit UnknownComponent(Context* context);

    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Return type of the stored component.
    StringHash GetType() const override { return typeHash_; }

    /// Return type name of the stored component.
    const String& GetTypeName() const override { return typeName_; }

    /// Return attribute descriptions, or null if none defined.
    const Vector<AttributeInfo>* GetAttributes() const override { return &xmlAttributeInfos_; }

    /// Load from binary data. Return true if successful.
    bool Load(Deserializer& source) override;
    /// Load from XML data. Return true if successful.
    bool LoadXML(const XMLElement& source) override;
    /// Load from JSON data. Return true if successful.
    bool LoadJSON(const JSONValue& source) override;
    /// Save as binary data. Return true if successful.
    bool Save(Serializer& dest) const override;
    /// Save as XML data. Return true if successful.
    bool SaveXML(XMLElement& dest) const override;
    /// Save as JSON data. Return true if successful.
    bool SaveJSON(JSONValue& dest) const override;

    /// Initialize the type name. Called by Node when loading.
    void SetTypeName(const String& typeName);
    /// Initialize the type hash only when type name not known. Called by Node when loading.
    void SetType(StringHash typeHash);

    /// Return the XML format attributes. Empty when loaded with binary serialization.
    const Vector<String>& GetXMLAttributes() const { return xmlAttributes_; }

    /// Return the binary attributes. Empty when loaded with XML serialization.
    const PODVector<unsigned char>& GetBinaryAttributes() const { return binaryAttributes_; }

    /// Return whether was loaded using XML data.
    bool GetUseXML() const { return useXML_; }

    /// Return static type.
    static Urho3D::StringHash GetTypeStatic()
    {
        static const StringHash typeStatic("UnknownComponent");
        return typeStatic;
    }
    /// Return static type name.
    static const Urho3D::String& GetTypeNameStatic()
    {
        static const String typeNameStatic("UnknownComponent");
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
    /// Binary attributes.
    PODVector<unsigned char> binaryAttributes_;
    /// Flag of whether was loaded using XML/JSON data.
    bool useXML_;

};

}
