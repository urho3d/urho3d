//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "XMLElement.h"

class TiXmlDocument;

/// XML document resource
class XMLFile : public Resource
{
    OBJECT(XMLFile);
    
public:
    /// Construct
    XMLFile(Context* context);
    /// Destruct
    virtual ~XMLFile();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful
    virtual bool Load(Deserializer& source);
    /// Save resource. Return true if successful. Only supports saving to a File
    virtual bool Save(Serializer& dest);
    
    /// Clear the document and create a root element
    XMLElement CreateRootElement(const String& name);
    
    /// Return the root element, with optionally specified name. Return null element if not found
    XMLElement GetRootElement(const String& name = String());
    /// Return the TinyXML document
    TiXmlDocument* GetDocument() const { return document_; }
    
private:
    /// TinyXML document
    TiXmlDocument* document_;
};
