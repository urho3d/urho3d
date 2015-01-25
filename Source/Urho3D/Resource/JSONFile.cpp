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

#include "../Container/ArrayPtr.h"
#include "../Core/Context.h"
#include "../IO/Deserializer.h"
#include "../Resource/JSONFile.h"
#include "../IO/Log.h"
#include "../Core/Profiler.h"
#include "../Resource/ResourceCache.h"
#include "../IO/Serializer.h"
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include "../DebugNew.h"

using namespace rapidjson;

namespace Urho3D
{

JSONFile::JSONFile(Context* context) :
    Resource(context),
    document_(new Document())
{
}

JSONFile::~JSONFile()
{
    delete document_;
    document_ = 0;
}

void JSONFile::RegisterObject(Context* context)
{
    context->RegisterFactory<JSONFile>();
}

bool JSONFile::BeginLoad(Deserializer& source)
{
    unsigned dataSize = source.GetSize();
    if (!dataSize && !source.GetName().Empty())
    {
        LOGERROR("Zero sized JSON data in " + source.GetName());
        return false;
    }

    SharedArrayPtr<char> buffer(new char[dataSize + 1]);
    if (source.Read(buffer.Get(), dataSize) != dataSize)
        return false;
    buffer[dataSize] = '\0';

    if (document_->Parse<0>(buffer).HasParseError())
    {
        LOGERROR("Could not parse JSON data from " + source.GetName());
        return false;
    }

    SetMemoryUse(dataSize);

    return true;
}

bool JSONFile::Save(Serializer& dest) const
{
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer, &(document_->GetAllocator()));
    writer.SetIndent('\t', 1);

    document_->Accept(writer);
    dest.Write(buffer.GetString(), buffer.GetSize());

    return true;
}

JSONValue JSONFile::CreateRoot(JSONValueType valueType)
{
    if (valueType == JSON_OBJECT)
        document_->SetObject();
    else
        document_->SetArray();

    return JSONValue(this, document_);
}

JSONValue JSONFile::GetRoot(JSONValueType valueType)
{
    if (!document_)
        return JSONValue::EMPTY;

    if ((valueType == JSON_OBJECT && document_->GetType() != kObjectType) ||
        (valueType == JSON_ARRAY && document_->GetType() != kArrayType))
    {
        LOGERROR("Invalid root value type");
        return JSONValue::EMPTY;
    }

    return JSONValue(this, document_);
}

}
