// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../IO/Deserializer.h"
#include "../IO/Log.h"
#include "../Resource/PListFile.h"
#include "../Resource/XMLFile.h"

#include <cstdio>

#include "../DebugNew.h"

namespace Urho3D
{

static PListValue EMPTY_VALUE;
static PListValueMap EMPTY_VALUEMAP;
static PListValueVector EMPTY_VALUEVECTOR;

PListValue::PListValue() :                                  // NOLINT(hicpp-member-init)
    type_(PLVT_NONE)
{
}

PListValue::PListValue(int value) :                         // NOLINT(hicpp-member-init)
    type_(PLVT_NONE)
{
    SetInt(value);
}

PListValue::PListValue(bool value) :                        // NOLINT(hicpp-member-init)
    type_(PLVT_NONE)
{
    SetBool(value);
}

PListValue::PListValue(float value) :                       // NOLINT(hicpp-member-init)
    type_(PLVT_NONE)
{
    SetFloat(value);
}

PListValue::PListValue(const String& value) :               // NOLINT(hicpp-member-init)
    type_(PLVT_NONE)
{
    SetString(value);
}

PListValue::PListValue(PListValueMap& valueMap) :           // NOLINT(hicpp-member-init)
    type_(PLVT_NONE)
{
    SetValueMap(valueMap);
}

PListValue::PListValue(PListValueVector& valueVector) :     // NOLINT(hicpp-member-init)
    type_(PLVT_NONE)
{
    SetValueVector(valueVector);
}

PListValue::PListValue(const PListValue& value) :           // NOLINT(hicpp-member-init)
    type_(PLVT_NONE)
{
    *this = value;
}

PListValue::~PListValue()
{
    Reset();
}

PListValue& PListValue::operator =(const PListValue& rhs)
{
    switch (rhs.type_)
    {
    case PLVT_NONE:
        Reset();
        break;
    case PLVT_INT:
        SetInt(rhs.int_);
        break;
    case PLVT_BOOL:
        SetBool(rhs.bool_);
        break;
    case PLVT_FLOAT:
        SetFloat(rhs.float_);
        break;
    case PLVT_STRING:
        SetString(*rhs.string_);
        break;
    case PLVT_VALUEMAP:
        SetValueMap(*rhs.valueMap_);
        break;
    case PLVT_VALUEVECTOR:
        SetValueVector(*rhs.valueVector_);
        break;
    }

    return *this;
}

void PListValue::SetInt(int value)
{
    if (type_ != PLVT_INT)
    {
        Reset();
        type_ = PLVT_INT;
    }

    int_ = value;
}

void PListValue::SetBool(bool value)
{
    if (type_ != PLVT_BOOL)
    {
        Reset();
        type_ = PLVT_BOOL;
    }

    bool_ = value;
}

void PListValue::SetFloat(float value)
{
    if (type_ != PLVT_FLOAT)
    {
        Reset();
        type_ = PLVT_FLOAT;
    }
    float_ = value;
}

void PListValue::SetString(const String& value)
{
    if (type_ != PLVT_STRING)
    {
        Reset();
        type_ = PLVT_STRING;
        string_ = new String();
    }

    *string_ = value;
}

void PListValue::SetValueMap(const PListValueMap& valueMap)
{
    if (type_ != PLVT_VALUEMAP)
    {
        Reset();
        type_ = PLVT_VALUEMAP;
        valueMap_ = new PListValueMap();
    }

    *valueMap_ = valueMap;
}

void PListValue::SetValueVector(const PListValueVector& valueVector)
{
    if (type_ != PLVT_VALUEVECTOR)
    {
        Reset();
        type_ = PLVT_VALUEVECTOR;
        valueVector_ = new PListValueVector();
    }

    *valueVector_ = valueVector;
}

int PListValue::GetInt() const
{
    return type_ == PLVT_INT ? int_ : 0;
}

bool PListValue::GetBool() const
{
    return type_ == PLVT_BOOL ? bool_ : false;
}

float PListValue::GetFloat() const
{
    return type_ == PLVT_FLOAT ? float_ : 0.0f;
}

const String& PListValue::GetString() const
{
    return type_ == PLVT_STRING ? *string_ : String::EMPTY;
}

IntRect PListValue::GetIntRect() const
{
    if (type_ != PLVT_STRING)
        return IntRect::ZERO;

    int x, y, w, h;
    sscanf(string_->CString(), "{{%d,%d},{%d,%d}}", &x, &y, &w, &h);    // NOLINT(cert-err34-c)
    return {x, y, x + w, y + h};
}

IntVector2 PListValue::GetIntVector2() const
{
    if (type_ != PLVT_STRING)
        return IntVector2::ZERO;

    int x, y;
    sscanf(string_->CString(), "{%d,%d}", &x, &y);                      // NOLINT(cert-err34-c)
    return IntVector2(x, y);
}

IntVector3 PListValue::GetIntVector3() const
{
    if (type_ != PLVT_STRING)
        return IntVector3::ZERO;

    int x, y, z;
    sscanf(string_->CString(), "{%d,%d,%d}", &x, &y, &z);               // NOLINT(cert-err34-c)
    return IntVector3(x, y, z);
}

const PListValueMap& PListValue::GetValueMap() const
{
    return type_ == PLVT_VALUEMAP ? *valueMap_ : EMPTY_VALUEMAP;
}

const PListValueVector& PListValue::GetValueVector() const
{
    return type_ == PLVT_VALUEVECTOR ? *valueVector_ : EMPTY_VALUEVECTOR;
}

PListValueMap& PListValue::ConvertToValueMap()
{
    if (type_ != PLVT_VALUEMAP)
    {
        Reset();
        type_ = PLVT_VALUEMAP;
        valueMap_ = new PListValueMap();
    }

    return *valueMap_;
}

PListValueVector& PListValue::ConvertToValueVector()
{
    if (type_ != PLVT_VALUEVECTOR)
    {
        Reset();
        type_ = PLVT_VALUEVECTOR;
        valueVector_ = new PListValueVector();
    }

    return *valueVector_;
}

void PListValue::Reset()
{
    if (type_ == PLVT_NONE)
        return;

    switch (type_)
    {
    case PLVT_STRING:
        delete string_;
        break;
    case PLVT_VALUEMAP:
        delete valueMap_;
        break;
    case PLVT_VALUEVECTOR:
        delete valueVector_;
        break;
    default:
        break;
    }

    type_ = PLVT_NONE;
}

PListFile::PListFile(Context* context) :
    Resource(context)
{
}

PListFile::~PListFile() = default;

void PListFile::RegisterObject(Context* context)
{
    context->RegisterFactory<PListFile>();
}

bool PListFile::BeginLoad(Deserializer& source)
{
    if (GetName().Empty())
        SetName(source.GetName());

    XMLFile xmlFile(context_);
    if (!xmlFile.Load(source))
    {
        URHO3D_LOGERROR("Could not load property list");
        return false;
    }

    XMLElement plistElem = xmlFile.GetRoot("plist");
    if (!plistElem)
    {
        URHO3D_LOGERROR("Invalid property list file");
        return false;
    }

    root_.Clear();

    XMLElement dictElem = plistElem.GetChild("dict");
    if (!LoadDict(root_, dictElem))
        return false;

    SetMemoryUse(source.GetSize());

    return true;
}

bool PListFile::LoadDict(PListValueMap& dict, const XMLElement& dictElem)
{
    if (!dictElem)
        return false;

    XMLElement keyElem = dictElem.GetChild("key");
    XMLElement valueElem = keyElem.GetNext();
    while (keyElem && valueElem)
    {
        String key = keyElem.GetValue();
        valueElem = keyElem.GetNext();

        PListValue value;
        if (!LoadValue(value, valueElem))
            return false;

        dict[key] = value;

        keyElem = valueElem.GetNext("key");
        valueElem = keyElem.GetNext();
    }

    return true;
}

bool PListFile::LoadArray(PListValueVector& array, const XMLElement& arrayElem)
{
    if (!arrayElem)
        return false;

    for (XMLElement valueElem = arrayElem.GetChild(); valueElem; valueElem = valueElem.GetNext())
    {
        PListValue value;

        if (!LoadValue(value, valueElem))
            return false;

        array.Push(value);
    }

    return true;
}

bool PListFile::LoadValue(PListValue& value, const XMLElement& valueElem)
{
    String valueType = valueElem.GetName();

    if (valueType == "string")
        value.SetString(valueElem.GetValue());
    else if (valueType == "real")
        value.SetFloat(ToFloat(valueElem.GetValue()));
    else if (valueType == "integer")
        value.SetInt(ToInt(valueElem.GetValue()));
    else if (valueType == "true")
        value.SetBool(true);
    else if (valueType == "false")
        value.SetBool(false);
    else if (valueType == "dict")
    {
        if (!LoadDict(value.ConvertToValueMap(), valueElem))
            return false;
    }
    else if (valueType == "array")
    {
        if (!LoadArray(value.ConvertToValueVector(), valueElem))
            return false;
    }
    else
    {
        URHO3D_LOGERROR("Supported value type");
        return false;
    }

    return true;
}


}
