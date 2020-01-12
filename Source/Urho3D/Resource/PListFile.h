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

#include "../Resource/Resource.h"

namespace Urho3D
{

class XMLElement;

/// PList value types.
enum PListValueType
{
    PLVT_NONE = 0,
    PLVT_INT,
    PLVT_BOOL,
    PLVT_FLOAT,
    PLVT_STRING,
    PLVT_VALUEMAP,
    PLVT_VALUEVECTOR,
};

class PListValue;

/// PList value map.
using PListValueMap = HashMap<String, PListValue>;

/// Vector of PList value.
using PListValueVector = Vector<PListValue>;

/// PList value.
class URHO3D_API PListValue
{
public:
    /// Construct.
    PListValue();
    /// Construct from int.
    explicit PListValue(int value);
    /// Construct from boolean.
    explicit PListValue(bool value);
    /// Construct from float.
    explicit PListValue(float value);
    /// Construct from string.
    explicit PListValue(const String& value);
    /// Construct from value map.
    explicit PListValue(PListValueMap& valueMap);
    /// Construct from value vector.
    explicit PListValue(PListValueVector& valueVector);
    /// Construct from another value.
    PListValue(const PListValue& value);
    /// Destruct.
    ~PListValue();

    /// Assign operator.
    PListValue& operator =(const PListValue& rhs);

    /// Return true if is valid.
    explicit operator bool() const { return type_ != PLVT_NONE; }

    /// Set int.
    void SetInt(int value);
    /// Set boolean.
    void SetBool(bool value);
    /// Set float.
    void SetFloat(float value);
    /// Set string.
    void SetString(const String& value);
    /// Set value map.
    void SetValueMap(const PListValueMap& valueMap);
    /// Set value vector.
    void SetValueVector(const PListValueVector& valueVector);

    /// Return type.
    PListValueType GetType() const { return type_; }

    /// Return int.
    int GetInt() const;
    /// Return boolean.
    bool GetBool() const;
    /// Return float.
    float GetFloat() const;
    /// Return string.
    const String& GetString() const;
    /// Return IntRect, for string type.
    IntRect GetIntRect() const;
    /// Return IntVector2, for string type.
    IntVector2 GetIntVector2() const;
    /// Return IntVector3, for string type.
    IntVector3 GetIntVector3() const;
    /// Return value map.
    const PListValueMap& GetValueMap() const;
    /// Return value vector.
    const PListValueVector& GetValueVector() const;

    /// Convert to value map (internal use only).
    PListValueMap& ConvertToValueMap();
    /// Convert to value vector (internal use only).
    PListValueVector& ConvertToValueVector();

private:
    /// Reset.
    void Reset();

    /// Type.
    PListValueType type_;
    /// Values.
    union
    {
        int int_;
        bool bool_;
        float float_;
        String* string_;
        PListValueMap* valueMap_;
        PListValueVector* valueVector_;
    };
};

/// Property list (plist).
class URHO3D_API PListFile : public Resource
{
    URHO3D_OBJECT(PListFile, Resource);

public:
    /// Construct.
    explicit PListFile(Context* context);
    /// Destruct.
    ~PListFile() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;

    /// Return root.
    const PListValueMap& GetRoot() const { return root_; }

private:
    /// Load dictionary.
    bool LoadDict(PListValueMap& dict, const XMLElement& dictElem);
    /// Load array.
    bool LoadArray(PListValueVector& array, const XMLElement& arrayElem);
    /// Load value.
    bool LoadValue(PListValue& value, const XMLElement& valueElem);

    /// Root dictionary.
    PListValueMap root_;
};

}
