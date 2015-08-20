//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:addmember
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../IO/Log.h"
#include "../Resource/JSONValue.h"

#include "../DebugNew.h"

namespace Urho3D
{

const JSONValue JSONValue::EMPTY;
const JSONArray JSONValue::EMPTY_ARRAY;
const JSONObject JSONValue::EMPTY_OBJECT;

void JSONValue::SetType(JSONValueType valueType)
{
    if (valueType == valueType_)
        return;

    switch (valueType_)
    {
    case JSON_STRING:
        delete stringValue_;
        break;

    case JSON_ARRAY:
        delete arrayValue_;
        break;

    case JSON_OBJECT:
        delete objectValue_;
        break;

    default:
        break;
    }

    valueType_ = valueType;

    switch (valueType_)
    {
    case JSON_STRING:
        stringValue_ = new String();
        break;

    case JSON_ARRAY:
        arrayValue_ = new JSONArray();
        break;

    case JSON_OBJECT:
        objectValue_ = new JSONObject();
        break;

    default:
        break;
    }
}

JSONValue& JSONValue::operator =(bool rhs)
{
    SetType(JSON_NUMBER);
    numberValue_ = rhs;

    return *this;
}

JSONValue& JSONValue::operator =(int rhs)
{
    SetType(JSON_NUMBER);
    numberValue_ = rhs;

    return *this;
}

JSONValue& JSONValue::operator =(unsigned rhs)
{
    SetType(JSON_NUMBER);
    numberValue_ = rhs;

    return *this;
}

JSONValue& JSONValue::operator =(float rhs)
{
    SetType(JSON_NUMBER);
    numberValue_ = rhs;

    return *this;
}

JSONValue& JSONValue::operator =(double rhs)
{
    SetType(JSON_NUMBER);
    numberValue_ = rhs;

    return *this;
}

JSONValue& JSONValue::operator =(const String& rhs)
{
    SetType(JSON_STRING);
    *stringValue_ = rhs;

    return *this;
}

JSONValue& JSONValue::operator =(const char* rhs)
{
    SetType(JSON_STRING);
    *stringValue_ = rhs;

    return *this;
}

JSONValue& JSONValue::operator =(const JSONArray& rhs)
{
    SetType(JSON_ARRAY);
    *arrayValue_ = rhs;

    return *this;
}

JSONValue& JSONValue::operator =(const JSONObject& rhs)
{
    SetType(JSON_OBJECT);
    *objectValue_ = rhs;

    return *this;
}

JSONValue& JSONValue::operator =(const JSONValue& rhs)
{
    if (this == &rhs)
        return *this;

    SetType(rhs.valueType_);

    switch (valueType_)
    {
    case JSON_BOOL:
        boolValue_ = rhs.boolValue_;
        break;

    case JSON_NUMBER:
        numberValue_ = rhs.numberValue_;
        break;

    case JSON_STRING:
        *stringValue_ = *rhs.stringValue_;
        break;

    case JSON_ARRAY:
        *arrayValue_ = *rhs.arrayValue_;
        break;

    case JSON_OBJECT:
        *objectValue_ = *rhs.objectValue_;

    default:
        break;
    }

    return *this;
}

JSONValue& JSONValue::operator [](unsigned index)
{
    // Convert to array type
    SetType(JSON_ARRAY);

    return (*arrayValue_)[index];
}

const JSONValue& JSONValue::operator [](unsigned index) const
{
    if (valueType_ != JSON_ARRAY)
        return EMPTY;

    return (*arrayValue_)[index];
}

JSONValue& JSONValue::At(unsigned index)
{
    // Convert to array type
    SetType(JSON_ARRAY);

    return arrayValue_->At(index);
}

const JSONValue& JSONValue::At(unsigned index) const
{
    if (valueType_ != JSON_ARRAY)
        return EMPTY;

    return arrayValue_->At(index);
}

void JSONValue::Push(const JSONValue& value)
{
    // Convert to array type
    SetType(JSON_ARRAY);

    arrayValue_->Push(value);
}

void JSONValue::Pop()
{
    if (valueType_ != JSON_ARRAY)
        return;

    arrayValue_->Pop();
}

void JSONValue::Insert(unsigned pos, const JSONValue& value)
{
    if (valueType_ != JSON_ARRAY)
        return;

    arrayValue_->Insert(pos, value);
}

void JSONValue::Erase(unsigned pos, unsigned length)
{
    if (valueType_ != JSON_ARRAY)
        return;

    arrayValue_->Erase(pos, length);
}

void JSONValue::Resize(unsigned newSize)
{
    // Convert to array type
    SetType(JSON_ARRAY);

    arrayValue_->Resize(newSize);
}

unsigned JSONValue::Size() const
{
    if (valueType_ == JSON_ARRAY)
        return arrayValue_->Size();

    return 0;
}

JSONValue& JSONValue::operator [](const String& key)
{
    // Convert to object type
    SetType(JSON_OBJECT);

    return (*objectValue_)[key];
}

const JSONValue& JSONValue::operator [](const String& key) const
{
    if (valueType_ != JSON_OBJECT)
        return EMPTY;

    return (*objectValue_)[key];
}

void JSONValue::Set(const String& key, const JSONValue& value)
{
    // Convert to object type
    SetType(JSON_OBJECT);

    objectValue_->Insert(MakePair<String, JSONValue>(key, value));
}

const JSONValue& JSONValue::Get(const String& key) const
{
    if (valueType_ != JSON_OBJECT)
        return EMPTY;

    JSONObject::ConstIterator i = objectValue_->Find(key);
    if (i == objectValue_->End())
        return EMPTY;

    return i->second_;
}

bool JSONValue::Erase(const String& key)
{
    if (valueType_ != JSON_OBJECT)
        return false;

    return objectValue_->Erase(key);
}

bool JSONValue::Contains(const String& key) const
{
    if  (valueType_ != JSON_OBJECT)
        return false;

    return objectValue_->Contains(key);
}

void JSONValue::Clear()
{
    if (valueType_ == JSON_ARRAY)
        arrayValue_->Clear();
    else if (valueType_ == JSON_OBJECT)
        objectValue_->Clear();
}

}