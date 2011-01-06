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

#include "Precompiled.h"
#include "File.h"
#include "SharedArrayPtr.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include <tinyxml.h>

#include "DebugNew.h"

XMLFile::XMLFile(const std::string& name) :
    Resource(name),
    mDocument(new TiXmlDocument(name.c_str()))
{
}

XMLFile::~XMLFile()
{
    delete mDocument;
    mDocument = 0;
}

void XMLFile::load(Deserializer& source, ResourceCache* cache)
{
    unsigned dataSize = source.getSize();
    
    SharedArrayPtr<char> buffer(new char[dataSize + 1]);
    source.read(buffer.getPtr(), dataSize);
    buffer[dataSize] = 0;
    
    mDocument->Clear();
    mDocument->Parse(buffer.getPtr());
    if (mDocument->Error())
    {
        mDocument->ClearError();
        EXCEPTION("Could not parse XML data from " + source.getName());
    }
    
    // This probably does not reflect internal data structure size accurately
    setMemoryUse(dataSize);
}

void XMLFile::save(Serializer& dest)
{
    // Only support saving to a File
    File* file = dynamic_cast<File*>(&dest);
    if (!file)
        EXCEPTION("XML data destination is not a File");
    if (!mDocument->SaveFile(file->getHandle()))
        EXCEPTION("Failed to save XML data to " + file->getName());
}

XMLElement XMLFile::createRootElement(const std::string& name)
{
    TiXmlElement newRoot(name.c_str());
    mDocument->Clear();
    mDocument->InsertEndChild(newRoot);
    return getRootElement();
}

XMLElement XMLFile::getRootElement(const std::string& name, bool throwIfMissing) const
{
    XMLElement rootElem = XMLElement(mDocument->RootElement());
    
    if ((rootElem.isNull()) && (throwIfMissing))
        SAFE_EXCEPTION_RET("No root XML element", XMLElement());
    
    if ((!name.empty()) && (rootElem.notNull()) && (rootElem.getName() != name))
    {
        if (throwIfMissing)
            SAFE_EXCEPTION_RET("XML document has no root element " + name, XMLElement())
        else
            rootElem = XMLElement();
    }
    
    return rootElem;
}
