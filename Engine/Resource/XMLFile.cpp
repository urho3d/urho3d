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
#include "Context.h"
#include "File.h"
#include "Log.h"
#include "ArrayPtr.h"
#include "XMLFile.h"

#include <tinyxml.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(XMLFile);

XMLFile::XMLFile(Context* context) :
    Resource(context),
    document_(new TiXmlDocument())
{
}

XMLFile::~XMLFile()
{
    delete document_;
    document_ = 0;
}

void XMLFile::RegisterObject(Context* context)
{
    context->RegisterFactory<XMLFile>();
}

bool XMLFile::Load(Deserializer& source)
{
    unsigned dataSize = source.GetSize();
    if (!dataSize)
        return false;
    
    SharedArrayPtr<char> buffer(new char[dataSize + 1]);
    if (source.Read(buffer.RawPtr(), dataSize) != dataSize)
        return false;
    
    buffer[dataSize] = 0;
    
    document_->Clear();
    document_->Parse(buffer.RawPtr());
    if (document_->Error())
    {
        document_->ClearError();
        LOGERROR("Could not parse XML data from " + source.GetName());
        return false;
    }
    
    // Note: this probably does not reflect internal data structure size accurately
    SetMemoryUse(dataSize);
    return true;
}

bool XMLFile::Save(Serializer& dest)
{
    // Only support saving to a File
    File* file = dynamic_cast<File*>(&dest);
    if (!file)
    {
        LOGERROR("XML data destination is not a File");
        return false;
    }
    if (!file->IsOpen())
        return false;
    if (!document_->SaveFile((FILE*)file->GetHandle()))
    {
        LOGERROR("Failed to save XML data to " + file->GetName());
        return false;
    }
    
    return true;
}

XMLElement XMLFile::CreateRoot(const String& name)
{
    TiXmlElement newRoot(name.CString());
    document_->Clear();
    document_->InsertEndChild(newRoot);
    return GetRoot();
}

XMLElement XMLFile::GetRoot(const String& name)
{
    XMLElement rootElem = XMLElement(this, document_->RootElement());
    
    if (rootElem.IsNull() || (!name.Empty() && rootElem.GetName() != name))
        return XMLElement();
    return rootElem;
}
