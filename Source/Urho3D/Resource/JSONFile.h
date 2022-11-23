// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Resource/Resource.h"
#include "../Resource/JSONValue.h"

namespace Urho3D
{

/// JSON document resource.
class URHO3D_API JSONFile : public Resource
{
    URHO3D_OBJECT(JSONFile, Resource);

public:
    /// Construct.
    explicit JSONFile(Context* context);
    /// Destruct.
    ~JSONFile() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;
    /// Save resource with default indentation (one tab). Return true if successful.
    bool Save(Serializer& dest) const override;
    /// Save resource with user-defined indentation, only the first character (if any) of the string is used and the length of the string defines the character count. Return true if successful.
    bool Save(Serializer& dest, const String& indendation) const;

    /// Deserialize from a string. Return true if successful.
    bool FromString(const String& source);
    /// Save to a string.
    String ToString(const String& indendation = "\t") const;

    /// Return root value.
    /// @property
    JSONValue& GetRoot() { return root_; }
    /// Return root value.
    const JSONValue& GetRoot() const { return root_; }

private:
    /// JSON root value.
    JSONValue root_;
};

}
