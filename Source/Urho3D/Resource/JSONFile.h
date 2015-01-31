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
#include "../Resource/JSONValue.h"

namespace rapidjson
{
    template <typename Encoding, typename Allocator> class GenericDocument;
    typedef GenericDocument<UTF8<char>, MemoryPoolAllocator<CrtAllocator> > Document;
}

namespace Urho3D
{

/// JSON document resource.
class URHO3D_API JSONFile : public Resource
{
    OBJECT(JSONFile);

public:
    /// Construct.
    JSONFile(Context* context);
    /// Destruct.
    virtual ~JSONFile();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Save resource. Return true if successful. Only supports saving to a File.
    virtual bool Save(Serializer& dest) const;

    /// Clear the document and create a root value, default is object type.
    JSONValue CreateRoot(JSONValueType valueType = JSON_OBJECT);
    /// Return the root value with specific value type, Return null value if not found.
    JSONValue GetRoot(JSONValueType valueType = JSON_ANY);

    /// Return rapidjson document.
    rapidjson::Document* GetDocument() const { return document_; }

private:
    /// Rapid JSON document.
    rapidjson::Document* document_;
};

}
