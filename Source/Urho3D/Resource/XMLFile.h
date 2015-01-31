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
#include "../Resource/XMLElement.h"

namespace pugi
{
    class xml_document;
    class xml_node;
    class xpath_node;
}

namespace Urho3D
{

/// XML document resource.
class URHO3D_API XMLFile : public Resource
{
    OBJECT(XMLFile);
    
public:
    /// Construct.
    XMLFile(Context* context);
    /// Destruct.
    virtual ~XMLFile();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Save resource. Return true if successful. Only supports saving to a File.
    virtual bool Save(Serializer& dest) const;
    
    /// Deserialize from a string. Return true if successful.
    bool FromString(const String& source);
    /// Clear the document and create a root element.
    XMLElement CreateRoot(const String& name);
    
    /// Return the root element, with optionally specified name. Return null element if not found.
    XMLElement GetRoot(const String& name = String::EMPTY);
    /// Return the pugixml document.
    pugi::xml_document* GetDocument() const { return document_; }
    /// Serialize the XML content to a string.
    String ToString() const;

    /// Patch the XMLFile with another XMLFile. Based on RFC 5261.
    void Patch(XMLFile* patchFile);
    /// Patch the XMLFile with another XMLElement. Based on RFC 5261.
    void Patch(XMLElement patchElement);
    
private:
    /// Add an node in the Patch.
    void PatchAdd(const pugi::xml_node& patch, pugi::xpath_node& original);
    /// Replace a node or attribute in the Patch.
    void PatchReplace(const pugi::xml_node& patch, pugi::xpath_node& original);
    /// Remove a node or attribute in the Patch.
    void PatchRemove(const pugi::xpath_node& original);

    /// Add a node in the Patch.
    void AddNode(const pugi::xml_node& patch, pugi::xpath_node& original);
    /// Add an attribute in the Patch.
    void AddAttribute(const pugi::xml_node& patch, pugi::xpath_node& original);
    /// Combine two text nodes.
    bool CombineText(const pugi::xml_node& patch, pugi::xml_node original, bool prepend);

    /// Pugixml document.
    pugi::xml_document* document_;
};

}
