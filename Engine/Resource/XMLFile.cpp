//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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
#include "ArrayPtr.h"
#include "Context.h"
#include "Deserializer.h"
#include "Log.h"
#include "Profiler.h"
#include "Serializer.h"
#include "XMLFile.h"

#include <pugixml.hpp>

#include "DebugNew.h"

namespace Urho3D
{

/// XML writer for pugixml.
class XMLWriter : public pugi::xml_writer
{
public:
    /// Construct.
    XMLWriter(Serializer& dest) :
        dest_(dest),
        success_(true)
    {
    }
    
    /// Write bytes to output.
    void write(const void* data, size_t size)
    {
        if (dest_.Write(data, size) != size)
            success_ = false;
    }
    
    /// Destination serializer.
    Serializer& dest_;
    /// Success flag.
    bool success_;
};

OBJECTTYPESTATIC(XMLFile);

XMLFile::XMLFile(Context* context) :
    Resource(context),
    document_(new pugi::xml_document())
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
    PROFILE(LoadXMLFile);
    
    unsigned dataSize = source.GetSize();
    if (!dataSize)
        return false;
    
    SharedArrayPtr<char> buffer(new char[dataSize]);
    if (source.Read(buffer.Get(), dataSize) != dataSize)
        return false;
    
    if (!document_->load_buffer(buffer.Get(), dataSize))
    {
        LOGERROR("Could not parse XML data from " + source.GetName());
        return false;
    }
    
    // Note: this probably does not reflect internal data structure size accurately
    SetMemoryUse(dataSize);
    return true;
}

bool XMLFile::Save(Serializer& dest)
{
    XMLWriter writer(dest);
    document_->save(writer);
    return writer.success_;
}

XMLElement XMLFile::CreateRoot(const String& name)
{
    document_->reset();
    pugi::xml_node root = document_->append_child(name.CString());
    return XMLElement(this, root.internal_object());
}

XMLElement XMLFile::GetRoot(const String& name)
{
    pugi::xml_node root = document_->first_child();
    if (root.empty())
        return XMLElement();
    
    if (!name.Empty() && name != root.name())
        return XMLElement();
    else
        return XMLElement(this, root.internal_object());
}

}
