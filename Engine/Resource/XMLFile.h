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

#ifndef RESOURCE_XMLFILE_H
#define RESOURCE_XMLFILE_H

#include "Resource.h"
#include "XMLElement.h"

class TiXmlDocument;

//! An XML document resource
class XMLFile : public Resource
{
    DEFINE_TYPE(XMLFile);
    
public:
    //! Construct with name
    XMLFile(const std::string& name = std::string());
    //! Destruct
    virtual ~XMLFile();
    
    //! Load resource. Throw exception on error
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    //! Save resource. Throw exception on error. Only supports saving to a File
    virtual void save(Serializer& dest);
    
    //! Clear the document and create a root element
    XMLElement createRootElement(const std::string& name);
    
    //! Return the root element
    XMLElement getRootElement(const std::string& name = std::string(), bool throwIfMissing = true) const;
    //! Return the TinyXML document
    TiXmlDocument* getDocument() const { return mDocument; }
    
private:
    //! TinyXML document
    TiXmlDocument* mDocument;
};

#endif // RESOURCE_XMLFILE_H
