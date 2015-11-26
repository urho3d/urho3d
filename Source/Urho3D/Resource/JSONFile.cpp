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

#include "../Precompiled.h"

#include "../Container/ArrayPtr.h"
#include "../Core/Profiler.h"
#include "../Core/Context.h"
#include "../IO/Deserializer.h"
#include "../IO/Log.h"
#include "../Resource/JSONFile.h"
#include "../Resource/ResourceCache.h"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include "../DebugNew.h"

using namespace rapidjson;

namespace Urho3D
{

JSONFile::JSONFile(Context* context) :
    Resource(context)
{
}

JSONFile::~JSONFile()
{
}

void JSONFile::RegisterObject(Context* context)
{
    context->RegisterFactory<JSONFile>();
}

// Convert rapidjson value to JSON value.
static void ToJSONValue(JSONValue& jsonValue, const rapidjson::Value& rapidjsonValue)
{
    switch (rapidjsonValue.GetType())
    {
    case kNullType:
        // Reset to null type
        jsonValue.SetType(JSON_NULL);
        break;

    case kFalseType:
        jsonValue = false;
        break;

    case kTrueType:
        jsonValue = true;
        break;

    case kNumberType:
        if (rapidjsonValue.IsInt())
            jsonValue = rapidjsonValue.GetInt();
        else if (rapidjsonValue.IsUint())
            jsonValue = rapidjsonValue.GetUint();
        else
            jsonValue = rapidjsonValue.GetDouble();
        break;

    case kStringType:
        jsonValue = rapidjsonValue.GetString();
        break;

    case kArrayType:
        {
            jsonValue.Resize(rapidjsonValue.Size());
            for (unsigned i = 0; i < rapidjsonValue.Size(); ++i)
            {
                ToJSONValue(jsonValue[i], rapidjsonValue[i]);
            }
        }
        break;

    case kObjectType:
        {
            jsonValue.SetType(JSON_OBJECT);
            for (rapidjson::Value::ConstMemberIterator i = rapidjsonValue.MemberBegin(); i != rapidjsonValue.MemberEnd(); ++i)
            {
                JSONValue& value = jsonValue[String(i->name.GetString())];
                ToJSONValue(value, i->value);
            }
        }
        break;

    default:
        break;
    }
}

bool JSONFile::BeginLoad(Deserializer& source)
{
    unsigned dataSize = source.GetSize();
    if (!dataSize && !source.GetName().Empty())
    {
        URHO3D_LOGERROR("Zero sized JSON data in " + source.GetName());
        return false;
    }

    SharedArrayPtr<char> buffer(new char[dataSize + 1]);
    if (source.Read(buffer.Get(), dataSize) != dataSize)
        return false;
    buffer[dataSize] = '\0';

    rapidjson::Document document;
    if (document.Parse<0>(buffer).HasParseError())
    {
        URHO3D_LOGERROR("Could not parse JSON data from " + source.GetName());
        return false;
    }

    ToJSONValue(root_, document);

    SetMemoryUse(dataSize);

    return true;
}

static void ToRapidjsonValue(rapidjson::Value& rapidjsonValue, const JSONValue& jsonValue, rapidjson::MemoryPoolAllocator<>& allocator)
{
    switch (jsonValue.GetValueType())
    {
    case JSON_NULL:
        rapidjsonValue.SetNull();
        break;

    case JSON_BOOL:
        rapidjsonValue.SetBool(jsonValue.GetBool());
        break;

    case JSON_NUMBER:
        {
            switch (jsonValue.GetNumberType())
            {
            case JSONNT_INT:
                rapidjsonValue.SetInt(jsonValue.GetInt());
                break;

            case JSONNT_UINT:
                rapidjsonValue.SetUint(jsonValue.GetUInt());
                break;

            default:
                rapidjsonValue.SetDouble(jsonValue.GetDouble());
                break;
            }
        }
        break;

    case JSON_STRING:
        rapidjsonValue.SetString(jsonValue.GetCString(), allocator);
        break;

    case JSON_ARRAY:
        {
            const JSONArray& jsonArray = jsonValue.GetArray();

            rapidjsonValue.SetArray();
            rapidjsonValue.Reserve(jsonArray.Size(), allocator);

            for (unsigned i = 0; i < jsonArray.Size(); ++i)
            {
                rapidjson::Value value;
                rapidjsonValue.PushBack(value, allocator);
                ToRapidjsonValue(rapidjsonValue[i], jsonArray[i], allocator);
            }
        }
        break;

    case JSON_OBJECT:
        {
            const JSONObject& jsonObject = jsonValue.GetObject();

            rapidjsonValue.SetObject();
            for (JSONObject::ConstIterator i = jsonObject.Begin(); i != jsonObject.End(); ++i)
            {
                const char* name = i->first_.CString();
                rapidjson::Value value;
                rapidjsonValue.AddMember(name, value, allocator);
                ToRapidjsonValue(rapidjsonValue[name], i->second_, allocator);
            }
        }
        break;

    default:
        break;
    }
}

bool JSONFile::Save(Serializer& dest) const
{
    return Save(dest, "\t");
}

bool JSONFile::Save(Serializer& dest, const String& indendation) const
{
    rapidjson::Document document;
    ToRapidjsonValue(document, root_, document.GetAllocator());

    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer, &(document.GetAllocator()));
    writer.SetIndent(!indendation.Empty() ? indendation.Front() : '\0', indendation.Length());

    document.Accept(writer);
    unsigned size = (unsigned)buffer.GetSize();
    return dest.Write(buffer.GetString(), size) == size;
}

}
